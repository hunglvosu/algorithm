/*
 * An implementation of DIRECTED ACYCLIC GRAPH CHECKER with list representation
 * See http://www.giaithuatlaptrinh.com/?p=590 for more details.
 *
 * This implementation is not fully tested. Use at your own risk
 *
 *  Created on: March 9, 2016
 *      Author: hunglv
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define UNVISITED 0
#define VISITING 1
#define VISITED 2
#define INFTY 1000000



// the vertex list data structure, it is a linked list
typedef struct vlist{
	int v;		// vertex v is adjacent to the index of the list
	struct vlist *next;
}vlist;

vlist **G;
int n;		// the number of veritces
int m;		// the number of edges

int* mark; 	// an array to mark visited vertices



void add_arc(int u, int v);		// add an arc u->v
void read();				// the interface to read the graph, you can modify to read from a file
void print_int_array(int *arr , int f, int l);
void print_vertex_list(int u);		// print the vertex-list of the vertex u
void print_list_graph();
void dag_checker();
void dfs_checker(int s);
vlist *find_sources();

int main (void){
	read();
	print_list_graph();
	dag_checker();
	return 0;
}

// read the set of edges: (0-1), (1-2), (2-0), (4-5)
void read(){
	n = 11; 	
	m = 19;
	G = (vlist **)malloc((n+1)*sizeof(vlist*));	// allocate one more list to add a vertex s later
	int i = 0;
	for(; i < n+1; i++){
		G[i] = NULL;
	}
	add_arc(0,1);		// add arc a->b
	add_arc(0,2);		// add arc a->c
	add_arc(0,4);		// add arc a->e
	add_arc(1,2);		// add arc b->c
	add_arc(2,3);		// add arc c->d
	add_arc(1,3);		// add arc b->d	
	//add_arc(3,1);		// add arc d->b		uncomment this to make the graph non-dag
	add_arc(4,3);		// add arc e->d
	add_arc(4,6);		// add arc e->g
	add_arc(4,7);		// add arc e->h
	add_arc(5,4);		// add arc f->e
	add_arc(5,6);		// add arc f->g
	add_arc(5,9);		// add arc f->j
	add_arc(6,8);		// add arc g->i
	add_arc(7,3);		// add arc h->d
	add_arc(7,6);		// add arc h->g
	add_arc(7,8);		// add arc h->i
	add_arc(9,8);		// add arc j->i
	add_arc(10,5);		// add arc k->f
	add_arc(10,9);		// add arc k->j
}

void dag_checker(){
	vlist *S = find_sources();
	mark = (int *)malloc((n+1)*sizeof(int));
	memset(mark, UNVISITED, (n+1)*sizeof(int));
	int s = n;	// the new added vertex s
	while(S != NULL){
		add_arc(s,S->v);
		S = S->next;
	}
	
	printf("checking dag graph.....\n");
	dfs_checker(s);
	printf("The input graph is a DAG\n");

}
void dfs_checker(int u){
	printf("visiting %d\n",u);
	mark[u] = VISITING;
	// loop through neighbors of u
	vlist *runner = G[u];
	int v;
	while(runner != NULL){ // examine all neighbors of s
		v = runner->v;
		if(mark[v] == VISITING){
			printf("The input graph is non-dag\n");
			exit(0);
		} else if(mark[v] == UNVISITED){
			dfs_checker(v);
		}
		runner = runner->next;
	}
	mark[u] = VISITED;
}


// we use vlist as a linked list of sources
vlist *find_sources(){
	int *M = (int *)malloc(n*sizeof(int));	// array M to mark which vertex is not a source
	memset(M,0,n*sizeof(int));				
	// loop through all edges of G to find sources
	int u = 0;
	vlist *nbrRunner;		
	for(; u < n; u++){
		nbrRunner = G[u];
		while(nbrRunner != NULL){
			M[nbrRunner->v] = 1;	// v is not a source
			nbrRunner = nbrRunner->next;
		}
	}
	
	vlist *head = NULL;	// the head of the source list
	
	for( u = 0; u < n; u++){
		if(M[u] == 0){	// u is a source
			vlist *node  = malloc(sizeof(vlist));
			node->v = u;
			node->next = head;
			head = node;
		}		
	}
	return head;
}
// add an arc u->v
void  add_arc(int u, int v){
		// edd v to the head of the  vertex list of u
		vlist *node  = malloc(sizeof(vlist));
		node->v = v;
		node->next = G[u];
		G[u] = node; 
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


void print_int_array(int *arr , int f, int l){
	int i = 0;
	for (i = f ; i <= l  ; i++){
		printf("%d,", arr[i]);
	}
	printf("\n");
}


