/********************************************************************************* 
* Nicholas Chu, nchu5
* 2022 Spring CSE101 PA4
* Matrix.c
* Contains the implementation of the Matrix ADT.
*********************************************************************************/

#include "Matrix.h"

#include <stdio.h>
#include <stdlib.h>

// Struct for each entry in the matrix
typedef struct EntryObj{
    int col;
    double val;
} EntryObj;
typedef EntryObj* Entry;

// Struct for Matrix ADT
typedef struct MatrixObj{
    List* matrix; // List is Lists that represent a matrix
    int size;   // Size of nXn matrix
    int elements; // Number of non-zero elements
} MatrixObj;
typedef MatrixObj* Matrix;

// newEntry()
// Returns a referene to a new Entry object
Entry newEntry(int col, double val){
    Entry e = malloc(sizeof(EntryObj));
    e->col = col;
    e->val = val;
    return e;
}

// freeEntry()
// Frees an entry
void freeEntry(Entry* e){
    if (e != NULL && *e != NULL){
        free(*e);
        *e = NULL;
    }
}

// newMatrix() 
// Returns a reference to a new nXn Matrix object in the zero state. 
Matrix newMatrix(int n){
    Matrix m = malloc(sizeof(MatrixObj));
    m->matrix = calloc(n+1, sizeof(List));
    for (int i = 1; i < n+1; i++){
        m->matrix[i] = newList();
    }
    m->size = n;
    return m;
}
 
// freeMatrix() 
// Frees heap memory associated with *pM, sets *pM to NULL. 
void freeMatrix(Matrix* pM){
    for (int i = 1; i < size((*pM))+1; i++){
        moveFront((*pM)->matrix[i]);
        Entry e = NULL;
        // Goes through list freeing all entries
        while (index((*pM)->matrix[i]) >= 0){
            e = get((*pM)->matrix[i]);
            freeEntry(&e);
            moveNext((*pM)->matrix[i]);
        }
        // Frees list itself
        freeList(&((*pM)->matrix[i]));
    }
    free((*pM)->matrix);
    free(*pM);
    *pM = NULL;
}
 
 
// Access functions  
 
// size() 
// Return the size of square Matrix M. 
int size(Matrix M){
    return M->size;
}
 
// NNZ() 
// Return the number of non-zero elements in M. 
int NNZ(Matrix M){
    // Uses a for loop to go through all the lists and get their lengths
    // then adds its to a sum which is returned
    int elements = 0;
    for (int i = 1; i < size(M)+1; i++){
        elements += length(M->matrix[i]);
    }
    return elements;
}
 
// equals() 
// Return true (1) if matrices A and B are equal, false (0) otherwise. 
int equals(Matrix A, Matrix B){
    if (size(A) != size(B)){

        //printf("Not the same size\n");

        return 0;
    }
    // Goes through each row of the matrix
    for (int i = 1; i < size(A)+1; i++){
        // If the lists are the same length, check if elements of both lists have same data
        if (length(A->matrix[i]) == length(B->matrix[i])){
            if (length(A->matrix[i]) > 0){
                 moveFront(A->matrix[i]);
                moveFront(B->matrix[i]);
                while (index(A->matrix[i]) >= 0){
                // Gets values of entry from A
                    Entry a = get(A->matrix[i]);
                    int colA = a->col;
                    double valA = a->val;
                    // Gets values of entry from B
                    Entry b = get(B->matrix[i]);
                    int colB = b->col;
                    double valB = b->val;
                // Returns 0 is either of the values are not equal
                    if (colA != colB || valA != valB){
                    
                    //printf("Entries do not match up.\n");

                        return 0;
                    }
                    moveNext(A->matrix[i]);
                    moveNext(B->matrix[i]);
            }

            }
           
        // When lists are not the same length return 0
        } else {
            return 0;
        }
    }
    // If its has gone through all the entries and made sure everything
    // matches then it returns a 1
    return 1;
}
 
 
// Manipulation procedures  
 
