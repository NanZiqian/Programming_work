#! /bin/bash

# get current direction
curDir=`pwd`
# get shell direction
workDir=$(cd "$(dirname "$0")";pwd)

cd $workDir

if [ ! -f ./src/engine.exe ]; then
    bash ./src/_compile.sh
fi

bash ./src/_run.sh

cd $curDir