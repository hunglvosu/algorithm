/*
 * number.h
 *
 *  Created on: Aug 22, 2015
 *      Author: hunglv
 */

#ifndef NUMBER_H_
#define NUMBER_H_

typedef unsigned long long int LLU;
#define PRIME 1
#define COMPOSITE 0
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) < (y)) ? (y) : (x))


/*Miller-Rabin primality testing algorithm*/
int miller_rabin_testing(int acc, LLU N);

/*Pollard-Rho algorithm for integer factorization*/
void pollard_rho_fact(LLU N);


#endif /* NUMBER_H_ */
