/*
 * An implementation of arc classfication  with list representation
 * See http://www.giaithuatlaptrinh.com/?p=590 for more details.
 * Warning: This implementation is not fully tested. Use at your own risk.
 *
 *  Created on: March 8, 2018
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

int *L; 	
int *P;		// to trace the path between s and t
int* mark; 	// an array to mark visited vertices



void add_arc(int u, int v);		// add an arc u->v
void read();				// the interface to read the graph, you can modify to read from a file
void print_int_array(int *arr , int f, int l);
void print_vertex_list(int u);		// print the vertex-list of the vertex u
void print_list_graph();
void recursive_dfs(int s);
void dfs_all();
void print_reverse_path(int v, int *P);

int main (void){
	read();
	print_list_graph();
	mark = (int *)malloc(n*sizeof(int));
	memset(mark, UNVISITED, n*sizeof(int));
	L = (int*)malloc(n*sizeof(int));
	P = (int *)malloc(n*sizeof(int));
	printf("executing recursive dfs.....\n");
	dfs_all();
	printf("done recursive dfs\n");
	print_reverse_path(2, P);
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
	add_arc(3,1);		// add arc d->b
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


void dfs_all(){
	int u = 0;
	for(; u < n; u++){
		if(mark[u] == UNVISITED){
			P[u] = u;
			L[u] = u;
			recursive_dfs(u);			
		}
	}
}
void recursive_dfs(int u){
	printf("visiting %d\n",u);
	mark[u] = VISITING;
	// loop through neighbors of s
	vlist *runner = G[u];
	int v;
	while(runner != NULL){ // examine all neighbors of s
		v = runner->v;
		if(mark[v] == VISITING){
			printf("arc (%d->%d) is a back arc\n", u,v);
		} else if(mark[v] == VISITED){
			printf("arc (%d->%d) is a cross arc or a forward arc\n", u,v);
		} else {		// mark[v] == UNVISITED
			printf("arc (%d->%d) is a tree arc\n", u,v);
			P[v] = u;
			L[v] = L[u];
			recursive_dfs(v);
		}
		runner = runner->next;
	}
	mark[u] = VISITED;

}

// print the dfs path from a vertex v to its source

void print_reverse_path(int v, int *P){
	while(v != P[v]){
		printf("%d ",v);
		v = P[v];
	}
	printf("%d\n",v);
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


