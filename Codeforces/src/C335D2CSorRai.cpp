//============================================================================
// Author      : Hung Le
// Description : C++ Code for http://codeforces.com/contest/606/problem/C
//============================================================================

#include <iostream>
#include<stdlib.h>
#include<string.h>
#include<queue>
using namespace std;
typedef unsigned long long LLU;
#define loop(i,n) for(int i = 0; i < n; i++)
#define loopp(i,j,n) for(int i = j; i < n; i++)
#define pr(s) cout << s << endl;
#define MAX 750
#define INFTY 10000000000000
#define ALP  2


int N;
int *A;
int *I;
int *F;
void printArray(int *A, int i,int j);
int main() {
	cin >> N;
	A = (int *)(malloc(N*sizeof(int)));
	I = (int *)(malloc(N*sizeof(int)));
	F = (int *)(malloc(N*sizeof(int)));
	memset(F,0,N*sizeof(int));
	loop(i,N){
		cin >> A[i];
		I[A[i]-1] = i;
	}
	F[0] = 1;
	int m = 1;
	loopp(i,1,N){
		if(A[i] == 1) F[i] = 1;
		else {
			F[i] = F[I[A[i]-2]]+1;
		}
		m = (m > F[i] ? m : F[i]);
	}
	cout << N-m << endl;
}

void printArray(int *A, int i,int j){
	for(int k = i; k <= j-1; k++ ){
		cout << A[k]<<" ";
	}
	cout << A[j]<< endl;
}
