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
//#define INFTY 10000000000000
//#define ALP  2
//
//
//int N, M;
//LLU bx, by;
//LLU *X, *Y;
//
//
//
//void printArray(LLU *A, int i,int j);
//
//int main() {
//	cin >> N >> bx;
//	X = (LLU *)malloc(N*sizeof(LLU));
//	loop(i,N){
//		cin >> X[i];
//	}
////	printArray(X, 0, N-1);
//	cin >> M >> by;
//	Y = (LLU *)malloc(M*sizeof(LLU));
//	loop(i,M){
//			cin >> Y[i];
//	}
////	printArray(Y, 0, M-1);
////	if(bx == by){
////		if(N > M)
////	}
//	LLU Ba[N], Bb[M];
//	LLU sa = 0, sb = 0;
//	Ba[0] = 1;Bb[0] = 1;
//
//	loopp(i,1,N){
//		Ba[i] = Ba[i-1]*bx;
//	}
//	loopp(i,1,M){
//		Bb[i] = Bb[i-1]*by;
//	}
//	loop(i,N){
//		sa += X[N-i-1]*Ba[i];
//	}
//	loop(i,M){
//			sb += Y[M-i-1]*Bb[i];
//	}
////	cout <<"sa: "<< sa << "  sb:" << sb<< endl;
//	if(sa > sb) cout << ">" << endl;
//	else if(sa < sb) cout << "<" << endl;
//	else cout << "=" << endl;
//}
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
