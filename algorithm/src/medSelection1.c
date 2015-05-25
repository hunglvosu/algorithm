/*
 * medSelection.c
 *
 *  Created on: May 24, 2015
 *      Author: hunglv
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1000000
int main(void) {
	int _array[SIZE];
	int k = rand()%SIZE + 1;
	memset(_array, 0, sizeof(_array));
	random_array(_array, SIZE, 10000);
	int r = quick_select(_array, 0, SIZE-1, k-1);
	printf("%d\n",r);
	return EXIT_SUCCESS;
}

int quick_select(int arr[], int x, int y, int k){
	if(y <= x) return arr[x];
	else {
		int p = (y+x)/2;
		int r = partition(arr, x, y, p);
		if ( k < r){
			return quick_select(arr, x, r-1, k);
		}else if (k > r) {
			return quick_select(arr, r+1, y, k);
		}else {
			return arr[r];
		}
	}
}



