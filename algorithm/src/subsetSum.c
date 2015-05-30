/*
 * subsetSum.c
 *
 *  Created on: May 29, 2015
 *      Author: hunglv
 */

#include<time.h>
#include<stdio.h>
#include<string.h>



int subset_sum(int X[], int r, int T){
	if(T == 0) return 1;
	if(T < 0 || r == -1) return 0;
	if(subset_sum(X, r-1, T-X[r]) == 1) return 1;
	if(subset_sum(X,r-1, T) == 1) return 1;
	return 0;
}



