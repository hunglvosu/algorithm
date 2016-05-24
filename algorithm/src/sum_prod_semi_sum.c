/*
 * An implementation of bug-fixing for sum, product and semi-sum. 
 *
 * Warning: this implementation is not fully tested, use at your own risk.
 * See http://www.giaithuatlaptrinh.com/?p=1117 for more details.
 *
 *  Created on: May 20, 2016
 *  Author: Hung Le
 */  

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int sum_mod(int a, int b, int p);
int prod_mod(int a, int b, int p);
int semi_sum(int a, int b);

int diff_mod(int a, int b, int p);
int sum_mod_fixed(int a, int b, int p);
int prod_mod_fixed(int a, int b, int p);
int semi_sum_fixed(int a, int b);

int main(){
	int a = 2147483629;
	int b = 2029484451;
	int p = 2147483633;
	printf("overflow modulo sum: %d\n", sum_mod(a,b,p));
	printf("modulo sum: %d\n", sum_mod_fixed(a,b,p));
	
	printf("overflow modulo product: %d\n", prod_mod(a,b,p));
	printf("modulo product: %d\n", prod_mod_fixed(a,b,p));
	printf("overflow semi-sum: %d\n", semi_sum(a,b));
	printf("semi-sum:%d\n", semi_sum_fixed(a,b));
	int x = -2147483628;
	int y = 2029484451;
	printf("wrong semi-sum:%d\n", semi_sum(x,y));
	printf("semi-sum:%d\n", semi_sum_fixed(x,y));
	return 0;
}


int sum_mod(int a, int b, int p){
	return (a+b)%p;
}

int prod_mod(int a, int b, int p){
	return (a*b)%p;
}

int semi_sum(int a, int b){
	return (a+b)/2;
}

int diff_mod(int a, int b, int p){
	return (a >= b)? (a-b) : (p + a - b);
}

int sum_mod_fixed(int a, int b, int p){
	int x = a%p;
	int y = b%p;
	return diff_mod(x, p-y,p);
}

int prod_mod_fixed(int a, int b, int p){
	if (b==1) return a%p;
	else{
		int x = prod_mod_fixed(a,b/2,p);
		int y = sum_mod_fixed(x,x,p);
		if(b%2 == 0){	// b is even
			return y;
		} else return sum_mod_fixed(y,a,p); 
	}
}

int semi_sum_fixed(int a, int b){
	if((a^b) < 0){	// a and b has different sign
			return (a + b < 0? a+b - (a+b)/2 : (a+b)/2);
	} else {
		return (a < b ? a + (b-a)/2 : b + (a-b)/2);
	}
}