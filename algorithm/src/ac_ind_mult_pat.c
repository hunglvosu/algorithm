/*
 * An implementation of Aho-Corasick multiple-pattern search algorithm when the keyword set is independent
 * Warning: this implementation is not fully tested, use at your own risk
 * See http://www.giaithuatlaptrinh.com/?p=703 for more details.
 *
 *  Created on: Jan 1, 2016
 *      Author: hunglv
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAXS 10000 // the maximum number of states
#define ALB 26 // the size of the alphabet

// this struct is for the queue to do bfs on the trie
struct Node {
	int data;
	struct Node* next;
};
struct Node* front = NULL;
struct Node* rear = NULL;
// queue interfaces
void enqueue(int x);
int dequeue();
int front_queue();
int is_empty();

char **Keys;
int nstates;// the number of states

void print_char_arr(char *str);
int **construct_trie(char **Keys, int num_keys, int num_state, int alpb);
int *construct_fsm(char **Keys, int **G, int alpb, int num_keys);
void independent_search(char *T, char **Keys, int num_states, int num_keys, int alpb);
int is_leaf(int x, int **G, int alpb); // check whether a state is a leaf of the Trie
int id(char c); // return the index of a character c in the alphabet
char **L;

int main(){
	char *ka  = " she"; // add a space so that every string is indeded from 1
	char *kb  = " his";
	char *kc  = " hers";
	Keys = (char **)malloc(3*sizeof(char*));
	Keys[0] = ka; Keys[1] = kb; Keys[2] = kc;
	char *T = " ushers";
	L =  (char **)malloc(MAXS*sizeof(char *));
	independent_search(T, Keys, MAXS, 3, ALB);
	return 0;
	}


// Construct the Trie and stores its structure in a 2D array
// Keys:	the set of keywords
// num_keys:	the number of keywords in Keys
// num_state: 	the number of states in the finite state machine, this parameter need not to be exact
//		any upper bound of this parameter is ok
// alpb:	the size of the alphabet

int **construct_trie(char **Keys, int num_keys, int num_state, int alpb){
	int **G;
	G = (int **)malloc(num_state*sizeof(int*));
	int i = 0;
	for(; i < num_state; i++){
		G[i] = (int *)malloc(alpb*sizeof(int));	
		memset(G[i],-1, alpb*sizeof(int));
	}
	int state  = 0;
	int j = 1;
	for(i = 0; i < num_keys; i++){
		int klen = strlen(Keys[i])-1; // -1 since each string is added a space char at the beginning
		int ell = 0;
		j = 1;
		while(G[ell][id(Keys[i][j])] != -1){
			ell = G[ell][id(Keys[i][j])];
			j ++;
		}
		while(j <= klen){
			state++;
			G[ell][id(Keys[i][j])] = state;
			j++;
			ell = state;
		}
		printf("key '");
		print_char_arr(Keys[i]);
		printf("' is added to state %d\n",ell);
		L[ell] = Keys[i]; // put the key to the state i
	}
	nstates = state+1;
	printf("the numer of state is %d\n", nstates);
// print out the trie
//	for(i = 0; i < nstates; i++){
//		for(j = 0; j < alpb; j++){
//			printf("%d ", G[i][j]);
//		}
//		printf("\n");
//	}
	return G;
}

// Construct the finite state machine for the set of keywords
// Keys:	the set of keywords
// G:		the 2D array represents the Trie for the keyword set Keys
// alpb: 	the size of the alphabet
// num_keys:	the number of keys in the keyword set Keys

int *construct_fsm(char **Keys, int **G, int alpb, int num_keys){
		int *F;
		F = (int *)malloc(nstates*sizeof(int));
		F[0] = -1;
		enqueue(0);
		int i = 0;
		while(is_empty() == 0){
			int j = dequeue();
			int c = 0;
			for(; c < alpb; c++){
				if(G[j][c] != -1){
					// j is the parent of i
					i = G[j][c];
					int k = F[j];
					while(k >= 0 && G[k][c] == -1){
						k  = F[k];
					}
					if(k == -1){
						F[i] = 0;
					}else{
						F[i] = G[k][c];
					}
					enqueue(i);
				}
			}
		} // end while
		printf("the failure array: \n");
		for(i = 0; i < nstates; i++){
			printf("%d ", F[i]);
		}
		printf("\n");
		return F;
	}


// search keywords in array Keys in the text T
// Keys: 	the 2D char array holding keywords
// T:		the pointer to the text array
// num_states: 	the number of states in the finite state machine, 
// 		this parameter need not to be exact, you can input the maximum number of states
// num_keys: 	the number of keys in the keyword set
// alpb:	the size of the alphabet. 
void independent_search(char *T, char **Keys, int num_states, int num_keys, int alpb){
	int **G = construct_trie(Keys, num_keys, num_states, alpb);
	int *F = construct_fsm(Keys,G, alpb, num_keys);
	int j = 0;
	int i = 1;
	int n = strlen(T) - 1; // characters in T are indexed from 1
	for(; i <= n; i++){
		while(j >= 0 && G[j][id(T[i])] == -1){
			j = F[j];
		}
		if(j == -1) j = 0;
		else {
			j = G[j][id(T[i])];
			if(is_leaf(j, G, alpb)){
				printf("the keyword found at state %d is: ", j);
				print_char_arr(L[j]);
				printf("\n");
				int keylen = strlen(L[j])-1; // ignore the first empty character
				printf("this keywords is at pos %d of the text\n", i -keylen + 1);
				j = F[j];
			}
		}
	}
}

// check whether a state is a leaf of the Trie
// x: 	the state 
// G: 	the Trie
// alpb:the size of the alphabet

int is_leaf(int x, int **G, int alpb){
	int j = 0;
	for(; j < alpb; j++){
		if(G[x][j] != -1){
			return 0;
		}
	}
	return 1;
}

void print_char_arr(char *str){
	int len = strlen(str)-1;
	int i = 1;
	for(; i <= len; i++)printf("%c",str[i]);
}

int id(char c){
	return c - 'a';
}
//////////////////////////////////////////////////
///
///	QUEUE IMPLEMENTATION BELOW
///
////////////////////////////////////////////////

void enqueue(int x) {
	struct Node* temp = 
		(struct Node*)malloc(sizeof(struct Node));
	temp->data =x; 
	temp->next = NULL;
	if(front == NULL && rear == NULL){
		front = rear = temp;
		return;
	}
	rear->next = temp;
	rear = temp;
}

int dequeue() {
	struct Node* temp = front;
	if(front == NULL) {
		printf("Queue is Empty\n");
		return;
	}
	if(front == rear) {
		int val = front->data;
		front = rear = NULL;
		free(temp);
		return val;
	}
	else {
		int val = front->data;
		front = front->next;
		free(temp);
		return val;
	}
}

int front_queue() {
	if(front == NULL) {
		printf("Queue is empty\n");
		return;
	}
	return front->data;
}	

int is_empty(){
	return (front == NULL? 1 : 0);	
}
