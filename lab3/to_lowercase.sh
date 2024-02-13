# Lab 3 - exercise 7
# This script changes all file names in a directory to lowercase
#!/bin/sh
CWD=$(pwd)
dir=$1
if [ -d $dir ]; then
	if [ -z "$dir" ]; then
		echo "No directory sepcified"
	else
		cd $dir
		echo "Before: " && ls
		echo
		echo "After: "
		mmv '*' '#l1' && ls
		cd $CWD
	fi
fi
