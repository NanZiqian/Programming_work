#! /bin/bash

# get current direction
curDir=`pwd`
# get shell direction
workDir=$(cd "$(dirname "$0")";pwd)

cd $workDir

if [ ! -f Inverted_File_index.txt ]; then
    echo "<<< Running preprocessor... >>>"
    ./preprocessor.exe -D dataset
    echo "<<< Finish! >>>"
fi

if [ ! -f Word_Count.txt ]; then
    echo "<<< Running preprocessor_stop_word... >>>"
    ./preprocessor_stop_word.exe -D dataset
    echo "<<< Finish! >>>"
fi

echo "<<< Running engine... >>>"
./engine.exe
echo "<<< Finish! >>>"

cd $curDir