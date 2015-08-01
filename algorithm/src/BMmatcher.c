/*
 * An implementation of Boyer-Moore matching algorithm with different heuristic rules
 * For more information, see ...
 *  Created on: Jul 19, 2015
 *      Author: hunglv
 */

#include<time.h>
#include<stdio.h>
#include<string.h>
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) < (y)) ? (y) : (x))
#define MAXN 100
#define MAXM 20
#define INFTY 100000000

char T[MAXN];
char P[MAXM];

int BFmatcher(int n,int m);
int BMmatcher(int n,int m);
int fastBMmatcher(int n,int m);
int fastfastBMmatcher(int n,int m);
void badCharBackup(int m, int *R); // the implementation of bad character rule.
void extendedBadChar(int m, int *S); // the implementation of the extended bad character rule.
void computeLL(int m, int *LL, int *Zbar);
void computeSL(int m, int *SL, int *Zbar);
void compute_Z_function(char *S, int *Z, int n);

int main (void){
	char text[] = "dlcimglkblhcch";
	char pattern[] = "mglkblhc";
	int i = 0;
	T[0] = " ";
	for(i = 0; i < strlen(text); i++){
		T[i+1] = text[i];
	}
	P[0] = " ";
	for(i = 0; i < strlen(pattern); i++){
		P[i+1] = pattern[i];
	}
	int n = 14, m = 8;
	i = 1;
	printf("%d\n",BFmatcher(n,m));
	printf("%d\n",BMmatcher(n,m));
	printf("%d\n",fastBMmatcher(n,m));
	printf("%d\n", fastfastBMmatcher(n,m));
	return 0;
}
/*
 * An implementation of Boyer-Moore algorithm with bad character rule.
 */
int BMmatcher(int n, int m){
	int  R[28];
	badCharBackup(m, R);
	int i = 1, j = 0, p = 0, skip = 0;
	while(i <= n-m+1){
		skip = 0;
		j = m;
		while(j >= 1 && skip == 0){
			if(T[i+j-1] != P[j]){
				p = T[i+j-1]-96;
				skip = max(1, j - R[p]);
			}
			j--;
		}
		if(skip == 0) return i;
		i = i + skip;
	}
	return -1;
}

void badCharBackup(int m, int *R){
	int i = 0;
	for(i = 1; i <= m; i++){
		R[P[i] - 96] = i;
	}
}

/*
 * An implementation of Boyer-Moore algorithm with the extended bad character rule.
 */
int fastBMmatcher(int n, int m){
	int i = 0, j = 0;
	int S[28][m+1];
	for(i = 1; i < 28; i++)
		memset(S[i], 0, sizeof(S[i]));
	extendedBadChar(m, (int *)S);
	int p = 0, skip = 0;
	i = 1;
	while(i <= n-m+1){
		skip = 0;
		j = m;
		while(j >= 1 && skip == 0){
			if(T[i+j-1] != P[j]){
				p = T[i+j-1]-96;
				skip = j - S[p][j];
			}
			j--;
		}
		if(skip == 0) return i;
		i = i + skip;
	}
	return -1;
}

void extendedBadChar(int m, int *S){
	int X[28];
	memset(X, 0, sizeof(X));
	int i = 0,k = 0;
	for(i = 1; i <= m ; i++){
		for(k = 1; k < 28; k++){
//			S[k][i] = X[k];
			*((S + k*(m+1)) + i) = X[k];
		}
		X[P[i] - 96] = i;
	}
}
/*
 * An implementation of Boyer-Moore algorithm with bad character rule and good suffix rule.
 */
int fastfastBMmatcher(int n, int m){
	int  R[28];
	/*
	 * Zbar[i] is the lenght of the longest suffix of P[1,2,...,i]
	 * matched with a suffix of P[1,2,..,m]
	 */

	int Zbar[MAXM];
	/*
	 * LL[i] is the maximum index smaller than m such that P[i,i+1,..,m]
	 * matched with a suffix of P[1,2,..,LL[i]] such that the char to the left of
	 * of the matched substring of  P[1,2,..,LL[i]] is not equal from P[i-1]
	*/
	int LL[MAXM];
	/*
	 * SL[i] is the length of the longest suffix of P[i,i+1,..,m] that is matched with
	 * a prefix of P[1,2,...,m]
	 */
	int SL[MAXM];
	badCharBackup(m,R);
	int i = 1, j = 0, p = 0, skip = 0;
	memset(Zbar, 0, sizeof(Zbar)); // set everything to 0
	memset(LL,0,sizeof(LL));// set everything to 0
	memset(SL,0, sizeof(SL));// set everything to 0
	computeLL(m, LL, Zbar);
	computeSL(m, SL, Zbar);
	while(i <= n-m+1){
		skip = 0;
		j = m;
		while(j >= 1 && skip == 0){
			if(T[i+j-1] != P[j]){
				p = T[i+j-1]-96;
				skip = max(1, j - R[p]); // skip by the bad character rule;
				if(j!=m){
					if(LL[j+1] !=0){
						skip = max(skip, m - LL[j+1]);// (1) and (2) of the good suffix rule
					} else {
						skip = max(skip, m - SL[j+1]);// (3) and (4) of the good suffix rule
						/*
						 * For more information about the rules, see .... blogpost
						 */
					}
				}
			}
			j--;
		}
		if(skip == 0) return i;
		i = i + skip;
	}
	return -1;
}
/*
 * See ... for details
 */
void computeLL(int m, int *LL, int *Zbar){
	int i = 0, j = 0;
	char Prev[m+1]; // the reverse of P[1,2,....,m]
	int Zrev[m+1]; // the Z function of Prev[1,2,...,m]
	for(i = m; i >= 1; i--){
		Prev[m-i+1] = P[i];
	}
	//See http://www.giaithuatlaptrinh.com/?p=250 for details of Z function
	compute_Z_function(Prev, Zrev, m);
	for(i = 1; i<= m-1; i++){
		Zbar[i] = Zrev[m-i+1];
	}
	for(j = 1; j <= m-1; j++){
		i = m - Zbar[j]+1;
		LL[i] = j;
	}
}
/*
 * See... for details
 */
void computeSL(int m, int *SL, int *Zbar){
	int i = 1,j = 0;
	for(i = 1; i  <= m-1; i++){
		if(Zbar[i] == i){
			SL[m-i+1] = i;
			j = i;
		} else {
			SL[m-i+1] = j;
		}
	}
}


