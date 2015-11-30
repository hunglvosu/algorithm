////============================================================================
//// Author      : Hung Le
//// Description : C++ Code for http://codeforces.com/contest/590/problem/D
////============================================================================
//
//#include <iostream>
//#include<stdlib.h>
//#include<string.h>
//#include<queue>
////#include "utils.h"
//using namespace std;
//typedef unsigned long long LLU;
//#define loop(i,n) for(int i = 0; i < n; i++)
//#define loopp(i,j,n) for(int i = j; i < n; i++)
//#define pr(s) cout << s << endl;
//#define MAX 150
//#define INFTY 10000000000000
//int N , K, S;
//LLU cost = 0;
//int *A;
//LLU **F[2];
//
//int int_cmp(const void *a, const void *b);
//void printArray(int *A, int i,int j);
//
//int main() {
//	cin >> N >> K >> S;
//	A = (int *)malloc(N*sizeof(int));
//	loop(i, N){
//		cin >> A[i];
//	}
//	if(S  > N*(N-1)/2) {
//		qsort(A, N, sizeof(int), &int_cmp);
////		printArray(A, 0, N-1);
//		loop(i, K){
//			cost += (LLU)A[i];
//		}
//		cout << cost << endl;
//	} else {
//		int P = S + K*(K-1)/2;
//		F[0] = (LLU **)(malloc((K+1)*sizeof(LLU*)));
//		F[1] = (LLU **)(malloc((K+1)*sizeof(LLU*)));
//		loop(j, K+1){
//			F[0][j] = (LLU *)malloc((P+1)*sizeof(LLU));
//			F[1][j] = (LLU *)malloc((P+1)*sizeof(LLU));
//		}
//
////		cout << "p "<< P <<endl;
//		loop(i,N){
//			loop(j , K+1){
//				loop(k, P+1){
//					F[i&1][j][k] = INFTY;
//				}
//			}
//		}
//		loop(i, N){
//			loop(k, P+1){
//				F[i&1][0][k] = 0;
//			}
//		}
//		loop(k,P+1){
//			F[0][0][k] = 0;
//			F[0][1][k] = (LLU)A[0];
//		}
//		loopp(i,1,N){
//			loopp(j,1,K+1){
//				loop(k,P+1){
//					if(i <= k) F[i&1][j][k] = (F[(i+1)&1][j-1][k-i] + (LLU)A[i] < F[(i+1)&1][j][k] ?F[(i+1)&1][j-1][k-i] + (LLU)A[i]: F[(i+1)&1][j][k]);
//					else F[i&1][j][k] = F[(i+1)&1][j][k];
//				}
//			}
//		}
//		cout << F[(N-1)&1][K][P] << endl;
//
//	}
//
//	return 0;
//}
//
//int int_cmp(const void *a, const void *b){
//	int *x = (int *)a; int *y = (int *)b;
//	return (*x-*y);
//}
//
//void printArray(int *A, int i,int j){
//	for(int k = i; k <= j-1; k++ ){
//		cout << A[k]<<" ";
//	}
//	cout << A[j]<< endl;
//}
//
