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
//int Sc = 0;
//int *A;
//double eps = 1e-9;
//double **F;
//
//void printArray(int *A, int i,int j);
//
//int main() {
//	cout.precision(9);
//	cin >> N >> M;
//	A = (int *)malloc(N*sizeof(int));
//
//	loop(i,N){
//		cin >> A[i];
//		Sc += A[i]-1;
//	}
//	F = (double **)malloc(N*sizeof(double *));
//	loop(i,N){
//		F[i] = (double *)malloc((Sc+1)*sizeof(double));
//	}
//	cout << eps<< endl;
//	loop(i,M){
//		if(i < A[0]-1){
//			F[0][i] = (double)(i+1)/(double)M;
//		} else {
//			F[0][i] = (double)(i)/(double)M;
//		}
//	}
//	loopp(i,M,Sc){
//		F[0][i] = (double)(M-1)/(double)M;
//	}
//	loopp(i,1,N){
//		loop(j,Sc+1){
//			F[i][j] = 0.0;
//			loop(k,M){
//				if(k != A[i]-1){
//					if(k <= j)F[i][j] += F[i-1][j - k] + (double)1/(double)M;
//					else F[i][j] = 0.0;
//				}
//			}
//		}
//	}
//	double res = (F[N-1][Sc-1]*(double)M+1.0);
//	cout << res << endl;
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
