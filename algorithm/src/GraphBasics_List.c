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
#define VISITED 1
#define TRUE 1
#define FALSE 0
#define INFTY 1000000



// the vertex list data structure, it is a linked list
typedef struct vlist{
	int v;		// vertex v is adjacent to the index of the list
	struct vlist *next;
}vlist;

vlist **G;
int n;		// the number of veritces
int m;		// the number of edges

int *D; 	// the distance of vertices from BFS
int* mark; 	// an array to mark visited vertices



void add_edge(int u, int v);		// add an arc u->v
void read();				// the interface to read the graph, you can modify to read from a file
void print_int_array(int *arr , int f, int l);
void print_vertex_list(int u);		// print the vertex-list of the vertex u
void print_list_graph();
void bfs(int s);
void dfs(int s);
void recursive_dfs(int s);
int connected_component();


typedef struct Stack {
	int *storage;
	int top;	
} Stack;

typedef struct Queue{
	int *storage;
	int back, front;
}Queue;
Queue *init_queue(int size);
void enqueue(Queue *Q, int elem); // push an element to the queue
int dequeue(Queue *Q); 		// take (and remove) an element from the queue
int is_queue_empty(Queue *Q);	

Stack *init_stack(int size);
void push(Stack *S, int elem); 	// push an element to the stack
int pop(Stack *S);  		// take (and remove) an element from the queue
int is_stack_empty(Stack *S);

int main (void){
	read();
	print_list_graph();
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
	G = (vlist **)malloc(n*sizeof(vlist*));
	int i = 0;
	for(; i < n; i++){
		G[i] = NULL;
	}
	add_edge(0,1);
	add_edge(0,2);
	add_edge(1,2);
	add_edge(4,5);
}


void bfs(int s){
	printf("executing bfs.....\n");
	D = (int *)(malloc(n*sizeof(int)));
	int i = 0;
	for(; i < n; i++) D[i] = INFTY;
	Queue *Q = init_queue(n);
	enqueue(Q,s);
	D[s] = 0;
	int u;
	int v;
	while(!is_queue_empty(Q)){
		u = dequeue(Q);
		if(mark[u] == UNVISITED){
			printf("visiting %d\n",u);
			mark[u] = VISITED;
			// loop through adjaceny list of u
			vlist *runner = G[u];
			while(runner != NULL){
				v = runner->v;
				if(mark[v] == UNVISITED){
					D[v] = D[u]+1;
					enqueue(Q,v);
				}
				runner = runner->next;
			}
		}
	}
	printf("done bfs\n");
}


void dfs(int s){
	printf("executing dfs.......\n");
	Stack *S = init_stack(n);
	push(S, s);
	int u;
	int v;
	while(!is_stack_empty(S)){
		u = pop(S);
		if(mark[u] == UNVISITED){
			printf("visiting %d\n",u);
			mark[u] = VISITED;
			// loop through neighbors of u
			vlist *runner = G[u];		// the ajdacency list of u
			while(runner!= NULL){
				v = runner->v;
				if(mark[v] == UNVISITED){
					push(S,v);
				}
				runner = runner->next;
			}
		}	
	}
	printf("done dfs\n");

}


void recursive_dfs(int s){
	printf("visiting %d\n",s);
	mark[s] = VISITED;
	// loop through neighbors of s
	vlist *runner = G[s];
	while(runner != NULL){ // examine all neighbors of s
		if(mark[runner->v] == UNVISITED){
			recursive_dfs(runner->v);
		}
		runner = runner->next;
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
		// edd v to the head of the  vertex list of u
		vlist *uedge = malloc(sizeof(vlist));
		uedge->v = v;
		uedge->next = G[u];
		G[u] = uedge; 
		// add u to the head of the vertex list of v
		vlist *vedge = malloc(sizeof(vlist));
		vedge->v = u;
		vedge->next = G[v];
		G[v] = vedge;
	}

void print_vertex_list(int u){
		printf("adj list of %d : ",u);
		vlist *it = G[u];
		while(it != NULL){
			printf("%d ", it->v);
			it = it->next;
		}
		printf("\n");
}

void print_list_graph(){
	printf("num vertices: %d\n", n);
	printf("num edges: %d\n", m);
	int i = 0;
	for(; i < n; i++){
		print_vertex_list(i);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////
////////////////	THE QUEUE INTERFACES
////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Queue *init_queue(int size){
	Queue *Q = malloc(sizeof(Queue));
	Q->storage = (int *)malloc(size*sizeof(int));
	Q->front = 0;
	Q->back = -1;
	return Q;
}
void enqueue(Queue *Q, int elem){
	Q->back ++;
	Q->storage[Q->back] = elem;
}
int dequeue(Queue *Q){
	if(is_queue_empty(Q)) {
		printf("nothing to dequeue\n");
		exit(0);
	}
	int elem = Q->storage[Q->front];
	Q->front++;
	return elem;
}

int is_queue_empty(Queue* Q){
	return Q->back < Q->front? TRUE : FALSE;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////
////////////////	THE STACK INTERFACES
////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Stack *init_stack(int size){
	Stack *S = (Stack *)malloc(sizeof(Stack));
	S->top = -1;
	S->storage = (int*)malloc(size*sizeof(int));
	return S;
}

void push(Stack *S, int elem){
	S->top++;
	S->storage[S->top] = elem;
}
int pop(Stack *S){
	if(is_stack_empty(S)){
		printf("nothing to pop\n");
		exit(0);
	}
	int elem = S->storage[S->top];
	S->top--;
	return elem;
}

int is_stack_empty(Stack *S){
	return S->top < 0 ? TRUE: FALSE;
}

void print_int_array(int *arr , int f, int l){
	int i = 0;
	for (i = f ; i <= l  ; i++){
		printf("%d,", arr[i]);
	}
	printf("\n");
}


