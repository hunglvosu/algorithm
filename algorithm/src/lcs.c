/*
 * Longest Common Subsequence
 *
 *  Created on: Jun 11, 2015
 *      Author: hunglv
 */

#include<time.h>
#include<stdio.h>
#include<string.h>
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) < (y)) ? (y) : (x))
#define is_equal(x,y) (((x) - (y) == 0) ? 1 : 0)
#define INFTY 100000000
#define NULL 0

int compare(const void *a, const void *b);
int dic_compare(const void *a, const void *b);

typedef struct{
    int x;
    int y;
  }pair;


void main (void){
	int n = 10, m = 12;
	int A[10] = {3,6,7,5,3,5,6,2,9,1};
	int B[12] = {2,7,0,9,3,6,0,6,2,6,1,8};
	printf("%d---%d\n",lcs(A,B,n,m), sparse_lcs(A, B, n,m));

}

int lcs(int A[], int B[], int n, int m){
	int LCS[n+1][m+1];
	int i = 0, j = 0;
	for(i = 0; i < n+1; i++){
		memset(LCS[i], 0, sizeof(LCS[i]));
	}
	for(i = 1; i <= n; i++){
		for(j = 1; j <= m; j++){
			if(A[i-1] == B[j-1]){
				LCS[i][j] = LCS[i-1][j-1]+1;
			}else {
				LCS[i][j] = max(LCS[i-1][j], LCS[i][j-1]);
			}
		}
	}
	return LCS[n][m];
}
int sparse_lcs(int A[], int B[], int n, int m){
	pair matches[m*n];
	int k = find_useful_pairs(matches, A, B, n, m);
	qsort(matches, k, sizeof(*matches), dic_compare);
	pair sentinel;
	sentinel.x = n + 1;
	sentinel.y = m+1;
	matches[k] = sentinel;// equivalent to add dummy characters at the end of A and B
	int LCS[k+1];
	memset(LCS, 0, sizeof(LCS));
	int kk = 0, l = 0;
	for (kk = 0; kk <=  k ; kk++){
		pair i = matches[kk];
		LCS[kk]  = 1;
		for(l = 0; l < kk; l++){
			pair j = matches[l];
			if((j.x < i.x ) && (j.y < i.y)){
				LCS[kk] = max(LCS[kk], LCS[l] + 1);
			}
		}
	}
	return LCS[k]-1;
}

int find_useful_pairs(pair matches[], int A[], int B[], int n, int m){
	int i = 0, j = 0;
	pair Ap[n];
	for(i = 0; i < n; i++){
		Ap[i].x = A[i];
		Ap[i].y = i; // keep track of indices of the sorted array
	}
	pair Bp[m];
	for(i = 0; i < m; i++){
			Bp[i].x = B[i];
			Bp[i].y = i; // keep track of indices of the sorted array
	}
	qsort(Ap, n, sizeof(*Ap), compare);
	qsort(Bp, m, sizeof(*Bp), compare);
	int mp = 0;
	int ii = 0, jj = 0;
	i = 0;
	while((i < n) && (j < m)){
		if(Ap[i].x < Bp[j].x){
			i++;
		}
		else if(Ap[i].x > Bp[j].x){
			j++;
		} else {
			ii = i;
			while(Ap[ii].x == Ap[i].x){
				jj = j;
				while(Bp[jj].x == Bp[j].x){
					matches[mp].x = Ap[ii].y;
					matches[mp].y = Bp[jj].y;
					mp++;
					jj++;
				}
				ii++;
			}
			i = ii;
			j = jj;
		}
	}
	return mp;// the number of useful pairs
}

int compare(const void *a, const void *b){
	pair *str_a = (pair *)a;
	pair *str_b = (pair *)b;
	return (str_a->x - str_b->x);
}

int dic_compare(const void *a, const void *b){
	pair *str_a = (pair *)a;
	pair *str_b = (pair *)b;
	if( str_a->x == str_b->x){
		return (str_a->y - str_b->y);
	} else {
		return (str_a->x - str_b->x);
	}
}



