/*
 * An implementation of Pollard-Rho algorithm for integer factorization
 * See http://www.giaithuatlaptrinh.com/?p=393 for details
 *
 *  Created on: Aug 14, 2015
 *      Author: hunglv
 */


#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "numbers.h"

#define MAXNUMFACT 64 // the maximum number of factors

LLU Fa[MAXNUMFACT];// the array storing factors
int nfact = -1; // the number of factors

LLU next_prng(LLU x, LLU N);
LLU find_factor(LLU N);
void fast_native_fact(LLU N);
int llu_cmp(const void *a, const void *b);
void print_factors(void);

//int main (void){
//	memset(Fa,0,sizeof(Fa)); // set everything to zero
//	pollard_rho_fact((LLU)2432902008176640000);
//	print_factors();
//	return 0;
//}


void pollard_rho_fact(LLU N){
	if(N == (LLU)1){
		return;
	}else if(N < (((LLU)1) << 10)){ // if N is too small
		fast_native_fact(N);
	}else if(miller_rabin_testing(10, N) == PRIME){ // 10 is the accuracy of the test which corresponds to 1 - 1/2^(10)
		Fa[++nfact] = N; // found a prime factor
	} else {
		LLU p = (LLU)0;
		while(p == 0 || p == N){
			p = find_factor(N);
		}
		pollard_rho_fact(p);
		pollard_rho_fact(N/p);
	}
}

LLU find_factor(LLU N){
	LLU x = random64()% N;
	LLU y = x;
	LLU p = 1;
	do{
		x = next_prng(x,N);  // x = f(x,N)
		y = next_prng(next_prng(y,N), N); // y = f(f(y,N),N)
		if(x > y){
			p = gcd(x-y,N);
		} else {
			p = gcd(y-x,N);
		}
	}while(p == 1);
	return p;
}
/*
 * compute f(x,N) = (x^2 + 1) mod N
 */
LLU next_prng(LLU x, LLU N){
	LLU xs = mod_mul(x,x,N);
	return xs + (LLU)1;
}
/*
 * The trial divisor algorithm for integer factorization
 * See http://www.giaithuatlaptrinh.com/?p=341 for details.
 */

void fast_native_fact(LLU N){
	while (N % 2 == 0){
		Fa[++nfact] = (LLU)2;
		N = N/2;
	}
	while (N % 3 == 0){
		Fa[++nfact] = (LLU)3;
		N = N/3;
	}
	if(N == 1){
		return;
	}
	if( miller_rabin_testing(10, N) == PRIME ){
			Fa[++nfact] = N;
			return;
	}
	LLU Q = 5;
	int diff = 2;
	int sqrtN = llu_fsqrt(N);
	while(Q <= sqrtN){
		if(N %Q == 0){
			Fa[++nfact] = Q;
			N = N/Q;
			sqrtN = llu_fsqrt(N);
			if(miller_rabin_testing(10, N) == PRIME ){
				Fa[++nfact] = N;
				return;
			}
		}else {
			Q = Q + (LLU)diff;
			diff = (diff&2) + 2;// diff is alternating between 2 and 4
		}
	}
}

void print_factors(){
	qsort(Fa, nfact+1, sizeof(*Fa), llu_cmp);
	int i = 0;
	for(i = 0; i < nfact; i++){
		printf("%llu*", Fa[i]);
	}
	printf("%llu\n", Fa[nfact]);

}
int llu_cmp(const void *a, const void *b){
	return *(LLU*)a - *(LLU*)b;
}

