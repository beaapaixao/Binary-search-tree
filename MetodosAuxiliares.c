#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Tree.h"
#include "MetodosAuxiliares.h"


void alphabetical_order(Tree* tree){
   print(tree);
}

void inserir_no_Arquivo(char nome[],FILE* arquivo){

	for(int i=0;i<strlen(nome);i++){
		if(nome[i]!= tolower(nome[i]) ){
			nome[i] = tolower(nome[i]);
		}
	}

	fprintf(arquivo,"%s",nome);
	fprintf(arquivo,"\n");
}

void list_name_substring(Tree * tree) {
    char * substring = (char *) malloc(40 * sizeof(char));

    printf("Listar todos os nomes que contem uma substring fornecida\n");
    printf("Insira a substring:\n");
    scanf("%s", substring);
    print_substring(tree, substring);
    free(substring);
}

void add_name(Tree * tree) {
    char * name = (char *) malloc(40 * sizeof(char));
	// FILE * arquivo = fopen("arquivo.txt", "a+");

    printf("Insira o nome a ser adicionado: ");
    scanf("%s", name);
    fflush(stdin);
    insert_name(tree, name);
	// inserir_no_Arquivo(name, arquivo);
	// fclose(arquivo);
    free(name);
}

void remove_node_name(Tree * tree) {
    char * name = (char *) malloc(40 * sizeof(char));

    printf("Insira o nome a ser removido: ");    
    scanf("%s", name);
    fflush(stdin);
    remove_name(tree, name);        
    free(name);
}

void remove_name_biggest(Tree * tree) {
    char * name = (char *) malloc(40 * sizeof(char));

    printf("Insira o nome: ");
    scanf("%s", name);    
    fflush(stdin);
    remove_node_biggest(tree, name);
    print(tree);
    free(name);
}

void remove_name_smallest(Tree * tree) {
	char * name = (char *) malloc(40 * sizeof(char));

    printf("Insira o nome: ");
    scanf("%s", name);    
    fflush(stdin);
    remove_node_smallest(tree, name);
    print(tree);
    free(name);	
}

void salvar_arquivo(Tree * tree) {
	FILE * file = fopen("arquivo.txt", "w");
	save_file(tree, file);
	fclose(file);
	printf("Arquivo salvo com sucesso\n");
}

void menu(Tree * tree){
	char nome[31]; //30 caracteres + o terminador '\0'
	char * substring = (char *) malloc(40 * sizeof(char));
	// FILE *arquivo = fopen("\\User\\thyago\\FB\\arquivo.txt", "a+");
	// FILE * arquivo = fopen("arquivo.txt", "w");


    int op = -1;
	while (op != 0) {
		printf("\n\n\tLista de Nomes - Escolha uma opcao");
		printf("\n\n");
		printf("1 - Listar em ordem alfabética\n");
		printf("2 - Listar todos os nomes que contem uma substring fornecida\n");
		printf("3 - Inserir um novo nome na memoria\n");
		printf("4 - Remover um novo nome na memoria\n");
		printf("5 - Listar e remover da memoria todos os nomes que sao maiores que um fornecido\n");
		printf("6 - Listar e remover da memoria todos os nomes que sao menores que um fornecido\n");
		printf("7 - Salvar o conteúdo da memória em um arquivo\n");
		printf("8 - Carregar Arquivo\n");
		printf("0 - Sair\n\n");
		scanf("%d", &op);

		switch (op) {
		case 0:
			break;		
		case 1: 
			printf("\t\tListar em ordem alfabética\n\n");
			alphabetical_order(tree);
			break;
		case 2: 
			list_name_substring(tree);
			break;
		case 3: 

            // printf("*** Inserir um novo nome na mem�ria\n***");
			// char *nameptr;
			

		    // printf("Insira o nome:\n");
            // scanf("%s",nome);
            // nameptr = nome;
			// insert_name(tree,nameptr);
			add_name(tree);
            
			break;
		case 4: 
		    // char *nameptr;

		    // printf("Insira o nome a ser removido:\n");
            // scanf("%s",nome);
            // nameptr = nome;
		    // remove_name(tree,nameptr);
			remove_node_name(tree);
			break;
		case 5: 
			remove_name_biggest(tree);
			break;
		case 6: 
			remove_name_smallest(tree);
			break;
		case 7:
			//ler_do_arquivo(arquivo);

			// char* buff[100];
			// fgets(*buff, 100, arquivo);
			// printf("1 : %s\n", buff );
			salvar_arquivo(tree);		
			break;
		case 8:
			carregar_arquivo(tree);
			printf("Arquivo carregado com sucesso\n");
			break;
		default:
			printf("Digite uma opção válida");
		}
	}
}

