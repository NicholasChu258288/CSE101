/********************************************************************************* 
* Nicholas Chu, nchu5
* 2022 Spring CSE101 PA4
* Sparse.c
* Program takes an input file and creates two matricies. Then using those two
* matricies does vaious operations creating new matricies and printing them all
* to an output file.
*********************************************************************************/

#include "Matrix.h"
#include "List.h"

#include <stdio.h>
#include <stdlib.h>

void usage(){
    printf("./Sparse <input file> <output file>\n");
}

int main(int argc, char* argv[]){
    // Checking if there are the correct number of arguements.
    if (argc != 3){
        fprintf(stderr, "Invalid number of arguements.\n");
        exit(EXIT_FAILURE);
    }

    // Opening files
    FILE *infile = fopen(argv[1], "r");
    FILE *outfile = fopen(argv[2], "w");
    
    int s;
    int nzA;
    int nzB;

    fscanf(infile, "%d %d %d\n", &s, &nzA, &nzB);

    Matrix A = newMatrix(s);
    Matrix B = newMatrix(s);

    int i;
    int j;
    double x;

    for (int y = 0; y < nzA; y++){
        fscanf(infile, "%d %d %lf\n", &i, &j, &x);
        changeEntry(A,i,j,x);
    }
    //For non zero entries nzA add to A

    for (int y= 0; y < nzB; y++){
        fscanf(infile, "%d %d %lf\n", &i, &j, &x);
        changeEntry(B,i,j,x);
    }

    fprintf(outfile, "A had %d non-zero entries:\n", nzA);
    printMatrix(outfile, A);
    fprintf(outfile, "\n");

    fprintf(outfile, "B had %d non-zero entries:\n", nzB);
    printMatrix(outfile, B);
    fprintf(outfile, "\n");

    Matrix C = scalarMult(1.5, A);
    fprintf(outfile, "(1.5)*A =\n");
    printMatrix(outfile, C);
    fprintf(outfile, "\n");

    Matrix D = sum(A, B);
    fprintf(outfile, "A+B =\n");
    printMatrix(outfile, D);
    fprintf(outfile, "\n");

    Matrix E = sum(A, A);
    fprintf(outfile, "A+A =\n");
    printMatrix(outfile, E);
    fprintf(outfile, "\n");

    Matrix F = diff(B, A);
    fprintf(outfile, "B-A =\n");
    printMatrix(outfile, F);
    fprintf(outfile, "\n");

    Matrix G= diff(A,A);
    fprintf(outfile, "A-A =\n");
    printMatrix(outfile, G);
    fprintf(outfile, "\n");

    Matrix H = transpose(A);
    fprintf(outfile, "Transpose(A) =\n");
    printMatrix(outfile, H);
    fprintf(outfile, "\n");

    Matrix I = product(A,B);
    fprintf(outfile, "A*B =\n");
    printMatrix(outfile, I);
    fprintf(outfile, "\n");

    Matrix J = product(B,B);
    fprintf(outfile, "B*B =\n");
    printMatrix(outfile, J);

    // Freeing memory and closing files
    fclose(infile);
    fclose(outfile);

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);
}