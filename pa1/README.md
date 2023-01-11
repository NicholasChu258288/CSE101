#Programming Assignment 1

## Short Description
    The main program, Lex takes two files, an input and output file, and alphabetically sorts the contents of the input file then placing it into the output file.

## Building
    To run Lex type "make" into the console which should create "Lex".

## Running
    ./Lex <input file> <output file>

## Errors
    Use "valgrind ./Lex <input file> <outputfile>" to detect memory errors.

    Getting warnings from valgrind when running Lex, primarily that: Conditional jump or move depends on uninitialized values(s). This occurs specifically when using strcmp during the insertion sort.

    Additionally the Lex.c passes all of the tests provided in the examples provided on the class web-site, however for the grading script it fails to properly sort one of the provided text files.
