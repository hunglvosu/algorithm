/*
 * A C implementation of Z algorithm from the blog post http://www.giaithuatlaptrinh.com/?p=250
 *
 *  Created on: Jul 21, 2015
 *      Author: hunglv
 */

#include<time.h>
#include<stdio.h>
#include<string.h>
#include"stringsearch.h"
#include"utilities.h"

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) < (y)) ? (y) : (x))
#define MAXN 10000
#define INFTY 100000000


//int main (void){
//	char S[] = " aaababaaaaab";
//	int Z[MAXN];
//	int n = strlen(S)-1;
//	compute_Z_function(S,Z, n);
//	printArr(Z, n+1);
//	return 0;
//}

void compute_Z_function(char *S,int *Z, int n){
	Z[1] = 0;
	int R = 0, L = 0;
	int i = 0, j = 0, k = 0, next = 0;
	for(i = 2; i <=n; i++){
		next  = 0;
		if(i >= R){
			k = i; j = 1;
			next = 1; // continue comparing characters of S
		} else {
			int al = i - L + 1;
			int be = R - L + 1;
			if(i + Z[al] <= R){
				Z[i] = Z[al];
			} else{ // i + Z[al] -1 = R[i-1]
				k = R + 1;
				j = be - al + 2;
				next = 1; // Z[i] is longer than Z[al], continue comparing characters of S
			}

		}
		if(next == 1){
			while(k <= n && S[k] == S[j]){
				k++; j++;
			}
			Z[i] = j-1;
			L = i; R = L + Z[i] - 1;
		}
	}
}





