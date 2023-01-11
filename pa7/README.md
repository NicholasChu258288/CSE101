#Programming Assignment 7

## Short Description
    The main program, Order.cpp, takes an input file and creates a dictionary using them via using a BST. It then prints out the sorted contents to an outfile.
## Files
    README                  Written by you, a catalog of submitted files and any notes to the grader 
    Makefile                Provided, alter as you see fit 
    Dictionary.h            Provided, you may alter the "helper functions" section, but nothing else 
    Dictionary.cpp          Written by you, the majority of work for this project 
    DictionaryClient.cpp      Written by you, your test client of the Dictionary ADT 
    Order.cpp               Written by you, the client for this project 

## Building
    To run Order type "make" into the console which should create the "Order" executable.
    Use "make clean" when done using Order

## Running
    ./Order <input file> <output file>

## Errors
    Use "valgrind ./Order <input file> <outputfile>" to detect memory errors.
    Alternatively could also use "make OrderCheck"
    
    No memory errors, or leaks were detected when running the script. All of the script tests passed as well.
    Test 5 occasionally times out, for the most part, about 9 out of 10 times, it is able to run and pass fine.
    I think this is just a timeshare thing.
