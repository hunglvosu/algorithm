/*
 * An implementation of AVL tree insertion and deletion operations
 *
 * Warning: this implementation is not fully tested, use at your own risk
 * See http://www.giaithuatlaptrinh.com/?p=2054 and http://www.giaithuatlaptrinh.com/?p=2125
 * for more details.
 *
 *  Created on: Sept 25, 2017
 */  
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define null 0
#define TRUE 1
#define FALSE 0
#define max(a, b) (((a) > (b)) ? (a) : (b))

typedef struct Node{
	int key;
	int value;
	struct Node *left, *right;
	int height;
} Node;
Node *root; //the root of the AVL tree

Node *insert(Node *root, int k, int value);
Node *delete(Node *root, int k);
Node *find_min(Node *root);
Node *left_rotate(Node *A);
Node *right_rotate(Node *A);
Node * double_left_rotate(Node *A);
Node * double_right_rotate(Node *A);

Node *create_node(int k, int v);
void print_tree(Node *root);
Node *create_heavy_right_sample_tree();
Node *create_heavy_left_sample_tree();
Node *create_deletion_sample_tree();
int height(Node *node);
void check_AVL(Node *root);	// check whether a tree is an AVL tree;
int check_node(Node *node);	// return true if the subtree rooted at an input node is an AVL tree;


int main(){
	root = create_heavy_right_sample_tree();
	print_tree(root);
	check_AVL(root);
	
	root = insert(root, 15, -7);
	print_tree(root);
	check_AVL(root);
	
	//uncomment for testing doubly left rotation	
	//root = insert(root, 12, 1);
	//print_tree(root);
	//check_AVL(root);
	
	root = insert(root, 17, 1);
	print_tree(root);
	check_AVL(root);
	
/*	uncomment to test right rotation operations
	root = create_heavy_left_sample_tree();
	print_tree(root);
	check_AVL(root);
	
	//uncomment for testing right rotation	
	//root = insert(root, 2, -7);
	//print_tree(root);
	//check_AVL(root);
	
	//uncomment for testing doubly right rotation	
	root = insert(root, 5, -7);
	print_tree(root);
	check_AVL(root);*/
	
/* 	uncomment to test deletion operation
	root = create_deletion_sample_tree();
	print_tree(root);
	check_AVL(root);
	
	root = delete(root, 19);
	print_tree(root);
	check_AVL(root);*/
	

}

Node *insert(Node *root, int k, int value){
	if(root == null) return create_node(k, value);
	if(root->key < k){
		root->right = insert(root->right, k, value);
		if(height(root->right) == height(root->left) + 2){
			Node *b = root->right;
			if(height(b->right) == height(b->left) + 1){
				//printf("we need to do LEFT ROTATION at %d\n", root->key);
				return left_rotate(root);
			}else {
				//printf("we need to do DOUBLY LEFT ROTATION at %d\n", root->key);
				return double_left_rotate(root);
			}
		}
	}else{	// note: we assume that k is not in the tree
		root->left = insert(root->left, k, value);
		if(height(root->left) == height(root->right) + 2){
			Node *b = root->left;
			if(height(b->left) == height(b->right) + 1){
				//printf("we need to do RIGHT ROTATION at %d\n", root->key);	
				return right_rotate(root);
			} else {
				//printf("we need to do DOUBLY RIGHT ROTATION at %d\n", root->key);	
				return double_right_rotate(root);
			}
		}
	}
	root->height  = max(height(root->left), height(root->right))+1;
	return root;
}

Node *delete(Node *root, int k){
	if(root->key < k){
		root->right = delete(root->right, k);
	}else if(root->key > k){
		root->left = delete(root->left, k);
	} else {
		if(root->left == null) return root->right;
		else if(root->right == null) return root->left;
		else {
			Node *y = find_min(root->right);
			root->key = y->key;
			root->value = y->value;
			root->right = delete(root->right, y->key);
		}
	}
	root->height = max(height(root->left), height(root->right))+1;
	int h = height(root);
	if(height(root->left) == height(root->right) + 2){
		Node *b = root->left;
		if(height(b->left) == h-2){
			//printf("we need to do RIGHT ROTATION at %d\n", root->key);
			return right_rotate(root);
		} else {
			//printf("we need to do DOUBLY RIGHT ROTATION at %d\n", root->key);
			return double_right_rotate(root);
		}
	}
	if(height(root->right) == height(root->left) + 2){
		Node *b = root->right;
		if(height(b->right) == h-2){
			return left_rotate(root);
		} else {
			return double_left_rotate(root);
		}
	}
	return root;
}

Node *find_min(Node *root){
	if(root->left == null) return root;
	else return find_min(root->left);
}
Node *left_rotate(Node *A){
	Node *B = A->right;
	A->right = B->left;
	B->left = A;
	A->height = max(height(A->left), height(A->right)) + 1;
	B->height = max(height(B->left), height(B->right)) + 1;
	return B;
}

