/*
 * utils.h
 *
 *  Created on: Nov 16, 2015
 *      Author: hunglv
 */

#ifndef UTILS_H_
#define UTILS_H_

#include<string.h>
using namespace std;
#define ALP  2

void  printArray(int *A, int i, int j);
typedef struct _ac_node{
	char c;
	int id;
	struct _ac_node *sli;
	struct _ac_node *par;
//	struct _ac_node *pr_child;
	struct _ac_node *cld[26];
} _ac_node;

vector<string> _acVs;
_ac_node *_ac_new_node(char s);
_ac_node *_ac_init_graph(vector<string> Ss);
void _ac_insert(_ac_node *root, string s, int id);

void _ac_build_link(_ac_node *root);

void print_ac_node(_ac_node *node);

void _ac_dfs_display_link(_ac_node *root);

#endif /* UTILS_H_ */
