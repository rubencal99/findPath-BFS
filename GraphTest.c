// Name: Ruben Calderon
// CruzID: rucalder
// Date: November 24, 2019
// Pa4

#include<stdio.h>
#include<stdlib.h>
//#include"List.h"
#include"Graph.h"
#include <string.h>

int main(int argc, char* argv[]){

	Graph G = newGraph(5);
	
	addEdge(G, 1, 2);
	addEdge(G, 3, 4);
	addEdge(G, 1, 3);
	addEdge(G, 2, 4);
	addEdge(G, 3, 2);
	addEdge(G, 4, 5);

	printGraph(stdout, G);
	printf("%d\n", getParent(G, 1));
	
	printf("Running BFS, source 1\n");
	BFS(G, 1);
	printf("Parent of 1: %d\n", getParent(G, 1));
	printf("Parent of 2: %d\n", getParent(G, 2));
	printf("Parent of 5: %d\n", getParent(G, 5));
	printf("Source of G: %d\n", getSource(G));

	freeGraph(&G);
	return(0);
}
