#ifndef INFO_H
#define INFO_H
typedef struct Line{
int n;
int *a;
} Line;
typedef struct Matrix{
int lines;
Line *matr;
} Matrix; 
int getInt(int *);
int input(Matrix *a);
void output(const char *msg, Matrix a);
void erase(Matrix *a);
void mass(Matrix *a,double *res);//гл рез-т
void output1 (const char *mus, double *res);//вывод гл рез-та
double aver(int k[], int s); // вычисление среднего арифметического
double max(double k[], int s); //вычисление максимума строк 
#endif
