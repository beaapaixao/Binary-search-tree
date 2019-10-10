#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

/*
 * Arvore.h
 *
 *  Created on: 24 de set de 2019
 *      Author: 04583259379
 */

#ifndef ARVORE_H_
#define ARVORE_H_

typedef struct node Node;

typedef struct TreeType Tree;

Tree * create();
void destroy(Tree * tree);

int height(Tree * tree);
int count_leaf(Tree * tree);
void print(Tree * tree);
void print_in(Node * root);
void print_substring(Tree * tree, char * substring);
void save_file(Tree * tree, FILE * file);
void carregar_arquivo(Tree * tree);
int search_name(Tree * tree, char* name);
void insert_name(Tree * tree, char* name);
void remove_name(Tree * tree, char* name);
void remove_node_biggest(Tree * tree, char * name);
void remove_node_smallest(Tree * tree, char * name);
int search2(Tree * tree, char* name);
void insert2(Tree* tree, char* name);
void remove2(Tree * tree, char* name);

#endif /* ARVORE_H_ */



#endif // TREE_H_INCLUDED
