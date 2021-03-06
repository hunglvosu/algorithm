/*
 * An implementation of Rabin-Karp algorithm
 * See http://www.giaithuatlaptrinh.com/?p=290 for details
 *
 *  Created on: Aug 5, 2015
 *      Author: hunglv
 */

#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "stringsearch.h"
#include "utilities.h"
#include "numbers.h"

#define MAXN 100
#define MAXM 20
#define PRIME 1
#define COMPOSITE 0

LLU random_prime(LLU N);
int isequal(int s,int m);


//int main (void){
//	int n = 14, m = 8;
//	printf("%d\n", RabinKarpMatcher(n,m));
//	return 0;
//}


int RabinKarpMatcher(int n, int m){
	LLU base = (LLU) 26; // the alphabet is {a,b,c,d,...,z}
	LLU q = random_prime((LLU)(1<<30) - 1);// generating a random prime number, assume that m^2 log m <= 2^(30)
	LLU p = 0;
	LLU Ts[n-m+2];
	LLU sig = mod_power(base,m-1,q); // base^(m-1) \mod q
	Ts[1] = 0;
	int i = 0;
	for(i = 1; i <=m; i++){
		p = (P[i]-'a' + ((base*p)%q))%q;
		Ts[1] = (T[i]-'a'+ ((base*Ts[1])%q))%q;
	}
	for(i = 1; i <= n-m+1; i++){
		if(Ts[i] == p){
			if(isequal(i,m)){ // compare T[s,s+1,.., s-m+1] with P[1,2,...,m]
				return i;
			}
		} else {
			Ts[i+1] =  ((base*((Ts[i]  - ((sig*(T[i]-'a')) %q) + q) %q))%q + T[i+m]-'a')%q;
		}
	}
  return 0;
}

int isequal(int s, int m){
	int i = 1;
	while(T[s+i-1] == P[i] && i <= m){
		i++;
	}
	if(i > m) return 1;
	else return 0;
}

/* Generating a random 32 bit prime number using Miller-Rabin primality testing
  See //www.giaithuatlaptrinh.com/?p=278 for details */
LLU random_prime(LLU N){
	LLU q = random64()%(N-2)+2;
	while(miller_rabin_testing(10, q) != PRIME){
		q = random64()%(N-2)+2;
	}
	return q;
}
