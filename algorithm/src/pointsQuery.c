/*
 * point query problem: given a set of lines D[1,2,...,n] and Q points, for each points p , find a
 * minimal value q = min {a_i*p + b_i| 1 <= i <= n}
 *
 *  Created on: Jun 20, 2015
 *      Author: hunglv
 */

#include<time.h>
#include<stdio.h>
#include<string.h>
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) < (y)) ? (y) : (x))
#define is_equal(x,y) (((x) - (y) == 0) ? 1 : 0)
#define MAX_SIZE 1000000
#define INFTY 100000000
#define NULL 0



typedef struct{
    double a;
    double b;
  } double_pair;


 struct Stack_node {
	int lineId;
	struct Stack_node *next;
  };
typedef struct Stack_node stack_node;

stack_node *S;
double_pair D[MAX_SIZE];
double_pair I[MAX_SIZE];
double      Q[MAX_SIZE];
int         ALines[MAX_SIZE];// the set of lines associated with I

int slope_compare(const void *a, const void *b);
double find_intersection_x(int x, int y);
stack_node *pop();
stack_node *peek();

//void main (void){
//	int n = 4;
//	D[0].a = 1; D[0].b = 3;
//	D[1].a = (double)4 /(double)5; D[1].b = 4;
//	D[2].a = (double)1 /(double)2; D[2].b = 2;
//	D[3].a = (double)1 /(double)6; D[3].b = (double)16 /(double)6;
//	int k = 5;
//	double points[5] = {-4.0, 1.0, 0.0, 2.0, 3.0};
//	query(points, k, n);
//	print_double_array(Q,k);
//}


void query(double points[], int k, int n){
	int m = find_hull(n);
	int i = 0, q = 0;
	for(i = 0; i < k; i++){
		q = interval_search(0, m-1, points[i]);
		Q[i] = D[ALines[q]].a*points[i] + D[ALines[q]].b;
	}
}


//int interval_search(int x, int y, double p){
//	if(y <= x){
//		return x;
//	} else {
//		int mid = (x+y)/2;
//		if((I[mid].a <= p) && (p <= I[mid].b)){
//			return mid;
//		} else if (p > I[mid].b){
//			return interval_search(mid+1, y, p);
//		} else {
//			return interval_search(x, mid-1, p);
//		}
//	}
//}

int find_hull(int n){
	qsort(D, n, sizeof(*D), slope_compare);
	S = malloc( sizeof(stack_node));
	S->lineId = -1; // head of the stack
	push(0); // push d_1 to the stack;
	I[0].a = -(double)INFTY;
	I[0].b = (double)INFTY;
	int m = 0;
	ALines[m] = 0;
	int i = 0;
	stack_node *d;
	double x = 0.0;
	for(i = 1; i <n ;i++){
		d = peek();
        x = find_intersection_x(d->lineId, i);
        while(x <= I[m].a){  // found a redundant line
        	pop();       // remove the redundant line
        	m--;
        	d = peek();
        	x = find_intersection_x(d->lineId, i);
        }
        push(i); // push d_i to the stack
        I[m].b = x;
        I[m+1].a = x;
        I[m+1].b = (double)INFTY;
        ALines[m+1] = i;
        m++;
	}

	return m+1; // the number of intervals
}

//double find_intersection_x(int x, int y){
//	double_pair d_a = D[x];
//	double_pair d_b = D[y];
//	return (d_b.b - d_a.b)/(d_a.a - d_b.a);
//}

stack_node *pop(){
	if(S->next == NULL){
		printf("Error: no element to pop\n");
		exit(1);
	} else {
		stack_node *elem = S->next;
		S->next = (S->next)->next;
		return elem;
	}
}

void push(int lineId){
	stack_node *elem = malloc( sizeof(stack_node));
	elem->lineId = lineId;
	elem->next = S->next;
	S->next = elem;
}

stack_node* peek(){
	return S->next;
}

int slope_compare(const void *a, const void *b){
	double_pair *d_a = (double_pair *)a;
	double_pair *d_b = (double_pair *)b;
	if(d_a->a > d_b->a) return -1;
	else return 1;
}

void print_lines(double_pair D[], int size){
	int i = 0;
	for(i = 0; i < size; i++){
		printf("%fx+%f   ", D[i].a, D[i].b);
	}
	printf("\n");
}

void print_intervals(double_pair I[], int size){
	int i = 0;
	for(i = 0; i < size; i++){
		printf("[%f,%f]   ", I[i].a, I[i].b);
	}
	printf("\n");
}

void print_double_array(double Q[], int size){
	int i = 0;
	for(i = 0; i < size; i++){
		printf("%f  ", Q[i]);
	}
	printf("\n");
}


