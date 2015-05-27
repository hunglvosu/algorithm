#include<time.h>
#include<stdio.h>
#include<string.h>


void main(void){
	int SIZE = 2000000;
	int _array[SIZE];
	int k = rand()%SIZE + 1;
	memset(_array, 0, sizeof(_array));
	random_array(_array, SIZE, 10000);
	clock_t tick = clock();
	quick_sort(_array, 0, SIZE-1);
	clock_t tock = clock();
	printf("time: %fs",(double)(tock - tick)/CLOCKS_PER_SEC);

}

void quick_sort(int _array[], int x, int y){
	if(x < y) {
		int p = (y+x)/2;
		int r = partition(_array, x,y,p);
		quick_sort(_array, x,r-1);
		quick_sort(_array, r+1,y);
	}
}