// makeZero() 
// Re-sets M to the zero Matrix state. 
void makeZero(Matrix M){
    // Goes through an clears all Lists in Matrix M
    for (int i = 1; i < size(M)+1; i++){
        clear(M->matrix[i]);
    }
}
 
// changeEntry() 
// Changes the ith row, jth column of M to the value x. 
// Pre: 1<=i<=size(M), 1<=j<=size(M) 
void changeEntry(Matrix M, int i, int j, double x){
    // Preconditions
    if (i < 1 || i > size(M)){
        printf("Matrix Error: called changeEntry() with index that is out of range.\n");
        exit(EXIT_FAILURE);
    }
    if (j < 1 || j > size(M)){
        printf("Matrix Error: called changeEntry() with row that is out of range.\n");
        exit(EXIT_FAILURE);
    }

    // If x is set to zero then it indicates a delete
    if (x == 0 && length(M->matrix[i]) > 0){
        moveFront(M->matrix[i]);
        Entry c = get(M->matrix[i]);
        int col = c->col;
        // Move through the list to find correct entry
        while (index(M->matrix[i]) >= 0 && col != j){
            c = get(M->matrix[i]);
            col = c->col;
            if (col == j){
                break;
            }
            moveNext(M->matrix[i]);
        }
        // If entry exists at specified column then delete it
        // and finish
        if (col == j){

            freeEntry(&c);
            delete(M->matrix[i]);
            
            return;
        }
    }

    // Otherwise this means when x is zero and just adding entry to an empty list
    // or the enrty was just zero to begin with so then the function does nothing.
    if (x == 0){
        return;
    }


    Entry e = newEntry(j, x);
    // If List is empty then just append, else find appropriate position to insert based off row
    if (length(M->matrix[i]) == 0){
        append(M->matrix[i], e);
        return;
    } else {
        
        
        moveFront(M->matrix[i]);
        Entry c;
        int col;
        // Go through the list and first checks if there is prexisting entry in given column and replaces it
        // If it doesnt find anything it just moves to correct position.
        for (int y = 0; y < length(M->matrix[i]); y++){
            
            c = get(M->matrix[i]);
            int col = c->col;
            if (col == j){
                freeEntry(&e);
                c = get(M->matrix[i]);
                c->val = x;
                return;
            }
            // Moves next if not the last entry in the list and when column
            // of then entry being inserted is greater than current column

            if (index(M->matrix[i]) < length(M->matrix[i])-1 && j > col){
                
                moveNext(M->matrix[i]);
            }
        }
        
        //printf("Finished moving\n");
        
        c = get(M->matrix[i]);
        col = c->col;
        // Depending on circumstances either inserts before or after cursor
        if (col < j){
            insertAfter(M->matrix[i], e);
        } else {
            insertBefore(M->matrix[i], e);
        }
    }
}
 
 
// Matrix Arithmetic operations  
 
// copy() 
// Returns a reference to a new Matrix object having the same entries as A. 
Matrix copy(Matrix A){
    Matrix m = newMatrix(size(A));
    Entry e;
    int col;
    double val;
    for (int i = 1; i < size(A)+1; i++){
        moveFront(A->matrix[i]);
        while (index(A->matrix[i]) >= 0){
            e = get(A->matrix[i]);
            col = e->col;
            val = e->val;
            changeEntry(m, i, col, val);
            moveNext(A->matrix[i]);
        }
    }
    return m;
}
 
// transpose() 
// Returns a reference to a new Matrix object representing the transpose 
// of A. 
Matrix transpose(Matrix A){
    Matrix m = newMatrix(size(A));
    // Transposing means to switch the rows with columns
    // Go through matrix A and just add new entries while switching the rows and cols

    for (int i = 1; i < size(A)+1; i++){
         moveFront(A->matrix[i]);
         Entry e;
         int col;
         double val;
         while (index(A->matrix[i]) >= 0){
             e = get(A->matrix[i]);
             col = e->col;
             val = e->val;
             changeEntry(m,col,i,val);
             moveNext(A->matrix[i]);
         }
    }

    return m;
}
 
