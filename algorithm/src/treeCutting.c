///*
// * Code for the tree cutting problem http://codeforces.com/contest/319/problem/C
// *
// *  Created on: Jun 23, 2015
// *      Author: hunglv
// */
//
//#include<time.h>
//#include<stdio.h>
//#include<string.h>
//#define min(x, y) (((x) < (y)) ? (x) : (y))
//#define max(x, y) (((x) < (y)) ? (y) : (x))
//#define is_equal(x,y) (((x) - (y) == 0) ? 1 : 0)
//#define MAX_SIZE 10000000
//#define INFTY 100000000
//#define NULL 0
//
//typedef struct{
//    double a;
//    double b;
//  } double_pair;
//
//
// struct Stack_node {
//	int lineId;
//	struct Stack_node *next;
//  };
//typedef struct Stack_node stack_node;
//
//stack_node *S;
//double_pair I[MAX_SIZE];
//int   		A[MAX_SIZE];
//int 		B[MAX_SIZE];
//int 		C[MAX_SIZE];
//double      Q[MAX_SIZE];
//int         ALines[MAX_SIZE];// the set of lines associated with I
//
//double find_intersection_x(int x, int y);
//int slow_dynamic(int A[], int B[], int n);
//stack_node *pop();
//stack_node *peek();
//
////void main (void){
////	int n = 6;
////	A[0] = 1; A[1]= 2; A[2] = 3; A[3] = 10; A[4] = 20; A[5] = 30;
////	B[0] = 6; B[1]= 5; B[2] = 4; B[3] = 3; B[4] = 2; B[5] = 0;
////	printf("%d -- %d -- %d\n", slow_dynamic(A, B, n), fast_dynamic(A, B, n), fast_fast_dynamic(A,B,n));
////}
//
//int slow_dynamic(int A[], int B[], int n){
//	memset(C, 0, sizeof(C));
//	C[0] = B[0];
//	int i  =  1, j = 1;
//	for(i = 1; i < n; i++){
//		C[i] = INFTY;
//		for(j = 0; j < i; j ++){
//			C[i] = min(C[i], C[j] + (A[i]-1)*B[j]);
//		}
//		C[i] = C[i] + B[j];
//	}
//	return C[n-1];
//}
//
//int fast_dynamic(int A[], int B[], int n){
//	memset(C, 0, sizeof(C));
//	C[0] = B[0]; // d_1 = B[0]x + C[0]
//	S = malloc( sizeof(stack_node));
//	S->lineId = -1; // head of the stack
//	push(0); // push d_1 to the top of the stack;
//	I[0].a = -(double)INFTY;
//	I[0].b = (double)INFTY;
//	int m = 0;
//	ALines[m] = 0;
//	int i = 0, q = 0;
//	stack_node *d;
//	double x = 0.0;
//	for(i = 1; i <n ;i++){
//		q = interval_search(0, m, (double)A[i]-1);  // doing binary search
//		C[i] = B[ALines[q]]*(A[i]-1) + C[ALines[q]] + B[i];
//		d = peek();   // examine the top element of the stack
//		x = find_intersection_x(d->lineId, i);
//		while(x <= I[m].a){  // found a redundant line
//			pop();           // remove the redundant line
//			m--;
//			d = peek();
//			x = find_intersection_x(d->lineId, i);
//		}
//	   if(x < (double) (INFTY-1)){ // two lines are not parallel
//		   push(i);
//		   I[m].b = x;
//		   I[m+1].a = x;
//		   I[m+1].b = INFTY;
//		   ALines[m+1] = i;
//		   m++;
//	   }
//	}
//return C[n-1];
//}
//
//int fast_fast_dynamic(int A[], int B[], int n){
//	memset(C, 0, sizeof(C));
//	C[0] = B[0]; // d_1 = B[0]x + C[0]
//	S = malloc( sizeof(stack_node));
//	S->lineId = -1; // head of the stack
//	push(0); // push d_1 to the top of the stack;
//	I[0].a = -(double)INFTY;
//	I[0].b = (double)INFTY;
//	int m = 0;
//	ALines[m] = 0;
//	int i = 0, q = 0, l =0;
//	stack_node *d;
//	double x = 0.0;
//	int prev_interval = 0;
//	for(i = 1; i <n ;i++){
//        l = prev_interval-1; // the interval associated with A[i-1]
//        while(1){
//        	l++;
//        	if((I[l].a <= (double)A[i]) && ((double)A[i]<= I[l].b)){
//        		q = l;
//        		break;
//        	}
//        }
//
//		C[i] = B[ALines[q]]*(A[i]-1) + C[ALines[q]] + B[i];
//		d = peek();   // examine the top element of the stack
//		x = find_intersection_x(d->lineId, i);
//		while(x <= I[m].a){  // found a redundant line
//			pop();           // remove the redundant line
//			m--;
//			d = peek();
//			x = find_intersection_x(d->lineId, i);
//		}
//		prev_interval = l;
//	   if(x < (double) (INFTY-1)){
//		   push(i);
//		   I[m].b = x;
//		   I[m+1].a = x;
//		   I[m+1].b = INFTY;
//		   if( l >= m){
//			   if ((I[m].a <= ((double)A[i])) && (((double)A[i]) <= I[m].b)){
//			      prev_interval = m;
//			  }else {
//				  prev_interval = m+1;
//			  }
//		   }
//		   ALines[m+1] = i;
//		   m++;
//	   }
//	}
//return C[n-1];
//}
//
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
//double find_intersection_x(int x, int y){
//	int a1 = B[x], b1 = C[x];
//	int a2 = B[y], b2 = C[y];
//	if(a1 == a2){
//		if (b2  < b1) return -(double)INFTY;
//		else return (double) INFTY;
//	} else{
//		return ((double)(b2-b1))/((double)(a1 - a2));
//	}
//}
//
//
