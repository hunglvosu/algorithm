#include<time.h>
#include<stdio.h>
#include<string.h>

void quick_sort(int _array[], int x, int y){
	if(x < y) {
		int p = (y+x)/2;
		int r = partition(_array, x,y,p);
		quick_sort(_array, x,r-1);
		quick_sort(_array, r+1,y);
	}
}

