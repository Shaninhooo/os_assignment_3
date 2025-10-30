README.template

## Assignment 3 Concurrency  

* Authors: Shane Lee, Ethan Dankiw, Tony Le
* Group name: Assignment 3 Groups 36

## Overview

This program will be a multi-threaded parallelised version of the merge sort algorithm using the pthread library.
It will simply take the size of a random array, the level of parallelisation or the cutoff number and the seed as input 
and return the time it took to sort the randomised array.

## Manifest

A listing of source files and other non-generated files, and a brief (one-line) explanation of the purpose of each file.
- mergesort.c
The file where all the functionalities of the program are in.
- mergesort.h
The file that has all the main variables initialised in.
- test-mergesort.c
The file that runs all the functions of the program using a test randomly generated array and prints the result and the time taken for finish.
- Makefile
The file used to compile the programs.

## Building the project

There are two ways to compile and run the program

### The automatic way

Automatically build and run by entering `make run_default` or `make run ARGS="<array_size> <cutoff_level> <seed>"`
- `make run_default` build and runs the code with the params `100000000 8 1234`
- Both `make run` and `make run_default` has dependencies for the compiled build, so if the build missing or has changes 
in the source code were made. It will auto compile when needed

### The manual way

To build and run the program you need to:
1. build by inputting `make all` on the terminal
2. run by running `./build/test-mergesort <array_size> <cutoff_level> <seed>` in the terminal

## Features and usage

Summarise the main features of your program. It is also appropriate to
instruct the user how to use your program.

## Testing

This section should detail how you tested your code. Simply stating "I ran
it a few times and it seems to work" is not sufficient. Your testing needs
to be detailed here.

## Known Bugs

List known bugs that you weren't able to fix (or ran out of time to fix).

## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your own?
What kinds of errors did you get? How did you fix them?

What parts of the project did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this project? How well
did the development and testing process go for you?

## Sources Used

If you used any sources outside of the textbook, you should list them here. 
If you looked something up on stackoverflow.com or you use help from AI, and 
fail to cite it in this section, it will be considered plagiarism and dealt 
with accordingly. So be safe CITE!

https://www.geeksforgeeks.org/c/c-program-for-merge-sort/
