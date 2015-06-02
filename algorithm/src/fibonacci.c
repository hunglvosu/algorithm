/*
 * dynamicFib.c
 *
 *  Created on: May 30, 2015
 *      Author: hunglv
 */
#include<time.h>
#include<stdio.h>
#include<string.h>
#define MAX 1000

int F[MAX];

int dynamic_fib(int n){
	F[0] = 0; F[1] = 1;
	int i = 2;
	for(i = 2; i <= n; i++){
		F[i] = F[i-1] + F[i-2];
	}
	return F[n];
}

int memorized_fib(int n){
	if(n < 2) return n;
	else {
		if(F[n] == 0){
			F[n] = memorized_fib(n-1) + memorized_fib(n-2);
		}
		return F[n];
	}
}
int save_mem_fib(int n){
	int prev = 0;
	int curr = 1;
	int next;
	int i = 0;
	for(i = 2; i <= n ; i++){
		next = prev + curr;
		prev = curr;
		curr = next;
	}
	return next;
}



