#Programming Assignment 8

## Short Description
    Dictionary.cpp is a Red Black Tree ADT. 
    The main program, Order.cpp, takes an input file and creates a dictionary using them via using a BST. It then prints out the sorted contents to an outfile.
    The other main program WordFrequency.cpp takes an input file and creates a dictionary which tracks the unique words and their frequency, then printing to 
    an output file.

## Files
    README                  Written by you, a catalog of submitted files and any notes to the grader 
    Makefile                Provided, alter as you see fit 
    Dictionary.h            Provided, you may alter the "helper functions" section, but nothing else 
    Dictionary.cpp          Written by you, the majority of work for this project 
    DictionaryClient.cpp    Written by you, your test client of the Dictionary ADT 
    Order.cpp               Written by you, the client for this project
    WordFrequency.cpp       Written by you, a client for this project

## Building
    To run Order type "make" into the console which should create the "WordFrequency" executable.
    Use "make Order" to make "Order"
    Use "make clean" when done using Order

## Running
    ./Order <input file> <output file>

    ./WordFrequency <input file> <output file>

## Errors
    Use "valgrind ./Order <input file> <outputfile>"  and "valgrind ./WordFrequency <input file> <outputfile>" to detect memory errors.
    
    No memory errors, or leaks were detected when running the script.