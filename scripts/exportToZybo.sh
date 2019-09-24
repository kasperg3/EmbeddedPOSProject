#!/bin/sh
# First argument has to be target location of the ssh target
# the following arguments is the files that need to be transfered


for var in "$@"
do
  if [ "$var" = "--help" ]
   then
    echo 'exportToZybo.sh [location on zybo] [Files] ... [more files]'
    echo 'ARG1 has to be target location of the ssh target'
    echo 'the following arguments is the files that need to be transfered. This can be unlimited.'
    exit
  fi
done

shift
files=""

for var in "$@"
do
  files="$files $var"
done

echo "Files to copy: $files"

scp $files root@192.168.0.2:$1