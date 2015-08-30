/*
 * An implementation of KMP matching algorithm
 *
 *  Created on: Jul 13, 2015
 *      Author: hunglv
 */

#include<time.h>
#include<stdio.h>
#include<string.h>
#include "stringsearch.h"
#define MAXM 20

char *T;
char *P;
//char T[] = " dlcimglkblhcch";
//char P[] = " mglkblhc";

int  S[28][MAXM];
int  F[MAXM];

char Alphabet[ALPHABET_SIZE] = " abcdefghijklmnopqrstuvwxyz{";

void compute_backup(int m);
void compute_failure(int m);

//
//int main (void){
//	int n = 14, m = 8;
//	printf("%d\n",BFmatcher(n,m));
//	printf("%d\n",KMPmatcher(n,m));
//	printf("%d\n",fastKMPmatcher(n,m));
//	return 0;
//}

int BFmatcher(char *Txt, char *Ptn){
	T = Txt;
	P = Ptn;
	int n = strlen(T)-1;
	int m = strlen(P)-1;
	int i = 0, s = 0;
	int matched = 1;
	for(i = 1;  i <= n-m+1; i++){
		s = 0;
		matched = 1;
		while((matched) && (s <= m-1)){
			if (T[i+s] != P[s+1]){
					matched = 0;
			}else {
				s++;
			}
		}
		if(matched){
			return i;
		}
	}
	return -1;
}
int KMPmatcher(int n, int m){
	compute_backup(m);
	int i = 1, j = 1, p = 0;
	for(i = 1; i <=n; i++){
		if(T[i] != P[j]){
			p = T[i]-96;
			j = S[p][j];
		}
		else j++;
		if(j == m+1){
			return i-m+1;
		}
	}
	return -1;
}

void compute_backup(int m){
	int X = -1;
	int j = 0 ,k = 0, p = 0;
	for(k = 0; k < 27; k++){
		memset(S[k], 0, sizeof(S[k]));
	}
	for(k = 0; k < 27 ; k ++){
		S[k][0] = 1;
	}
	for(j = 1; j <=m ; j++){
		for(k = 1; k < 27; k++){
			S[k][j] = S[k][X+1];
		}
		p = P[j]-96;
		S[p][j] = j+1;
		X = S[p][X+1]-1;
	}
}

int fastKMPmatcher(int n, int m){
	compute_failure(m);
	int i = 1, j = 1;
	for(i = 1; i <=n ; i++){
		while(T[i] != P[j] && j > 0){ // found a mismatch
			j = F[j];   // backup the pattern
		}
		if(j == m){
			return i-m+1;
		}
		j++;
	}
	return -1;

}

void compute_failure(int m){
	int k = 0, j = 1;
	F[1] = 0;
	for(j=1 ; j < m; j++){
		while(P[j] != P[k] && k > 0){
			k =  F[k];
		}
		k++;
		F[j+1] = k;
	}
}




//void update_str_depth(snode *r, int depth){
//	r->strdepth = depth;
//	int i = 0;
//	for(i = 0; i < ALPHABET_SIZE; i++){
//		if(r->Cr[i] != NULL){
//			update_str_depth(r->Cr[i], r->Cr[i]->rightEL - r->Cr[i]->leftEL+ 1 + depth);
//		}
//	}
//}

//void longest_repeated_substr(char *T){
//	snode *root = native_suffix_tree(T);
//	find_nonleaf_deepest_node(root);
//	printf("deepest node: %d--%d\n", deepest_node->leftEL, deepest_node->rightEL);
//}
//
//void find_nonleaf_deepest_node(snode *r){
//	if(r->strdepth > deepest_node->strdepth){
//		deepest_node = r;
//	}
//	int i = 0;
//	for(i = 0; i < ALPHABET_SIZE; i++){
//		if(r->Cr[i] != NULL && r->Cr[i]->node_label !=0){
//			find_nonleaf_deepest_node(r->Cr[i]);
//		}
//	}
//}
