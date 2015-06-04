/*
 * Longest Increasing Subsequence
 *
 *  Created on: Jun 1, 2015
 *      Author: hunglv
 */

#include<time.h>
#include<stdio.h>
#include<string.h>
#define INFTY 1000000000




int mem_waste_lis(int A[], int size){
	int LIS[size+2][size+2];
	int i = 0, j = 0;
	for(i = 0 ; i < size + 2; i++){
		memset(LIS[i], 0, sizeof(LIS[i]));
	}
	for (i = 1; i <= size; i++){
		for(j = 1; j <= size+1; j++){
			if(A[j-1] < A[i-1]){// array A is indexed from 0
				LIS[i][j] = LIS[i-1][j];
			}else{
				LIS[i][j] = (LIS[i-1][i] + 1 < LIS[i-1][j] ? LIS[i-1][j] :  LIS[i-1][i] + 1 );
			}
		}
	}
	return LIS[size][size+1];
}
int mem_saved_lis(int A[], int size){
	int B[size];
	int C[size];
	memset(B, 0, sizeof(B)); // set every element of B to 0
	memset(C, 0, sizeof(C)); // set every element of C to 0
	B[0] = 1;
	C[0] = 1;
	int i = 1, j = 0;
	int max = 0;
	for (i = 1; i < size ; i++){
		max = 0;
		for(j = 0; j < i; j++){
			if(B[j] > max && A[j] <= A[i]){
				max = B[j];
			}
		}
		B[i] = max + 1;
		C[i] = B[i] > C[i-1] ? B[i] : C[i-1];
	}
	return C[size-1];
}

int fast_lis(int A[], int size){
	int D[size+1];
	memset(D, 0, sizeof(D)); // set every element of D to 0
	D[0] = A[0];
	int i = 1,  k =0;
	int p = 0;
	for (i = 1; i < size ; i++){
		k = floor_binary_search(D, 0, p, A[i]);
		 if(k == p){ // found a longer subsequence
		        D[p+1] = A[i];
				p++;
		} else {
			D[k+1] = A[i];
		}
	}
	return p+1;
}

int floor_binary_search(int _array[], int x, int y, int a){
	int i = 0;
	if(y - x <=5){ // trying brute force search
		if(a < _array[x]) return x-1;
		if(a >= _array[y]) return y;
		else {
			for(i = x; i < y; i++){
				if(_array[i] <= a && a <_array[i+1]){
					return i;
				}
			}
		}
	} else {
		int m = (x+y)/2;
		if(a < _array[m]){
			return floor_binary_search(_array, x, m-1, a);
		} else if(a >= _array[m+1]){
			return floor_binary_search(_array, m+1, y, a);
		} else return m;
	}
}
