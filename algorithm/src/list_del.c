/*
 * An implementation of Kruskal algorithm to find the minimum spanning tree of a graph. This implement is combined with Union-Find data structure.
 *
 * Warning: this implementation is not fully tested, use at your own risk.
 * See http://www.giaithuatlaptrinh.com/?p=1140 for more details.
 *
 *  Created on: May 24, 2016
 *  Author: Hung Le
 */   
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct llnode{
	int x;
	struct llnode *next;
} llnode;

void print(llnode *head);
//void delete(llnode **curr);
void delete(llnode *curr);

int main(){
	llnode *head = (llnode *)malloc(sizeof(llnode));
	head->x = 0;
	head->next = NULL;
	llnode *tail = head;
	llnode *curr;
	int i = 1;
	for(i = 1; i < 5; i++){
		curr = (llnode *)malloc(sizeof(llnode));
		curr->x = i;
		curr->next = head;
		head = curr;
	}
	print(head);
	//delete(&(head->next->next->next->next));
	delete(head->next->next);
	print(head);
	return 0;
}


void print(llnode *head){
	while(head != NULL){
		printf("%d, ", head->x);
		head = head->next;
	}
	printf("\n");
}

/*void delete(llnode **curr){
	*curr = (*curr)->next;
}*/

void delete(llnode *curr){
	curr->x = curr->next->x;
	curr->next = curr->next->next;
}