/*
 * An implementation of graph representation and traversal.
 * See http://www.giaithuatlaptrinh.com/?p=553 for more details.
 *
 *  Created on: Oct 3, 2015
 *      Author: hunglv
 */


#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "utilities.h"
#include "numbers.h"
#include "graphs.h"


int *L; // label of vertices from BFS
edge *Cq; // simple array queue implementation of C for bfs
int qfirst, qend;
int *Cs; // simple array stack implementation of C for dfs;
int stop; // the top of the stack
int* mark;

void enqueue(edge *Cq, edge elem);
edge dequeue(edge *Cq);
int is_queue_empty();

void push(int *Cs, int elem);
int pop(int *Cs);
int is_stack_empty();


int main (void){
	edge E[7] = {{1,2}, {1,4}, {1,6}, {2,3}, {2,4}, {3,5}, {5,6}};
	int n = 6, m = 7;
	lgraph = new_list_graph(n,m,E);
	mark = (int *)(malloc((n+1)*sizeof(int)));
	print_list_graph(lgraph);
	L = (int *)(malloc((n+1)*sizeof(int)));
	Cq = (edge *)malloc((2*m)*sizeof(edge));
	Cs = (int *)malloc((2*lgraph.m)*sizeof(int));
	bfs_list_graph(1);
	printf("label:");
	print_int_array(L, 1, n);
	dfs_list_graph(1);
	memset(mark, UNVISITED, (n+1)*sizeof(int));
	recursive_dfs_list_graph(1);
	mgraph = new_matrix_graph(n,m,E);
	bfs_matrix_graph(1);
	dfs_matrix_graph(1);
	memset(mark, UNVISITED, (n+1)*sizeof(int));
	recursive_dfs_matrix_graph(1);
	return 0;
}

void bfs_list_graph(int s){
	qfirst = 0; qend = 0;
	int n = lgraph.n, m = lgraph.m;
	memset(mark, UNVISITED, (n+1)*sizeof(int));
	Cq = (edge *)malloc((2*m)*sizeof(edge));
	edge e = {0,s}; // -1 represent empty;
	L[s] = 0; L[0] = -1;
	enqueue(Cq, e);
	int p,u;
	vlist ulist;
	while(!is_queue_empty()){
		e = dequeue(Cq);
		p = e.u; u = e.v;
		if(mark[u] == UNVISITED){
			printf("visiting: %d\n",u);
			mark[u] = VISITED;
			L[u] = L[p] + 1;
			ulist = lgraph.vlists[u];
			vnode *it = ulist.head->next;
			while(it != NULL){
				if(mark[it->id] == UNVISITED){
					e.u = u; e.v = it->id;
					enqueue(Cq,e);
				}
				it = it->next;
			}
		}
	}

}

void bfs_matrix_graph(int s){
	qfirst = 0; qend = 0;
	int n = mgraph.n;
	memset(mark, UNVISITED, (n+1)*sizeof(int));
	edge e = {0,s}; // 0 represent empty;
	L[s] = 0; L[0] = -1;
	enqueue(Cq, e);
	int p,u,v;
	while(!is_queue_empty()){
		e = dequeue(Cq);
		p = e.u; u = e.v;
		if(mark[u] == UNVISITED){
			printf("visiting: %d\n",u);
			mark[u] = VISITED;
			L[u] = L[p] + 1;
			for(v = 1; v <= n; v++){
				if(mgraph.Adj[u][v] == 1 && mark[v] == UNVISITED){
					e.u = u;
					e.v = v;
					enqueue(Cq,e);
				}
			}
		}
	}

}

void dfs_list_graph(int s){
	stop = -1;
	memset(mark, UNVISITED, (lgraph.n+1)*sizeof(int));
	push(Cs, s);
	printf("s = %d\n", Cs[stop]);
	int u;
	vlist ulist;
	while(!is_stack_empty()){
		u = pop(Cs);
		if(mark[u] == UNVISITED){
			printf("visiting: %d\n",u);
			mark[u] = VISITED;
			ulist = lgraph.vlists[u]; // the adjacency list of u
			vnode *it = ulist.head->next;
			while(it != NULL){ // examine all neighbors of u
				if(mark[it->id] == UNVISITED){
					push(Cs, it->id);
				}
				it = it->next;
			}
		}
	}

}

