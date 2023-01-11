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

    printf("Testing Append:\n");
    append(A, 5);
    append(A, 11);
    append(A, 18);
    printList(stdout, A);
    printf("\n");

    printf("Testing prepend:\n");
    prepend(A, 7);
    printList(stdout, A);
    printf("\n");

    printf("List Properties: %d\n", length(A));
    printf("Iterating through the List:\n");

    //Testing move, get, and index
    moveFront(A);
    printf("index of cursor: %d\n", index(A));
    moveNext(A);
    moveNext(A);
    printf("index after moveNext: %d\n", index(A));
    printf("data at index: %d\n", get(A));
    printf("\n");

    //Testing insert
    printf("Testing insert Before:\n");
    printf("List before insert: ");
    printList(stdout, A);
    insertBefore(A, 12);
    printf("Inserted 12 before: ");
    printList(stdout, A);
    moveFront(A);
    printf("Now inserting at front: ");
    insertBefore(A, 1);
    printList(stdout, A);
    printf("Testing insert After:\n");
    printf("\n");

    printf("Now copying and printing:\n");
    List B = copyList(A);
    printList(stdout, B);
    printf("\n");


    printf("Compare both lists:\n");
    if (equals(A, B)){
        printf("Equals\n");
    } else {
        printf("Not equal\n");
    }
    printf("\n");

    printf("Testing free:\n");
    freeList(&A);
    freeList(&B);
    printf("Frees were successful\n");
    return 1;
}
// Need to still test insert after