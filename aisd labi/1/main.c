#include <stdio.h>
#include "info.h"
#include <malloc.h>
int main()
{
double *res=0;
Matrix matr;
if (input(&matr) == 0){
printf("%s\n", "End of file occured");
return 1;
}
output("Source matrix", matr);
mass(&matr,res);
erase(&matr);
return 0;
}