void dfs_matrix_graph(int s){
	stop = -1;
	int n = mgraph.n;
	memset(mark, UNVISITED, (n+1)*sizeof(int));
	push(Cs, s);
	printf("s = %d\n", Cs[stop]);
	int u,v;
	while(!is_stack_empty()){
		u = pop(Cs);
		if(mark[u] == UNVISITED){
			printf("visiting: %d\n",u);
			mark[u] = VISITED;
			for(v = 1; v <= n; v++){
				if(mgraph.Adj[u][v] == 1 && mark[v] == UNVISITED){
					push(Cs, v);
				}
			}
		}
	}

}

void recursive_dfs_list_graph(int s){
	printf("visiting %d\n",s);
	mark[s] = VISITED;
	vlist ulist = lgraph.vlists[s];
	vnode *it = ulist.head->next;
	while(it != NULL){
		if(mark[it->id] == UNVISITED){
			recursive_dfs_list_graph(it->id);
		}
		it = it->next;
	}

}

void recursive_dfs_matrix_graph(int s){
	int n = mgraph.n;
	printf("visiting %d\n",s);
	mark[s] = VISITED;
	int v = 1;
	for(v = 1; v<= n; v++){
		if(mgraph.Adj[s][v] == 1 && mark[v] == UNVISITED){
			recursive_dfs_matrix_graph(v);
		}
	}

}

void enqueue(edge *Cq, edge elem){
	Cq[qend] = elem;
	qend++;
}
edge dequeue(edge *Cq){
	if(is_queue_empty()) {
		printf("nothing to dequeue\n");
		exit(0);
	}
	edge elem = Cq[qfirst];
	qfirst++;
	return elem;
}

int is_queue_empty(){
	return qfirst < qend? 0 : 1;
}

void push(int *Cs, int elem){
	stop++;
	Cs[stop] = elem;
}
int pop(int *Cs){
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


list_graph new_list_graph(int n, int m, edge* E){
	list_graph lgraph;
	lgraph.n = n;
	lgraph.m = m;
	lgraph.vlists = (vlist *)malloc((n+1)*sizeof(vlist));
	int i = 1;

	for(i = 1; i <= n; i++){
		lgraph.vlists[i] = new_vertex_list(i);
	}
	vnode *unode, *vnode;
	for(i = 0; i < m; i++){
		unode = new_vertex(E[i].u);
		vnode = new_vertex(E[i].v);
		lgraph.vlists[E[i].u].tail->next = vnode;
		lgraph.vlists[E[i].u].tail = vnode;
		lgraph.vlists[E[i].v].tail->next = unode;
		lgraph.vlists[E[i].v].tail = unode;
	}
	return lgraph;
}


vlist new_vertex_list(int head_id){
	vlist vertex_list;
	vertex_list.head = new_vertex(head_id);
	vertex_list.tail = vertex_list.head;
	return vertex_list;
}
vnode *new_vertex(int id){
	vnode *node = (vnode *) malloc(sizeof(vnode));
	node->next = NULL;
	node->id = id;
	return node;
}

void print_list_graph(list_graph lgraph){
	printf("num vertices: %d\n", lgraph.n);
	printf("num edges: %d\n", lgraph.m);
	int i = 0;
	for(i = 1; i <= lgraph.n; i++){
		print_vertex_list(lgraph.vlists[i]);
	}

}


void print_vertex_list(vlist vertex_list){
		vnode* it = vertex_list.head;
		printf("adj list of %d : ",it->id);
		it = it->next;
		while(it!= NULL){
			printf("%d  ", it->id);
			it = it->next;
		}
		printf("\n");
}

matrix_graph new_matrix_graph(int n, int m, edge* E){
	matrix_graph mgraph;
	mgraph.n = n;
	mgraph.m = m;
	mgraph.Adj = (int **)malloc((n+1)*sizeof(int*));
	int i = 1;
	for(i= 1; i <=n; i++){
		mgraph.Adj[i] = (int*)malloc((n+1)*sizeof(int));
		memset(mgraph.Adj[i], 0, (n+1)*sizeof(int));
	}
	for(i = 0; i < m; i++){
		mgraph.Adj[E[i].u][E[i].v] = 1;
		mgraph.Adj[E[i].v][E[i].u] = 1;
	}
	for(i = 1; i <= n ;i++){
		print_int_array(mgraph.Adj[i], 1, n);
	}
	return mgraph;
}
