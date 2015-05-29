/*
 * mergeSort.c
 *
 *  Created on: May 26, 2015
 *      Author: hunglv
 */


#include<time.h>
#include<stdio.h>
#include<string.h>


void merge_sort(int _array[], int x, int y){
	if(x < y){
		int m = (y + x +1)/2-1;
		merge_sort(_array, x, m);
		merge_sort(_array, m+1,y);
		merge(_array, x, y, m);
	}
}

void merge(int _array[], int x, int y, int pivot){
	int i = x, k = 0;
	int j = pivot + 1;
	int size = y-x+1;
	int _brray[y-x+1];
	memset(_brray, 0, sizeof(_brray));
    for(k = 0 ; k < size; k ++) {
	   if(j > y) {
		   _brray[k] = _array[i]; i ++;
	   } else if(i > pivot) {
		   _brray[k] = _array[j]; j ++;
	   } else if(_array[i] < _array[j]){
		   _brray[k] = _array[i]; i++;
	   } else {
		   _brray[k] = _array[j]; j++;
	   }
   }
   for(i = 0; i < size ; i++) _array[x+i] = _brray[i];
}

