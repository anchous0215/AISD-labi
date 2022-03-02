#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "info.h"

int main()
{
	int flag=-1;
	char str[80];
	int length=getin(str);
	int number=number_of(str, length);
	int leng=length-number;
	shoose_algo(&flag);
	
	if (flag==0)
	{
		char res[leng];
		alg (str,res, length);
		for (int i=0; i<leng; i++)
			printf ("%c",res[i]);
	}
	else
	if (flag==1)
	{
		char res1[leng];	
		algs(str,res1, length);
		for (int i=0; i<leng; i++)
			printf ("%c",res1[i]);
	}
	return 0;
}


