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

typedef struct snode {
	int leftEL;
	int rightEL;
	int node_label;
	int leafcnt;  // the number of leaves of the subtree rooted at this node
	int strdepth; // the string depth
	struct snode** Cr; // children pointers
	struct snode *parent;
	struct snode *slink; // the suffix link
} snode;

/*Make a new node of the suffix tree*/
snode *make_node(int i, int j);

/*Make a new leaf of the suffix tree*/
snode *make_leaf(int i,int n, int k);

/*Get index of the character c in the alphabet*/
int get_index(char c);

/*Initialize a suffix tree with suffix T[1,2,...,n]*/
snode *init_suffix_tree(int n);

/*Replace parent of node v by x in the suffix tree*/
void replace_parent(snode *x, snode *v);

/*Find a string P[first,..., last] in the suffix tree with root r
  return the last matched location of the text T, which is mlt,
  and the last matched location of the pattern P, which is mlp */
snode *find_path(char *P, int first, int last, snode *r, int *mlp, int *mlt);

/*The suffix tree built by native algorithm*/
snode *native_suffix_tree(char *Txt);

/* The suffix tree built by Mccreight algorithm*/
snode *mccreight_suffix_tree(char *Txt);


/* Check whether a string P is a substring of a string represented by the suffix
   a suffix tree rooted at r */
int is_substring(char *P, snode *r);

/* Check whether a string P is a suffix of a string represented by the suffix
   a suffix tree rooted at r */
int is_suffix(char *P, char *Ts);

/* Count the number of occurrence of a string P is a suffix of a string represented by the suffix
   a suffix tree rooted at r */
int count_occurrence(char *P, snode *r);

/* Find the longest substring that appears more than 1 in the string represented by
   a suffix tree rooted at r*/
char *longest_repeated_substr(snode *r);

/* Print the smallest lexicographic suffix of  the string represented by
   a suffix tree rooted at r*/
void print_smallest_lex_suffix(snode *r);


/*Ac algorithm for building suffix array*/
int *pd_suffix_array(char *Txt);

/*The algorithm based on Rabin-Karp fingerprint for building suffix array*/

int *rk_suffix_array(char *Txt);

/*An implementation of brute-force string matching algorithm*/
int BFmatcher(char *Txt,char *Ptn);

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
