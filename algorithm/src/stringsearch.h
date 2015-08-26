/*
 * An interface for string searching programs
 *
 *  Created on: Aug 22, 2015
 *      Author: hunglv
 */

#ifndef STRINGSEARCH_H_
#define STRINGSEARCH_H_
#define ALPHABET_SIZE 28
extern char *T;
extern char *P;
extern char Alphabet[ALPHABET_SIZE]; // the alphabet is 26 character alphabet
/*An implementation of brute-force string matching algorithm*/
int BFmatcher(int n,int m);

/*KMP string matching algorithm with running time depending on
 the alphabet */

int KMPmatcher(int n,int m);

/* KMP string matching algorithm with running time depending on
 the input string only */
int fastKMPmatcher(int n,int m);

/*Boyer-Moore string matching algorithm with the bad character rule*/
int BMmatcher(int n,int m);

/*Boyer-Moore string matching algorithm with the extended bad character rule*/
int fastBMmatcher(int n,int m);

/*Boyer-Moore string matching algorithm with the bad character rule
  and the good suffix rule*/
int fastfastBMmatcher(int n,int m);

/*Rabin-Karp string matching algorithm*/
int RabinKarpMatcher(int n,int m);

/*Compute Z function of a string S with length n*/
void compute_Z_function(char *S,int *Z, int n);

#endif /* STRINGSEARCH_H_ */
