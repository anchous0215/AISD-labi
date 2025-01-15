#include <stdio.h>
#include "info.h"
#include <malloc.h>

int getInt(int *a)
{
int n;
do{
    ыщьуерштп ааа
n = scanf("%d", a);
if (n < 0)
return 0;
if (n == 0){
printf("%s\n", "Error! Repeat input");
scanf("%*c");
}
} while (n == 0);
return 1;
}

int input(Matrix *rm)
{
const char *pr = "";
int m;
int i, j;
int *p;
do{
printf("%s\n", pr);
printf("Enter number of lines: —> "); 
pr = "You are wrong; repeat, please!";
if(getInt(&m) == 0)
return 0;
} while (m < 1);
rm->lines = m;
rm->matr = (Line *)calloc(m, sizeof(Line));
for (i = 0; i < rm->lines; ++i){
pr = "";
do{
printf("%s\n", pr);
printf("Enter number of items in line %d: —> ", i + 1);
pr = "You are wrong; repeat, please!";
if (getInt(&m) == 0){
rm->lines = i;
erase(rm);
return 0;
}
} while (m < 1);
rm->matr[i].n = m; 
p = (int *)malloc(sizeof(int)* m);
rm->matr[i].a = p;
printf("Enter items for matrix line #%d:\n", i + 1);
for (j = 0; j < m; ++j, ++p)
if (getInt(p) == 0){
rm->lines = i + 1;
erase(rm);
return 0;
}
}
return 1;
}

void output(const char *msg, Matrix a)
{
int i, j;
int *p;
printf("%s:\n", msg);
for (i = 0; i < a.lines; ++i){
p = a.matr[i].a; 
for (j = 0; j < a.matr[i].n; ++j, ++p)
printf("%d ", *p);
printf("\n");
}}

void erase(Matrix *a)
{
int i;
for (i = 0; i < a->lines; ++i)
free(a->matr[i].a);
free(a->matr);
a->lines = 0;
a->matr = NULL;
}

double aver(int a[], int m)
{
double res = 0; 
for (int i=0; i< m; ++i,++a){
res=res+*a;
}
res = res/m;

return res;
}

double max(double a[], int m)
{
double res = *a;
for (int i=0; i<m; i++,a++){
if (*a > res)
res = *a;
}
return res;
}

void mass(Matrix *a,double *res) 
    { res= (double *)malloc(sizeof(double)* a->lines);
    double m;
    for(int i = 0;i<a->lines;i++ ) {
    *(res+i)=aver(a->matr[i].a,a->matr[i].n);
    }
    m=max(res, a->lines);
    for(int i = 0;i<a->lines;i++ ) {
    *(res+i)=*(res+i)/m;
    printf("%f ",*(res+i));
    }
    }
