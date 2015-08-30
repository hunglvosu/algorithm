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
#define MAXN 20
#define MAXM 10

//char *T;
char Alphabet[ALPHABET_SIZE];
snode *uu;
int L = 0;

int main (void){
    char Txt[] = " chccgbagbfjejajb{"; //bmemahiegehlakabfhgdagilcgnhngbmddldldfbfl
    char Ptn[] = " cgbagb";//fhgdagilcgnhn
//	char Txt[MAXN+1];
//	Txt[0] = ' ';
//	int i = 0;
//	for(i = 1; i < MAXN; i++){
//		Txt[i] = 'a';
//	}
//	Txt[MAXN] = '{';
//    char Ptn[] = " aaa";
    snode *root = mccreight_suffix_tree(Txt);
  //  printf("%d\n", BFmatcher(Txt,Ptn));
    int iss = is_substring(Ptn,root);
    if(iss == TRUE){
    	printf("yes\n");
    } else {
    	printf("no\n");
    }
    int cnt_occurence = count_occurrence(Ptn, root);
    printf("the number of occurences: %d\n", cnt_occurence);
    printf("the smallest lexicographic suffix: ");
    print_smallest_lex_suffix(root);
    printf("\n");
    printf("the longest repeated substring: ");
    char *lrs = longest_repeated_substr(root);
    print_str(lrs);
//    int i = 0;
//    for(i = 0; i < 100; i++ ){
//    	test(i);
//    }
    return 0;
}

void test(int num_test){
	printf("testnum: %d\n", num_test);
	char *Txt;
	char *Ptn;
	int n = rand()%(MAXN-10)+10;
	int m = MAXN+1;
	Txt = (char *) malloc((n+1)*sizeof(char));
	int t = rand()%26+1;
	while(m >= n-1){
		m = rand()%(MAXM-1) + 1;
	}
	Ptn = (char *) malloc((m+1)*sizeof(char));
	memset(Txt, ' ', sizeof(char)*(n+1));
	memset(Ptn, ' ', sizeof(char)*(m+1));
	int i = 0;
	Txt[0] = ' '; Ptn[0] = ' ';
	for(i = 1 ; i < n ; i++ ){
		Txt[i] = Alphabet[rand()%t+1];
		printf("%c", Txt[i]);
	}
	Txt[n] = '{';
	printf("\n");
	int r = rand()%(n-m)+1;
	printf("n=%d-- m = %d -- r=%d\n",n,m,r);

	for(i = 0 ; i < m ; i++ ){
			Ptn[i+1] = Txt[r+i];
			printf("%c", Ptn[i+1]);
	}
	printf("\n");
	int rs = BFmatcher(Txt,Ptn);
	snode *root = mccreight_suffix_tree(Txt);
	int rss = is_substring(Ptn,root);
	if(rss > 0 && rs > 0){
		printf("pass\n");
	}else if(rss <= 0 && rs < 0){
		printf("pass\n");
	}else {
		printf("fail\n");
		exit(0);
	}
	root = NULL;

//	if(r1 != r2){
//		printf("fails\n");
//		exit(0);
//	}else {
//		printf("%d--%d\n", r1,r2);
//	}

}