// scalarMult() 
// Returns a reference to a new Matrix object representing xA. 
Matrix scalarMult(double x, Matrix A){
    Matrix m = newMatrix(size(A));
    for (int i = 1; i < size(A)+1; i++){
         moveFront(A->matrix[i]);
         Entry e;
         int col;
         double val;
         while (index(A->matrix[i]) >= 0){
             e = get(A->matrix[i]);
             col = e->col;
             val = e->val;
             changeEntry(m,i,col,val*x);
             moveNext(A->matrix[i]);
         }
    }
    return m;
}
 
// sum() 
// Returns a reference to a new Matrix object representing A+B. 
// pre: size(A)==size(B) 
Matrix sum(Matrix A, Matrix B){
    // Precondition
    if (size(A) != size(B)){
        printf("Matrix Error: called sum() where two different size matricies.\n");
        exit(EXIT_FAILURE);
    }
    // Creating new matrix
    Matrix m = newMatrix(size(A));

    // For the sick and disgusting people who add two of the same matrix
    // Just to make my life harder.
    Matrix C = copy(A);
    Matrix D = copy(B);

    for (int i = 1; i < size(A)+1; i++){
        moveFront(C->matrix[i]);
        moveFront(D->matrix[i]);
        Entry a;
        int colA;
        double valA;
        Entry b;
        int colB;
        double valB;
        while (index(C->matrix[i]) >= 0 || index(D->matrix[i]) >= 0){
            // Getting values for entries
            if (index(C->matrix[i]) >= 0){
                a = get(C->matrix[i]);
                colA = a->col;
                valA = a->val;
            }
            
            if (index(D->matrix[i]) >= 0){
                b = get(D->matrix[i]);
                colB = b->col;
                valB = b->val;
            }
            
            if (index(C->matrix[i]) < 0){
                colA = colB;
                valA = 0;
            }

            if (index(D->matrix[i]) < 0){
                colB = colA;
                valB = 0;
            }

            if (colA == colB){
                // When adding two non-zero entries
                changeEntry(m, i, colA, valA+valB);
                moveNext(C->matrix[i]);
                moveNext(D->matrix[i]);
            }

            if (colA < colB){
                // Adding entry from A to a zero one from B
                changeEntry(m, i, colA, valA);
                moveNext(C->matrix[i]);
            }

            if (colB < colA){
                // Adding enrty from B to a zero one from A
                changeEntry(m, i, colB, valB);
                moveNext(D->matrix[i]);
            }

        }
    }
    freeMatrix(&C);
    freeMatrix(&D);
    return m;
}
 
// diff() 
// Returns a reference to a new Matrix object representing A-B. 
// pre: size(A)==size(B) 
Matrix diff(Matrix A, Matrix B){
    if (size(A) != size(B)){
        printf("Matrix Error: called sum() where two different size matricies.\n");
        exit(EXIT_FAILURE);
    }
    // Creating new matrix
    Matrix m = newMatrix(size(A));
    Matrix C = copy(A);
    Matrix D = copy(B);
    for (int i = 1; i < size(A)+1; i++){
        
        moveFront(C->matrix[i]);
        moveFront(D->matrix[i]);
        Entry a;
        int colA;
        double valA;
        Entry b;
        int colB;
        double valB;
        while (index(C->matrix[i]) >= 0 || index(D->matrix[i]) >= 0){
            // Getting values for entries
            if (index(C->matrix[i]) >= 0){
                a = get(C->matrix[i]);
                colA = a->col;
                valA = a->val;
            }
            
            if (index(D->matrix[i]) >= 0){
                b = get(D->matrix[i]);
                colB = b->col;
                valB = b->val;
            }
            
            if (index(C->matrix[i]) < 0){
                colA = colB;
                valA = 0;
            }

            if (index(D->matrix[i]) < 0){
                colB = colA;
                valB = 0;
            }

            if (colA == colB){
                // When adding two non-zero entries
                if(valA-valB != 0){
                    changeEntry(m, i, colA, valA-valB);
                }
                
                moveNext(C->matrix[i]);
                moveNext(D->matrix[i]);
            }

            if (colA < colB){
                // Adding entry from A to a zero one from B
                changeEntry(m, i, colA, valA);
                moveNext(C->matrix[i]);
            }

            if (colB < colA){
                // Adding enrty from B to a zero one from A
                changeEntry(m, i, colB, 0-valB);
                moveNext(D->matrix[i]);
            }

        }
    }
    freeMatrix(&C);
    freeMatrix(&D);
    return m;
}


