///*
// * An implementation of integer factorization algorithms
// * See http://www.giaithuatlaptrinh.com/?p=34 for details
// *
// *  Created on: Aug 5, 2015
// *      Author: hunglv
// */
//
//#include<time.h>
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#define PRIME 1
//#define COMPOSITE 0
//#define MAXNUMFACT 20 // the maximum number of factors
//
//typedef unsigned long long int LLU; // using unsigned long long type to avoid overflow
//
//LLU Fa[MAXNUMFACT];// the array storing factors
//int nfact = -1; // the number of factors
//
//int miller_rabin_testing(int acc, LLU N);
//void fast_native_fact(LLU N);
//void print_factors(void);
//LLU llu_fsqrt(LLU N);
//
////int main (void){
////	fast_native_fact((LLU)9383); // 11*853
////	print_factors();
////	return 0;
////}
//
///*
// * Q[0,1,...] = {2,3,5,7,11,13,17,19,23,25,29,31,35,....}
// * Except for 2 and 3, the difference between two consecutive elements of Q is 2 or 4 alternatively.
// */
//
//void fast_native_fact(LLU N){
//	if(N == 1){
//		return;
//	}
//	while (N % 2 == 0){
//		Fa[++nfact] = (LLU)2;
//		N = N/2;
//	}
//	while (N % 3 == 0){
//		Fa[++nfact] = (LLU)3;
//		N = N/3;
//	}
//	if( miller_rabin_testing(10, N) == PRIME ){
//			Fa[++nfact] = N;
//			return;
//	}
//	LLU Q = 5;
//	int diff = 2;
//	int sqrtN = llu_fsqrt(N);
//	while(Q <= sqrtN){
//		if(N %Q == 0){
//			Fa[++nfact] = Q;
//			N = N/Q;
//			sqrtN = llu_fsqrt(N);
//			if(miller_rabin_testing(10, N) == PRIME ){
//				Fa[++nfact] = N;
//				return;
//			}
//		}else {
//			Q = Q + (LLU)diff;
//			diff = (diff&2) + 2;// diff is alternating between 2 and 4
//		}
//	}
//}
//
//void print_factors(){
//	int i = 0;
//	for(i = 0; i < nfact; i++){
//		printf("%llu*", Fa[i]);
//	}
//	printf("%llu\n", Fa[nfact]);
//}
//
//
