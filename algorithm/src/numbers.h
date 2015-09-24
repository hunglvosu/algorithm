/*
 * number.h
 *
 *  Created on: Aug 22, 2015
 *      Author: hunglv
 */

#ifndef NUMBER_H_
#define NUMBER_H_

typedef unsigned long long int LLU;
typedef long long int LL;
#define PRIME 1
#define COMPOSITE 0
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) < (y)) ? (y) : (x))

#define TRUE 1
#define FALSE 0

/*Miller-Rabin primality testing algorithm*/
int miller_rabin_testing(int acc, LLU N);

/*Pollard-Rho algorithm for integer factorization*/
void pollard_rho_fact(LLU N);

/*Check whether x = 2^y for some y*/
int is_power_of_2(LLU x);


#endif /* NUMBER_H_ */
