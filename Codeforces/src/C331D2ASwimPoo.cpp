////============================================================================
//// Author      : Hung Le
//// Version     :
//// Description : C++ Code for http://codeforces.com/contest/590/problem/A
////============================================================================
//
//#include <iostream>
//#include<stdlib.h>
//#include<string.h>
//#include<math.h>
//using namespace std;
//int N;
//int X[4];
//int Y[4];
//bool checkEqual(int xa, int ya, int xb, int yb);
//int area(int xa, int ya, int xb,  int yb);
//
//int main() {
//	cin >> N;
//	for(int i =  0; i < N; i ++){
//		cin >> X[i];
//		cin >> Y[i];
//	}
//	if(N < 2) cout << -1 << endl;
//	else if(N > 2) {
//		if(checkEqual(X[0],Y[0], X[1], Y[1])){
//			if(checkEqual(X[1], Y[1], X[2], Y[2])){
//				cout << area(X[0],Y[0], X[2], Y[2]) << endl;
//			} else {
//				cout << area(X[1],Y[1], X[2], Y[2]) << endl;
//			}
//		}else {
//			cout << area(X[0],Y[0], X[1], Y[1]) << endl;
//		}
//	}
//	else {
//		if(checkEqual(X[0], Y[0], X[1], Y[1])) cout << -1 << endl;
//		else {
//			cout << area(X[0], Y[0], X[1], Y[1])<< endl;
//		}
//	}
//	return 0;
//}
//
//int area(int xa, int ya, int xb,  int yb){
//	return (xa - xb > 0 ? xa - xb: xb - xa)*(ya - yb > 0 ? ya - yb: yb - ya);
//}
//
//bool checkEqual(int xa, int ya, int xb, int yb){
//	if((xa == xb) || (ya == yb)) return true;
//	else return false;
//}
//
