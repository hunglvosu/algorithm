//
////============================================================================
//// Author      : Hung Le
//// Version     :
//// Description : C++ Code for http://codeforces.com/contest/590/problem/A
////============================================================================
//
//#include <iostream>
//#include<stdlib.h>
//#include<string.h>
//#define MAX 200005
//using namespace std;
//typedef unsigned long long LLU;
//int N;
//int B[MAX];
//void  printArray(int *A, int i, int j);
//unsigned long long cost;
//
//int main() {
//	cin >> N;
//	for(int i = 0; i < N; i++){
//		cin >> B[i];
//	}
//	cost = (LLU )(B[0] < 0 ? -B[0]: B[0]);
//	for(int i =1; i < N; i++){
//		cost += (LLU)(B[i-1] < B[i] ? B[i] - B[i-1] : B[i-1]-B[i]);
//	}
//	cout << cost<< endl;
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
