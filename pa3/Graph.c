/********************************************************************************* 
* Nicholas Chu, nchu5
* 2022 Spring CSE101 PA3
* Graph.c
* Contains the implementation of the Graph ADT and DFS.
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
    int* discover; // An array of ints whose ith element is the discover time stamp.  
    int* finish; // An array of ints whose ith element is the finish time stamp.
    int verticies; // Tracks number of verticies, or size
    int edges;  // Tracks number of edges, or order
} GraphObj;

/*** Constructors-Destructors ***/
// Function newGraph() returns a Graph pointing to a newly created GraphObj representing a graph having 
// n vertices and no edges.
Graph newGraph(int n){
    Graph pG = malloc(sizeof(GraphObj));
    // Filling neighbors with new empty Lists
    // Neighbors is used for adjacency lists
    pG->neighbors = calloc(n+1, sizeof(List));
    for (int i = 1; i < n+1; i++){
        pG->neighbors[i] = newList();
    }
    pG->color = calloc(n+1, sizeof(char));
    // Initializing parent with NIL before DFS
    pG->parent = calloc(n+1, sizeof(int));
    for (int i = 1; i < n+1; i++){
        pG->parent[i] = NIL;
    }
    // Initializing discover with UNDEF before DFS
    pG->discover = calloc(n+1, sizeof(int));
    for (int i = 1; i < n+1; i++){
        pG->discover[i] = UNDEF;
    }
    // Initializing finish with UNDEF before DFS
    pG->finish = calloc(n+1, sizeof(int));
    for (int i = 1; i < n+1; i++){
        pG->finish[i] = UNDEF;
    }
    pG->edges = 0;
    pG->verticies = n;
    return pG;
}

// Function freeGraph() frees all heap memory associated with the Graph *pG, 
// then sets the handle *pG to NULL.
void freeGraph(Graph* pG){
    for (int i = 1; i < (*pG)->verticies+1; i++){
        freeList(&((*pG)->neighbors[i]));
    }
    free((*pG)->neighbors);
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->discover);
    free((*pG)->finish);
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

