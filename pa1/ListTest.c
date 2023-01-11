/********************************************************************************* 
* Nicholas Chu, nchu5
* 2022 Spring CSE101 PA1
* ListTest.c
* Testing functionality of List.c
*********************************************************************************/

#include "List.h"

int main(){
    printf("TEST\n");
    List A = newList();
    
    prepend(A, 5);
    prepend(A, 65);
    prepend(A, 43);
    printList(stdout, A);
    moveBack(A);
    printf("index %d with data %d\n", index(A), get(A));
    printf("Work\n");
    delete(A);
    printList(stdout, A);
    if (index(A) != -1){
      printf("return 1\n");
    }
    prepend(A, 2);
    prepend(A, 8);
    prepend(A, 1);
    moveBack(A);
    if (index(A) != 4){
      printf("return 2\n");
    }
    delete (A);
    moveBack(A);
    // !!
    if (index(A) != 3){
      printf("return 3\n");
    }
    moveFront(A);
    delete (A);
    moveFront(A);
    if (index(A) != 0){
      printf("return 4\n");
    }
    delete (A);
    if (index(A) != -1){
      printf("return 5\n");
    }
    return 0;
}
// Need to still test insert after