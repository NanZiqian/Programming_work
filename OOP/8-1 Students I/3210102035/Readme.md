# Assignment 1

## Meaning of dir and file

* **src**
  source code, only main.cpp this time
* **data**
  the test data of this assignment
* **[build]**
  the directory of cmake cache
* **[bin]**
  the dirctory of executable binary file
* CMakeLists.txt
  the file for cmake
* go.bat
  the script for windows users


## How to use

For a basic test, you can just run go.bat and see the result in command line

If you want to make some changes, you can first run go.bat to generate a executable file (or compile by yourself), then you can change the records in *./data/records* to give different records.

You can also give a customed records data by giving the relative/absolute path for the executable file like `.\Assignment1.exe ..\data\records.txt `

But, remember the records should be given as the format below

> name/score1/score2/score3

one example is

> K.Weng/5/5/5
