/*
 * An implementation of greedy algorithm for scheduling with deadlines and profits problem
 *
 *  Created on: Jul 2, 2015
 *      Author: hunglv
 */


#include<time.h>
#include<stdio.h>
#include<string.h>
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) < (y)) ? (y) : (x))
#define is_equal(x,y) (((x) - (y) == 0) ? 1 : 0)
#define MAX 1000000
#define INFTY 100000000

typedef struct {
	int id;
	int d;
	int p;
} job;

job A[MAX];
int X[MAX];
int P[MAX], R[MAX], Lm[MAX];

int compare_profit(const void *a, const void *b);
long long greedy_scheduling(int n);
long long union_find_scheduling(int n);


//void main (void){
//	int n = 5;
//	A[0].id = 0; A[0].d = 2; A[0].p = 100;
//	A[1].id = 1; A[1].d = 2; A[1].p = 27;
//	A[2].id = 2; A[2].d = 1; A[2].p = 25;
//	A[3].id = 3; A[3].d = 3; A[3].p = 15;
//	A[4].id = 3; A[4].d = 1; A[4].p = 19;
//	long long result1 = greedy_scheduling(n);
//	long long result2 = union_find_scheduling(n);
//	printf("greedy scheduling: %ld \n", result1);
//	printf("union-find scheduling: %ld \n", result2);
//
//}

long long greedy_scheduling(int n){
	qsort(A, n, sizeof(*A), compare_profit);
	memset(X, -1, sizeof(X));
	int i = 0, j = 0;
	for(i = 0; i < n; i++){
		j = A[i].d;
		while((X[j]!= -1) && (j > 0)){
			j--;
		}
		if(j > 0) X[j] = i;
	}
    long long total = 0;
	for(i = 1; i <= n; i++){
		if(X[i] != - 1){
			total += (long long)A[X[i]].p;
		}
	}
	return total;
}

long long union_find_scheduling(int n){
	qsort(A, n, sizeof(*A), compare_profit);
	memset(X, -1, sizeof(X));
	memset(Lm, 0, sizeof(Lm));
	int i = 0, j = 0;
	for(i = 0; i < n; i++){
		j = A[i].d;
		if(X[j] == -1){
			X[j] = i;
			makeSet(j);
			if(X[j-1] != -1){
				uniOn(j-1,j);
			}
			if(X[j+1] != -1){
				uniOn(j,j+1);
			}
		} else {
			int k = Lm[find(j)];
			if(k != 0){
				X[k] = i;
				makeSet(k);
				uniOn(k, j);
				if(X[k-1] != -1){
					uniOn(k-1,k);
				}
			}
		}

	}
	long long total = 0;
	for(i = 1; i <= n; i++){
		if(X[i] != - 1){
			total += (long long) A[X[i]].p;
		}
	}
	return total;
}

void makeSet(int x){
	P[x] = x;
	R[x] = 0;
	Lm[x] = x-1;
}

int find(int x){
	if( P[x] != x){
		P[x] = find(P[x]);
	}
	return P[x];
}

void uniOn(int x, int y){
	int a = find(x);
	int b = find(y);
	if(R[a] > R[b]){
		P[b] = a;
	} else {
		P[a] = b;
		Lm[b] = Lm[a];
		if( R[a] == R[b]){
			R[b] ++;
		}
	}
}

int compare_profit(const void *a, const void *b){
	job *c_a = (job *)a;
	job *c_b = (job *)b;
	return c_b->p - c_a->p;
}
void printJobArr(job A[], int n){
	int i = 0;
	for(i = 0; i < n; i++){
		printf("(%d,%d,%d)  ", A[i].id, A[i].d, A[i].p);
	}
	printf("\n");
}
