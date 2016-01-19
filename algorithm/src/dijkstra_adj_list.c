/*
 * An implementation of Dijkstra algorithm using binary heap in SPARSE GRAPHS using adjacency list prepresentation
 *
 * Warning: this implementation is not fully tested, use at your own risk
 * See http://www.giaithuatlaptrinh.com/?p=764 for more details.
 *
 *  Created on: Jan 19, 2016
 *     
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define INFTY 1000000000
// interfaces of the binary heap
int *H; 	// the Heap array
int hsize = 0; 	// the number of elements in the current Heap
int *pos;	// the array marks position of each vertex in the Heap array

//void insert(int x);
void up_heapify(int u);
int parent(int u);
void print_heap();
void decrease_key(int u, int K);
void down_heapify(int u);
int extract_min();
void build_heap(int n, int s);
// end interfaces of the binray heap

// we use linked lists to represent adjacency lists
// each arc u->v with weight w(u->v) is represented by a node with data field v and weight w in the adacency list of u

typedef struct vlist{
	int v;	// the head of the directed edge
	int w;	// the weight of the directed edge
	struct vlist *next;
}vlist;

vlist **G;	// G[i] is the adjacency list of vertex i
int n;		// the number of vertices of the graph
int *D;		// the distance array
int *P;		// the parent array
void read(); 	// read the input
void dijkstra_heap(vlist** G, int s, int n);
void print_array(int *A, int n);
void print_reverse_path(int t);
void add_edge(int u, int v, int weight);
void print_vertex_list(int u);

int main(){
	read();
//	int i = 0;
//	for(;i < n; i++) print_vertex_list(i);
	dijkstra_heap(G, n-1, n);	// s = n-1
	print_reverse_path(4);
	print_array(D,n);
}

void read(){
	n = 9;
	int i = 0, j = 0;
	G = (vlist **) malloc(n*sizeof(vlist*));
	for(; i < n; i++)G[i] = NULL;
	add_edge(1,0,2);	// add edge b->a of weight 2
	add_edge(8,0,4);	// add edge s->a of weight 4
	add_edge(0,3,2);	// add edge a->d of weight 2
	add_edge(1,2,1);	// add edge b->c of weight 1
	add_edge(8,1,1);	// add edge s->b of weight 1
	add_edge(2,5,3);	// add edge c->f of weight 3
	add_edge(2,4,7);	// add edge c->e of weight 7
	add_edge(2,3,5);	// add edge c->d of weight 5
	add_edge(8,2,3);	// add edge s->c of weight 3
	add_edge(3,5,1);	// add edge d->f of weight 1
	add_edge(3,6,3);	// add edge d->g of weight 3
	add_edge(3,8,4);	// add edge d->s of weight 4
	add_edge(4,6,2);	// add edge e->g of weight 2
	add_edge(4,7,2);	// add edge e->h of weight 2
	add_edge(5,4,5);	// add edge f->e of weight 5
	add_edge(5,6,1);	// add edge f->g of weight 1
	add_edge(6,7,8);	// add edge g->h of weight 8
}


void add_edge(int u, int v, int weight){
	vlist* vnode = (vlist *)malloc(sizeof(vlist));
	vnode->v = v;
	vnode->w = weight;
	vnode->next = NULL;
	if(G[u] == NULL){
		G[u] = vnode;
	} else {
		vnode->next = G[u];
		G[u] = vnode;
	}
}


void dijkstra_heap(vlist** G, int s, int n){
	P = (int *)malloc(n*sizeof(int));
	D = (int *)malloc(n*sizeof(int));
	int i = 0;
	for(; i < n; i++)D[i] = INFTY;
	D[s] = 0;
	P[s] = s;
	int v = 0;
	vlist *Ns = G[s];	// the list of neighbors of s
	while(Ns != NULL){	// iterating over neighbors of s
		v = Ns->v;
		D[v] = Ns->w;	// Ns->w = w(s->v)
		P[v] = s;
		Ns = Ns->next;
	}
	build_heap(n,s);
	int u;
	while(hsize != 0){ 	// the heap is not empty
		u = extract_min();
		vlist *Nu = G[u];	// the list of neighbors of u
		while(Nu != NULL){	// iterating over neighbors of u
			v = Nu->v;
			if(D[v] > D[u] + Nu->w){
				D[v] = D[u] + Nu->w;	// Nu->w = w(u->v)
				P[v] = u;
				decrease_key(v,D[v]);
			}
			Nu = Nu->next;	
		} 
	}
}


// print the shortest path from s to t in reversed order
void print_reverse_path(int t){	
	printf("%d ",t);
	while(P[t]!= t){
		t = P[t];
		printf("%d ",t);
	}
	printf("\n");
}

void print_array(int *A, int n){
	int i = 0;
	for(; i < n; i++){
		printf("%d ", A[i]);
	}
	printf("\n");

}

// print the adjacency list of a vertex u
// for debugging purpose only
void print_vertex_list(int u){
	vlist *it = G[u];
	while(it != NULL){
		printf("(%d,%d,%d) ",u,it->v, it->w);
		it = it->next;
	}
	printf("\n");
}

///////////////////////////////////////////////////////////////////////
///
///		BINARY HEAP IMPLEMENTATION		
///
//////////////////////////////////////////////////////////////////////


void up_heapify(int u){
	int v = parent(u);
	if(v != -1 && D[H[u]] < D[H[v]]){ // u is not the root of the heap
		int tmp = H[u];
		H[u] = H[v];
		pos[H[v]] = u;		// update the position of node H[v] in the Heap
		H[v] = tmp;
		pos[tmp] = v;		// update the position of node tmp in the Heap
		up_heapify(v);
	}
}

// Note that array in C is indexed from 0 
// Two children of a node u is 2u+1 and 2u+2, the smaller one is the left child

int parent(int u){
	return ((u&1)==0 ? ((u-2)>> 1) : (u-1) >> 1);
}



void print_heap(){
	int i = 0;
	for(; i < hsize; i++){
		printf("%d ", H[i]);
	}
	printf("\n");
}


void decrease_key(int u, int k){
	D[u] = k;
	up_heapify(pos[u]);
}

int extract_min(){
	int tmp  = H[0];
	H[0] = H[hsize-1];
	pos[H[0]] = 0;
	hsize--;
	down_heapify(0);
	return tmp;
}

void down_heapify(int u){
	int v = 2*u+1;
	int w = 2*u+2;
	int min = INFTY;
	int x = -1;
	if(v < hsize && D[H[u]] > D[H[v]]){
		min = D[H[v]];
		x = v;
	}
	if(w < hsize && D[H[u]] > D[H[w]] && D[H[w]] < min){
		x = w;
	}
	if(x != -1){
		int tmp = H[u];
		H[u] = H[x];
		pos[H[x]] = u; 		// update position of node H[x] in the Heap
		H[x] = tmp;
		pos[tmp] = x;		// update the position of node tmp in the Heap
		down_heapify(x);
	}
}

// Build the heap from an array in O(n) time
void build_heap(int n, int s){
	hsize = n-1;
	H = (int *)malloc(hsize*(sizeof(int)));
	pos = (int *)malloc(hsize*sizeof(int));
	int i = 0;
	for(; i < s; i++) {
		H[i] = i;
		pos[i] = i;
	}

	for(i = s+1; i < n; i++){
		H[i-1]=i;
		pos[i] = i-1;
	}
	for(i = hsize-1; i >=0; i--){
		down_heapify(i);
	}
}
