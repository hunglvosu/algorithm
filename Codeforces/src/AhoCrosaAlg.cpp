////============================================================================
//// Author      : Hung Le
//// Description : C++ Code for http://codeforces.com/contest/590/problem/D
////============================================================================
//
//#include <iostream>
//#include<stdlib.h>
//#include<string.h>
//#include<queue>
//#include "utils.h"
//using namespace std;
//typedef unsigned long long LLU;
//#define loop(i,n) for(int i = 0; i < n; i++)
//#define loopp(i,j,n) for(int i = j; i < n; i++)
//#define pr(s) cout << s << endl;
//#define MAX 150
//#define INFTY 10000000000000
//int N;
//vector<string> Ss;
//int int_cmp(const void *a, const void *b);
//void printArray(int *A, int i,int j);
//
//int main() {
//	cin >> N;
//	Ss.reserve(N);
//	string s;
//	loop(i,N){
//		cin >> s;
//		Ss.push_back(s);
//	}
//	_ac_node *root  = _ac_init_graph(Ss);
////	loop(i,N){
////		pr(_acVs[i]);
////	}
//}
//
//_ac_node *_ac_init_graph(vector<string> Ss){
//	_acVs = Ss;
//	_ac_node *root = _ac_new_node('`');
//	loop(i,N){
//		_ac_insert(root, _acVs[i], i);
//	}
//	_ac_build_link(root);
//	_ac_dfs_display_link(root);
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
//	print_ac_node(tmp);
//	print_ac_node(tmp->par);
//	cout << endl;
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
//
