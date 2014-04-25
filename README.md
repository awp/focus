
####CONTENTS OF THIS FILE

 * Introduction
 * Installation
 * Updating

##INTRODUCTION

FOCUS for Drupal is a distribution built with the user in mind.


##INSTALLATION

 * Pull the latest FOCUS repo
 * Navigate to FOCUS repo in terminal

    ``cd /path/to/focus``

 * Build the distribution in the folder you want; it should be accessible via a
   local server

    ``make focus /path/to/project``

    or if you would like the project to be in the parent directory,

    ``make focus ../project``


 * You may be asked to authenticate with your system to set permissions
 * Open browser to the project; follow Drupal installation script
 * Permissions and database should be set automatically
 * Once installation is complete, build away!

##UPDATING

Once you have FOCUS installed, the FOCUS folder (located at ``profiles/focus/``) will already be tracking this repository, and you can update from the command line using make:

  ``make update``

This will run the update script and make database updates as well.