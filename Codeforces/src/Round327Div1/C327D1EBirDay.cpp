////============================================================================
//// Author      : Hung Le
//// Description : C++ Code for http://codeforces.com/contest/590/problem/D
////============================================================================
//
//#include <iostream>
//#include<stdlib.h>
//#include<string.h>
//#include<queue>
//using namespace std;
//typedef unsigned long long LLU;
//#define loop(i,n) for(int i = 0; i < n; i++)
//#define loopp(i,j,n) for(int i = j; i < n; i++)
//#define pr(s) cout << s << endl;
//#define MAX 750
//#define INFTY 10000000000000
//#define ALP  2
//
//
//int N;
//int **A;
//vector<string> Ss;
//
//
//void  printArray(int *A, int i, int j);
//typedef struct _ac_node{
//	char c;
//	int id;
//	struct _ac_node *sli;
//	struct _ac_node *par;
//	struct _ac_node *cld[ALP];
//} _ac_node;
//
//vector<string> _acVs;
//_ac_node *_ac_new_node(char s);
//_ac_node *_ac_init_graph(vector<string> Ss);
//
//void _ac_insert(_ac_node *root, string s, int id);
//
//void _ac_build_link(_ac_node *root);
//
//void print_ac_node(_ac_node *node);
//
//void _ac_dfs_display_link(_ac_node *root);
//int int_cmp(const void *a, const void *b);
//void printArray(int *A, int i,int j);
//int *find_matching();
//
//int main() {
//	cin >> N;
//	A = (int **)malloc(N*(sizeof(int *)));
//	loop(i,N){
//		A[i]= (int *)malloc(N*sizeof(int));
//		memset(A[i], 0, N*sizeof(int));
//	}
//	Ss.reserve(N);
//	string s;
//	loop(i,N){
//		cin >> s;
//		Ss.push_back(s);
//	}
//	_ac_node *root  = _ac_init_graph(Ss);
//	_ac_node *tmp;
//	int l;
//	loop(i,N){
//		s = Ss.at(i);
//		tmp = root;
//		l = (int) s.length()-1;
//		loop(j, l){
//			if(tmp->cld[s.at(j)-'a']->id != -1){
//				A[i][tmp->cld[s.at(j)-'a']->id] = 1;
//			}
//			tmp = tmp->cld[s.at(j)-'a'];
//		}
//		tmp = tmp->cld[s.at(s.length()-1)-'a'];
//		if(tmp->sli->id != -1){
//			A[i][tmp->sli->id] = 1;
//			}
//		}
////	loop(i,N){
////		printArray(A[i], 0,N-1);
////	}
//	loop(k,N){
//		loop(i,N){
//			loop(j,N){
//				A[i][j] |= A[i][k] & A[k][j];
//			}
//		}
//
//	}
//
////	loop(i,N){
////			printArray(A[i], 0,N-1);
////	}
//	find_matching();
//
//}
//
//int *find_matching(){
//	int* M;
//	M = (int *)malloc((2*N)*sizeof(int));
//	memset(M,-1,(2*N)*sizeof(int));
//	loop(i,N){
//		loop(j,N){
//			if(A[i][j] == 1){
//				if(M[j+N] == -1){
//					//push (i,j+N) to the matching
//					M[i] = j+N;
//					M[j+N] = i;
//					break;
//				}
//			}
//		}
//	}
////	loop(i,2*N){
////		cout << "(" << i  << ","<<M[i]<< ") " ;
////	}
//	queue<int> Qx;
//	bool vs[2*N];
//	int Pr[2*N];
//	int s,t;
//	bool pfound  = false;
//	loop(i,N){ // the number of augmenting steps
//		loop(j,2*N) {
//			vs[j] = false; // unmarked all vertices
//			Pr[j] = j;
//		}
//		while(!Qx.empty())Qx.pop();
//		loop(j,N){
//			if(M[j] == -1) {
//				Qx.push(j);
////				cout <<"pushing " << j << endl;
//				vs[j] = true;
//			}
//		}
//		pfound = false;
//		t = -1;
////		cout << "find augmenting path" << endl;
//		while(!Qx.empty()){ // looking for an augmenting path
//			s = Qx.front();
//			Qx.pop();
////			cout << "visiting " << s << endl;
//			loop(k,N){ // loop through nbr of s
//				if(A[s][k] == 1){
////					cout << "examining " << k + N << endl;
//					if(!vs[k+N]){ // k+N is unvisited
//						vs[k+N] = true;
//						Pr[k+N] = s; // update parent of k+N
//						if(M[k+N] == -1){
//							// found an agmenting path
//							pfound = true;
////							cout << "found " << k+N << endl;
//							t = k + N;
//							break;
//						} else if(!vs[M[k+N]]){
//							vs[M[k+N]] = true;
//							Pr[M[k+N]] = k+N;
//							Qx.push(M[k+N]);
//						}
//					}
//				}
//			}
//			if(pfound) break;
//		}
//		if(t== -1){ // there is no augmenting path
//			break;
//		} else{ // tracking back augmenting path
//			int j = t;
////			cout << "agumenting path:" << endl;
//			while(Pr[j] != j){
////				cout << "("<< j << ","<< Pr[j] <<")" << endl;
////				cout << "("<< Pr[j] << ","<< Pr[Pr[j]] <<")" << endl;
//				M[j] = Pr[j];
//				M[Pr[j]] = j;
//				j = Pr[Pr[j]];
//			}
//		}
//	}
//	// found all matching
////	loop(i,2*N){
////		cout << "(" << i  << ","<<M[i]<< ") " ;
////	}
////	cout << endl;
//	// find vertex cover
//	bool cv[2*N];
//	vector<int> vcover;
//	loop(i,2*N) cv[i] = false;
//	int taken = -1;
//	loop(i,N){
//		if(M[i] != -1){
//			cv[i] = true;
//			cv[M[i]] = true;
//			loop(j,N){
//				if(A[i][j] == 1 && !cv[j+N]){
//					cv[j+N] = true;
//					taken = i;
//				}
//				if(A[j][M[i]-N] == 1 && M[j] == -1 &&!cv[j]){
//					cv[j] = true;
//					taken = M[i] - N;
//				}
//			}
//			vcover.push_back((taken == -1 ? i : taken));
////			cout << "add " << (taken == -1 ? i : taken) << " to vc" << endl;
//			taken = -1;
//		}
//	}
//	loop(i,N) cv[i] = false;
//	int sum = 0;
//	loop(i,vcover.size()) {
//		if(!cv[vcover.at(i)]){
//			sum++;
//			cv[vcover.at(i)]= true;
//		}
//
//	}
//	cout << (N - sum) << endl;
//	loop(i,N) if(!cv[i]) cout << i+1 << " ";
//	cout << endl;
//
//	return M;
//}
//
//
//_ac_node *_ac_init_graph(vector<string> Ss){
//	_acVs = Ss;
//	_ac_node *root = _ac_new_node('`');
//	loop(i,N){
//		_ac_insert(root, _acVs[i], i);
//	}
//	_ac_build_link(root);
////	_ac_dfs_display_link(root);
//	return root;
//}
//
//void _ac_dfs_display_link(_ac_node *root){
//	cout << "link of ";
//	print_ac_node(root);
//	cout << "is " ;
//	if(root->sli != NULL){
//		print_ac_node(root->sli);
//	} else {
//		cout << " NULL";
//	}
//	cout << endl;
//	loop(i,ALP){
//		if(root->cld[i] != NULL){
//			_ac_dfs_display_link(root->cld[i]);
//		}
//	}
//}
//
//
//
//_ac_node *_ac_new_node(char s){
//	_ac_node *node = (_ac_node*)malloc(sizeof(_ac_node));
//	node->c = s;
//	node->id = -1;
//	node->sli = NULL;
//	node->par = NULL;
//	loop(i,ALP){
//		node->cld[i] = NULL;
//	}
//	return node;
//}
//
//void _ac_insert(_ac_node *root, string s, int id){
////	cout << "inserting "<< s << endl;
//	_ac_node *tmp = root;
//	unsigned int i  = 0;
//	while(i < s.length() && tmp->cld[s.at(i) - 'a']!= NULL){
//		tmp = tmp->cld[s.at(i) - 'a'];
//		i++;
//	}
//	if( i == s.length()){
//		tmp->id = id;
//	} else {
//		_ac_node *nnode;
//		for(unsigned int j = i; j < s.length(); j++){
//			nnode = _ac_new_node(s.at(j));
//			tmp->cld[s.at(j)-'a'] = nnode;
//			nnode->par = tmp;
//			tmp = nnode;
//		}
//		tmp->id = id;
//	}
////	print_ac_node(tmp);
////	print_ac_node(tmp->par);
////	cout << endl;
//}
//
//void _ac_build_link(_ac_node *root){
//	root->sli = NULL;
//	queue<_ac_node *> q;
//	loop(i, ALP){
//		if(root->cld[i]!= NULL){
//			root->cld[i]->sli = root;
//			loop(j, ALP){
//				if(root->cld[i]->cld[j]!= NULL)
//					q.push(root->cld[i]->cld[j]);
//			}
//		}
//	}
//	_ac_node *tmp;
//	_ac_node *tmp_link;
//	while(!q.empty()){
//			tmp = q.front();
////			print_ac_node(tmp);
////			print_ac_node(q.front());
//			tmp_link = tmp->par->sli;
//			while(tmp_link != NULL){
//				if(tmp_link->cld[tmp->c - 'a'] != NULL){
//					tmp->sli = tmp_link->cld[tmp->c - 'a'];
//					if(tmp->id == -1) tmp->id = tmp_link->cld[tmp->c - 'a']->id;
//					break;
//				} else {
//					tmp_link = tmp_link->sli;
//				}
//			}
//			if(tmp_link == NULL){
//				tmp->sli = root;
//			}
//			loop(i, ALP){
//				if(tmp->cld[i] !=  NULL){
//					q.push(tmp->cld[i]);
//				}
//			}
//			q.pop();
//	}
//}
//void print_ac_node(_ac_node *node){
//
//		cout << '(' << node->c << ',' << node->id << ')';
//}
//int int_cmp(const void *a, const void *b){
//	int *x = (int *)a; int *y = (int *)b;
//	return (*x-*y);
//}
//
//void printArray(int *A, int i,int j){
//	for(int k = i; k <= j-1; k++ ){
//		cout << A[k]<<" ";
//	}
//	cout << A[j]<< endl;
//}
//
//
////10
////aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
////aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
////aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
////aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
////aaaaaaaaaaaaaaaaaaaaaaaaa
////aaaaaaaaaa
////aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
////aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
////aaa
////aaaa
//
