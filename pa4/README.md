#Programming Assignment 4

## Short Description
    The main program, Sparse.c takes a formatted input file then uses it to create two sparse matricies. Using these two matricies the program preforms various operations and prints all this out to a specified outfile.

## Files
    Sparse.c               Main program that creates sparse matricies and does operations
    Matrix.c               Matrix ADT and its functions
    Matrix.h               Header file for Matrix ADT
    MatrixTest.c           File for testing functionality of Matrix ADT
    List.c                 List ADT and functions for it
    List.h                 Header file for List ADT
    ListTest.c             Was used for doing tests for modified List ADT
    Makefile
    README                 A list of files submitted, and any notes to the grader

## Building
    To run Sparse type "make Sparse" into the console which should create the "Sparse" executable.

## Running
    ./Sparse <input file> <output file>

## Errors
    Use "valgrind ./Sparse <input file> <outputfile>" to detect memory errors.
    No detected memory errors.

    Grading Script Notes:
    Could not pass the NonEmpty_equals because the test timed out. I could not find the source of the loop that might be causing it. Aside for that every other test passed.