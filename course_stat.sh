#!/bin/bash

read course
echoerr() { echo "$@" 1>&2; }

if [ -z "$course" ]
then echoerr Wrong number of arguments
exit 1
fi

file=$course".txt"
if ! test -f $file
then echoerr Course not found
exit 1
else echo "exists"
fi

folder=$course"_stat"
if [ -d $folder ]
then rm -r $folder
fi

mkdir $folder
grades=$folder"/grades.txt"

row="0"
while read -r line
do col="0"
if [[ $row != "0" ]]
then for word in $line
do if [[ $col == "1" ]]
then echo $word >> $grades
fi
col="1"
done
fi
row="1+"
done < $file

stats=$folder"/course_statistics.txt"
gcc -c -g -Wall calc_statistics.c -o prog.exe
prog.exe $grades $stats

while read -r line
do echo $line
done < $stats


echo "done"