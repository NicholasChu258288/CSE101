/********************************************************************************* 
* Nicholas Chu, nchu5
* 2022 Spring CSE101 PA1
* List.c 
* Used for alphabetizing lines in a file by using the List ADT
*********************************************************************************/

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 2048

void usage(){
    printf("./Lex <input file> <output file>\n");
}

int main(int argc, char* argv[]){
    // Checking if there are the correct number of arguements.
    if (argc != 3){
        usage();
        fprintf(stderr, "Invalid number of arguements.\n");
        exit(EXIT_FAILURE);
    }

    // Opening files
    FILE *infile = fopen(argv[1], "r");
    FILE *outfile = fopen(argv[2], "w");

    // Precondition to check if infile exists and was openable
    if (infile == NULL){
        fprintf(stderr, "Lex error: coud not open input file.\n");
        exit(EXIT_FAILURE);
    }
    
    // Get line count
    int count = 1;
    int c = getc(infile);
    while (c != EOF){
        if (c == '\n'){
            count += 1;
        }
        c = getc(infile);
    }
    rewind(infile); // Sets pointer back to the beginning of file

    // Scanning lines into array
    char** lines = (char **)calloc(count, sizeof(char*)); // Array of all lines in file
    char *line; // Contents of each line
    // Using fgets, gets each line and saves it into lines
    for (int r = 0; r < count; r += 1){
        line = malloc(BUFFER_SIZE * sizeof(char));
        fgets(line, BUFFER_SIZE, infile);
        lines[r] = line;
    }

    // Creating List to go along with lines
    List L = newList();
    append(L, 0);
    moveFront(L);
    // Insertion sort
    for (int i = 1; i < count; i++){
        while (index(L) < i-1){
            moveNext(L);
        }
        int j = i-1;
        while (j > 0 && strcmp(lines[i],lines[get(L)]) < 0){
            movePrev(L);
            j-=1;
        }
        if (strcmp(lines[i], lines[get(L)]) < 0){
            insertBefore(L,i);
        } else {
            insertAfter(L,i);
        }
    }

    //Printing sorted alphabetical list to outfile
    moveFront(L);
    fprintf(outfile,"%s", lines[get(L)]);
    while (index(L) < length(L)-1){
        moveNext(L);
        fprintf(outfile,"%s", lines[get(L)]);
        
    }

    //Freeing and closing everything so there are no memory leaks
    freeList(&L);
    //Freeing all contents of array
    for (int i = 0; i < count; i++){
        free(lines[i]);
    }
    //Freeing array itself
    free(lines);
    //Closing files
    fclose(infile);
    fclose(outfile);
    return 1;
}