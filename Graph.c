// Name: Ruben Calderon
// CruzID: rucalder
// Date: November 24, 2019
// Pa4


#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"


typedef struct GraphObj{
        List* adjList;
	int order;
	int size;
	int source;
	int* color;
        int* p;
        int* d;
} GraphObj;

Graph newGraph(int n){

        Graph G = malloc(sizeof(GraphObj));

        G->adjList = calloc(n+1, sizeof(List));

        for(int i = 1; i <= n; i++){
                G->adjList[i] = newList();
        }

	//G->color = (int*)calloc(n+1, sizeof(int));
	//G->p = 
	
	G->color = calloc(n+1, sizeof(int));
	G->p = calloc(n+1, sizeof(int));
	G->d = calloc(n+1, sizeof(int));

	G->order = n;
	G->size = 0;
	G->source = NIL;

        return(G);
}

void freeGraph(Graph* pG){
	if(pG!=NULL && *pG!=NULL){
                for(int i = 1; i <= (*pG)->order; i++){
                        freeList(&((*pG)->adjList[i]));
                }
                free((*pG)->adjList);
                free((*pG)->color);
		free((*pG)->p);
		free((*pG)->d);
		free(*pG);
                *pG=NULL;
        }

}

/*** Access functions ***/
// getOrder
// returns order, or number of vertices, of graph
int getOrder(Graph G){
	if(G == NULL){
		printf("Graph Error: calling getOrder on null graph\n");
		exit(1);
	}
	
	return G->order;
}

// getSize
// returns size, or number of edges, of graph
int getSize(Graph G){
	if(G == NULL){
                printf("Graph Error: calling getSize on null graph\n");
                exit(1);
        }
	return G->size;
}

// getSource
// returns source of graph
int getSource(Graph G){
	if(G == NULL){
                printf("Graph Error: calling getSource on null graph\n");
                exit(1);
        }
	return G->source;
}


// getParent
// returns parent of vertex u
int getParent(Graph G, int u){
	if(G == NULL){
                printf("Graph Error: calling getParent on null graph\n");
                exit(1);
        }
	if(G->source == NIL){
		return NIL;
	}
	return (G->p[u]);
}


// getDist
// returns distance from vertex u to source vertex
int getDist(Graph G, int u){
	if(G == NULL){
                printf("Graph Error: calling getDist on null graph\n");
                exit(1);
        }
	if(getSource(G) == NIL){
		return INF;
	}
	return (G->d[u]);
}


// getPath
// returns shortest path from vertex u to source vertex
void getPath(List L, Graph G, int u){
	if(G == NULL){
                printf("Graph Error: calling getPath on null graph\n");
                exit(1);
        }
	if(getSource(G) == NIL){
		printf("Graph ERror: calling getPath on null path\n");
		exit(1);
	}
	//clear(L);
	int parent = G->p[u];
	
	if(u == getSource(G)){
		append(L, u);
	}
	else if(parent == NIL){
		append(L, NIL);
	}
	else{
		getPath(L, G, parent);
		append(L, u);
	}
}	



/*** Manipulation procedures ***/
// makeNull
// deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G){
	if(G == NULL){
                printf("Graph Error: calling getNull on null graph\n");
                exit(1);
        }
	//moveFront(G->adjList);
	for(int i = 1; i <= (G->order); i++){
		clear(G->adjList[i]);
		G->color[i] = 1;
		G->p[i] = NIL;
		G->d[i] = INF;
	}
	G->size = 0;
	G->source = NIL;
}


// addEdge
// inserts a new edge joining u to v. u is added to list of v, and vice verse.
// Must be inserted in sorted order
// pre: u and v be between 1 and order
void addEdge(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: calling addEdge on null graph\n");
                exit(1);
        }
	if(u < 1 || u > G->order){
		printf("Graph Error: calling addEdge on out of bounds u\n");
                exit(1);
        }
	if(v < 1 || v > G->order){
                printf("Graph Error: calling addEdge on out of bounds v\n");
                exit(1);
        }
	List listU = G->adjList[u];
	List listV = G->adjList[v];
	
	moveBack(listU);
	moveBack(listV);

	while(index(listU) != -1){
		if(get(listU) > v){
			if(index(listU) == 0){
				insertBefore(listU, v);
				moveFront(listU);
				movePrev(listU);
			}
			movePrev(listU);
		}
		else{
			insertAfter(listU, v);
			moveFront(listU);
			movePrev(listU);
		}
	}
	
	while(index(listV) != -1){
                if(get(listV) > u){
                        if(index(listV) == 0){
                                insertBefore(listV, u);
                                moveFront(listV);
                                movePrev(listV);
                        }
                        movePrev(listV);
                }
                else{
                        insertAfter(listV, u);
                        moveFront(listV);
                        movePrev(listV);
                }
        }


	
	if(length(listU) == 0){
		prepend(listU, v);
	}
	if(length(listV) == 0){
		prepend(listV, u);
	}
	G->size++;
}	


// addArc
// inserts a new directed edge from u to v. v is added to list of u.
// pre: u and v be between 1 and order
void addArc(Graph G, int u, int v){
	if(G == NULL){
                printf("Graph Error: calling addEdge on null graph\n");
                exit(1);
        }
        if(u < 1 || u > G->order){
                printf("Graph Error: calling addEdge on out of bounds u\n");
                exit(1);
        }
        if(v < 1 || v > G->order){
                printf("Graph Error: calling addEdge on out of bounds v\n");
                exit(1);
        }
        List listU = G->adjList[u];

        moveBack(listU);

        while(index(listU) != -1){
                if(get(listU) > v){
                        if(index(listU) == 0){
                                insertBefore(listU, v);
                                moveFront(listU);
                                movePrev(listU);
                        }
                        movePrev(listU);
                }
                else{
                        insertAfter(listU, v);
                        moveFront(listU);
                        movePrev(listU);
                }
        }
	if(length(listU) == 0){
		prepend(listU, v);
	}
	G->size++;
}




// BFS
// runs BFS algorithm on graph G with source S, setting color, distance, parent, and source fields of G respectively.
void BFS(Graph G, int s){
	for(int i = 1; i <= G->order; i++){
		/*if(i == s){
			i++;
		}*/
		G->color[i] = 1;
		G->d[i] = INF;
		G->p[i] = NIL;
	}
	G->color[s] = 2;
	G->d[s] = 0;
	G->p[s] = NIL;
	List Queue = newList();
	append(Queue, s);
	while(length(Queue) != 0){
		moveFront(Queue);
		int x = get(Queue);
		deleteFront(Queue);
		List adj = G->adjList[x];
		moveFront(adj);
		while(index(adj) != -1){
			int y = get(adj);
			if(G->color[y] == 1){
				G->color[y] = 2;
				G->d[y] = G->d[x] + 1;
				G->p[y] = x;
				append(Queue, y);
			}
			moveNext(adj);
		}
		G->color[x] = 3;
	}
	freeList(&Queue);
	G->source = s;
}


/*** Other operations ***/
// printGraph
// prints graph lmao what else
void printGraph(FILE* out, Graph G){
	if(G == NULL){
                printf("Graph Error: calling addEdge on null graph\n");
                exit(1);
        }
	List list;
	for(int i = 1; i <= G->order; i++){
		list = G->adjList[i];
		fprintf(out, "%d: ", i);
		moveFront(list);
		printList(out, list);
		/*while(index(list) != -1){
			if(index(list) != (length(list)-1)){
				fprintf(out, "%d, ", get(list));
			}
			else{
				fprintf(out, "%d", get(list));
			}
			moveNext(list);
		}*/
		fprintf(out, "\n");
	}
}















