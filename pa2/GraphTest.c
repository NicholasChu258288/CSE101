#include "Graph.h"
#include "List.h"

#include <stdio.h>
#include <stdlib.h>

int main(){
    Graph A = newGraph(100);
    Graph C = newGraph(100);
    List L = newList();
    addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);
    BFS(A, 3);
    getPath(L, A, 64);
    append(C, 3);
    append(C, 42);
    append(C, 2);
    append(C, 64);
    if (!equals(L, C))
      printf("1\n");
    moveFront(L);
    BFS(A, 2);
    getPath(L, A, 2);
    append(C, 2);
    if (!equals(L, C))
      printf("2\n");
    getPath(L, A, 99);
    if (equals(L, C))
      printf("3\n");
    clear(L);
    clear(C);
    append(C, NIL);
    BFS(A, 99);
    getPath(L, A, 2);
    if (!equals(C, L))
      return 4;
    return 0;
}