// Return parent of vertex u
int getParent(Graph G, int u){
    if (1 > u || u > G->verticies || G->verticies != getOrder(G)){
        printf("Graph error: getParent() precondtitions not met.\n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}

int getDiscover(Graph G, int u){
    /* Pre: 1<=u<=n=getOrder(G) */
    if (1 > u || u > G->verticies || G->verticies != getOrder(G)){
        printf("Graph error: getDiscover() preconditions not met.\n");
        exit(EXIT_FAILURE);
    }
    return G->discover[u];
}

int getFinish(Graph G, int u){
    /* Pre: 1<=u<=n=getOrder(G) */
    if (1 > u || u > G->verticies || G->verticies != getOrder(G)){
        exit(EXIT_FAILURE);
    }
    return G->finish[u];
}
 
/*** Manipulation procedures ***/ 

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
    moveFront(G->neighbors[u]);
    // When adjacency list is empty just append or move through the list until right spot the insert
    if (length(G->neighbors[u]) == 0){
        append(G->neighbors[u], v);
        G->edges += 1;
    } else {
	for (int i = 0; i < length(G->neighbors[u]); i++){
		if (get(G->neighbors[u]) == v){
			return;
		} else {
			moveNext(G->neighbors[u]);
		}
	}
	moveFront(G->neighbors[u]);
        while (index(G->neighbors[u]) < length(G->neighbors[u])-1 && get(G->neighbors[u]) < v){
            moveNext(G->neighbors[u]);
        }

       if (get(G->neighbors[u]) < v){
           insertAfter(G->neighbors[u],v);
       } else {
           insertBefore(G->neighbors[u],v);
       }
       G->edges += 1;
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
    // Adding v to u
    moveFront(G->neighbors[u]);
    if (length(G->neighbors[u]) == 0){
        append(G->neighbors[u], v);
    } else {
        while (index(G->neighbors[u]) < length(G->neighbors[u])-1 && get(G->neighbors[u]) < v){
            moveNext(G->neighbors[u]);
        }
       if (get(G->neighbors[u]) < v){
           insertAfter(G->neighbors[u],v);
       } else {
           insertBefore(G->neighbors[u],v);
       }
    } 
    // Adding u to v
    moveFront(G->neighbors[v]);
    if (length(G->neighbors[v]) == 0){
        append(G->neighbors[v], u);
    } else {
        while (index(G->neighbors[v]) < length(G->neighbors[v])-1 && get(G->neighbors[v]) < u){
            moveNext(G->neighbors[v]);
        }
       if (get(G->neighbors[v]) < u){
           insertAfter(G->neighbors[v],u);
       } else {
           insertBefore(G->neighbors[v],u);
       }
    }
    G->edges += 1;
} 

// Private Visit function used in DFS
void Visit(Graph G, List S, int x, int* time){
    G->discover[x] = ++(*time); // First adds then evals, discovering an edge
    G->color[x] = 'g';
    moveFront(G->neighbors[x]);
    int y;
    while (index(G->neighbors[x]) >= 0){
        y = get(G->neighbors[x]); 
        if (G->color[y] == 'w'){
            G->parent[y] = x;
            Visit(G, S, y, time);
        }
        moveNext(G->neighbors[x]);
    }
    G->color[x] = 'b';
    G->finish[x] = ++(*time); 
    append(S, x); // Appends finished edge to stack
}

void DFS(Graph G, List S){
    /* Pre: length(S)==getOrder(G) */ 
    if (length(S) != getOrder(G)){
        printf("Graph Error: failed to meet precondtions in DFS().\n");
        exit(EXIT_FAILURE);
    }
    // Preforming DFS after all preconditions met
    // Setting up color, parent, and time
    for (int i = 1; i < getOrder(G)+1; i++){
        G->color[i] = 'w';
        G->parent[i] = NIL;
    }
    int time = 0;
    // Going through the verticies in adjacency list
    // Order depends on stack
    moveFront(S);
    int n = length(S);
    while (index(S) >= 0 && n > 0){
        int x = get(S);
        if (G->color[x] == 'w'){
            Visit(G, S, x, &time);
        }
        n--;
        moveNext(S);
        deleteFront(S);
    }
    // Reversing the List to turn it into to the correct stack
    moveBack(S);
    for (int i = getOrder(G); i > 0; i--){
        append(S, get(S));
        movePrev(S);
    }
    // printf("\n");
    for (int i = getOrder(G); i > 0; i--){
        deleteFront(S);
    }
    
}   
 
/*** Other operations ***/ 
Graph transpose(Graph G){
    // Function  transpose()  returns  a  reference  to  a  new  graph  object  representing  the  transpose  of  G
    Graph Gt = newGraph(getOrder(G));
    for (int u = 1; u < getOrder(G)+1; u++){
        moveFront(G->neighbors[u]);
        while (index(G->neighbors[u]) >= 0){
            addArc(Gt, get(G->neighbors[u]), u);
            moveNext(G->neighbors[u]);
        }
    }
    return Gt;
}
Graph copyGraph(Graph G){
    // Creates a new graph based off G's order (n)
    Graph cG = malloc(sizeof(GraphObj));
    cG->edges = getSize(G);
    cG->verticies = getOrder(G);
    
    // Creates copy of adjacency list
    cG->neighbors = calloc(getOrder(G)+1, sizeof(List));
    for (int i = 1; i < getOrder(G)+1; i++){
        cG->neighbors[i] = copyList(G->neighbors[i]);
    }
    return cG;

    // Creating copy of color array
    cG->color = calloc(getOrder(G)+1,sizeof(char));
    for (int i = 1; i < getOrder(G)+1; i++){
        cG->color[i] = G->color[i];
    }

    // Creating copy of parent array
    cG->parent = calloc(getOrder(G), sizeof(int));
    for (int i = 1; i < getOrder(G)+1; i++){
        cG->parent[i] = G->parent[i];
    }

    // Creating copy of discover array
    cG->discover = calloc(getOrder(G)+1, sizeof(int));
    for (int i = 1; i < getOrder(G)+1; i++){
        cG->discover[i] = G->discover[i];
    }

    // Creating copy of finish array
    cG->finish = calloc(getOrder(G)+1, sizeof(int));
    for (int i = 1; i < getOrder(G)+1; i++){
        cG->finish[i] = G->finish[i];
    }

    return cG;
} 

// Prints out adjacency list of Graph
void printGraph(FILE* out, Graph G){
    for (int i = 1; i < G->verticies+1; i++){
        fprintf(out, "%d: ", i);
        printList(out, G->neighbors[i]);
    } 
}