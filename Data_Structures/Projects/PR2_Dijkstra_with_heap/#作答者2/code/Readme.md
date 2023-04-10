# Readme

## How to compile

Type in the following command in the terminal to compile and run our code:
```
g++ main.cpp Heap.cpp -o main
./main
```

## What can you change

### 4 versions of heaps

We implemented $4$ types of heaps, all with the same interface. In the current code, we used Fibonacci Heap. By changing the type of heap in function djkstra in main.cpp into one of 

* CompleteHeap
* LeftistHeap
* SkewedHeap
* FibonacciHeap

you can test all the versions we have implemented. No other changes are need to make to the code.

### 3 versions of main

We implemented $3$ versions of main function, as stated in the report. They serve for different purposes and you can adjust the code to run any of them. 
Refer to the report for detailed information.

## How to use

Here we describe how to use the third version of main, which is for user testing and is the currently adopted version in the code. The code read graph data from input.txt. In this file, first use "p sp $n$ $m$" in a line to offer vertex number $n$ and edge number $m$. Then, in the following lines, use "a $x$ $y$ $z$" in a line to denote a directional edge from $x$ to $y$ with length $z$.

When running the code, you will first receive "Graph built" after the program had read the data. Then type in a single query in a line with $2$ integers, denoting the source and destination. You will get the answer in the standard output.

We offers a sample of input.txt in the folder.