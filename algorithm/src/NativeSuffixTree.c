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

#define MAXN 100
#define MAXM 20

typedef struct node {
	int leftEL;
	int rightEL;
	int node_label;
	struct node** Cr;
	struct node *parent;
	int num_child;
} node;

node *make_node(int i, int j);
node *make_leaf(int i, int k);
void replace_parent(node *x, node *v);
int get_index(char c);
node *init_suffix_tree(char S[]);
node *find_path(int i, node *r, int *ss, int *j);

char Sx[] = " xabxacxabxxabx}";
extern int n;
//int main (void){
//	node *root = init_suffix_tree(Sx);
//	int i = 0;
//	int s = 0,j=0;
//	node *v = NULL;
//	int rv,lv;
//	node *x;
//	for(i = 2; i <= n ;i++){
////		printf("i= %d:",i);
//		v = find_path(i,root, &s, &j);
//		lv = v->leftEL;
//		rv = v->rightEL;
//		 if(s < rv){
//			v->leftEL = s+1;
//			x = make_node(lv,s);
//			replace_parent(x,v);
////			printf("new x: %d -- %d --%c\n",x->leftEL,x->rightEL, Sx[s+1]);
//		} else {
//			x = v;
//		}
//		node *u = make_leaf(j,i);
//		u->parent = x;
//		x->Cr[get_index(Sx[j])]  = u;
////		printf("s=%d++u=%c\n",s, Sx[j]);
//
//	}
//	return 0;
//}

void replace_parent(node *x, node *v){
	node *pv = v->parent;
	int lx = x->leftEL;
	int lv = v->leftEL;
	pv->Cr[get_index(Sx[lx])] = x;
	x->Cr[get_index(Sx[lv])] = v;
	v->parent = x;
	x->parent = pv;
}

node *find_path(int i, node *r, int *ss, int *jj){
//	printf("find:%d++%d\n", r->leftEL, r->rightEL);
	node *c = r->Cr[get_index(Sx[i])];
//	printf("Sx[%d] : %c\n",i, Sx[i]);
	if(r->Cr[get_index(Sx[i])] == NULL){
		*ss = r->rightEL;
		*jj = i;
		return r;
	}
	int j = i;
	int s = c->leftEL;
	int rc = c->rightEL;
//	printf("%c:index:%d++ j++s: %d++%d\n", Sx[i],get_index(Sx[i]),j, s);

	while(Sx[j] == Sx[s] && s <= rc){
		j++; s++;
	}
	if( s > rc){
		return find_path(j,c,ss,jj);
	}
	else {
		*ss = s-1;
		*jj = j;
		return c;
	}
	return NULL;
}

node *init_suffix_tree(char Sx[]){
	node *r = make_node(0,0);
	node *u = make_leaf(1,1);
	r->Cr[get_index(Sx[1])] = u;
	u->parent = r;
	return r;
}


node *make_node(int i, int j){
	node *u  = malloc(sizeof(node));
	u->leftEL = i;
	u->rightEL = j;
	u->node_label = 0;
	u->Cr = malloc(28*sizeof(node*));
	u->parent = NULL;
	u->num_child = 0;
//	int ii = 0;
//	for(ii = 0; ii < 28; ii++){
//		u->Cr[ii] = NULL;
//	}
	memset(u->Cr, 0, sizeof(*u->Cr));
	return u;
}

node *make_leaf(int i, int k){
	node *u = make_node(i,n);
	u->node_label = k;
	return u;
}

int get_index(char c){
	return c - 'a';
}

