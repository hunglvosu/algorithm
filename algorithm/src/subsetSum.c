/*
 * subsetSum.c
 *
 *  Created on: May 29, 2015
 *      Author: hunglv
 */

#include<time.h>
#include<stdio.h>
#include<string.h>

void main (void){
	int X[7] = {8,6,7,5,3,10,9};
	int T = 12;
	printf("%d\n", dynamic_subset_sum(X, 7, T));
}

int subset_sum(int X[], int r, int T){
	if(T == 0) return 1;
	if(T < 0 || r == -1) return 0;
	if(subset_sum(X, r-1, T-X[r]) == 1) return 1;
	if(subset_sum(X,r-1, T) == 1) return 1;
	return 0;
}

int dynamic_subset_sum(int X[], int size, int T){
	int S[size+1][T+1];
	int i = 0, t = 0;
	for(i = 0 ; i < size+1; i++)
		memset(S[i], 0, sizeof(S[i])); // set every element to be 0
	for( i = 0 ; i < size+1; i++){
		S[i][0] = 1;
	}
	for(i = 1; i < size+1; i++){
		S[i][0] = 1;
		for(t = 1; t < X[i-1]; t++){
			S[i][t] = S[i-1][t];
		}
		for(t = X[i-1]; t < T+1; t++){
			S[i][t] = (S[i-1][t] + S[i-1][t - X[i-1]] > 0? 1 : 0);
		}
	}
	return S[size][T];
}



