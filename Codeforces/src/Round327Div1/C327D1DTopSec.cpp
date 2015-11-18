//============================================================================
// Author      : Hung Le
// Description : C++ Code for http://codeforces.com/contest/590/problem/C
//============================================================================

#include <iostream>
#include<stdlib.h>
#include<string.h>
#include<queue>
//#include "utils.h"
using namespace std;
#define loop(i,n) for(int i = 0; i < n; i++)
#define loopp(i,j,n) for(int i = j; i < n; i++)
#define pr(s) cout << s << endl;
#define MAX 150
#define INFTY 10000000
int N , K, S;
int cost = 0;
int *A;
int **F[2];

int int_cmp(const void *a, const void *b);
void printArray(int *A, int i,int j);

int main() {
	cin >> N >> K >> S;
	A = (int *)malloc(N*sizeof(int));
	loop(i, N){
		cin >> A[i];
	}
	if(S  > N*(N-1)/2) {
		qsort(A, N, sizeof(int), &int_cmp);
//		printArray(A, 0, N-1);
		loop(i, K){
			cost += A[i];
		}
		cout << cost << endl;
	} else {
		int P = S + K*(K-1)/2;
		F[0] = (int **)(malloc((K+1)*sizeof(int*)));
		F[1] = (int **)(malloc((K+1)*sizeof(int*)));
		loop(j, K+1){
			F[0][j] = (int *)malloc((P+1)*sizeof(int));
			F[1][j] = (int *)malloc((P+1)*sizeof(int));
		}

//		cout << "p "<< P <<endl;
		loop(i,N){
			loop(j , K+1){
				loop(k, P+1){
					F[i&1][j][k] = INFTY;
				}
			}
		}
		loop(i, N){
			loop(k, P+1){
				F[i&1][0][k] = 0;
			}
		}
		loop(k,P+1){
			F[0][0][k] = 0;
			F[0][1][k] = A[0];
		}
		loopp(i,1,N){
			loopp(j,1,K+1){
				loop(k,P+1){
					if(i <= k) F[i&1][j][k] = (F[(i+1)&1][j-1][k-i] + A[i] < F[(i+1)&1][j][k] ?F[(i+1)&1][j-1][k-i] + A[i]: F[(i+1)&1][j][k]);
					else F[i&1][j][k] = F[(i+1)&1][j][k];
				}
			}
		}
		cout << F[(N-1)&1][K][P] << endl;

	}

	return 0;
}

int int_cmp(const void *a, const void *b){
	int *x = (int *)a; int *y = (int *)b;
	return (*x-*y);
}

void printArray(int *A, int i,int j){
	for(int k = i; k <= j-1; k++ ){
		cout << A[k]<<" ";
	}
	cout << A[j]<< endl;
}

