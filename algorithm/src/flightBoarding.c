/*
 * this code is for this problem http://codeforces.com/contest/321/problem/E
 *
 *  Created on: Jun 25, 2015
 *      Author: hunglv
 */

#include<time.h>
#include<stdio.h>
#include<string.h>
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) < (y)) ? (y) : (x))
#define is_equal(x,y) (((x) - (y) == 0) ? 1 : 0)
#define MAXN 5000
#define MAXK 5000
#define INFTY 100000000

int	C[MAXK][MAXN];
int D[MAXN][MAXN];
int A[MAXN][MAXN];
int R[MAXN][MAXN];
int B[MAXN][MAXN];


void main (void){
	int n = 6, k = 2;
	A[0][0] = 0; A[0][1]= 0; A[0][2] = 1; A[0][3] = 1; A[0][4] = 1; A[0][5] = 1;
	A[1][0] = 0; A[1][1]= 0; A[1][2] = 1; A[1][3] = 1; A[1][4] = 1; A[1][5] = 1;
	A[2][0] = 1; A[2][1]= 1; A[2][2] = 0; A[2][3] = 0; A[2][4] = 0, A[2][5] = 0;
	A[3][0] = 1; A[3][1]= 1; A[3][2] = 0; A[3][3] = 0; A[3][4] = 0; A[3][5] = 0;
	A[4][0] = 1; A[4][1]= 1; A[4][2] = 0; A[4][3] = 0; A[4][4] = 0; A[4][5] = 0;
	A[5][0] = 1; A[5][1]= 1; A[5][2] = 0; A[5][3] = 0; A[5][4] = 0; A[5][5] = 0;
	printf("%d--%d\n",slow_dynamic_program(n,k), fast_dynamic_program(n, k));
}

int slow_dynamic_program(int n, int k){
	compute_dissimilarity(n);
	int i = 0, j = 0, l = 0, tmp;
	for( i = 0 ; i < n ; i ++){
		memset(C[i], 0, sizeof(C[i]));
	}
	for (j = 1; j < n; j++){
		C[0][j] = D[0][j];
	}
	for(i = 1; i < k; i++){
		for(j = i+1; j < n; j++){
			tmp = INFTY;
			for(l = i; l <=j ; l++){
				tmp = min(tmp, C[i-1][l-1] + D[l][j]);
			}
			C[i][j] = tmp;
		}
	}
	return C[k-1][n-1];
}

int fast_dynamic_program(int n, int k){
	compute_dissimilarity(n);
	int i = 0, j = 0, l = 0, tmp;
	for( i = 0 ; i < n ; i ++){
			memset(C[i], 0, sizeof(C[i]));
	}
	for (j = 1; j < n; j++){
		C[0][j] = D[0][j];
	}
	for(i = 1; i < k; i++){
		R[i][i] = i;
		R[i][n-1] = computeR(i,n-1, i, n-1);
		div_con_dynamic(i, i+1, n-2, i, R[i][n-1]);
	}
	return C[k-1][n-1];
}

void div_con_dynamic(int i, int x, int y, int optL, int optR){
	if(y < x) return;
	else if(y == x){
		R[i][x] = computeR(i, x, optL, optR);
	} else {
		int m = (x+y)/2;
		R[i][m] = computeR(i,m,optL,optR);
		div_con_dynamic(i, x, m-1, optL, R[i][m]);
		div_con_dynamic(i, m+1,y,R[i][m], optR);
	}
}

int computeR(int i, int j, int L, int R){
	int tmp = INFTY, p = L, l = 0;
	for(l = L; l <= R; l++){
		if(C[i-1][l-1] + D[l][j] < tmp){
			tmp = C[i-1][l-1] + D[l][j];
			p = l;
		}
	}
	C[i][j] = tmp;
	return p;
}


void compute_dissimilarity(int n){
	int d = 0, i = 0;
	for( i = 0; i < n; i++){
		memset(D[i], 0, sizeof(D[i]));
		memset(B[i], 0, sizeof(B[i]));
	}
	for( d = 1; d < n; d++){
		for(i = 0; i < n-d; i++){
			B[i][i+d] = B[i+1][i+d] + A[i][i+d];
			D[i][i+d] = D[i][i+d-1] + B[i][i+d];
		}
	}
}

