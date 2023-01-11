/********************************************************************************* 
* Nicholas Chu, nchu5
* 2022 Spring CSE101 PA3
* Graph.c
* Contains testing environment for Graph.c. Takes input same formatted input file
* as the FindComponents and prints everything out to make it easier to check.
*********************************************************************************/

#include "Graph.h"
#include "List.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(){
    // Checking if there are the correct number of arguements.
    Graph A = newGraph(100);
    List L = newList();
    
    if (getSize(A) != 0)
      printf("Error 1\n");
    addArc(A, 54, 1);
    addArc(A, 54, 2);
    addArc(A, 54, 2);
    addArc(A, 54, 3);
    addArc(A, 1, 54);
    addArc(A, 1, 54);
    addArc(A, 1, 55);
    addArc(A, 1, 55);
    
    
    printf("No errors when adding Arcs");
    if (getSize(A) != 5)
      printf("Erorr2");
    for (uint8_t i = 1; i <= 100; i++) {
      append(L, i);
    }
    DFS(A, L);
    if (getSize(A) != 5)
      printf("Error 3");
    addArc(A, 55, 1);
    if (getSize(A) != 6)
      printf("Error 4");
    printf("Yeet");
    return 0;
}
