/*
 * binarySearch.c
 *
 *  Created on: May 28, 2015
 *      Author: hunglv
 */
#include<time.h>
#include<stdio.h>
#include<string.h>


void main(void){
		int SIZE = 10;
		int _array[10] = {2,4,5,6,7,7,8,10,12,13};
		int a = 6;
		printf("a[%d] = %d\n", binary_search(_array, 0, SIZE-1, a), a);
}


int binary_search(int _array[], int x, int y, int a){
	if(x == y) return x;
	else if( x< y){
		int m = (x+y)/2;
		if(_array[m] < a) {
			return binary_search(_array, m+1, y, a);
		}
		else if(_array[m] > a){
			return binary_search(_array, x, m-1, a);
		} else {
			return m;
		}
	}
	return -1;
}

