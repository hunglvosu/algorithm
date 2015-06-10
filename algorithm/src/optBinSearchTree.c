/*
 * Optimal Binary Search Tree
 *
 *  Created on: Jun 4, 2015
 *      Author: hunglv
 */
#include<time.h>
#include<stdio.h>
#include<string.h>
#define MAX 1000
#define INFTY 100000000

int F[MAX][MAX];
int C[MAX][MAX];//cost array
int R[MAX][MAX];// root array


int opt_binary_search_tree(int f[], int size){
	int i = 0, j = 0;
	for(i = 0; i <= size; i++){
		memset(F[i], 0, sizeof(F[i]));
		memset(C[i], 0, sizeof(C[i]));
	}
	precompute_cost(f, size);
	for(i = 0; i <= size; i++){
			R[i][i] = i;
			C[i][i] = F[i][i];
		}
	int d = 1;
	for(d = 1; d < size; d++){
		for(i = 1; i <= size-d; i++){
		  compute_opt_cost(i, i+d);
		 }
	}
	return C[1][size];
}

int knuth_binary_search_tree( int f[], int size){
	int i = 0, j = 0;
	for(i = 0; i <= size; i++){
		memset(F[i], 0, sizeof(F[i]));
		memset(C[i], 0, sizeof(C[i]));
	}
	precompute_cost(f, size);
	for(i = 0; i <= size; i++){
		R[i][i] = i;
		C[i][i] = F[i][i];
	}
	int d = 0;
	for(d = 1; d < size; d++){
		for(i = 1; i <= size-d; i++){
		  knuth_opt_cost(i, i+d);
		 }
	}
	return C[1][size];
}


void compute_opt_cost(int i, int j){
	  int r = 0;
	  int tmp = 0;
	  C[i][j] = INFTY;
	  for(r = i; r <= j ; r++){
		  tmp = C[i][r-1] + C[r+1][j];
		  if(tmp <= C[i][j]){
			  C[i][j] = tmp;
			  R[i][j] = r;
		  }
	  }
	  C[i][j] = C[i][j] + F[i][j];
}

void knuth_opt_cost(int i, int j){
	  int r = 0;
	  int tmp = 0;
	  C[i][j] = INFTY;
	  for(r = R[i][j-1]; r <= R[i+1][j] ; r++){
		  tmp = C[i][r-1] + C[r+1][j];
		  if(tmp <= C[i][j]){
			  C[i][j] = tmp;
			  R[i][j] = r;
		  }
	  }
	  C[i][j] = C[i][j] + F[i][j];
}

void precompute_cost(int f[], int size){
	int i = 0, j = 0;
	for(i = 1; i <= size; i++){
		for(j = i; j <= size; j++){
			F[i][j] = F[i][j-1] + f[j-1];
		}
	}
}


