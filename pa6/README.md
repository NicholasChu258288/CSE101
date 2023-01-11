#Programming Assignment 6

## Short Description
    The main program, Arithmatic.c takes a formatted input file of two large integers then preforms various calculations with these numbers.

## Files
    Arithmetic.cpp         Top level client for the project, described above
    BigInteger.cpp         BigInteger implementation file
    BigInteger.h           BigInteger header file, provided
    BigIntegerTest.cpp     Test suite for the BigInteger ADT
    List.cpp               List implementation file
    List.h                 List header file, provided
    ListTest.cpp           Test suite for the List ADT
    Makefile               Included in Examples/pa6
    README                 A list of files submitted, and any notes to the grader

## Building
    To run Sparse type "make" into the console which should create the "Arithmatic" executable.

## Running
    ./Arithmatic <input file> <output file>

## Errors
    Use "valgrind ./Arithmatic <input file> <outputfile>" to detect memory errors.
    Alternatively could also use "make ArithmeticCheck"
    No memory errors but earaseAfter() and clear() occassionally cause some warnings during some of the tests.

    Grading Script Notes:
    Note that when running and and issue occurs try changing the typedef in ListElement from List.h from long to int64_t if long is not working or overflowing.
    