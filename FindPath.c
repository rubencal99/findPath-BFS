// Name: Ruben Calderon
// CruzID: rucalder
// Date: November 24, 2019
// Pa4


#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"



int main(int argc, char* argv[]){

        if(argc != 3){
                fprintf(stderr, "Error: Incorrect amount of command line arguments.\n");
                exit(1);
        }

        FILE* in;
        FILE* out;
        in = fopen(argv[1], "r");
        out = fopen(argv[2], "w");
        if(in == NULL){
                fprintf(stderr, "Error: input file not found.\n");
                exit(1);
        }
	
	int numV;
	fscanf(in, "%d\n", &numV);
	Graph G = newGraph(numV);
	
	//char temp[4];
	int v1;
	int v2;
	int t =1;
	while(t == 1){
		fscanf(in, "%d %d\n", &v1, &v2);
		if(v1 == 0 && v2 == 0){
			break;
		}
		
		addEdge(G, v1, v2);
	}
	
	printGraph(out, G);
	
	fprintf(out, "\n");
	t = 1;
	while(t == 1){
		fscanf(in, "%d %d\n", &v1, &v2);
		if(v1 == 0 && v2 == 0){
                        break;
                }
		BFS(G, v1);
		List L = newList();
		getPath(L, G, v2);
		moveFront(L);
		if(get(L) != v1){
			fprintf(out, "The distance from %d to %d is infinity\n", v1, v2);
			fprintf(out, "No %d-%d path exists\n", v1, v2);
			//continue;
		}
		else{
			fprintf(out, "The distance from %d to %d is %d\n", v1, v2, getDist(G, v2));
			fprintf(out, "A shortest %d-%d path is: ", v1, v2);
			while(index(L) != -1){
				fprintf(out, "%d ", get(L));
				moveNext(L);
			}
		}
		fprintf(out, "\n");
		fprintf(out, "\n");
	}
	freeGraph(&G);	
	return(0);
}
