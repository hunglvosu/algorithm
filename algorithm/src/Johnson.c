/*
 * An implementation of Johnson algorithm using binary heap in SPARSE GRAPHS using adjacency list prepresentation
 *
 * Warning: this implementation is not fully tested, use at your own risk.
 * See http://www.giaithuatlaptrinh.com/?p=874 for more details.
 *
 *  Created on: March 10, 2016
 *  Author: Hung Le
 */   
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
	int v;		// the head of the directed edge
	int w;		// the original weight of the directed edge
	int Delta;	// the modified weight using potential
	struct vlist *next;
}vlist;

vlist **G;				// G[i] is the adjacency list of vertex i
int n;					// the number of vertices of the graph
int **D;				// the all-pair distance array of Johnson algorithm
int *d;					// the distance array for Dijkstra's algorithm
void read(); 				// read the input
void add_arc(int u, int v, int w);	// add an u->v arc of weight w
int *bellman_ford(vlist **G, int s, int n);
void dijkstra_heap(vlist** G, int s, int n);
int  **johnson();

void print_array(int *A, int n);
void print_list_graph();
void print_vertex_list(int u);
int main(){
	read();
	print_list_graph();
	D = johnson();
	printf("all-pair distances found by Johnson's algorithm\n");
	int i = 0;
	for(; i < n; i++) print_array(D[i], n);
}

int **johnson(){
	int s = n;				// add a new vertex s
	int u = 0, v = 0;
	for(; u < n; u++){
		add_arc(s,u,0);			// add an arc s->u of weight 0		
	}
	int *P = bellman_ford(G,s,n+1);		// the distance array from Bellman-Ford algorithm
	//loop through all arcs of G
	for(u = 0; u < n; u++){
		vlist *nbrs = G[u];		// the head of the list of neighbors of u
		while(nbrs != NULL){
			v = nbrs->v;
			nbrs->Delta = nbrs->w + P[u] - P[v];	// the modified weight
			nbrs = nbrs->next;		
		}
	}
	printf("the graph after weight modification\n");
	print_list_graph();
	H = (int *)malloc((n-1)*(sizeof(int)));		// initialize the heap
	pos = (int *)malloc((n-1)*sizeof(int));
	
	int **D = (int **) malloc(n*sizeof(int*));		// initialize the all-pairs distance array ;
	d = (int *)malloc(n*sizeof(int));			// initialize the distance array for Dijkstra;
	for( u = 0; u < n; u++){
		D[u] = (int *)malloc(n*sizeof(int));		
		dijkstra_heap(G, u, n);	 	// the shortest distances from u to other vertices are stored in array d
		for(v = 0; v < n; v++){
			D[u][v] = d[v] + P[v] - P[u];	// the real u to v distance		
		}
	}
	
	return D;
}


// The Bellman-Ford algorithm. See http://www.giaithuatlaptrinh.com/?p=789 for more details

int *bellman_ford(vlist **G, int s, int n){
	int* D = (int *)malloc(n*sizeof(int));
	int i = 0;
	for(; i < n; i++)D[i] = INFTY;
	D[s] = 0;
	int v = 0;
	vlist *nbrs = G[s];	// the list of neighbors of s
	while(nbrs != NULL){	// iterating over neighbors of s
		v = nbrs->v;
		D[v] = nbrs->w;	// nbrs->w = w(s->v)
		nbrs = nbrs->next;
	}
	int  u = 0;
	for(i = 0; i < n-2; i++){
			for(u = 0; u < n; u++){
				vlist *nbrs = G[u];	// the list of neighbors of u
				while(nbrs != NULL){	// iterating over neighbors of u
					v = nbrs->v;
					if(D[v] > D[u] + nbrs->w){	// the arc u->v is tense
						D[v] = D[u] + nbrs->w;	// nbrs->w = w(u->v)
					}
				nbrs = nbrs->next;	
				} 
			}
	}
	return D;
}


