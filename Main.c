#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"
#include "MetodosAuxiliares.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	Tree * tree = create();
	carregar_arquivo(tree);
	// insert_name(tree,"brenda");
	// insert_name(tree,"paulo");
	// insert_name(tree,"tiago");
	// insert_name(tree,"ryan");
	// insert_name(tree,"leonardo");
	// insert_name(tree,"talita");
	// insert_name(tree,"murilo");
	// insert_name(tree,"lucas");



    // remove_name(tree, "murilo");
	// remove_name(tree, "lucas");


	menu(tree);
//	print(tree);
	destroy(tree);



	printf("\nObrigada! O codigo encerra aqui!\n\n");
	return 0;
	// fclose(arquivo);
	//getchar();
	// system("pause");
}
