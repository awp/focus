#!/bin/bash
set -e

#
# Update FOCUS profile
#

WT4_PATH="`pwd`"

# Go to Drupal root directory.
cd ../../

# Create settings.php
if [ ! -f sites/default/settings.php ]; then
	cp sites/default/default.settings.php sites/default/settings.php
	while [ ! $database ]; do
		read -p "Local database to use: " database

		if [ ! $database ]; then
			echo "Database name is required."
		fi
	done

	while [ ! $user ]; do
		read -p "Username: " user

		if [ ! $user ]; then
			echo "Username is required."
		fi
	done

	while [ ! $pass ]; do
		read -p "Password: " pass

		if [ ! $pass ]; then
			echo "Password is required."
		fi
	done

	echo "\$databases['default']['default'] = array(" >> sites/default/settings.php
	echo "  'driver' => 'mysql'," >> sites/default/settings.php
	echo "  'database' => '$database'," >> sites/default/settings.php
	echo "  'username' => '$user'," >> sites/default/settings.php
	echo "  'password' => '$pass'," >> sites/default/settings.php
	echo "  'host' => 'localhost'," >> sites/default/settings.php
	echo "  'prefix' => ''," >> sites/default/settings.php
	echo ");" >> sites/default/settings.php
fi

# Create files folder
if [ ! -d sites/default/files ]; then
	mkdir sites/default/files
fi
chmod -R 777 sites/default/files

# Clear the cache
echo "Clearing the cache..."
drush cc all

# All done!
echo "Local setup is complete.  You will need an .htaccess file to complete your local setup."
