/********************************************************************************* 
* Nicholas Chu, nchu5
* 2022 Spring CSE101 PA1
* List.c 
* Contains the implementation of the List ADT.
*********************************************************************************/

// Includes -------------------------------------------------------------------
#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

// Structs --------------------------------------------------------------------
// Type that list will hold, change when changing what element you want in list
typedef int ListElement;

// Private structure for node data-type
// For this assignment it will hold the index and char array used in list
typedef struct NodeObj{
    ListElement data; // Array to hold string of node
    struct NodeObj* next; // Points to next node in the list
    struct NodeObj* prev; // Points to previous node in the list
} NodeObj;
typedef NodeObj* Node;

// Structure of list data-type
// List is a doubly linked list
typedef struct ListObj{
    int length; // Tracks length of the list
    Node cursor; // Points to focused on Node
    Node front; //First Node of the list
    Node back; //Last Node of the list
} ListObj;
typedef ListObj* List;


//Constructors-Destructors ---------------------------------------------------
// Private constructor that constructs a new node
Node newNode(ListElement i){
    Node n = malloc(sizeof(NodeObj));
    n->data = i;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

// Frees all heap memory associated with n
void freeNode(Node* n){
    if (n != NULL && *n != NULL){
        // Nulls the prev and next node, and frees n
        free(*n);
        n = NULL;
    }
}

// Creates and returns a new empty List.
List newList(void){
    List pL;
    pL = malloc(sizeof(ListObj));
    pL->front = NULL;
    pL->back = NULL;
    pL->cursor = NULL;
    pL->length = 0;
    return pL;
} 

// Frees all heap memory associated with *pL, and sets
// *pL to NULL.
void freeList(List* pL){
    if (pL != NULL && *pL != NULL){
        // Frees nodes in List
        clear(*pL);
        // Frees List itself
        free(*pL);
        *pL = NULL;
    }
}


// Access functions -----------------------------------------------------------
// Returns the number of elements in L.
int length(List L){
    return L->length;
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
    // Preconditions
    if (L == NULL){
        printf("List error: calling index() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0){
        printf("List error: calling index() on empty List.\n");
        exit(EXIT_FAILURE);
    }
    // If cursor is defined return it
    //printf("\n");
    //printf("Getting index\n");
    if (L->cursor != NULL){
        //printf("Conditions met\n");
        Node n = L->front;
        int i;
        for (i = 0; i < length(L); i++){
                //printf("Current i: %d\n", i);
                 if (L->cursor->data == n->data){
                     //printf("Returning current i: %d\n", i);
                     return i;
                 }
                n = n->next;
        }
    }
    // If cursor is not defined then return -1
    return -1;
}

// Returns front element of L. Pre: length()>0
int front(List L){
    // Preconditions
    if (L == NULL){
        printf("List error: calling front() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0){
        printf("List error: calling front() on empty List.\n");
        exit(EXIT_FAILURE);
    }

    return L->front->data;
}

// Returns back element of L. Pre: length()>0
int back(List L){
    // Preconditions
    if (L == NULL){
        printf("List error: calling back() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0){
        printf("List error: calling back() on empty List.\n");
        exit(EXIT_FAILURE);
    }

    return L->back->data;
}

// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L){
    // Preconditions
    if (length(L) == 0){
        printf("List Error: calling get() on an empty list\n");        
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0){
        printf("List Error: calling get() with invalid index\n");
        exit(EXIT_FAILURE);
    }
    // Returning data from cusor element
    return L->cursor->data;
}

// Returns true if Lists A and B are in same
// state, and returns false otherwise.
bool equals(List A, List B){
    // Precondition to check if A and B exist
    if (A == NULL || B == NULL){
        printf("List Error: calling equals() on NULL List reference");
        exit(EXIT_FAILURE);
    }
    // Checks if the lists are the same size, then goes through the list to match
    bool r = (length(A) == length(B));
    Node a = A->front;
    Node b = B->front;
    while (a != NULL){
        r = (a->data == b->data);
        a = a->next;
        b = b->next;        
    }
    return r;
}


// Manipulation procedures ----------------------------------------------------
// Resets L to its original empty state.
void clear(List L){
    // Preconditions
    if (L == NULL){
        printf("List error: calling clear() on NULL list reference.");
        exit(EXIT_FAILURE);
    }
    // Clearing the list
    Node n = L->front;
    Node t = n;
    while (n != NULL){
        //printf("Visited element: %d\n", n->data);
        t = n->next;
        freeNode(&n);
        n = t;
    }
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
} 

// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, int x){
    // Preconditions
    if (L == NULL){
        printf("List error: calling set() on  NULL list reference.");
    }
    if (length(L) == 0){
        printf("List error: calling set() on an empty list.");
    }
    if (index(L) < 0){
        printf("List error: calling set() with invalid index.");
    }
    // Setting the element's data
    L->cursor->data = x;
}

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
    if (length(L) > 0){ 
        L->cursor = L->front;
        //printf("Move front was used\n");
    }
}

// If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
void moveBack(List L){
    if (length(L) > 0){
        L->cursor = L->back;
    }
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){
    if (L->cursor != NULL && L->cursor->prev == NULL){
        L->cursor = NULL;
        return;
    }
    if (L->cursor != NULL && L->cursor->data != L->front->data){
        L->cursor = L->cursor->prev;
        return;
    }
    
} 

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){
    // If not back node
    if (L->cursor != NULL && L->cursor->next != NULL){
        L->cursor = L->cursor->next;
        return;
    }
    if (L->cursor->data == L->back->data && L->cursor->next == NULL){
        printf("Using next on end of list\n");
        L->cursor = NULL;
        return;
    }
    
    // If not front node
    
}

 // Insert new element into L. If L is non-empty,
 // insertion takes place before front element.
