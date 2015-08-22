/*
 * utilities.h
 *
 *  Created on: Aug 22, 2015
 *      Author: hunglv
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

typedef unsigned long long int LLU;

void printArr(int arr[] , int n);

/* Computing a^b mod p*/
LLU mod_power(LLU a, LLU b, LLU p);

/*Computing (a*b) mod p using (\log_2 b + 1) space */
LLU mod_mul(LLU a, LLU b, LLU p);

/* Generating  a 64-bit random integer*/
LLU random64();

/*Computing the greatest common divisor of a and b*/
LLU gcd(LLU a, LLU b);


/* Computing the floor of square root of a 64-bit integer
 See http://www.giaithuatlaptrinh.com/?p=402 for details. */
LLU llu_fsqrt(LLU  N);

#endif /* UTILITIES_H_ */
