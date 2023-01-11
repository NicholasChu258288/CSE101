/********************************************************************************* 
* Nicholas Chu, nchu5
* 2022 Spring CSE101 PA3
* FindComponents.c
* Find strongly connected componenets of a Graph given an input file.
*********************************************************************************/

#include "Graph.h"
#include "List.h"

#include <stdio.h>
#include <stdlib.h>

void usage(){
    printf("./FindComponents <input file> <output file>\n");
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
    
    // Getting size of graph from infile
    int n;
    fscanf(infile, "%d\n", &n);
    Graph pG = newGraph(n);
    
    // Scanning infile to create adjacency list of graph and prints it to outfile
    int u;
    int v;
    fscanf(infile, "%d %d", &u, &v);
    if (u > 0 && v > 0){
        addArc(pG, u, v);
    }
    while (fscanf(infile, "%d %d", &u, &v) != EOF && (u != 0 && v != 0)){
        addArc(pG, u, v);
    }
    fprintf(outfile, "Adjacency list representation of G:\n");
    printGraph(outfile, pG);
    fprintf(outfile, "\n");
    
    // Creating initial ordered stack for first DFS
    List S = newList();
    for (int i = 1; i < n+1; i++){
        append(S, i);
    }

    DFS(pG, S);
    Graph Gt = transpose(pG);
    DFS(Gt, S);

    // Getting total number of components
    int componentCount = 0;
    moveBack(S);
    for (int i =  0; i < n; i++){
        if (getParent(Gt, get(S)) == 0){
            componentCount++;
        }
        movePrev(S);
    }

    fprintf(outfile, "G contains %d strongly connected components:\n", componentCount);

    List L = newList(); // Just to keep track

    moveBack(S);
    int count =  1;
    
    for (int i = 1; i < n+1; i++){
        prepend(L, get(S));
        if (getParent(Gt, get(S)) == 0){
            fprintf(outfile, "Component %d: ", count);
            printList(outfile, L);
            clear(L);
            count  += 1;
        }
        movePrev(S);
    }
    freeList(&L);

    // Freeing memory and closing files
    fclose(infile);
    fclose(outfile);
    freeGraph(&pG);
    freeGraph(&Gt);
    freeList(&S);
}