////============================================================================
//// Author      : Hung Le
//// Version     :
//// Description : C++ Code for http://codeforces.com/contest/590/problem/A
////============================================================================
//
//#include <iostream>
//#include<stdlib.h>
//#include<string.h>
//using namespace std;
//int N;
//int *A;
//void  printArray(int *A, int i, int j);
//
//
//int main() {
//	cin >> N;
//	A = (int *)malloc(N*sizeof(int));
//	for(int i =0 ;i < N; i++){
//		cin>> A[i];
//	}
//	int *L = (int *)malloc(N*sizeof(int));
//	for(int i = 0; i < N; i++){
//		L[i] = 0;
//	}
//	int *R = (int *)malloc(N*sizeof(int));
//	L[0] = 0;
//	int i = 0, l = 0;
//	if(A[1] != A[0]) {
//		R[0] = 0;
//		i++;
//	}else {
//		 l = 1;
//	}
//	for(int j = 2; j < N; j++){
//		if(A[j] == A[j-1]){
//			if(l == 0) L[i] = j-1;
//			l++;
//		}else {
//			if(l > 0){
//				R[i]= j-1;
//				i++;
//				l = 0;
//			}
//		}
//	}
//	if(L[i] == 0){
//		L[i] = N-1;
//	}
//	R[i] = N-1;
//	int s  = 0;
//	int *B = (int *)malloc(N*sizeof(int));
//	for(int k = 0; k <= R[0]; k++ ){
//		B[k] = A[0];
//	}
//	int max = 0;
//	for(int k = 1; k  <= i ; k++){
//		s = (L[k] - R[k-1]-1);
//		if((s&1) == 0) {
//			s = s >> 1;
//			for(int j = R[k-1]+1; j <= R[k-1] + s; j++){
//				B[j] = A[R[k-1]];
//			}
//			for(int j = R[k-1] + s+1; j <= L[k] ; j++){
//				B[j] = A[L[k]];
//			}
//		} else{
//			s = (s >> 1) + 1;
//			for(int j = R[k-1]+1; j < L[k]; j++){
//				B[j] = A[R[k-1]];
//			}
//		}
//
//		for(int j = L[k]; j <= R[k]; j++){
//			B[j] = A[L[k]];
//		}
//		if(s  > max) max = s;
//	}
//	cout<< max << endl;
//	printArray(B, 0, N-1);
//	return 0;
//}
//
//
//void printArray(int *A, int i,int j){
//	for(int k = i; k <= j-1; k++ ){
//		cout << A[k]<<" ";
//	}
//	cout << A[j]<< endl;
//}
