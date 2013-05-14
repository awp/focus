#!/bin/bash
set -e

#
# Update FOCUS profile
#

WT4_PATH="`pwd`"

# Check Drush Version
DRUSH=$(`drush --version`)
DRUSH_MIN="5.5"
IFS=' ' read -a array <<< $DRUSH
VERSION=(`echo "${array[2]} < $DRUSH_MIN" | bc`)
if [ "$VERSION" == "1" ]; then
	echo "Update requires Drush version $DRUSH_MIN and up; you are running $DRUSH.  Consider updating drush or manually update your project."
	exit
fi

# Update the profile.
echo "Updating the FOCUS profile..."
git fetch origin

# Go to Drupal root directory.
cd ../../

# Update Drupal, contrib modules, and libraries.
echo "Updating the FOCUS distribution..."
drush -y make $WT4_PATH/scripts/focus.make

# Update the system and registry so we don't break the bootstrap
echo "Updating the system registry..."
drush sqlq "UPDATE system SET filename = REPLACE(filename,'sites/all/modules','sites/all/modules/contrib') WHERE filename LIKE '%sites/all/modules%' AND filename NOT LIKE '%sites/all/modules/contrib%'"
drush sqlq "UPDATE system SET filename = REPLACE(filename,'sites/all/themes','sites/all/themes/contrib') WHERE filename LIKE '%sites/all/themes%' AND filename NOT LIKE '%sites/all/themes/contrib%'"
drush sqlq "UPDATE registry SET filename = REPLACE(filename,'sites/all/modules','sites/all/modules/contrib') WHERE filename LIKE '%sites/all/modules%' AND filename NOT LIKE '%sites/all/modules/contrib%'"
drush sqlq "UPDATE registry SET filename = REPLACE(filename,'sites/all/themes','sites/all/themes/contrib') WHERE filename LIKE '%sites/all/themes%' AND filename NOT LIKE '%sites/all/themes/contrib%'"

# Clear the bootstrap cache to allow the updates to set in.
echo "Clearing the bootstrap cache..."
php -r "print json_encode(array());" | drush cache-set --format=json lookup_cache -

# Clear all caches.
echo "Clearing all caches..."
drush cc all

# Patch core with custom patches.
echo "Implementing FOCUS patches..."

# Patch core with .htaccess, if needed.
FILE=".htaccess"
CHECK="x-font-woff"
RESULT=$(cat ${FILE} | grep "${CHECK}")
if [ "$RESULT" == "" ]; then
	echo "Patching .htaccess..."
	patch .htaccess < $WT4_PATH/patches/focus-htaccess.patch
fi

# Run update.php script to get the db up to date.
drush updb

# All done.
echo "Congratulations!  FOCUS has finished updating."
