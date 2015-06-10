/*
 * linkedList.c
 *
 *  Created on: Jun 6, 2015
 *      Author: hunglv
 */

#include <stdio.h>
#include <stdlib.h>
#define NULL 0

struct node *single_list_demo(int n, int s);

struct node {
  int x;
  struct node *next;
};

//void main(void)
//{
//   array_of_list_demo(10,5);
//}
struct node *append(int v) {
	struct node *ptr;
	struct node *t;
	ptr->x = 1;
	return ptr;
}

struct node *single_list_demo(int n, int s){
	/* This won't change, or we would lose the list in memory */
    struct node *root;
    /* This will point to each node as it traverses the list */
    struct node *conductor;
    root = malloc( sizeof(struct node) );
    int i = 0;
    root->next = NULL;
    root->x = s;
    conductor = root;
    for(i = 1; i < n; i++){
    	struct node* elem =  malloc( sizeof(struct node) );
    	elem->x = s+i;
    	elem->next = NULL;
    	conductor->next = elem;
    	conductor = conductor->next;
    }
    return root;
}

void array_of_list_demo(int n, int m){
	struct node *array[n];
	int i = 0;
	for(i = 0; i < n; i++){
		array[i] = single_list_demo(m, i*n);
	}
	for(i = 0; i < n; i++){
		print_list(array[i]);
	}
}