void prepend(List L, int x){
    //Preconditions
    if (L == NULL){
        printf("ListError: calling prepend() on NULL List reference.");
        exit(EXIT_FAILURE);
    }
    if (x < 0){
        printf("List error: calling prepend() and appending negative index.");
        exit(EXIT_FAILURE);
    }

    //Creating node and prepending it to list
    Node n = newNode(x);
    if (length(L) == 0){
        L->back = n;
    }
    if (length(L) > 0){
        L->front->prev = n;
        n->next = L->front;
    }
    L->front = n;
    L->length += 1;
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int x){
    // Preconditions
    if (L == NULL){
        printf("List error: calling append() on NULL List reference.");
        exit(EXIT_FAILURE);
    }
    if (x < 0){
        printf("List error: calling append() and appending negative index.");
        exit(EXIT_FAILURE);
    }
    // Creating node and appending it to list
    Node n = newNode(x);
    if (length(L) == 0){
        L->front = n;
    }
    if (length(L) > 0){
        L->back->next = n;
        n->prev = L->back;
    }
    L->back = n;
    L->length += 1;
}
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x){
    // Preconditions
    if (L == NULL){
        printf("List error: calling insertBefore() on NULL List reference.");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0){
        printf("List error: calling insertBefore() with negative index.");
        exit(EXIT_FAILURE);
    }
    // Inserting new element before cursor
    Node n = newNode(x);
    int i = index(L);
    n->next = L->cursor;
    if (i == 0){
        //printf("Making front, index at: %d\n", i);
        L->front = n;
    }
    if (i > 0){
        //printf("Insert conditions met and not at front at index %d\n", i);
        n->prev = L->cursor->prev;
        L->cursor->prev->next = n;
    }
    L->cursor->prev = n;
    L->length += 1;
    //printf("Finished inserting\n");
}
// Insert new element after cursor.
// Pre: length()>0, index()>=0
// Delete the front element. Pre: length()>0
void insertAfter(List L, int x){
    // Preconditions
    if (L == NULL){
        printf("List error: calling insertAfter() on NULL List reference.");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0){
        printf("List error: calling insertAfter() with negative index.");
        exit(EXIT_FAILURE);
    }
    Node n = newNode(x);
    int i = index(L);
    //When index is at the back
    n->prev = L->cursor;
    if (i == L->length-1){
        L->back = n;
    }
    //When index is in not at the back
    if (i < L->length-1){
        n->next = L->cursor->next;
        L->cursor->next->prev = n;
    }
    L->cursor->next = n;
    L->length += 1;
}
void deleteFront(List L){
    // Preconditions
    if (L == NULL){
        printf("List error: calling deleteFront() on NULL List reference.");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0){
        printf("List error: calling deleteFront() on empty list.");
        exit(EXIT_FAILURE);
    }
    // Deleting front element
    Node n = NULL;
    if (length(L) > 1){
        n = L->front->next;
        freeNode(&n);
    }
    freeNode(&n);
    L->length -= 1;
} 
// Delete the back element. Pre: length()>0
void deleteBack(List L){
    // Preconditions
    if (L == NULL){
        printf("List error: calling deleteFront() on NULL List reference.");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0){
        printf("List error: calling deleteFront() on empty list.");
        exit(EXIT_FAILURE);
    }
    // Deleting back node
    Node n = L->back;
    L->back = n->prev;
    freeNode(&n);
    L->length -= 1;
}
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
    //Preconditions
    if (L == NULL){
        printf("List error: calling delete() on NULL List reference.");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0){
        printf("List error: calling delete() on empty list.");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0){
        printf("List error: calling delete() with invalid index");
        exit(EXIT_FAILURE);
    }
    //FIXME
    Node n = L->cursor;
    //When cursor is at the front
    if (n->prev == NULL && index(L) == 0){
        L->front = n->next;
        freeNode(&n);
    }
    //When cursor is at the back
    if (n->next == NULL && index(L) == length(L)-1){
        L->back = n->prev;
        freeNode(&n);
    }
    //When cursor is between two nodes
    if (n->next != NULL && n->prev != NULL){
        n->prev->next = n->next;
        n->next->prev = n->prev;
        freeNode(&n);
    }
    L->length -= 1;
}

// Other operations -----------------------------------------------------------
 // Prints to the file pointed to by out, a
 // string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L){
    // Preconditions
    if (out == NULL){
        printf("List error: calling printList() with invalid file.");
        exit(EXIT_FAILURE);
    }
    if (L == NULL){
        printf("List error: calling printList() on NULL reference List.");
        exit(EXIT_FAILURE);
    }
    // Printing List
    Node n = L->front;
    while (n != NULL){
        fprintf(out, "%d ", n->data);
        n = n->next;
    }
    fprintf(out, "\n");
}
// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){
    //Precondition
    if (L == NULL){
        printf("List error: calling copyList() on NULL reference List.");
        exit(EXIT_FAILURE);
    }
    // Copying over List L to new List l which is then returned.
    List l = newList();
    Node n = L->front; // Node of L that is currently being tracked
    while (n != NULL){
        append(l, n->data);
        n = n->next;       
    }
    return l;
} 
