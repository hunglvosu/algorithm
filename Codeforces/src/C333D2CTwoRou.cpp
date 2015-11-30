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
//#define INFTY 100000000
//#define ALP  2
//
//
//int N,M;
//int **A;
//
//
//void printArray(int *A, int i,int j);
//
//int main() {
//	cin >> N >> M;
//	A = (int **)malloc(N*sizeof(int*));
//	loop(i,N){
//		A[i] = (int *)malloc(N*sizeof(int));
//		loop(j,N){
//			A[i][j] = 0;
//		}
//	}
////	printArray(A[0], 0, N-1);
//	int p, q;
//	loop(i,M){
//		cin >> p >> q;
//		A[p-1][q-1] = 1;
//		A[q-1][p-1] = 1;
//	}
//	if(A[0][N-1] == 1){
//		loop(i,N){
//			loop(j,N) A[i][j] = 1 - A[i][j];
//		}
//	}
//	int *D;
//	bool *vs;
//
//	D = (int *)malloc(N*sizeof(int));
//	vs = (bool *)malloc(N*sizeof(bool));
//	loop(i,N)vs[i] = false;
//	loop(i,N) D[i] = INFTY;
////	memset(D,INFTY, N*sizeof(int));
////	printArray(D, 0, N-1);
//
//	int t = 0;
//	vs[t] = true;
//	D[t] = 0;
//	queue<int> Q;
//	Q.push(t);
//	while(!Q.empty()){
//		p = Q.front();
////	cout << "running "<< p<<  endl;
//		Q.pop();
//		loop(j,N){
//			if(A[p][j] == 1 && !vs[j]){
//				D[j] = D[p]+ 1;
//				vs[j] = true;
//				Q.push(j);
////				cout << "update "<< j << "  "<< D[j] << endl;
//			}
//		}
//	}
//	if(D[N-1] > 10*M){
//		cout << "-1"<< endl;
//	} else {
//		cout << D[N-1] << endl;
//	}
//}
//
//
//
//void printArray(int *A, int i,int j){
//	for(int k = i; k <= j-1; k++ ){
//		cout << A[k]<<" ";
//	}
//	cout << A[j]<< endl;
//}
//
//
//
