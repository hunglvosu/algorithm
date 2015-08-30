/*
 * An implementation of native algorithm for building suffix tree
 * See http://www.giaithuatlaptrinh.com/?p=420 for details
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
#define MAXN 20
#define MAXM 8


snode *find_nonleaf_deepest_node(snode *r);

char *T;
char Alphabet[ALPHABET_SIZE];


//int main (void){
//    char Txt[] = " xabxacxabxxabx{";
//    char Ptn[] = " xab";
//    snode *root = native_suffix_tree(Txt);
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
//

snode *native_suffix_tree(char *Txt){
	T = Txt;
	int n = strlen(T)-1;
	snode *root = init_suffix_tree(n);
	int i = 0;
	int mlt = 0,mlp=0;
	snode *v = NULL;
	int rv,lv;
	snode *x;
	for(i = 2; i <= n ;i++){
		v = find_path(T,i,n,root, &mlp, &mlt);
		lv = v->leftEL;
		rv = v->rightEL;
		 if(mlt < rv){
			v->leftEL = mlt+1;
			x = make_node(lv,mlt);
			snode *pv = v->parent;
			x->strdepth = pv->strdepth + mlt - lv + 1;
			replace_parent(x,v);
		} else {
			x = v;
		}
		snode *u = make_leaf(mlp+1,n,i);
		u->parent = x;
		x->Cr[get_index(T[mlp+1])]  = u; // T[mlp+1] is the first character of the edge xu
	}
	return root;
}

snode *find_path(char *P, int first, int last, snode *r, int *mlp, int *mlt){
	snode *c = r->Cr[get_index(P[first])];
	if(c == NULL || first > last){
		*mlt = r->rightEL;
		*mlp = first-1;
		return r;
	}
	int i = first;
	int j = c->leftEL;
	int rc = c->rightEL;
	while(P[i] == T[j] && j <= rc){
		i++; j++;
	}
	if( j > rc){
		return find_path(P,i, last,c,mlp,mlt);
	}
	else {
		*mlt = j-1;
		*mlp = i-1;
		return c;
	}
}

void replace_parent(snode *x, snode *v){
	snode *pv = v->parent;
	int lx = x->leftEL;
	int lv = v->leftEL;
	pv->Cr[get_index(T[lx])] = x;
	x->Cr[get_index(T[lv])] = v;
	v->parent = x;
	x->parent = pv;
}


snode *init_suffix_tree(int n){
	snode *r = make_node(0,0);
	snode *u = make_leaf(1,n,1);
	r->Cr[get_index(T[1])] = u;
	r->slink = r;
	u->parent = r;
	return r;
}


snode *make_node(int i, int j){
	snode *u  = malloc(sizeof(snode));
	u->leftEL = i;
	u->rightEL = j;
	u->node_label = 0;
	u->Cr = malloc(ALPHABET_SIZE*sizeof(snode));
	u->parent = NULL;
	u->slink = NULL;
	u->leafcnt = 0;
	u->strdepth = 0;
	memset(u->Cr, 0, sizeof(*u->Cr));
	return u;
}

snode *make_leaf(int i,int n, int k){
	snode *u = make_node(i,n);
	u->node_label = k;
	u->strdepth = n-i+1;
	return u;
}

void update_leaf_count(snode *r){
	if(r->node_label != 0){
		r->leafcnt = 1;
	} else {
		int leafcnt = 0;
		int i = 0;
		for(i = 0; i < ALPHABET_SIZE; i++){
			if(r->Cr[i] != NULL){
				update_leaf_count(r->Cr[i]);
				leafcnt += r->Cr[i]->leafcnt;
			}
		}
		r->leafcnt = leafcnt;
	}
}


int is_substring(char *P, snode *r){
	int mlp = 0;
    int mlt = 0;
    int m = strlen(P)-1;
    find_path(P, 1, m, r, &mlp, &mlt);
    if( m == mlp){
    	return TRUE;
    } else {
    	return FALSE;
    }
}

int is_suffix(char *P, char *T){
	snode *root = native_suffix_tree(T);
    int mlp = 0;
    int mlt = 0;
    int m = strlen(P)-1;
    snode *v = find_path(P, 1, m, root, &mlp, &mlt);
    if( v->node_label != 0 && v->rightEL == mlt){
    	return TRUE;
    } else {
    	return FALSE;
    }
}

int count_occurrence(char *P, snode *r){
	update_leaf_count(r);
	int mlp = 0;
    int mlt = 0;
    int m = strlen(P)-1;
    snode *v = find_path(P, 1, m, r, &mlp, &mlt);
    if(mlp < m) return 0;
    else return v->leafcnt;
}

void print_smallest_lex_suffix(snode *r){
	int i = 0, j, jj = 0;
	if(r->leftEL == 0 || r->Cr[get_index('{')] == NULL){
		while(i < ALPHABET_SIZE && r->Cr[i] == NULL)i++;
			if(i != ALPHABET_SIZE){
				j = r->Cr[i]->leftEL;
				jj = r->Cr[i]->rightEL;
				for(; j <= jj; j++){
					printf("%c", T[j]);
				}
				print_smallest_lex_suffix(r->Cr[i]);
		}
	}
}

char *longest_repeated_substr(snode *r){
	snode * dpn = find_nonleaf_deepest_node(r);
	char *S;
	S = (char *)malloc(dpn->strdepth*sizeof(char));
	int i = -1, j = 0;
	snode *it = dpn;
	while(it != r){
		for(j = it->rightEL; j >= it->leftEL; j--){
			S[++i] = T[j];
		}
		it = it->parent;
	}
	return strrev(S);
}

snode *find_nonleaf_deepest_node(snode *r){
	int i = 0;
	snode *dpn, *tmp;
	int j = 0;
	dpn = r;
	for(i = 0; i < ALPHABET_SIZE; i++){
		if(r->Cr[i] != NULL && r->Cr[i]->node_label == 0){
			tmp = find_nonleaf_deepest_node(r->Cr[i]);
			if(tmp->strdepth > j){
				j = tmp->strdepth;
				dpn = tmp;
			}
		}
	}
	return dpn;
}
// Get the index of a character in the alphabet
int get_index(char c){
	return c - 'a';
}

//void print_depth(snode *r){
//		printf("depth: %d---%d = %d \n", r->leftEL, r->rightEL, r->strdepth);
//		int i = 0;
//		for(i = 0; i < ALPHABET_SIZE; i++){
//			if(r->Cr[i] != NULL){
//				if(r->Cr[i]->node_label != 0){
//					printf("leaf: %d  ", r->Cr[i]->node_label);
//				}
//				print_depth(r->Cr[i]);
//			}
//		}
//}
