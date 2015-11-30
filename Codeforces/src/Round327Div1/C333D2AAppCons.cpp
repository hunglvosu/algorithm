///*
// * C333D2ATwoBas.cpp
// *
// *  Created on: Nov 24, 2015
// *      Author: hunglv
// */
//
//
////============================================================================
//// Author      : Hung Le
//// Description : C++ Code for http://codeforces.com/contest/590/problem/D
////============================================================================
//
//#include <iostream>
//#include<stdlib.h>
//#include<string.h>
//#include<queue>
//using namespace std;
//typedef unsigned long long LLU;
//#define loop(i,n) for(int i = 0; i < n; i++)
//#define loopp(i,j,n) for(int i = j; i < n; i++)
//#define pr(s) cout << s << endl;
//#define MAX 40
//#define INFTY 1000000
//#define ALP  2
//
//
//int N;
//int *A;
//int *F[2];
//
//
//void printArray(LLU *A, int i,int j);
//
//int main() {
//	cin >> N;
//	A = (int *)malloc(N*sizeof(int));
//	F[0] = (int *)malloc(N*sizeof(int));
//	F[1] = (int *)malloc(N*sizeof(int));
//	loop(i,N){
//		cin >> A[i];
//	}
//	F[0][0] = 1;
//	F[1][0] = 1;
//	loopp(i,1,N){
//		if(A[i] == A[i-1]){
//			F[0][i]  = F[0][i-1]+1;
//			F[1][i]  = F[1][i-1]+1;
//		} else if(A[i] > A[i-1]){
//			F[0][i] = F[1][i-1] + 1;
//			F[1][i] =  1;
//		} else {
//			F[1][i] = F[0][i-1] + 1;
//			F[0][i] =  1;
//		}
//	}
//	int  m = 0;
//	loop(i,N){
//		m = (F[0][i] > m? F[0][i] :m );
//		m = (F[1][i] > m? F[1][i] :m );
//
//	}
//	cout << m  << endl;
//	}
//
//
//
//void printArray(LLU *A, int i,int j){
//	for(int k = i; k <= j-1; k++ ){
//		cout << A[k]<<" ";
//	}
//	cout << A[j]<< endl;
//}
//
//
//
