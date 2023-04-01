#! /bin/bash

# get current direction
curDir=`pwd`
# get shell direction
workDir=$(cd "$(dirname "$0")";pwd)

cd $workDir

find . -name "*.txt"  | xargs rm -f
find . -name "*.exe"  | xargs rm -f

cd $curDir