/*
 * Traveling Salesman Problem
 *
 *  Created on: Jun 6, 2015
 *      Author: hunglv
 */


#include<time.h>
#include<stdio.h>
#include<string.h>
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define MAX (1<<22)
#define INFTY 100000000
#define NULL 0

int Cost[MAX][30];
int C[30][30];
struct node *generate_set(unsigned int seed, int n);
struct node *generate_subset(unsigned int seed, int n);

// for backtracking algorithm
int visit[30];
int backtrackOpt = INFTY;// optimal value for backtracking algorithm

struct node {
  int id;
  int x;
  struct node *next;
};
//void main (void){
//	int n = 4;
//	C[0][0] = 0; C[0][1] = 5; C[0][2] = 7; C[0][3] = 3;
//	C[1][0] = 5; C[1][1] = 0; C[1][2] = 10; C[1][3] = 4;
//	C[2][0] = 7; C[2][1] = 10; C[2][2] = 0; C[2][3] = 2;
//	C[3][0] = 3; C[3][1] = 4; C[3][2] = 2; C[3][3] = 0;
//	printf("optimal tour: %d \n", dynamic_tsp(n));
//}

int dynamic_tsp (int n){
	unsigned int set;
	int size = 1 << n;
	struct node *subsets[size];
	generate_all_subsets(subsets,size, n);
	struct node *subset;
	struct node *iterator;
	int i = 0;
	int opt_tour = INFTY;
	int s = 2;
	for(s = 2; s < n; s++){
		set = (1<<s)-1; // the first set of size s in lexicographic order
		while(1){
			if((set&1) == 0){
				subset = subsets[set]; // subsets of the set "set"
				iterator = subset->next; // skip the head
				while(iterator != NULL){
					subtour_cost(subsets, iterator->id, iterator->x);
					if(s == n-1){// save Cost[S][i] for S such that |S| = n-2
						opt_tour = min(opt_tour,Cost[iterator->id][iterator->x] + C[iterator->x-1][0]);
					}
					iterator = iterator->next;
				}
			}
			set = next_set(set, n);// generate next subset in lexicographic order
			if(set == 0){ // no more subset
				break;
			}
		}
	}
	return opt_tour;
}


void generate_all_subsets(struct node *subsets[], int size, int n){
	int i = 0;
	for(i = 1; i < size; i++){
		subsets[i] = generate_subset(i,n);
	}
}

void subtour_cost(struct node *subsets[], int set_id, int i){
	struct node *subset = subsets[set_id];
	struct node *iterator = subset->next;
	if(iterator->id == 0){// if the set with id set_id has only one element
		Cost[set_id][i] = C[0][iterator->x-1] + C[iterator->x-1][i-1];
	}else{
		Cost[set_id][i] = INFTY;
		while(iterator != NULL){
			Cost[set_id][i] = min(Cost[set_id][i], Cost[iterator->id][iterator->x] + C[iterator->x-1][i-1]);
			iterator = iterator->next;
		}
	}

}

struct node *generate_subset(unsigned int seed, int n){
	struct node *head;
	head = malloc( sizeof(struct node));
	head->next = NULL;
	head->id = seed;
	struct node *iterator = head;
	int i = 0;
	for(i = 0; i< n; i++){
		if(((seed >> i)&1) == 1){
			struct node* elem =  malloc( sizeof(struct node) );
			elem->id = (1<<i)^seed;
			elem->x = i+1;
			elem->next = NULL;
			iterator->next = elem;
			iterator = iterator->next;
		}
	}
	return head;
}

struct node *generate_set(unsigned int seed, int n){
	struct node *root;
	root = malloc( sizeof(struct node));
	root->x = seed;
	root->next = NULL;
	struct node *iterator = root;
	unsigned int w = seed;
	while(1){
		unsigned set_id = next_set(w,n);
		if(set_id != 0){
			struct node* elem =  malloc( sizeof(struct node) );
			elem->x = set_id;
			elem->next = NULL;
			iterator->next = elem;
			iterator = iterator->next;
		} else break;
	}
	return root;
}
int next_set(unsigned int v, int n){
	unsigned int w;
	unsigned int t = (v |(v - 1)) + 1;
	w = t | ((((t & -t) / (v & -v)) >> 1) - 1);
	if(w >> n == 0)return w;
	else return 0;
}

void backtrack(int i, int currTourVal, int n){
	visit[i] = 1;
	int j = 0;
	int visitable = 0;
	for(j = 0; j < n; j++ ){
		if(visit[j] == 0){
			visitable = 1;
			if(currTourVal + C[i][j] < backtrackOpt){
				backtrack(j, currTourVal + C[i][j], n);
			}
		}
	}
	if(visitable == 0){
		backtrackOpt = min(backtrackOpt, currTourVal + C[i][0]);
	}
	visit[i] = 0;
}






