#!/bin/bash
# Compatible with drush 5.5 and up due to stability to drush make.
# @see https://drupal.org/node/1719512
set -e

#
# Update FOCUS profile
#

WT4_PATH="`pwd`"

# Check that sites/default has proper permissions to be updated
TEST=$(test -w ../../sites/default; echo $?);
if [ "$TEST" == "1" ]; then
	echo "No write permissions on sites/default.  Updating..."
	sudo chmod -R 755 ../../sites/default
fi

# Update the profile.
echo "Updating the FOCUS profile..."
git fetch origin
git add .
git clean -f -d
git reset --hard origin/7.x-3.x

# Go to Drupal root directory.
cd ../../

# Update Drupal, contrib modules, and libraries.
echo "Updating the FOCUS distribution..."
drush make -y $WT4_PATH/scripts/focus.make --no-cache

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
echo "Congratulations! FOCUS has finished updating."
