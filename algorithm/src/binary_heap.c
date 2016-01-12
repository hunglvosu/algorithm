/*
 * An implementation of heap data structure and heapsort
 * Warning: this implementation is not fully tested, use at your own risk
 * See http://www.giaithuatlaptrinh.com/?p=736 for more details.
 *
 *  Created on: Jan 12, 2016
 *      Author: hunglv
 */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define INFTY 1000000000

int *H; // the heap
int n = 0; // the number of elements in the current Heap
int mlen = 16; //the initial length of the heap
 
void insert(int x);
void up_heapify(int u);
int parent(int u);
void print_heap();
void decrease_key(int u, int k);
void down_heapify(int u);
int extract_min();
void build_heap(int *A, int len);
int *heapsort(int *A, int size);

int main(){
	H = (int *)malloc(mlen*sizeof(int));
	int A[9] = {8,6,4,5,2,2,9,7,3};
//	int i = 0;
//	for(; i < 9; i++){
//		insert(A[i]);
//	}
//	decrease_key(8,1);
//	build_heap(A,9);
//	print_heap();
	int *B = heapsort(A, 9);
	int i = 0;
	for(; i < 9; i++)printf("%d ",B[i]);
	printf("\n");
}


int  *heapsort(int *A, int size){
	build_heap(A, size);
	int i = 0;
	for(; i < size; i++){
		A[i] = extract_min();
	}
	return A;	
}

void insert(int x){
	if(n == mlen){ // if the heap is full, double the size of the heap
		H = (int *)realloc(H,2*mlen*sizeof(int));
		mlen = 2*mlen;
	}
	H[n] = x;
	n++;
	up_heapify(n-1);
}

void up_heapify(int u){
	int v = parent(u);
	if(v != -1 && H[u] < H[v]){ // u is not the root of the heap
		int tmp = H[u];
		H[u] = H[v];
		H[v] = tmp;
		up_heapify(v);
	}
}

// Note that array in C is indexed from 0 
// Two children of a node u is 2u+1 and 2u+2, the smaller one is the left child

int parent(int u){
	return ((u&1)==0 ? ((u-2)>> 1) : (u-1) >> 1);
}



void print_heap(){
	int i = 0;
	for(; i < n; i++){
		printf("%d ", H[i]);
	}
	printf("\n");
}


void decrease_key(int u, int k){
	if(H[u] < k){
		printf("new key is bigger than the old key\n");
		return;
	} else {
		H[u] = k;
		up_heapify(u);
	}
}

int extract_min(){
	int tmp  = H[0];
	H[0] = H[n-1];
	n--;
	down_heapify(0);
	return tmp;
}

void down_heapify(int u){
	int v = 2*u+1;
	int w = 2*u+2;
	int min = INFTY;
	int x = -1;
	if(v < n && H[u] > H[v]){
		min = H[v];
		x = v;
	}
	if(w < n && H[u] > H[w] && H[w] < min){
		x = w;
	}
	if(x != -1){
		int tmp = H[u];
		H[u] = H[x];
		H[x] = tmp;
		down_heapify(x);
	}
}

// Build the heap from an array in O(n) time
void build_heap(int *A, int len){
	n = len;
	mlen = n+1;
	H = (int *)malloc(mlen*(sizeof(int)));
	int i = 0;
	for(; i < len; i++){
		H[i] = A[i];
	}
	for(i = len-1; i >=0; i--){
		down_heapify(i);
	}
}
