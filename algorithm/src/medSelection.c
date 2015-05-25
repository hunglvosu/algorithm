/*
 * medSelection.c
 *
 *  Created on: May 24, 2015
 *      Author: hunglv
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {

	int i = 0;
	for ( i = 0; i < 100; i++){
		int size = rand()%15;
		int k = rand()%size+1;
		printf("size: %d   k:%d \n", size, k);
		if(test(size, k)==0) break;
	}
	int SIZE = 0;

//	int arr[SIZE];
	//int arr[10] = {1,9,12,13,16,23,16,25,27,25};
//	int k = SIZE/2;
//	random_array(arr,SIZE, 10000);
//	int r = quick_select(arr, 0, SIZE-1, k-1);
//	buble_sort(arr, SIZE);
///	printf("%d --- %d\n",r,arr[k-1]);
	//printArr(arr,SIZE);
	return EXIT_SUCCESS;
}

int test(int size, int k){
		int _array[size];
		random_array(_array, size, 10000);
		int r = quick_select(_array, 0, size-1, k-1);
		buble_sort(_array, size);
		if(r == _array[k-1]) {
			printf("Pass\n");
			return 1;
		}
		else {

			printf("Fail\n");
			printf("r: %d\n",r);
			printArr(_array, size);
			return 0;
		}

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

void printArr(int arr[] , int n){
	int i = 0;
	for (i = 0 ; i < n ; i++){
		printf("%d  ", arr[i]);
	}
}

