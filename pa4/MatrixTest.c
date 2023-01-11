/********************************************************************************* 
* Nicholas Chu, nchu5
* 2022 Spring CSE101 PA1
* Matrix.h
* Contains the implementation of the Matrix ADT.
*********************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
int main(){
   Matrix A = newMatrix(100);
   Matrix B = newMatrix(100);
   Matrix pC = newMatrix(15);
    changeEntry(A, 1, 1, 1);
    changeEntry(pC, 1, 1, 1);
    printf("A:\n");
    printMatrix(stdout, A);
    printf("pC:\n");
    printMatrix(stdout, pC);
    if (equals(A, pC))
      printf("Failed Test1\n");
   printf("Passed test1\n");
   Matrix pD = newMatrix(15);
    changeEntry(A, 1, 1, 1);
    changeEntry(A, 1, 3, 1);
    changeEntry(B, 1, 1, 1);
    changeEntry(B, 1, 3, 1);
    if (!equals(A, B))
      printf("Failed Test2\n");
   printf("Passed test2\n");
    changeEntry(A, 1, 3, 0);
    if (equals(A, B))
      printf("Failed test 3\n");
    changeEntry(A, 1, 1, 0);
    makeZero(B);
    changeEntry(A, 10, 10, 10);
    changeEntry(B, 10, 10, 10);
    if (!equals(A, B))
      printf("Failed test 4\n");

   printf("Passed test 4\n");
    Matrix pA = newMatrix(100);
    Matrix pB = newMatrix(100);
    int valcount = 1;
    for (int j = 1; j <= 100; j++) {
      for (int k = 1; k <= 100; k++) {
        // hint: this is 1-10000 left-to-right row-by-row
        changeEntry(A, j, k, valcount++);
      }
      changeEntry(B, j, j, 1); // hint: this is the identity matrix
    }
    freeMatrix(&pC);
    freeMatrix(&pD);
    pC = scalarMult(2, A);
    pD = sum(A, A);
    if (!equals(pC, pD))
      printf("Failed test5");

    freeMatrix(&pC);
    freeMatrix(&pD);
    pC = scalarMult(-2, A);
    Matrix As1 = diff(A, A);
    Matrix As2 = diff(As1, A);
    pD = diff(As2, A);
    freeMatrix(&As1);
    freeMatrix(&As2);
    if (!equals(pC, pD))
      printf("Failed Test6");

    freeMatrix(&pC);
    pC = product(A, B);
    if (!equals(pC, A))
      printf("Falied test7\n");

   printf("Reached end\n");

    return 0;
  }



/*    
//-----------------------------------------------------------------------------
//  MatrixClient.c 
//  A test client for the Matrix ADT
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"

int main(){
   int n=100000;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C, D, E, F, G, H;

   changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
   changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
   changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
   changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);

   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);
   printf("\n");

    printf("NNZ worked\n");

   printf("%d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\n");

   C = scalarMult(1.5, A);
   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");

   D = sum(A, B);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");

   E = diff(A, A);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");

   F = transpose(B);
   printf("%d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");

   G = product(B, B);
   printf("%d\n", NNZ(G));
   printMatrix(stdout, G);
   printf("\n");

   H = copy(A);
   printf("%d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("\n");

   printf("%s\n", equals(A, H)?"true":"false" );
   printf("%s\n", equals(A, B)?"true":"false" );
   printf("%s\n", equals(A, A)?"true":"false" );

   makeZero(A);
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);

   return EXIT_SUCCESS;
}
*/

/*
Output of this program:
9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0)
3: (1, 1.0) (2, 1.0) (3, 1.0)

9
1: (1, 1.5) (2, 3.0) (3, 4.5)
2: (1, 6.0) (2, 7.5) (3, 9.0)
3: (1, 10.5) (2, 12.0) (3, 13.5)

9
1: (1, 2.0) (2, 2.0) (3, 4.0)
2: (1, 4.0) (2, 6.0) (3, 6.0)
3: (1, 8.0) (2, 9.0) (3, 10.0)

0

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0) (3, 1.0)
3: (1, 1.0) (3, 1.0)

7
1: (1, 2.0) (2, 1.0) (3, 2.0)
2: (2, 1.0)
3: (1, 2.0) (2, 2.0) (3, 2.0)

9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

true
false
true
0
*/