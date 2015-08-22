/*
 * An implementation of Miller-Rabin primality testing algorithm for this problem: http://www.spoj.com/problems/PON/
 * See http://www.giaithuatlaptrinh.com/?p=278 for details
 *
 *  Created on: Aug 1, 2015
 *      Author: hunglv
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "numbers.h"

#define NUMTEST 500

LLU N[NUMTEST];
int n;


int witness(LLU a,  LLU N);
void decompose(LLU p, int *k, LLU *m);

//int main() {
//    cin >> n; // the number of test cases
//    for(int i = 0; i < n; i++){
//    	cin >> N[i];
//    }
//    int acc = 10; // the accuracy of the test is at least 1 - 1/1000.
//    for(int i = 0; i < n; i++){
//    	if(N[i] == 2){
//    		printf("YES\n");
//    	}
//    	else if(miller_rabin_testing(acc, N[i])){
//    		printf("YES\n");
//    	} else {
//    		printf("NO\n");
//    	}
//    }
//	LLU N = 10000019;
//	if(miller_rabin_testing(10, N) == PRIME){
//		printf("prime\n");
//	}else {
//		printf("composite\n");
//	}
//	return 0;
//}

/* The miller-rabin primality testing algorithm
   See http://www.giaithuatlaptrinh.com/?p=278 for details. */
int miller_rabin_testing(int acc, LLU N){
	LLU a = 0;
	int i = 0;
	for(i = 0; i <= acc; i++){
		a = random64()%(N-2)+ 2;
		if(gcd(a,N) != 1){
			return COMPOSITE;
		} else if (mod_power(a,N-1,N) != 1){
			return COMPOSITE;
		}else {
			if (witness(a,N) == COMPOSITE){
				return COMPOSITE;
			}
		}
	}
	return PRIME;
}


int witness(LLU a,  LLU N){
	LLU m;
	int k;
	decompose(N-1,&k,&m);
	LLU B[k+1];
	B[0] = mod_power(a,m,N);
	if(B[0] == 1){
		return PRIME;
	} else {
		int i = 1;
		while(i <= k){
			B[i] =  mod_mul(B[i-1],B[i-1],N);// (B[i-1]*B[i-1])%N;
			if(B[i] == 1){
				if(B[i-1] == N-1){
					return PRIME;
				} else {
					return COMPOSITE;
				}
			}
			i++;
		}
	}
	return COMPOSITE;
}
/*
 * decomposing p = 2^k*m
 */
void decompose(LLU p, int *k, LLU *m){
	int i = 0;
	while ((p& 1) == 0){ // p is even
		i++;
		p = p >> 1; // p = p /2
	}
	*k = i;
	*m = p;
}

