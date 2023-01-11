#include "Graph.h"

#include <stdio.h>
#include <stdlib.h>

void usage(){
    printf("./FindPath <input file> <output file>\n");
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
    
    // Getting size of graph from infile
    int n;
    fscanf(infile, "%d\n", &n);
    Graph pG = newGraph(n);
    
    // Scanning infile to create adjacency list of graph
    int u;
    int v;
    fscanf(infile, "%d %d", &u, &v);
    if (u > 0 && v > 0){
        addEdge(pG, u, v);
    }
    while (fscanf(infile, "%d %d", &u, &v) != EOF && (u != 0 && v != 0)){
        addEdge(pG, u, v);
    }
    printGraph(outfile, pG);
    fprintf(outfile, "\n");
    List path = newList();

    while (fscanf(infile, "%d %d", &u, &v) != EOF && (u != 0 && v != 0)){
        BFS(pG, u);
        if (getDist(pG, v) == INF){
            fprintf(outfile, "The distance from %d to %d is infinity\n", u ,v);
            fprintf(outfile, "No %d-%d path exists\n", u ,v);
        }
        if (getDist(pG, v) != INF){
            fprintf(outfile, "The distance from %d to %d is %d\n", u, v, getDist(pG, v));
            getPath(path, pG, v);
            fprintf(outfile, "A shortest %d-%d path is: ", u, v);
            printList(outfile, path);
        }
        clear(path);
        fprintf(outfile, "\n");
    }
    
    // Freeing memory and closing files
    freeList(&path);
    fclose(infile);
    fclose(outfile);
    freeGraph(&pG);
}