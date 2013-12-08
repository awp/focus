#!/bin/bash

#
# Deploy Project with WebDav
#

PROJECT_PATH="`pwd`"

# Display usage notice and exit.
usage() {
  echo "Usage: webdav.sh <DESTINATION_PATH>" >&2
  exit 1
}

if [ ! $1 ]; then
  usage
fi

if [ "x$1" == "x" ]; then
  usage
fi

read -p "Are you sure you want to copy this project to $1? " -n 1 -r
echo # new line

if [[ ! $REPLY =~ ^[Yy]$ ]]; then
  echo 'Quitting... Your project has not been copied.'
  exit
fi

cd $PROJECT_PATH
cd ../../

if [ -f $1/.revision ]; then
  echo 'Revision file found. Generating diff.'
  rev=$(<$1/.revision)
fi

if [ $rev ]
then
  HEAD=$(git rev-parse --verify HEAD)
  for i in $(git diff --name-only $rev..$HEAD); do
    if [ -f $i ]; then
      mkdir -p "$1/$(dirname $i)"
      echo "copying..."
      cp -v "$i" "$1/$i"
    elif [ -f $1/$i ]; then
      echo "removing..."
      rm -v "$1/$i"
    fi
  done 
  echo $HEAD > $1/.revision
  echo "Update complete."
else
  echo 'No diff found. If the project has not been copied over before, it is safe to copy the entire project without this script.'
  exit 1
fi
