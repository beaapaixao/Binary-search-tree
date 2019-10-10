/*
 * Arvore.c
 *
 *  Created on: 24 de set de 2019
 *      Author: 04583259379
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"

typedef struct node Node;

typedef struct TreeType {
	Node * root;
}Tree;

struct node {
	// char * name;
	char name[31];
	Node * father;
	Node * left;
	Node * right;
};

Tree * create() {
   Tree * tree = malloc(sizeof(Tree));
   tree->root = NULL;
   return tree;
}

void destroy_node_rec(Node * root) {
	if (root != NULL) {
		destroy_node_rec(root->left);
		destroy_node_rec(root->right);
		free(root);
	}
}
void destroy(Tree * tree) {
	destroy_node_rec(tree->root);
	free(tree);
}

void print_pre(Node * root) {
	if (root != NULL) {
		printf("%s ", root->name);
		print_pre(root->left);
		print_pre(root->right);
	}
}

void print_in(Node * root) {
	if (root != NULL) {
		print_in(root->left);
		printf("%s ", root->name);
		print_in(root->right);
	}
}

void print_pos(Node * root) {
	if (root != NULL) {
		print_pos(root->left);
		print_pos(root->right);
		printf("%s ", root->name);
	}
}

void print(Tree * tree) {
	print_in(tree->root);
	printf("\n");
}

void save_file_rec(Node * node, FILE * file) {
	if(node != NULL) {
		save_file_rec(node->left, file);
		fprintf(file,"%s ", node->name);
		fprintf(file, "\n");
		save_file_rec(node->right, file);
	}
}

void save_file(Tree * tree, FILE * file) {	
	save_file_rec(tree->root, file);	
}

void print_substring_rec(Node * node, char * substring) {
	if(node != NULL) {
		print_substring_rec(node->left, substring);
		if(strstr(node->name, substring)) {
			printf("%s ", node->name);
		}
		print_substring_rec(node->right, substring);
	}
}

void print_substring(Tree * tree, char * substring) {
	print_substring_rec(tree->root, substring);
	printf("\n");
}

void carregar_arquivo(Tree * tree) {
	FILE * arquivo = fopen("arquivo.txt", "r");
	char string[100];
	char name[31];
	destroy_node_rec(tree->root);
	tree->root = NULL;
	if(arquivo != NULL) {			
		while( (fgets(string, sizeof string - 1, arquivo)) != NULL) {
			sscanf(string, "%[^\n]", name);
			insert_name(tree, name);
		}

	}
	fclose(arquivo);
}

int height_rec(Node * root) {
	if (root != NULL) {
		int rt = height_rec(root->right);
		int lt = height_rec(root->left);
		return (rt > lt ? rt : lt) + 1;
	}
	return -1;
}

int height(Tree * tree) {
	return height_rec(tree->root);
}


int count_leaf_rec(Node * root) {
	if (root != NULL) {
		if (root->left == NULL && root->right == NULL) {
			return 1;
		} else {
			return count_leaf_rec(root->left) +
				   count_leaf_rec(root->right);
		}
	}
	return 0;
}

int count_leaf(Tree * tree) {
	return count_leaf_rec(tree->root);
}


int search_rec(Node * root, char* name) {
	if (root != NULL) {
		if (strcmp(root->name,name) > 0) {
			return search_rec(root->left, name);
		}
		if (strcmp(root->name,name)<0) {
			return search_rec(root->right, name);
		}
		return 1;
	}
	return 0;
}

int search_name(Tree * tree, char* name) {
	return search_rec(tree->root, name);
}



Node * insert_rec(Node * root, char name[]) {
	if (root != NULL) {
		if (strcmp(root->name,name) > 0) {
			root->left = insert_rec(root->left, name);
		}
		if (strcmp(root->name,name) < 0) {
			root->right = insert_rec(root->right,name);
		}
	} else {
		root = malloc(sizeof(Node));	
		strcpy(root->name,name);		
		root->left = NULL;
		root->right = NULL;
	}
	return root;
}

void insert_name(Tree * tree, char* name) {
	tree->root = insert_rec(tree->root, name);
}

//TODO REVER ESSE M�TODO
Node * remove_biggest(Node * root, char * pbiggest_name) {
	if (root != NULL) {
		if (root->right != NULL) {
			root->right = remove_biggest(root->right, pbiggest_name);
		} else {
			Node * aux = root;
			pbiggest_name = root->name;
			root = root->left;
			free(aux);
		}
	}
	return root;
}

Node * remove_rec(Node * root, char* name) {
	if (root != NULL) {
		if (strcmp(root->name,name) > 0) {
			root->left = remove_rec(root->left, name);			
		} else {
			if (strcmp(root->name,name) < 0) {
				root->right = remove_rec(root->right, name);
			} else { //ENCONTROU
				Node * aux = root;
				// FOLHA (GRAU 0)				
				if (root->left == NULL && root->right == NULL) {

					root = NULL;
					free(aux);
				} else {
					//GRAU 1
					if (root->left == NULL || root->right == NULL) {

						root = root->left != NULL ? root->left : root->right;
						free(aux);
					} else { //GRAU 2
						
						char* biggest_name = NULL;
						root->left = remove_biggest(root->left, biggest_name);
						strcpy(root->name, biggest_name);
						// root->name = biggest_name;
					}
				}
			}
		}
	}
	return root;
}

void remove_name(Tree * tree, char* name) {
	tree->root = remove_rec(tree->root,name);
}

// void * remove_node_biggest_rec(Node * node, char * name) {
//     if(node != NULL) {
//         if(strcmp(name, node->name) == 0){

//         }
//         if(strcmp(name, node->name) < 0) {
//             remove_rec(node, node->name);
//         }
//         remove_node_biggest_rec(node->right, name);
//     }
//     return node;
// }

void remove_node_biggest_rec(Node * * node, char * name) {
	Node * root = * node;
	if(root != NULL) {
		remove_node_biggest_rec(&root->right, name);
		if(strcmp(name, root->name) < 0) {
			remove_node_biggest_rec(&root->left, name);
			Node * help = root;
			root = root->left;
			free(help);
			*node = root;
		}
	}
}

void remove_node_biggest(Tree * tree, char * name) {
    remove_node_biggest_rec(&tree->root, name);
}

void remove_node_smallest_rec(Node * * node, char * name) {
	Node * root = * node;
	if(root != NULL) {
		remove_node_smallest_rec(&root->left, name);
		if(strcmp(name, root->name) > 0) {
			remove_node_smallest_rec(&root->right, name);
			Node * help = root;
			root = root->right;
			free(help);
			*node = root;
		}
	}
}

void remove_node_smallest(Tree * tree, char * name) {
	remove_node_smallest_rec(&tree->root, name);
}

int search2(Tree * tree, char* name) {
	Node * root = tree->root;
	while(root != NULL) {
		if (strcmp(root->name,name) == 0){
			return 1;
		}
		root = (strcmp(root->name,name) > 0) ?
			root->left : root->right;
	}
	return 0;
}

// void insert2(Tree* tree, char* name) {
// 	Node * father = NULL, * root = tree->root;
// 	while(root != NULL) {
// 		if (strcmp(root->name,name) == 0){
// 			return;
// 		}
// 		father = root;
// 		root = (strcmp(root->name,name) > 0) ? root->left : root->right;
// 	}
// 	root = malloc(sizeof(Node));
// 	root->name = name;
// 	root->left = NULL;
// 	root->right = NULL;
// 	if (father == NULL) {
// 		tree->root = root;
// 	} else {
// 		if (strcmp(father->name,name) > 0) {
// 			father->left = root;
// 		} else {
// 			father->right = root;
// 		}
// 	}
// }

void remove2(Tree * tree, char* name) {
	Node * father = NULL, * root = tree->root;
	//COME�A COM UMA BUSCA
	while(root != NULL) {
		if (strcmp(root->name,name) == 0) {
			break;
		}
		father = root;
		father = (strcmp(root->name,name) > 0)?
			root->left : root->right;
	}
	if (root == NULL) {
		return;
	}
	// FOLHA (GRAU 0)
	if (root->left == NULL && root->right == NULL) {
		if (father != NULL) {
			if (father->name > root->name) {
				father->left = NULL;
			} else {
				father->right = NULL;
			}
		} else {
			tree->root = NULL;
		}
		free(root);
	} else {
		//GRAU 1
		if (root->left == NULL || root->right == NULL) {
			if (father != NULL) {
				if (root->left != NULL) {
					if (strcmp(father->name,root->name) > 0) {
						father->left = root->left;
					} else {
						father->right = root->left;
					}
				} else {
					if (strcmp(father->name,root->name) < 0) {
						father->left = root->right;
					} else {
						father->right = root->right;
					}
				}
			} else {
				if (root->left != NULL) {
					tree->root = root->left;
				} else {
					tree->root = root->right;
				}
			}
			free(root);
		} else { //GRAU 2
			Node * biggest_node = root->left;
			//percorre � direita at� NULO
			father = root;
			while(biggest_node->right != NULL) {
				father = biggest_node;
				biggest_node = biggest_node->right;
			}
			strcpy(root->name,biggest_node->name);
			if (father == root) {
				father->left = biggest_node->left;
			} else {
				father->right = biggest_node->left;
			}
			free(biggest_node);
	}
}
}
