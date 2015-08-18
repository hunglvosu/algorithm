/*
 * utilities.c
 *
 *  Created on: May 24, 2015
 *      Author: hunglv
 */
#include <string.h>
#include<stdlib.h>
#include<math.h>

typedef unsigned long long int LLU;


struct node {
  int id;
  int x;
  struct node *next;
};

typedef struct{
    int x;
    int y;
  }pair;

LLU  mod_mul(LLU a, LLU b, LLU p);

void random_array(int _array[], int size, int max){
	int i = 0;
	memset(_array, 0, sizeof(_array));
	for( i= 0; i < size; i++ ) _array[i] = rand() %max;
}

int int_inc_compare(const void *a, const void *b){
	int *d_a = (int *)a;
	int *d_b = (int *)b;
	return (*d_a - *d_b);
}

int int_dec_compare(const void *a, const void *b){
	int *d_a = (int *)a;
	int *d_b = (int *)b;
	return (*d_b - *d_a);
}

char *random_string(int length){
	static const char alphanum[] =
	"0123456789"
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz";
	int stringLength = sizeof(alphanum) - 1;
	char *str = (char *) malloc(length+1);
	int i = 0;
	for( i = 0; i < length; i++){
	    str[i] = alphanum[rand()%stringLength];// starting on 'A', ending on 'Z'
	}
	str[length] = '\0';
	return str;
}
void printArr(int arr[] , int n){
	int i = 0;
	for (i = 0 ; i < n ; i++){
		printf("%d,", arr[i]);
	}
	printf("\n");
}



void print_list(struct node *root){
	struct node *conductor;
	conductor = root;
	while(conductor != NULL){
	   	printf("%d,%d->", conductor->id, conductor->x);
	   	conductor = conductor-> next;
	 }
	printf("\n");
}

void print_bit(int n){
	int i = 0;
	int t = n;
	int A[32];
	for (i = 0; i < 32; i++){
			A[i] = t&1;
			t = t >> 1;
	}
	for(i = 31; i >= 0; i--){
		printf("%d",A[i]);
	}
	printf("\n");
}

void print_pair_array(pair A[], int n){
	int i = 0;
	for(i = 0; i < n; i++){
		printf("(%d,%d) ", A[i].x, A[i].y);
	}
	printf("\n");
}
/*
 * Computing $a^b mod p$
 */

LLU mod_power(LLU a, LLU b, LLU p){
	if (b == 1){
		return a %p;
	} else {
		LLU x = mod_power(a, b/2, p);
		if((b& 1) == 0){ // b is even
			return mod_mul(x,x,p); // return  (x*x)%p;
		} else {
			return (mod_mul(mod_mul(x,x,p), a, p));// return (x*x*a)%p;
		}
	}
}
/*
 * computing the greatest common divisor of $a$ and $b$
 */
LLU gcd(LLU a, LLU b){
	LLU tmp;
	while  (b != 0){
		tmp  = b;
		b = a % b;
		a = tmp;
	}
	return a;
}
/*
 * generating  a 64-bit random integer
 */

LLU random64(){
	LLU n  = 0;
	int l = rand()%(RAND_MAX-2)+2; // the last 32 bits
	int r = rand()%(RAND_MAX) + rand()%2; // the first 32 bit
	n = n | ((LLU)r);
	n = n << 32;
	n = n | ((LLU)l);
	return n;
}
void display_bit(LLU n){
	int bit[64];
	int i = 0;
	for(i = 0; i < 64; i++){
		bit[63-i] = (n& ((LLU)1));
		n = n >> 1;
	}
	for(i = 0; i < 64;i ++){
		printf("%d", bit[i]);
	}
	printf("\n");
}

/*
 * N = (a[1]+a[2]+...+a[m])^2
 *   = a[1]^2 + (2a[1] + a[2])a[2] + ...+ (2(a[1]+a[2]+..+a[m-1]) + a[m])a[m]
 * Y[m] = (2(a[1]+a[2]+..+a[m-1]) + a[m])a[m] = r[m-1] + a[m]^2 where r is the result
 * we found so far, R[m] = 2(a[1]+a[2]+..+a_[m-1])a[m]
 *
 * Note that if two digits correspond to a[m-1] and a[m] is 1, then R[m] = R[m-1]/2 + a^2[m-1]
 *
 *  Y[1] = a[1]^2
 *  X[0] = N
 *  X[m] = X[m-1] - Y[m]
 *  we guess a[m] so that X[m-1] - Y[m] >= 0
 */
int int_rfsqrt(int N){
/*
 * We define A2[i] = a[i]^2
 */
	int X[31], A2[31], R[31];
	int m = 1;
	X[0] = N;
	A2[1] = 1 << 30; // guessing a[1]^2
	R[1] = 0;
	while(N < A2[1]){
		A2[1] >>= 2;
	}
	while(A2[m] > 0){
		if (X[m-1] >= R[m] + A2[m]) { // your guess of a[m] is correct
			X[m] =  X[m-1] -  (R[m] + A2[m]); // update X[m], note that Y[m] = R[m] + A_2[m]
			R[m+1] = (R[m] >> 1) + A2[m];
			A2[m+1] = A2[m]>> 2; // your next guess of a[m+1] = a[m]/2;
			m++;
		} else { // your guess of a[m] is wrong, then reduce a[m] by a factor of 2
			A2[m] = A2[m] >> 2; // a[m] is reduced by 2 factor and hence A2[m] reduce by 4
			R[m] = R[m] >> 1; // R[m] is reduced by 2
		}
	}
	return R[m];

}
/*
 * computing (a*b) mod p using (\log_2 b + 1) space
 */
LLU mod_mul(LLU a, LLU b, LLU p){
	if (b == 1){
		return a %p;
	} else {
		LLU x = mod_mul(a, b>>1, p);
		if((b& 1) == 0){ // b is even
			return (x<<1)%p;
		} else {
			return (((x<<1)%p)+a)%p;
		}
	}
	return 0;
}


int int_fsqrt(int  N){
	int X, A2, R;
	X = N;
	A2 = 1 << 30;
	R = 0;
	while(N < A2){
		A2 >>= 2;
	}
	while(A2 > 0){
		if (X >= R + A2) {
			X -= R + A2;
			R = (R >> 1) + A2;
			A2 = A2>> 2;
		} else {
			A2 = A2 >> 2;
			R = R >> 1;
		}
	}
	return R;

}

/*
 * Computing the floor of square root of a 64-bit integer
 * See http://www.giaithuatlaptrinh.com/?p=402 for details.
 */

LLU llu_fsqrt(LLU  N){
	LLU X, A2, R;
	X = N;
	A2 = ((LLU)1) << 62; // guessing a[1]^2
	R = 0;
	while(N < A2){
		A2 >>= 2;
	}

	while(A2 > 0){
		if (X >= R + A2) {
			X -= R + A2;
			R = (R >> 1) + A2;
			A2 = A2>> 2;
		} else {
			A2 = A2 >> 2;
			R = R >> 1;
		}
	}
	return R;
}
//int main (void){
//	LLU x = (LLU)3457250758095349;
//	printf("%llu", llu_fsqrt(x));
//}
