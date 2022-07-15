#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "func.h"
#define MSIZE2 10

int main () {
	Table table;
	initTable_zeroes(&table);
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
	fileInput(&table, f);
	while (dialog(&table, f));
	FILE* p;
	char* o = "p";
	p = fopen(o, "w");
	show_tab (&table, p, f);
	fclose (f);
	remove (fname);
	rename ("p", "tab");
	fclose (p);
	printf("That's all. Bye!\n");
	return 0;
}
