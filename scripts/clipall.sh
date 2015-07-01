#!/bin/bash

if [[ $# < 1 ]]
then
	echo "Usage: $0 <output root dir> <source dir>"
	exit 1;
fi

outputdir=$1
sourcedir='.'
if [[ $# > 1 ]]
then
	sourcedir=$2
fi

for f in $(find $sourcedir -name '*.c.dump')
do
newpath=$outputdir/${f/%.dump//}
mkdir -p $newpath
~/projects/gcc_plugin/scripts/clip.pl $newpath < $f
done
