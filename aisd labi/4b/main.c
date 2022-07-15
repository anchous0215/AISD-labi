#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include "func.h"

int main (){
Node *tree = (Node *)malloc(sizeof(Node));
	inittree_zeroes(&tree);
	FILE* f;
	char* fname = (char*)malloc(10);
	while(1){
		printf("Введите название файла: \n");
		scanf ("%s", fname);
	if((f = fopen(fname, "rb"))==NULL){
		printf("Некорректно введено имя файла или такого файла не существует. Попробуйте ещё раз.\n");
		}
	    	else
			break;
	}
	f = fopen(fname, "rb");
	fileInput(&tree, f);
	while (dialog(&tree, f));
	printf("That's all. Bye!\n");
	return 0;
}
