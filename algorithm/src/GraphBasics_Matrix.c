/*
 * An implementation of UNDIRECTED GRAPH  traversal with list representation
 * See http://www.giaithuatlaptrinh.com/?p=553 for more details.
 *
 *  Created on: Oct 3, 2015
 *      Author: hunglv
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define UNVISITED 0
#define VISITING 1
#define VISITED 2
#define INFTY 1000000




int **G;	// the adjacency matrix
int n;		// the number of veritces
int m;		// the number of edges

int *D; 	// the distance of vertices from BFS
int* mark; 	// an array to mark visited vertices



void add_edge(int u, int v);		// add an arc u->v
void read();				// the interface to read the graph, you can modify to read from a file
void print_int_array(int *arr , int f, int l);
void print_graph();
void bfs(int s);
void dfs(int s);
void recursive_dfs(int s);
int connected_component();


int *Cq; 		// simple array queue implementation of C for bfs
int qfirst, qend;
void enqueue(int elem); // push an element to the queue
int dequeue(); 		// take (and remove) an element from the queue
int is_queue_empty();	


int *Cs; 		// simple array stack implementation of C for dfs;
int stop; 		// the top of the stack
void push(int elem); 	// push an element to the stack
int pop();  		// take (and remove) an element from the queue
int is_stack_empty();

int main (void){
	read();
	print_graph();
	mark = (int *)malloc(n*sizeof(int));
	int s = 0;
	memset(mark, UNVISITED, n*sizeof(int));
	bfs(s);
	printf("distance label from %d: ",s);
	print_int_array(D, 0, n-1);
	memset(mark, UNVISITED, n*sizeof(int));
	dfs(s);
	memset(mark, UNVISITED, n*sizeof(int));
	printf("executing recursive dfs.....\n");
	recursive_dfs(0);
	printf("done recursive dfs\n");
//	memset(mark, UNVISITED, (n+1)*sizeof(int));
	printf("counting connected components.......\n");
	printf("the number of connected components: %d\n", connected_component());
	return 0;
}

// read the set of edges: (0-1), (1-2), (2-0), (4-5)
void read(){
	n = 6; 	
	m = 4;
	G = (int **)malloc(n*sizeof(int*));
	int i = 0;
	for(; i < n; i++){
		G[i] = (int *)malloc(n*sizeof(int));
		memset(G[i], 0, n*sizeof(int));
	}
	add_edge(0,1);
	add_edge(0,2);
	add_edge(1,2);
	add_edge(4,5);
}


void bfs(int s){
	printf("executing bfs from %d.....\n",s);
	D = (int *)(malloc(n*sizeof(int)));
	int i = 0;
	for(; i < n; i++) D[i] = INFTY;

	Cq = (int *)malloc(n*sizeof(int));
	enqueue(s);
	D[s] = 0;
	int u;
	int v;
	while(!is_queue_empty()){
		u = dequeue();
		printf("visiting %d\n",u);
		mark[u] = VISITED;
		// loop through neighbors of u
		for(v = 0; v < n; v++){
			if(G[u][v] == 1 && mark[v] == UNVISITED){
				mark[v] = VISITING;
				D[v] = D[u]+1;
				enqueue(v);
			}

		}

	}
	printf("done bfs\n");
}


void dfs(int s){
	printf("executing dfs from %d.......\n",s);
	/*Initialize the stack*/
	Cs = (int *)malloc(n*sizeof(int));
	stop = -1;
	push(s);
	int u;
	int v;
	while(!is_stack_empty()){
		u = pop();
		printf("visiting %d\n",u);
		mark[u] = VISITED;
		// loop through neighbors of u
		for(v = 0; v < n; v ++){
			if(G[u][v] == 1 && mark[v] == UNVISITED){
				mark[v] = VISITING;
				push(v);
			}
		}
	}
	printf("done dfs\n");
}


void recursive_dfs(int s){
	printf("visiting %d\n",s);
	mark[s] = VISITED;
	// loop through neighbors of s
	int v = 0;
	for(; v < n; v++){
		if(G[s][v] == 1 && mark[v] == UNVISITED){
			recursive_dfs(v);
		}
	}

}



int connected_component(){
	memset(mark, UNVISITED, (n+1)*sizeof(int)); // mark all vertices unvisited
	int s = 0;
	int count = 0;
	for(; s < n; s++){
		if(mark[s] == UNVISITED){
			bfs(s);
			count++;
		}
	}
	return count;
}


void  add_edge(int u, int v){
		G[u][v] = 1;
		G[v][u] = 1;
	}

void print_graph(){
	int u  = 0;
	int v = 0;
	for(; u < n; u++)print_int_array(G[u], 0, n-1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////
////////////////	THE QUEUE INTERFACES
////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void enqueue(int elem){
	Cq[qend] = elem;
	qend++;
}
int dequeue(){
	if(is_queue_empty()) {
		printf("nothing to dequeue\n");
		exit(0);
	}
	int elem = Cq[qfirst];
	qfirst++;
	return elem;
}

int is_queue_empty(){
	return qfirst < qend? 0 : 1;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////
////////////////	THE STACK INTERFACES
////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void push(int elem){
	stop++;
	Cs[stop] = elem;
}
int pop(){
	if(is_stack_empty()){
		printf("nothing to pop\n");
		exit(0);
	}
	int elem = Cs[stop];
	stop--;
	return elem;
}

int is_stack_empty(){
	return stop < 0 ? 1: 0;
}


void print_int_array(int *arr , int f, int l){
	int i = 0;
	for (i = f ; i <= l  ; i++){
		printf("%d,", arr[i]);
	}
	printf("\n");
}


