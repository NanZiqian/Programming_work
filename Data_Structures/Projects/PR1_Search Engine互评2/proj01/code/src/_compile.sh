#! /bin/bash

# get current direction
curDir=`pwd`
# get shell direction
workDir=$(cd "$(dirname "$0")";pwd)

cd $workDir

# Setup

echo "<<< Compiling preprocessor... >>>"
g++ preprocessor/*.cpp stemizer/*.c stemizer/*.cpp --std=c++11 -O3 -o preprocessor.exe
g++ preprocessor/*.cpp stemizer/*.c stemizer/*.cpp --std=c++11 -O3 -o preprocessor_stop_word.exe -D Stop_Word
echo "<<< Finish! >>>"

echo "<<< Compiling engine... >>>"
g++ engine/*.cpp stemizer/*.c stemizer/*.cpp --std=c++11 -O3 -o engine.exe
echo "<<< Finish! >>>"

cd $curDir