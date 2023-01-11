#Programming Assignment 5

## Short Description
    The main program, Shuffle.cpp, takes a maximum deck, creates a decks of individual cards up the specified size, then calculates the amount of perfect shuffles it would take to revert back to its original order, then prints the results.

## Files
    Shuffle.c              Main program that simulates the perfect deck shuffles
    List.c                 List ADT and functions for it
    List.h                 Header file for List ADT
    ListClient.c           Was used for doing tests for modified List ADT
    Makefile
    README                 A list of files submitted, and any notes to the grader

## Building
    To run Sparse type "make Shuffle" into the console which should create the "Shuffle" executable.

## Running
    ./Shuffle <int deckSize>

## Errors
    Use "valgrind ./Shuffle <int deckSize>" to detect memory errors.
    No detected memory errors when running Shuffle.

    Grading Script Notes:
    There were some issues where it would free too much due to either clear() or eraseBefore(). This was never an issue during testing and using Shuffle.