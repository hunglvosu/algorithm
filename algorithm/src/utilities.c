/*
 * utilities.c
 *
 *  Created on: May 24, 2015
 *      Author: hunglv
 */
 #include <string.h>

struct node {
  int id;
  int x;
  struct node *next;
};

typedef struct{
    int x;
    int y;
  }pair;

void random_array(int _array[], int size, int max){
	int i = 0;
	memset(_array, 0, sizeof(_array));
	for( i= 0; i < size; i++ ) _array[i] = rand() %max;
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
