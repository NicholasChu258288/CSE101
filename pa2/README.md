#Programming Assignment 2

## Short Description
    The main program, FindPath.c takes a formatted input file then uses it to create a graph. It then, using the same input file finds a shortest path between specified edges. It then prints the adjacency representation of the graph along with the shortest paths to the outfile.

## Files
    List.c          List ADT and functions for it
    List.h          Header file for List ADT
    Graph.c         Graph ADT and functions for it 
    Graph.h         Header file for Graph ADT
    GraphTest.c     Just was for testing purposes
    FindPath.c      Main program used to find shortest path of a graph using BFS
    Makefile
    README          a list of files submitted, and any notes to the grader

## Building
    To run FindPath type "make FindPath" into the console which should create the "FindPath" executable.

## Running
    ./FindPath <input file> <output file>

## Errors
    Use "valgrind ./Lex <input file> <outputfile>" to detect memory errors.
    No detected memory errors.

## Side notes
    I accidentally skipped over the part where we were it recommended that we make the arrays n+1 size, so I had -1 on all the indecies to compensate.

