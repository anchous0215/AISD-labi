#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "func.h"
#define MSIZE2 10

int main () {
	Table table;
	initTable_zeroes(&table);
	while (dialog(&table));
	printf("That's all. Bye!\n");
	return 0;
}
