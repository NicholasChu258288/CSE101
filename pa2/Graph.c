/********************************************************************************* 
* Nicholas Chu, nchu5
* 2022 Spring CSE101 PA1
* Graph.c
* Contains the implementation of the Graph ADT.
*********************************************************************************/

// Includes -------------------------------------------------------------------
#include "List.h"
#include "Graph.h"

#include <stdio.h>
#include <stdlib.h>

// Structs
typedef struct GraphObj {
    List* neighbors; // An array of Lists whose ith element contains the neighbors of vertex i.
    char* color; // An array of chars whose ith element is the color (white, gray, black) of vertex i.    
    int* parent; // An array of ints whose ith element is the parent of vertex i.
    int* distance; // An array of ints whose ith element is the distance from the (most recent) source to vertex i.   
    int verticies; // Tracks number of verticies, or size
    int edges;  // Tracks number of edges, or order
    int recentSource; //Tracks most recent source used 
} GraphObj;

/*** Constructors-Destructors ***/
// Function newGraph() returns a Graph pointing to a newly created GraphObj representing a graph having 
// n vertices and no edges.
Graph newGraph(int n){
    Graph pG = malloc(sizeof(GraphObj));
    pG->edges = 0;
    pG->verticies = n;
    pG->recentSource = NIL;
    // Filling neighbors with new empty Lists
    // Neighbors is used for adjacency lists
    pG->neighbors = calloc(n, sizeof(List));
    for (int i = 0; i < n; i++){
        pG->neighbors[i] = newList();
    }
    // Creating color, actual colors will be filled in during BFS
    pG->color = calloc(n, sizeof(char));
    
    pG->distance = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++){
        pG->distance[i] = INF;
    }
    pG->parent = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++){
        pG->parent[i] = NIL;
    }
    return pG;
}

// Function freeGraph() frees all heap memory associated with the Graph *pG, 
// then sets the handle *pG to NULL.
void freeGraph(Graph* pG){
    for (int i = 0; i < (*pG)->verticies; i++){
        freeList(&((*pG)->neighbors[i]));
    }
    free((*pG)->neighbors);
    free((*pG)->color);
    free((*pG)->distance);
    free((*pG)->parent);
    free(*pG);
    *pG = NULL;
}
 
/*** Access functions ***/ 
int getOrder(Graph G){
    return G->verticies;
}

int getSize(Graph G){
    return G->edges;
}

int getSource(Graph G){
    // Finds vertex with distance 0 to get source
    return G->recentSource;
}

// Return parent of vertex u
int getParent(Graph G, int u){
    return G->parent[u-1];
}

// Returns distance of vertex u
int getDist(Graph G, int u){
    return G->distance[u-1];
}

void getPath(List L, Graph G, int u){
    // Precondition for when BFS has not been called 
    // Used psuedo-code from GraphAlgorithms examples
    if (u == getSource(G)){
        append(L,u);
    } else if (getParent(G,u) == NIL){
        append(L, NIL);
    } else {
        getPath(L,G,getParent(G,u));
        append(L, u);
    }
} 
 
/*** Manipulation procedures ***/ 
// Removes all edges from graph
void makeNull(Graph G){
    for (int i = 0; i < G->verticies; i++){
        clear(G->neighbors[i]);
    }
}
void addEdge(Graph G, int u, int v){
    // Preconditions
    if (1 > u && u > getOrder(G)){
        printf("Graph error: calling addEdge() with invalid u.");
        exit(EXIT_FAILURE);
    }
    if (1 > v && v > getOrder(G)){
        printf("Graph error: calling addEdge() with invalid v.");
        exit(EXIT_FAILURE);
    }
    // Adding edges to adjacency list(neighbors)
    append(G->neighbors[u-1], v);
    append(G->neighbors[v-1], u);
    G->edges += 1;
} 
void addArc(Graph G, int u, int v){
    // Preconditions
    if (1 > u && u > getOrder(G)){
        printf("Graph error: calling addArc() with invalid u.");
        exit(EXIT_FAILURE);
    }
    if (1 > v && v > getOrder(G)){
        printf("Graph error: calling addArc() with invalid v.");
        exit(EXIT_FAILURE);
    }
    // Adding directed edge to adjacency list(neighbors)
    append(G->neighbors[u-1], v);
    G->edges += 1;
}

void BFS(Graph G, int s){
    // First filling coloring all verticies white
    for (int i = 0; i < getOrder(G); i++){
        G->color[i] = 'w';
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    // Reason for -1 is to account for 0 indexing 
    G->color[s-1] = 'g';
    G->distance[s-1] = 0;
    G->parent[s-1] = NIL;
    G->recentSource = s;
    List Q = newList();
    append(Q, s);
    while (length(Q) != 0){
        moveFront(Q);
        int x = get(Q);
        deleteFront(Q);
        moveFront(G->neighbors[x-1]);
        
        int y;
        while (index(G->neighbors[x-1]) >= 0){
            y = get(G->neighbors[x-1]);
            moveNext(G->neighbors[x-1]);
            if (G->color[y-1] == 'w'){
                G->color[y-1] = 'g'; 
                G->distance[y-1] = G->distance[x-1] + 1;
                G->parent[y-1] = x;
                append(Q, y);
            }
        }
        G->color[x-1] = 'b';
        
    }
    freeList(&Q);
}
 
/*** Other operations ***/ 
// Prints out adjacency list of Graph
void printGraph(FILE* out, Graph G){
    for (int i = 0; i < G->verticies; i++){
        fprintf(out, "%d: ", i+1);
        printList(out, G->neighbors[i]);
    } 
}