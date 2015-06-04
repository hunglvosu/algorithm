/*
 * String Edi tDistance.c
 *
 *  Created on: Jun 3, 2015
 *      Author: hunglv
 */

#include<time.h>
#include<stdio.h>
#include<string.h>



int edit_distance(char A[], char B[]){
	int n = strlen(A), m = strlen(B);
	int ED[n+1][m+1];
	int i = 0;
	int j = 0;
	for(i = 0; i  <= n; i++){
		memset(ED[i], 0, sizeof(ED[i]));
	}
	for(j = 0; j <= m; j++){
		ED[0][j] = j;
	}
	for(i = 0 ; i <= n; i++){
		ED[i][0] = i;
	}
	int diff;
	for(i = 1; i <= n ;i++){
		for(j = 1; j <= m; j++){
			ED[i][j] = ED[i-1][j] + 1;
			ED[i][j] = (ED[i][j] < ED[i][j-1] + 1? ED[i][j] : ED[i][j-1] + 1);
			diff = (A[i-1] == B[j-1]? 0 :  1);
			ED[i][j] = (ED[i][j] < ED[i-1][j-1] + diff? ED[i][j] : ED[i-1][j-1] + diff);
		}
	}
	return ED[n][m];
}

int mem_saved_edit_distance(char A[], char B[]){
	int n = strlen(A), m = strlen(B);
	int ED[m+1];
	int i = 0;
	int j = 0;
	memset(ED, 0, sizeof(ED));
	int dag = 0;
	int left = 0;
	for(j = 0; j <= m; j++){
		ED[j] = j;
	}
	int diff;
	int curr = 0;
	for(i = 1; i <= n ;i++){
		left = i;
		dag = i-1;
		for(j = 1; j <= m; j++){
			curr = ED[j] + 1;
			curr = (curr < left + 1? curr : left + 1);
			diff = (A[i-1] == B[j-1]? 0 :  1);
			curr = (curr < dag + diff? curr : dag + diff);
			left = curr;
			dag = ED[j];
			ED[j] = curr;
			}
	}
	return ED[m];
}



