/*
 * function.c
 *
 *  Created on: May 24, 2015
 *      Author: hunglv
 */


int partition(int arr[], int x, int y, int p){
	swap(&arr[p],&arr[y]);
	int i = x;
    int j = y;
    while( i < j){
    	while(arr[i] < arr[y] && i < j){i++;}
    	while(arr[j] >= arr[y] && i < j){j--;}
    	if(i < j) {
    		swap(&arr[i],&arr[j]);
    		i++; j--;
    	}
    }
    swap(&arr[i],&arr[y]);
    return i;
}
void swap(int *a, int *b){
		int i = *a;
		*a = *b;
		*b = i;
}



