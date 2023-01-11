/********************************************************************************* 
* Nicholas Chu, nchu5
* 2022 Spring CSE101 PA1
* Graph.c
* Header file for Graph ADT
*********************************************************************************/

// Includes -------------------------------------------------------------------
#pragma once
#include "List.h"

// Defining infinity and nil using different arbitrary negative num
// These will be used when implementing BFS
#define NIL -1
#define INF -2

// Public struct
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/ 
Graph newGraph(int n); 
void freeGraph(Graph* pG); 
 
/*** Access functions ***/ 
int getOrder(Graph G); 
int getSize(Graph G); 
int getSource(Graph G); 
int getParent(Graph G, int u); 
int getDist(Graph G, int u); 
void getPath(List L, Graph G, int u); 
 
/*** Manipulation procedures ***/ 
void makeNull(Graph G); 
void addEdge(Graph G, int u, int v); 
void addArc(Graph G, int u, int v); 
void BFS(Graph G, int s); 
 
/*** Other operations ***/ 
void printGraph(FILE* out, Graph G);