/*
 * graphs.h
 *
 *  Created on: Oct 3, 2015
 *      Author: hunglv
 */

#ifndef GRAPHS_H_
#define GRAPHS_H_

#define UNVISITED 0
#define VISITED 1

typedef struct vnode{
	int id;
	struct vnode *next;
}vnode;

typedef struct vlist {
	vnode *head;
	vnode *tail;
}vlist;


typedef struct edge {
	int u;
	int v;
} edge;

typedef struct list_graph{
	int n; // the number of veritces
	int m; // the number of edges
	vlist *vlists;
}list_graph;


typedef struct matrix_graph{
	int n; // the number of veritces
	int m; // the number of edges
	int **Adj;
}matrix_graph;

list_graph lgraph; // the adjacency list representation of graphs
matrix_graph mgraph; // the adjacency matrix represention of graphs
int* mark; // the array to mark visited vertices

vnode *new_vertex(int id);

list_graph new_list_graph(int n, int m, edge* E);

vlist new_vertex_list(int head_id);


void print_list_graph(list_graph lgraph);

void print_vertex_list(vlist vertex_list);

void bfs_list_graph(int s);

void dfs_list_graph(int s);

void recursive_dfs_list_graph(int s);

matrix_graph new_matrix_graph(int n, int m, edge* E);

void bfs_matrix_graph(int s);

void dfs_matrix_graph(int s);

void recursive_dfs_matrix_graph(int s);



#endif /* GRAPHS_H_ */
