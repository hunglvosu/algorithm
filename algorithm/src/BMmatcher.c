/*
 * An implementation of Boyer-Moore matching algorithm
 *
 *  Created on: Jul 19, 2015
 *      Author: hunglv
 */

#include<time.h>
#include<stdio.h>
#include<string.h>
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) < (y)) ? (y) : (x))
#define MAXN 100
#define MAXM 20
#define INFTY 100000000

char T[MAXN];
char P[MAXM];
int  R[28];

int X[28];
int S[28][MAXM];

void main (void){
	char text[] = "dlcimglkblhcch";
	char pattern[] = "mglkblhc";
	int i = 0;
	T[0] = " ";
	for(i = 0; i < strlen(text); i++){
		T[i+1] = text[i];
	}
	P[0] = " ";
	for(i = 0; i < strlen(pattern); i++){
		P[i+1] = pattern[i];
	}
	int n = 14, m = 8;
	i = 1;
	printf("%d\n",BFmatcher(n,m));
	printf("%d\n",BMmatcher(n,m));
	printf("%d\n",fastBMmatcher(n,m));
//	for(i = 0; i < 100; i++){
//		test(i);
//	}
}

int BMmatcher(int n, int m){
	badCharBackup(m);
	int i = 1, j = 0, p = 0, skip = 0;
	while(i <= n-m+1){
		skip = 0;
		j = m;
		while(j >= 1 && skip == 0){
			if(T[i+j-1] != P[j]){
				p = T[i+j-1]-96;
				skip = max(1, j - R[p]);
			}
			j--;
		}
		if(skip == 0) return i;
		i = i + skip;
	}
	return -1;
}

void badCharBackup(int m){
	int i = 0;
	memset(R, 0, sizeof(R));
	for(i = 1; i <= m; i++){
		R[P[i] - 96] = i;
	}
}

int fastBMmatcher(int n, int m){
	extendedBadChar(m);
	int i = 1, j = 0, p = 0, skip = 0;
	while(i <= n-m+1){
		skip = 0;
		j = m;
		while(j >= 1 && skip == 0){
			if(T[i+j-1] != P[j]){
				p = T[i+j-1]-96;
				skip = j - S[p][j];
			}
			j--;
		}
		if(skip == 0) return i;
		i = i + skip;
	}
	return -1;
}

void extendedBadChar(int m){
	memset(X, 0, sizeof(X));
	int i = 0,k = 0, p = 0;
	for(k = 1; k < 28; k++)
		memset(S[k], 0, sizeof(S[k]));
	for(i = 1; i <= m ; i++){
		for(k = 1; k < 28; k++){
			S[k][i] = X[k];
		}
		X[P[i] - 96] = i;
	}
}