// The Dijkstra algorithm with Binary Heap. See  http://www.giaithuatlaptrinh.com/?p=764 for more details
// Note here that we are running Dijkstra with new weight function Delta
void dijkstra_heap(vlist** G, int s, int n){
	int i = 0;
	for(; i < n; i++)d[i] = INFTY;
	d[s] = 0;
	int v = 0;
	vlist *nbrs = G[s];	// the list of neighbors of s
	while(nbrs != NULL){	// iterating over neighbors of s
		v = nbrs->v;
		d[v] = nbrs->Delta;	// nbrs->Delta = Delta(s->v)
		nbrs = nbrs->next;
	}
	build_heap(n,s);
	int u;
	while(hsize != 0){ 	// the heap is not empty
		u = extract_min();
		vlist *nbrs = G[u];	// the list of neighbors of u
		while(nbrs != NULL){	// iterating over neighbors of u
			v = nbrs->v;
			if(d[v] > d[u] + nbrs->Delta){
				d[v] = d[u] + nbrs->Delta;	// nbrs->w = w(u->v)
				decrease_key(v,d[v]);
			}
			nbrs = nbrs->next;	
		} 
	}
}


void read(){
	n = 6;
	int i = 0, j = 0;
	G = (vlist **) malloc((n+1)*sizeof(vlist*));		// we preserve a slot for added vertex s
	for(; i < n+1; i++)G[i] = NULL;
	add_arc(0,2,-1);	// add arc a->c of weight -1
	add_arc(1,0,5);		// add arc b->a of weight 5
	add_arc(2,0,3);		// add arc c->a of weight 3
	add_arc(2,1,-3);	// add edge c->b of weight -3
	add_arc(2,4,11);	// add edge c->e of weight 11
	add_arc(3,0,-6);	// add edge d->a of weight -6
	add_arc(4,3,-3);	// add edge e->d of weight -3
	add_arc(4,5,4);		// add edge e->f of weight 4
	add_arc(5,1,-4);	// add edge f->b of weight -4
	add_arc(5,2,1);		// add edge f->c of weight 1

}


//	add an arc u->v to the graph with weight w
void add_arc(int u, int v, int w){
	// append v to the head of the adjacency list of u
	vlist* vnode = (vlist *)malloc(sizeof(vlist));
	vnode->v = v;
	vnode->w = w;
	vnode->Delta = -1;	// Delta is undefined
	vnode->next = G[u];
	G[u] = vnode;
}




///////////////////////////////////////////////////////////////////////
///
///		BINARY HEAP IMPLEMENTATION		
///
//////////////////////////////////////////////////////////////////////


void up_heapify(int u){
	int v = parent(u);
	if(v != -1 && d[H[u]] < d[H[v]]){ // u is not the root of the heap
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
	d[u] = k;
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
	int m = 2*u+1;
	if(m < hsize){	// u is not a leaf of the heap
		if(2*u+2 < hsize && d[H[m]] > d[H[2*u+2]]){
			m = 2*u+2;		
		}
		if(d[H[u]] > d[H[m]]){
			int tmp = H[u];
			H[u] = H[m];
			pos[H[m]] = u;	// update position of node H[m] in the Heap
			H[m] = tmp;
			pos[tmp] = m;	// update the position of node tmp in the Heap
			down_heapify(m);		
		}
	}
}

// Build the heap from an array in O(n) time
void build_heap(int n, int s){
	hsize = n-1;
	memset(H,-1,hsize*sizeof(int));		// clear the heap
	memset(pos, -1, hsize*sizeof(int));	// clear the post array
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

///////////////////////////////////////////////////////////////////////
//////////////////////
//////////////////////	PRINTING INTERFACE FOR DEBUGGING
//////////////////////
//////////////////////////////////////////////////////////////////////


void print_list_graph(){
	int u = 0;
	for(; u < n; u++){
		print_vertex_list(u);
	}	
}
// for debugging purpose only
void print_vertex_list(int u){
	vlist *it = G[u];
	while(it != NULL){
		printf("(%d->%d,%d,%d) ",u,it->v, it->w, it->Delta);
		it = it->next;
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