// Private helper function to get vector dot product used when
// calculating matrix product
double vectorDot(List P, List Q){

    double product = 0;

    moveFront(P);
    moveFront(Q);
    
    Entry p;
    int colP;
    double valP;

    Entry q;
    int colQ;
    double valQ;

    // Goes through both lists to get dot product
    while (index(P) >= 0 || index(Q) >= 0){
        // Gets current data from cursor
        if (index(P) >= 0){
            p = get(P);
            colP = p->col;
            valP = p->val;   
        }
        if (index(Q) >= 0){
            q = get(Q);
            colQ = q->col;
            valQ = q->val;
        }

        // When the finding the product of a column with
        // an existing entry and an empty one
        if (index(P) < 0){
            colP = colQ;
            valP = 0;
        }
        if (index(Q) < 0){
            colQ = colP;
            valQ = 0;
        }

        if (colP == colQ){
            product += (valP*valQ);
            moveNext(P);
            moveNext(Q);
        }

        if (colP < colQ){
            moveNext(P);
        }

        if (colQ < colP){
            moveNext(Q);
        }
    }

    return product;
}
 
// product() 
// Returns a reference to a new Matrix object representing AB 
// pre: size(A)==size(B) 
Matrix product(Matrix A, Matrix B){
    // Precondition
    if (size(A) != size(B)){
        printf("Matrix Error: calling product() with different sized Lists.");
        exit(EXIT_FAILURE);
    }

    Matrix m = newMatrix(size(A)); // Matrix to store result
    Matrix Bt = transpose(B); // Transposed B matrix to be used during calculation
    
    for (int i = 1; i < size(A)+1; i++){
        
        // For each row
        if (length(A->matrix[i]) > 0){

            if (length(A->matrix[i]) > 0){

                // Adjust this since it cuts off to early
                for (int j = 1; j < size(A)+1; j++){
                    // For each entry in row
                    changeEntry(m, i, j, vectorDot(A->matrix[i], Bt->matrix[j]));
                }
            }
        }

    }

    // Freeing transposed B since no longer needed after calculations
    freeMatrix(&Bt);
    return m;
}
 
// printMatrix() 
// Prints a string representation of Matrix M to filestream out. Zero rows  
// are not printed.  Each non-zero row is represented as one line consisting  
// of the row number, followed by a colon, a space, then a space separated  
// list of pairs "(col, val)" giving the column numbers and non-zero values  
// in that row. The double val will be rounded to 1 decimal point. 
void printMatrix(FILE* out, Matrix M){
    // Iterates through matrix rows
    for (int i = 1; i < size(M)+1; i++){
        // If row not empty then iterates through the row and prints entrys'
        // col and val respectively
        if (length(M->matrix[i]) > 0){
            fprintf(out, "%d: ", i);
            moveFront(M->matrix[i]);
            Entry e;
            int col;
            double val;
            while (index(M->matrix[i]) >= 0){
                e = get(M->matrix[i]);
                col = e->col;
                val = e->val;
                fprintf(out, "(%d, %0.1f) ", col, val);
                moveNext(M->matrix[i]);
            }
            fprintf(out, "\n");
        }

    }
}

