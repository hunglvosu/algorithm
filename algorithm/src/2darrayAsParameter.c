/*
 * 2darrayAsParameter.c
 *
 *  Created on: Jun 4, 2015
 *      Author: hunglv
 */

#include <stdio.h>

void print(int *arr, int m, int n)
{
    int i, j;
    for (i = 0; i < m; i++)
      for (j = 0; j < n; j++){
    	   *((arr+i*n) + j) = 3;
      }

}

//void main (void){
//	 int arr[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//	 int m = 3, n = 3;
//	 print((int *)arr, m, n);
//	 printArr(arr[0], 3);
//}


