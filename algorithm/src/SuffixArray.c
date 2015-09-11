/*
 * An implementation of algorithms for building suffix arrays
 * See .... for details
 *
 *  Created on: Sep 7, 2015
 *      Author: hunglv
 */

#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "stringsearch.h"
#include "utilities.h"
#include "numbers.h"

#define TRUE 1
#define FALSE 0
#define MAXN 100000

char *T;
int n;
typedef struct data{
	int lkey, rkey;
	int index;
}data;
data *S;
int **M;
int *A;
LLU *B, *PP;
LLU b = (LLU)200; // the base assuming English text only
LLU p = (LLU) 1000000007;


int rk_compare(const void *a, const void *b);
int lex_compare(const void *u, const void *v);
LLU hashcode(int i, int j);

int main (void){
	char Txt[] = " gcgaoblbrqgrjrpkimqlcdbqhe`";
	print_int_array(rk_suffix_array(Txt), 28);
	print_int_array(pd_suffix_array(Txt), 28);
	return 0;
}
int *rk_suffix_array(char *Txt){
	T = Txt;
    n = strlen(T)-1;
	B = (LLU *)malloc((n+1)*sizeof(LLU));
	PP = (LLU *)malloc((n+1)*sizeof(LLU));
	A = (int *)malloc((n+1)*sizeof(int));
	memset(A, 0, (n+1)*sizeof(int));
	B[0] = 0;B[1] = (LLU)get_index(T[1]);
	PP[0] = 1; PP[1] = b; A[1] = 1;
	int i = 0;
	for(i = 2; i <= n; i++){
		B[i] = (B[i-1]*b+ (LLU)get_index(T[i])) %p;
		PP[i] = (PP[i-1]*b)%p;
		A[i] = i;
	}
	qsort(A, n+1, sizeof(int), rk_compare);
	return A;
}

int rk_compare(const void *a, const void *b){
	int *i = (int *)a;
	int *j = (int *)b;
	int h = min(n - *i + 1, n - *j+1);
	int l = 0, m = 0;
	while(l <= h){
		m = (l+h)/2;
		if(hashcode(*i,*i+m) == hashcode(*j,*j+m)){
			l = m+1;
		}else {
			h = m -1;
		}
	}
	return get_index(T[*i+l]) - get_index(T[*j+l]);
}
LLU hashcode(int i, int j){
	return (B[j] + p - (B[i-1]*PP[j-i+1])%p)%p;
}


int *pd_suffix_array(char *Txt){
	T = Txt;
	n = strlen(T)-1;
	S = (data *)malloc((n+1)*sizeof(data));
	M = (int **)malloc(32*sizeof(int *)); // 2^31-1 is the maximum length of the text
	A = (int *)malloc((n+1)*sizeof(int));
	memset(A, 0, (n+1)*sizeof(int));
	int k = 0, i = 0;
	for(k = 0; k < 32; k++){
		M[k] = (int *)malloc((n+1)*sizeof(int));
	}
	S[0].lkey = 0; S[0].rkey = 0; S[0].index = 0;
	for(k = 1; k <= n; k++) {
		S[k].index = k;
		S[k].lkey = T[k] - '`';
		S[k].rkey = S[k].lkey;
	}
	int ell = 1;
	k = -1;
	while(ell < n){
		k++;
		ell = 1 << k;
		qsort(S, n+1, sizeof(data), lex_compare);
		for(i = 1; i <=n; i++){
			M[k][S[i].index] = lex_compare(&S[i], &S[i-1]) == 0? M[k][S[i-1].index] : i;
		}
		for(i = 1; i <=n; i++){
			S[i].lkey = M[k][S[i].index];
			S[i].rkey = (S[i].index + ell) <= n ? M[k][S[i].index + ell] : 0;
		}
	}
	for(k = 1; k <= n ;k++){
		A[k] = S[k].index;
	}
	return A;
}

int pd_lcp(int x, int y) {
	int k = 1;
	for(k =1; (1<<k) < n; k++){} // k = [log_2 n]
	if( x == y){
		return n-x+1;
	}
	int s = 0;
	while(k >= 0){
		if(M[k][x] == M[k][y]){
			x+= (1 << k);
			y+= (1 << k);
			s+= (1 << k);
		}
		k--;
	}
	return s;
}
int lex_compare(const void *u, const void *v){
	data *a = (data *)u;
	data *b = (data *)v;
	return (a->lkey == b->lkey) ? (a->rkey == b->rkey ? 0 : (a->rkey > b->rkey ? 1 : -1)) : ((a->lkey > b->lkey) ? 1: -1);
}