snode *mccreight_suffix_tree(char *Txt){
	T = Txt;
	int n = strlen(T)-1;
	snode *root = init_suffix_tree(n);
	uu = root;
	int i = 0;
	int mlt = 0,mlp=0;
	snode *v = NULL;
	int rv,lv, dp;
	snode *x, *u;
	snode *vv = NULL;
	for(i = 2; i <= n ;i++){
		u = uu;
		dp = uu->strdepth;
		if(u->Cr[get_index(T[i + dp])] == NULL){
			snode *w = make_leaf(i+dp,n,i);
			w->parent  = u;
			u->Cr[get_index(T[i+dp])] = w;
			uu = u->slink;
			if(vv != NULL){
				vv->slink = u;
				vv = NULL;
			}
			printf("i = %d-root : %d--%d\n",i,u->leftEL, u->rightEL);
		} else {
			if( L == 0) {
				v = find_path(T,i,n,root, &mlp, &mlt);
				printf("i = %d-- slow\n",i);
			} else {
				printf("i = %d -- L = %d -- u = %d--%d--fast\n",i,L,u->leftEL, u->rightEL);
				v = fast_find_path(T,i+ dp,n,L, u, &mlt);
				mlp = i+dp + L-1;
				printf("v: %d--%d,  mlp = %d\n", v->leftEL, v->rightEL, mlp);
			}
			int mlgp = mlp - i +1;
			lv = v->leftEL;
			rv = v->rightEL;
			printf("mlgp: %d\n",mlgp);
			if(mlt < rv){
				v->leftEL = mlt+1;
				x = make_node(lv,mlt);
				snode *pv = v->parent;
				x->strdepth = pv->strdepth + mlt - lv + 1;
				replace_parent(x,v);
				uu = x->parent->slink;
				L = (uu == root)? mlgp-1: mlgp - x->parent->strdepth;
				if(vv != NULL){
					printf("update slink: %d--%d to %d--%d\n",vv->leftEL, vv->rightEL, x->leftEL, x->rightEL);
					vv->slink = x;
				}
				vv = x;
			} else {
				printf("not yet occured\n");
				x = v;
				uu = v->slink;
				if (uu == NULL){
					v->slink = root;
					uu = root;
				}
				L = 0;
				if(vv != NULL){
					printf("updatelink: %d--%d to %d--%d", vv->leftEL, vv->rightEL, x->leftEL, x->rightEL);
					vv->slink = x;
					vv = NULL;
				}
			}
			snode *u = make_leaf(mlp+1,n,i);
			u->parent = x;
			x->Cr[get_index(T[mlp+1])]  = u; // T[mlp+1] is the first character of the edge xu
		}
	}
	return root;
//	T = Txt;
//	int n = strlen(T)-1;
//	int i = 0, mlt = 0, mlp=0, rv, lv, dp;
//	snode *v = NULL, *vv = NULL, *x;
//	snode *root = init_suffix_tree(n);
//	uu = root;
//	for(i = 2; i <= n ;i++){
//		dp = uu->strdepth;
//		if(uu->Cr[get_index(T[i + dp])] == NULL){
//			snode *w = make_leaf(i+dp,n,i);
//			w->parent  = uu;
//			uu->Cr[get_index(T[i+dp])] = w;
//			uu = uu->slink;
//			if(vv != NULL){
//				vv->slink = uu;
//				vv = NULL;
//			}
//		} else {
//			if( L == 0) {
//				v = find_path(T,i,n,root, &mlp, &mlt);
//			} else {
//				v = fast_find_path(T,i+ dp,n,L, uu, &mlt);
//				mlp = i+dp + L-1;
//			}
//			int mlgp = mlp - i +1;
//			lv = v->leftEL;
//			rv = v->rightEL;
//			if(mlt < rv){
//				v->leftEL = mlt+1;
//				x = make_node(lv,mlt);
//				snode *pv = v->parent;
//				x->strdepth = pv->strdepth + mlt - lv + 1;
//				replace_parent(x,v);
//				uu = x->parent->slink;
//				L = (uu == root)? mlgp-1: mlgp - x->parent->strdepth;
//				if(vv != NULL){
//					vv->slink = x;
//				}
//				vv = x;
//			} else {
//				x = v;
//				uu = v->slink;
//				L = 0;
//				if(vv != NULL){
//					vv->slink = x;
//					vv = NULL;
//				}
//			}
//			snode *u = make_leaf(mlp+1,n,i);
//			u->parent = x;
//			x->Cr[get_index(T[mlp+1])]  = u; // T[mlp+1] is the first character of the edge xu
//		}
//	}
//	return root;
}

snode *fast_find_path(char *P, int first, int last, int L, snode *r, int *mlt){
	snode *u = r->Cr[get_index(P[first])];
	int s = u->rightEL - u->leftEL + 1;
	if(L <= s){
		*mlt = L + u->leftEL -1;
		return u;
	} else {
		return fast_find_path(P, first + s-1, last, L-s, u, mlt);
	}
}

