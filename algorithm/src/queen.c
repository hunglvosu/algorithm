/*
 * queen.c
 *
 *  Created on: May 29, 2015
 *      Author: hunglv
 */
#include<time.h>
#include<stdio.h>
#include<string.h>
void main (void){
	int _array[8];
	memset(_array, 0, sizeof(_array));
	recursive_queen(_array, 7, 0);
}

void recursive_queen(int _array[], int n, int r){
	int i=1, j = 1;
	int legal = 0;
	if(r == n +1){
		print_queen(_array, n);
		exit(0);
	}
	else{
		for(j = 1; j <= n ; j++){
			legal = 1; // legal = true
			for(i = 1; i <= r-1; i++){
				if(_array[i] == j || _array[i] == j + r - i ||_array[i] == j - r + i){
					legal = 0; // legal = false
				}
			}
			if(legal == 1) {
				// legal = true
				_array[r] = j;
				recursive_queen(_array, n, r+1);
			}
		}
	}
}

void print_queen(int _array[], int n){
	int i = 1, j =1;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n ; j++){
			if(j == _array[i]){
				printf("  1   ");
			}
			else printf("  0   ");
		}
		printf("\n");
	}
}


