> In documents directory, the origin version of this file is provided. Check it if you can't run.

# Requirements

In order to run all the module in the project, you are supposed to have those environment.

- C & C++17 environment.
- `bash` command line environment.
  - If you are not familiar with this and you are Windows user, just install Git Bash for windows.
    - Recommended reading: 
      - [安装Git - 廖雪峰的官方网站 (liaoxuefeng.com)](https://www.liaoxuefeng.com/wiki/896043488029600/896067074338496)

  - If you are not familiar with this and you are Linux or Mac user, just use your default terminal app.



# Instructions

## Run the codes and test them.

- After making sure you have prepared all the environments, you only need to do one thing.

1. For Windows user, open your `git bash` and `cd` to this folder (or open `git bash` in the folder) and type in `bash _auto.sh` and press enter.
2. For Linux or Mac user, open your terminal and `cd` to this folder and type in `bash _auto.sh` and press enter.

- Then you should see following logs:

```
<<< Compiling preprocessor... >>>
<<< Finish! >>>
<<< Compiling engine... >>>
<<< Finish! >>>
<<< Running engine... >>>
Please enter the words you want to search, and enter an '#' to end the input.
<waiting for entering>
```

- If you want to test again, don't afraid to run `_auto.sh` again. It won't repeatedly compile the codes.

## Clear useless files.

- Everything is the same except run the `_clear.sh` instead of `_auto.sh`.

## Others

- If you want to try the module singly, I also provide the scripts for them. 
- Try to run them.

# File Tree

> Before compile.

```shell
.
├── _auto.sh
├── _clear.sh
└── src
    ├── _compile.sh
    ├── _run.sh
    ├── engine
    │   ├── search.cpp
    │   ├── search.h
    │   └── test.cpp
    ├── preprocessor
    │   └── preprocess.cpp
    └── stemizer
        ├── Stemize.cpp
        ├── Stemize.h
        ├── stmr.c
        └── stmr.h
```

> After compile & run.

```shell
.
├── _auto.sh
├── _clear.sh
└── src
    ├── Inverted_File_Index.txt
    ├── Word_Count.txt
    ├── _compile.sh
    ├── _run.sh
    ├── engine
    │   ├── search.cpp
    │   ├── search.h
    │   └── test.cpp
    ├── engine.exe
    ├── preprocessor
    │   └── preprocess.cpp
    ├── preprocessor.exe
    ├── preprocessor_stop_word.exe
    └── stemizer
        ├── Stemize.cpp
        ├── Stemize.h
        ├── stmr.c
        └── stmr.h
```
