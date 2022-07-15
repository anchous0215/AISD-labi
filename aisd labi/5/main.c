#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include "func.h"

int main (){
	Graf graf;
	initgraf_zeroes(&graf);
	while (dialog(&graf));
	printf("That's all. Bye!\n");
	return 0;
}
