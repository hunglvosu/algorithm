/*
 * An implementation of TOPOLOGICAL SORT OF A DAG with list representation
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
#define TRUE 1
#define FALSE 0


// the vertex list data structure, it is a linked list
typedef struct vlist{
	int v;		// vertex v is adjacent to the index of the list
	struct vlist *next;
}vlist;

vlist **G;		// G[u] is the adjacency list of G
int n;		// the number of veritces
int m;		// the number of edges



void add_arc(int u, int v);		// add an arc u->v
void read();				// the interface to read the graph, you can modify to read from a file
void print_int_array(int *arr , int f, int l);
void print_vertex_list(int u);		// print the vertex-list of the vertex u
void print_list_graph();
vlist *find_sources();
int *find_din();
int *topo_sort();

int main (void){
	read();
	print_list_graph();
	int *Ts = topo_sort();
	print_int_array(Ts,0,n-1);
	return 0;
}

// read the set of edges: (0-1), (1-2), (2-0), (4-5)
void read(){
	n = 11; 	
	m = 19;
	G = (vlist **)malloc(n*sizeof(vlist*));	
	int i = 0;
	for(; i < n; i++){
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

int *topo_sort(){
	int *Del = (int *)malloc(n*sizeof(int));
	memset(Del, FALSE, n*sizeof(int));

	int *Din = find_din();				// find in-degree of all vertices

	int *Ts = (int *)malloc(n*sizeof(int));		// the topological order
	memset(Ts, 0, n*sizeof(int));

	vlist *S = find_sources();
	int i = 1;
	int s;
	while(S != NULL){
		s = S->v;
		S = S->next;	// remove s from S
		Ts[s] = i;
		i++;
		Del[s] = TRUE;
		// loop through all neighbors of s;
		vlist *runner = G[s];
		int v;
		while(runner != NULL){
			v = runner->v;
			Din[v] --;
			if(Din[v] == 0){
				// add v to S
				vlist *node = malloc(sizeof(vlist));
				node->v = v;
				node->next = S;
				S = node;
			}		
			runner = runner->next;
		}
	}
	return Ts;

}

int *find_din(){
	int *Din = (int *)malloc(n*sizeof(int));
	memset(Din, 0, n*sizeof(int));
	// loop through all edges of G to find in-degree of vertices
	int u = 0;
	vlist *nbrRunner;	
	for(; u < n; u++){
		nbrRunner = G[u];
		while(nbrRunner != NULL){
			Din[nbrRunner->v] ++;
			nbrRunner = nbrRunner->next;
		}
	}
	return Din;
}
// we use vlist as a linked list of sources
vlist *find_sources(){
	int *M = (int *)malloc(n*sizeof(int));	// array M to mark which vertex is not a source
	memset(M,0,n*sizeof(int));				
	// loop through all edges of G to find sources
	int u = 0;
	vlist *nbrRunner;		
	for(; u < n; u++){
		nbrRunner = G[u];		// the list of out-neighbors of u
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


