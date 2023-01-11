#Programming Assignment 3

## Short Description
    The main program, FindComponents.c takes a formatted input file then uses it to create a graph. It then, uses DFS to find all the strongly connected components of a graph. It then prints the adjacency representation of the graph along with the components to the outfile.

## Files
    List.c                 List ADT and functions for it
    List.h                 Header file for List ADT
    Graph.c                Graph ADT and functions for it 
    Graph.h                Header file for Graph ADT
    GraphTest.c            Just was for testing purposes
    FindComponents.c      Main program used to find shortest path of a graph using BFS
    Makefile
    README                 A list of files submitted, and any notes to the grader

## Building
    To run FindComponents type "make FindComponents" into the console which should create the "FindComponents" executable.

## Running
    ./FindComponents <input file> <output file>

## Errors
    Use "valgrind ./FindComponents <input file> <outputfile>" to detect memory errors.
    No detected memory errors.