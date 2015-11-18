////============================================================================
//// Author      : Hung Le
//// Description : C++ Code for http://codeforces.com/contest/590/problem/C
////============================================================================
//
//#include <iostream>
//#include<stdlib.h>
//#include<string.h>
//#include<queue>
////#include "utils.h"
//using namespace std;
//#define loop(i,n) for(int i = 0; i < n; i++)
//#define pr(s) cout << s << endl;
//#define MAX 20005
//#define INFTY 10000000
//int N , M;
//char **A;
//
//void printCharArray(char **A, int N, int M);
//bool check_surrounded(int x, int y, char c);
//void find_sp(queue<int> Sx, char c, int id);
//void printQueue(queue<int> Sa);
//void printSP(int id);
//int find_sp_length(int x, char c);
//
//
//int **Dx;
//int main() {
//	cin >> N >> M;
//	A = (char **) malloc(N*sizeof(char *));
//	loop(i, N){
//		A[i] = (char *)malloc(M*sizeof(char));
//		loop(j,M){
//			cin >> A[i][j];
//		}
//
//	}
//	Dx = (int **)malloc(4*sizeof(int*));
//	Dx[1] = (int*)(malloc((M*N)*sizeof(int)));
//	memset(Dx[1], -1 , (M*N)*sizeof(int));
//	Dx[2] = (int*)(malloc((M*N)*sizeof(int)));
//	memset(Dx[2], -1 , (M*N)*sizeof(int));
//	Dx[3] = (int*)(malloc((M*N)*sizeof(int)));
//	memset(Dx[3], -1 , (M*N)*sizeof(int));
//
//	queue <int> Sa;
//	queue <int> Sb;
//	queue <int> Sc;
//	loop(i,N){
//		loop(j,M){
//			if(A[i][j] == '1'){
//				Dx[1][i*M+j] = 0;
//				if(!check_surrounded(i,j, '1')){
//					Sa.push(i*M+j);
//				}
//			}
//			else if(A[i][j] == '2'){
//				Dx[2][i*M+j] = 0;
//				if(!check_surrounded(i,j, '2')){
//					Sb.push(i*M+j);
//				}
//			}
//			else if(A[i][j] == '3'){
//				Dx[3][i*M+j] = 0;
//				if(!check_surrounded(i,j, '3')){
//					Sc.push(i*M+j);
//				}
//			}
//		}
//	}
//	find_sp(Sa, '1', 1);
//	find_sp(Sb, '2', 2);
//	find_sp(Sc, '3', 3);
//	int cost = INFTY;
//	int a,b,c, tmp;
//	loop(i,N){
//		loop(j ,M){
//			if(A[i][j] == '.'){
//				a = (Dx[1][i*M + j] == -1)? INFTY : (Dx[1][i*M + j]);
//				b = ((Dx[2][i*M + j] == -1)? INFTY :( Dx[2][i*M + j]));
//				c =((Dx[3][i*M + j] == -1)? INFTY : (Dx[3][i*M + j]));
//				tmp = a+b+c-2;
//				if(tmp< cost) cost  = tmp;
//			}
//		}
//	}
//	int d[3][3];
//	d[0][1] = find_sp_length(1,'2');
//	d[1][0] = d[0][1];
//	d[1][2] = find_sp_length(2,'3');
//	d[2][1] = d[1][2];
//	d[0][2] = find_sp_length(1,'3');
//	d[2][0] = d[0][2];
//	cost  = (d[0][1] + d[0][2]-2 < cost)? d[0][1] + d[0][2]-2: cost;
//	cost  = (d[1][2] + d[1][0]-2 < cost)? d[1][2] + d[1][0]-2: cost;
//	cost  = (d[2][1] + d[2][0]-2 < cost)? d[2][1] + d[2][0]-2: cost;
//
//	if(cost >= INFTY/2){
//		cout << -1 << endl;
//	}else{
//		cout << cost << endl;
//	}
//
//	return 0;
//}
//bool check_surrounded(int x, int y, char c){
//	return (x == 0? true: (A[x-1][y] == c || A[x-1][y] == '#') )
//			&&  (x == N-1? true: (A[x+1][y] == c || A[x+1][y] == '#'))
//			&& (y == 0? true: (A[x][y-1] == c || A[x][y-1] == '#') )
//			&& (y == M-1? true: (A[x][y+1] == c || A[x][y+1] == '#'));
//	}
//
//int find_sp_length(int x, char c){
//	int length = INFTY;
//	loop(i,N){
//		loop(j,M){
//			if(A[i][j] == c && (Dx[x][i*M+j]!= -1) &&  Dx[x][i*M+j]< length){
//				length = Dx[x][i*M+j];
//			}
//		}
//	}
//	return length;
//}
//
//void find_sp(queue<int> Sx, char c, int id){
//		int x;
//		while(!Sx.empty()){
//				x = Sx.front();
//				Sx.pop();
//				int p = x/M;
//				int q = x%M;
//				if((p > 0) && Dx[id][(p-1)*M + q] == -1 && A[p-1][q] != '#'){
//					Dx[id][(p-1)*M + q] = Dx[id][x] + 1;
//					Sx.push((p-1)*M + q);
//				}
//				if((p < N-1) && Dx[id][(p+1)*M + q] == -1 && A[p+1][q] != '#'){
//							Dx[id][(p+1)*M + q] = Dx[id][x] + 1;
//							Sx.push((p+1)*M + q);
//				}
//				if((q > 0) && Dx[id][p*M + q-1] == -1  && A[p][q-1] != '#'){
//							Dx[id][p*M + q-1] = Dx[id][x] + 1;
//							Sx.push(p*M + q-1);
//				}
//				if((q < M-1) && Dx[id][p*M + q+1] == -1  && A[p][q+1] != '#'){
//							Dx[id][p*M + q+1] = Dx[id][x] + 1;
//							Sx.push(p*M + q+1);
//				}
//
//		}
//}
//
//
//void printQueue(queue<int> Sa){
//	while(!Sa.empty()){
//		int x = (int)Sa.front();
//		Sa.pop();
//		cout << "(" << x/M << "," << x%M << ")" << endl;
//	}
//}
//void printArray(int *A, int i,int j){
//	for(int k = i; k <= j-1; k++ ){
//		cout << A[k]<<" ";
//	}
//	cout << A[j]<< endl;
//}
//
//void printSP(int id){
//	loop(i, N){
//		loop(j,M){
//			cout << Dx[id][i*M + j] << " ";
//		}
//		cout << endl;
//	}
//}
//void printCharArray(char **A, int N, int M){
//	loop(k, N){
//		loop(j,M){
//			cout << A[k][j]<< " ";
//		}
//		cout << endl;
//	}
//}
