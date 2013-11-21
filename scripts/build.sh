#!/bin/bash
set -e

#
# Build the distribution using the same process used on Drupal.org
#
# Usage: scripts/build.sh [-y] <destination> from the profile main directory.
#

FOCUS_PATH="`pwd`"

# Figure out directory real path.
realpath () {
  TARGET_FILE=$1

  cd `dirname $TARGET_FILE`
  TARGET_FILE=`basename $TARGET_FILE`

  while [ -L "$TARGET_FILE" ]
  do
    TARGET_FILE=`readlink $TARGET_FILE`
    cd `dirname $TARGET_FILE`
    TARGET_FILE=`basename $TARGET_FILE`
  done

  PHYS_DIR=`pwd -P`
  RESULT=$PHYS_DIR/$TARGET_FILE
  echo $RESULT
}

usage() {
  echo "Usage: build.sh <DESTINATION_PATH>" >&2
  exit 1
}

DESTINATION=$(realpath $1)

if [ "x$DESTINATION" == "x" ]; then
  usage
fi

if [ ! -f scripts/drupal.make ]; then
  echo "[error] Run this script from the distribution base path."
  exit 1
fi

echo "Building FOCUS in $DESTINATION..."
if [ -d $DESTINATION ]; then
  echo -e "\033[31m[error]\033[0m Destination '$DESTINATION' already exists."
  exit
fi

# Build the distribution and copy the profile in place.
echo "Building the FOCUS distribution..."
drush make $FOCUS_PATH/scripts/focus.make $DESTINATION --no-cache

# Add custom focus patches
echo "Implementing FOCUS patches..."
patch $DESTINATION/.htaccess < $FOCUS_PATH/patches/focus-htaccess.patch
patch $DESTINATION/.gitignore < $FOCUS_PATH/patches/focus-gitignore.patch

# Move to destination
echo "Copying FOCUS profile..."
cp -R $FOCUS_PATH $DESTINATION/profiles/focus/

# Setup Drupal stuff
echo "Creating settings.php..."
cp $DESTINATION/sites/default/default.settings.php $DESTINATION/sites/default/settings.php
chmod 666 $DESTINATION/sites/default/settings.php # need write permissions

echo "Creating themes directory..."
mkdir $DESTINATION/sites/default/themes
chmod -R 755 $DESTINATION/sites/default/themes # need write permissions

echo "Creating files directory..."
mkdir $DESTINATION/sites/default/files
chmod -R 775 $DESTINATION/sites/default/files # need write permissions

echo "Creating dandelion file..."
touch $DESTINATION/dandelion.yml
chmod 777 $DESTINATION/dandelion.yml # need write permissions

echo "Initializing git repository..."
cd $DESTINATION
git init
git add profiles/focus/
git add .
git commit -am "initial commit.  this commit was automatically created by the FOCUS build script."

case $OSTYPE in
  darwin*)
    # No chown needed for OSX
    ;;
  *)
    echo "Setting necessary permissions..."
    sudo chgrp -R www-data $DESTINATION/sites/default/files # need write permissions
    sudo chown -R www-data:www-data $DESTINATION/sites/default/settings.php # need write permissions
    sudo chown -R www-data:www-data $DESTINATION/sites/default/themes # need write permissions
    ;;
esac

# All Done!
echo "Congratulations!  FOCUS has finished building."
