/*
 * An implementation of McCreight algorithm for building suffix tree
 * See http://www.giaithuatlaptrinh.com/?p=451 for details
 *
 *  Created on: Aug 14, 2015
 *      Author: hunglv
 */


#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "stringsearch.h"
#include "utilities.h"

#define TRUE 1
#define FALSE 0
#define MAXN 100
#define MAXM 10

char *T;
snode *uu,*vv;
int L = 0;
/*Find a string P[first,..., last] in the suffix tree with root r when we know the
  length of the matched substring, return the last matched location of the text T, which is mlt,
  and the last matched location of the pattern P, which is mlp */
snode *fast_find_path(char *P, int first, int last, int L, snode *r, int *mlt, int *mlp);
/*Make a new node of the suffix tree*/
snode *make_node(int i, int j);

/*Make a new leaf of the suffix tree*/
snode *make_leaf(int i,int n, int k);

/*Get index of the character c in the alphabet*/
int get_index(char c);

/*Initialize a suffix tree with suffix T[1,2,...,n]*/
snode *init_suffix_tree(int n);

/*Replace parent of node v by x in the suffix tree*/
void replace_parent(snode *x, snode *v);

//int main (void){
//	char Txt[] = " xabxacxabxxabx{";
//	char Ptn[] = " xab";
//	snode *root = mccreight_suffix_tree(Txt);
//    int iss = is_substring(Ptn,root);
//    if(iss == TRUE){
//    	printf("yes\n");
//    } else {
//    	printf("no\n");
//    }
//    int cnt_occurence = count_occurrence(Ptn, root);
//    printf("the number of occurences: %d\n", cnt_occurence);
//    printf("the smallest lexicographic suffix: ");
//    print_smallest_lex_suffix(root);
//    printf("\n");
//    printf("the longest repeated substring: ");
//    char *lrs = longest_repeated_substr(root);
//    print_str(lrs);
//    return 0;
//}

snode *mccreight_suffix_tree(char *Txt){
		T = Txt;
		int n = strlen(T)-1;
		snode *root = init_suffix_tree(n);
		uu = root; vv = NULL;
		int i = 0;
		int mlt = 0,mlp=0, mlgp = 0;
		snode *v = NULL;
		int dp;
		snode *x, *u;
		int L = 0;
		for (i = 2; i <= n; i++){
			dp = uu->strdepth;
			v = fast_find_path(T, i + dp, n, L, uu, &mlp, &mlt);
			if(mlt < v->rightEL){
				x = make_node(v->leftEL, mlt);
				snode *pv = v->parent;
				x->strdepth = pv->strdepth + mlt - v->leftEL + 1;
				v->leftEL = mlt + 1;
				replace_parent(x,v);
				if(vv != NULL)	vv->slink = x;
				vv = x;
				L = (x->rightEL - x->leftEL+ 1)  - ((pv == root )?1:0);
			} else {
				x = v;
				L = 0;
			}
			u = make_leaf(mlp + 1, n, i);
			u->parent = x;
			x->Cr[get_index(T[mlp+1])] = u;
		}
		return root;

}

snode *fast_find_path(char *P, int first, int last, int L, snode *root, int *mlp, int *mlt){
	snode *u = root->Cr[get_index(P[first])];
	if( L == 0 && vv != NULL){
		vv->slink = root;
		vv = NULL;
	}
	if( u == NULL){
		if( L == 0){
			uu = root->slink;
		} else {
			printf("invalid parameter setup! %d\n", L);
			exit(0);
		}
		*mlp = first-1;
		*mlt = root->rightEL;
		return root;
	}else {
		int elg = u->rightEL - u->leftEL + 1;
		if(L >=  elg){
			return fast_find_path(P, first + elg, last, L - elg, u, mlp, mlt);
		}else {
			int i = first + L;
			int j = u->leftEL + L;
			while(P[i] == T[j] && j <= u->rightEL){
				i++;j++;
			}
			if(j > u->rightEL){
				return fast_find_path(P, first + elg, last, 0, u, mlp, mlt);
			} else {
				uu = root->slink;
				*mlp = i-1;
				*mlt = j -1;
				return u;
			}
		}
	}
}


