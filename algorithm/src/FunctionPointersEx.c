

#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int (*__get_key_) (const void *a);
int get_key(const void *a);
void counting_sort(int *A, size_t n);
void print_size(void *a);

typedef struct entry{
	int key;
	int val;
}entry;


//int main (void){
//	int A[6] = {5,0,2,1,4,3};
//	entry N[6];
//	N[0].key = 6;
//	N[1].key = 1;
//	N[2].key = 3;
//	N[3].key = 2;
//	N[4].key = 5;
//	N[5].key = 4;
////	qsort
//	entry *ptr;
//	ptr = N;
//	printf("%d\n", (ptr+2)->key);
//	printf("%d--%d\n", sizeof(int), sizeof(entry*));
//	double *x;
//	double xx[] = {1.0,2.0,3.0};
//	x = xx;
//	print_size(x);
//	counting_sort(A, 6);
//}

void print_size(void *a){
	printf("xx=%d\n", sizeof(a));
}
void counting_sort(int *A, size_t n){
	int *M;
	M = (int *)malloc(n*sizeof(int));
	memset(M, 0, sizeof(int));
	size_t i = 0;
	for(i = 0; i < n; i++){
		M[A[i]]++;
	}
	print_int_array(M,n);
	size_t j = 0;
	i = 0;
	while(i <  n){
		if(M[i] != 0){
			A[j] = i;
			M[i]--;
			j++;
		} else {
			i++;
		}

	}
	print_int_array(A,n);
}


int get_key(const void *a){
	entry *en = (entry *)a;
	return en->key;
}

void cnt_sort(void *_base, size_t count, size_t size, size_t l, size_t h, __get_key_ get_key){
	size_t range = h-l+1;
	void **_bucket = (void **)malloc(range*sizeof(_base));

}