Node *right_rotate(Node *A){
	Node *B = A->left;
	A->left = B->right;
	B->right = A;
	A->height = max(height(A->left), height(A->right)) + 1;
	B->height = max(height(B->left), height(B->right)) + 1;
	return B;
}
Node * double_left_rotate(Node *A){ // see http://www.giaithuatlaptrinh.com/?p=2054 for notation
	Node *B = A->right;
	Node *C = B->left;
	A->right = C->left;
	B->left = C->right;
	C->left = A;
	C->right = B;
	B->height = max(height(B->left), height(B->right)) + 1;
	A->height = max(height(A->left), height(A->right)) + 1;
	C->height = max(height(C->left), height(C->right)) + 1;
	return C;
}

Node * double_right_rotate(Node *A){
	Node *B = A->left;
	Node *C = B->right;
	A->left = C->right;
	B->right = C->left;
	C->right = A;
	C->left = B;
	B->height = max(height(B->left), height(B->right)) + 1;
	A->height = max(height(A->left), height(A->right)) + 1;
	C->height = max(height(C->left), height(C->right)) + 1;
	return C;	
}

int height(Node *node){
	if(node == null) return 0;
	else return node->height;
}

// create a heavy-right tree as in http://www.giaithuatlaptrinh.com/?p=2054 to test left rotation
Node *create_heavy_right_sample_tree(){	
	Node *	root = create_node(7,5);
	root->height = 4;
	root->left = create_node(3,-1);
	root->left->height = 2;
	root->left->left = create_node(2,0);
	root->right = create_node(10,6);
	root->right->height = 3;
	root->right->right =  create_node(14,2);
	root->right->right->height = 2;
	root->right->left = create_node(9,9);
	root->right->right->left =  create_node(13,-3);
	return root;
}
// create a heavy-left sample AVL tree to test right rotation
Node *create_heavy_left_sample_tree(){
	Node *	root = create_node(10,5);
	root->height = 4;
	root->left = create_node(7,-1);
	root->left->height = 3;
	root->left->left = create_node(3,0);
	root->left->left->height = 2;
	root->left->right = create_node(8,3);
	root->left->left->left = create_node(1,4);
	root->left->left->right = create_node(4,5);
	root->right = create_node(12,9);
	root->right->height = 2;
	root->right->right = create_node(13,10);
	return root;
}
Node *create_deletion_sample_tree(){ // create a tree for testing deletion operation from http://www.giaithuatlaptrinh.com/?p=2125
	Node *	root = create_node(10,5);
	root->height = 6;
	// create the left tree
	root->left = create_node(6,2);
	root->left->height = 4;
	root->left->left = create_node(3,0);
	root->left->left->height = 3;
	root->left->right = create_node(9,9);
	root->left->right->height = 2;
	root->left->left->left = create_node(2,7);
	root->left->left->left->height = 2;
	root->left->left->right = create_node(5,4);
	root->left->right->left = create_node(7,2);
	root->left->left->left->left = create_node(1,3);
	// create the right tree
	root->right = create_node(19,10);
	root->right->height = 5;
	root->right->right = create_node(22,-1);
	root->right->right->height = 3;
	root->right->left = create_node(15,-5);
	root->right->left->height = 4;
	root->right->left->left = create_node(13,-2);
	root->right->left->left->height = 3;
	root->right->left->right = create_node(17,20);
	root->right->left->right->height = 2;
	root->right->right->left = create_node(20,0);
	root->right->right->left->height = 2;
	root->right->right->right = create_node(23,12);
	root->right->left->left->left = create_node(12,6);
	root->right->left->left->left->height = 2;
	root->right->left->left->right = create_node(14,17);
	root->right->left->right->left = create_node(16,5);
	root->right->right->left->right = create_node(21,2);
	root->right->left->left->left->left = create_node(11,7);
	return root;
}


// create a new node
Node *create_node(int k, int v){
	Node *x = (Node *)malloc(sizeof(Node));
	x->key = k; x->value = v;
	x->left = null; x->right = null;
	x->height = 1;		// null nodes have 0 height
	return x;
}


void print_tree(Node *root){
	printf("Node: %d\t height: %d\t",root->key, root->height);
	if(root->left != null)	printf("Left: %d\t",root->left->key);
	if(root->right != null)	printf("Right: %d ",root->right->key);
	printf("\n");
	if(root->left != null)	print_tree(root->left);
	if(root->right != null)	print_tree(root->right);
}

void check_AVL(Node *root){
	printf("\n\n\n");
	printf("Checking AVL properties of the tree rooted at: %d\n", root->key);
	int check_result = check_node(root);
	printf("Checking done!\n");
	if(check_result == TRUE){
		printf("The input tree is AVL\n");
	}else {
		printf("The input tree is NOT AVL\n");
	}
	printf("\n\n\n");
}
int check_node(Node *node){
	if(node == null) return TRUE;
	if(check_node(node->left) && check_node(node->right) &&
		height(node) == max(height(node->left), height(node->right)) + 1 &&
		(abs(height(node->left) - height(node->right)) <= 1)) return TRUE;
	else{
		printf("node (%d, %d) is violated, height: %d, left height: %d, right height: %d \n", node->key, node->value, height(node), height(node->left), height(node->right));
	} 
	return FALSE;
}
