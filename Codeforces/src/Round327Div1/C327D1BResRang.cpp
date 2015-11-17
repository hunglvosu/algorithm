///*
// * C327D1BResRang.cpp
// *
// *  Created on: Nov 14, 2015
// *      Author: hunglv
// */
//
////============================================================================
//// Author      : Hung Le
//// Version     :
//// Description : C++ Code for http://codeforces.com/contest/590/problem/B
////============================================================================
//
//#include <iostream>
//#include<stdlib.h>
//#include<string.h>
//#include<math.h>
//using namespace std;
//int xa,ya,xb,yb;
//int vm, t;
//int vx,vy,wx,wy;
//double eps = 0.000001;
//
//int main() {
//	cout.precision(15);
//	cin >> xa >> ya >> xb>>yb;
//	cin >> vm>>t;
//	cin >> vx>> vy>> wx>> wy;
//	double dis = sqrt((double)(xa-xb)*(xa-xb)  + (double)(ya-yb)*(ya-yb));
//	double va = sqrt(vx*vx + vy*vy);
//	double vb = sqrt(wx*wx + wy*wy);
//	double eda = (vm -va)*t;
//	double ut;
//	if(eda > dis){
//		ut  = dis/(vm-va);
//	} else{
//		ut = t+ (dis - eda)/(vm -vb);
//	}
//	double lt = 0.0, m = ut, mm = ut;
//	double xd, yd, nndis;
//	while((ut- lt) > eps){
//		mm = (ut+lt)/2.0;
//		xd = (double)xa + (double)mm*vx;
//		yd = (double)ya + (double)mm*vy;
//		nndis = sqrt((xb-xd)*(xb-xd)  + (yb-yd)*(yb-yd));
//		if( (nndis/vm) <= mm ){
//			ut = mm;
//		} else  {
//			lt = mm;
//		}
//	}
//	if(mm  < t){
//		cout << mm << endl;
//	}else {
//		ut = m; lt = 0.0;
//		double xc = 0.0, yc = 0.0;
//		double ndis  =  0.0;
//		while((ut - lt) > eps){
//			m = (ut + lt)/2.0;
//			xc = (double)xa + (double)t*vx + (double)(m-t)*wx;
//			yc = (double)ya + (double)t*vy + (double)(m-t)*wy;
//			ndis  = sqrt((xb-xc)*(xb-xc)  + (yb-yc)*(yb-yc));
//			if((ndis/vm) <= m) {
//				ut = m;
//			} else  {
//				lt = m;
//			}
//		}
//		cout << m << endl;
//	}
//	return 0;
//}
//
//
//
