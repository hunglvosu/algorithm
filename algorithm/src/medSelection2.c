/*
 * medSelection2.c
 *
 *  Created on: May 25, 2015
 *      Author: hunglv
 */

#include<time.h>
#include<stdio.h>
#include<string.h>


void test_linear_selection(){
	int SIZE = 1000000;
	int _array[SIZE];
	int k = rand()%SIZE + 1;
	memset(_array, 0, sizeof(_array));
	random_array(_array, SIZE, 10000);
	int r = linear_selection(_array, 0, SIZE-1, k-1);


}
int linear_selection(int _array[], int x, int y, int k){
	if(y - x <= 24) {
		return med_exhaustive(_array, x, y ,k);
	}
	else {
		int m = (y-x+1)/5 + ((y-x+1)%5 > 0? 1 : 0); // m = ceiling(n/5)
		int _brray[m];
		int i = 0;
        for (i = 0 ; i < m-1 ; i++){
        	_brray[i] = med_of_five(_array[5*i+x], _array[5*i+1+x],_array[5*i+2+x], _array[5*i+3+x], _array[5*i+4+x]);
        }
        _brray[m-1] = _array[y];
        int med_of_brray = linear_selection(_brray, 0, m-1, m/2-1);
        int p  =  0;
        for( i = x ; i <= y  ; i++){
        	if (_array[i] == med_of_brray) p = i;
        }
        int r = partition(_array, x, y, p);
		if ( k < r){
			return linear_selection(_array, x, r-1, k);
		}else if (k > r) {
			return linear_selection(_array, r+1, y, k);
		}else {
			return _array[r];
		}
	}
}


int med_exhaustive(int _array[], int x, int y, int k){
	int i = x, j = x;
	for (i = x; i <= y; i++){
		for (j = i+1; j <= y; j++){
			if(_array[i] > _array[j]) swap(&_array[i], &_array[j]);
		}
	}
	return _array[k];
}
int med_of_five(int a, int b, int c, int d, int e){
	int _array[5] = {a,b,c,d,e};
	int i = 0,j = 0;
	for(i = 0 ; i < 5; i++){
		int smaller = 0;
		int bigger = 0;
		for(j = 0; j < 5; j++)
		if(j != i){
			if(_array[j] < _array[i]) smaller++;
			if(_array[j] > _array[i]) bigger++;
		}
		if(smaller < 3 && bigger  < 3) return _array[i];
	}
  return -1;
}


