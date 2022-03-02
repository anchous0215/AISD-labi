#ifdef INFO_H
#define INFO_H
#define ST_SIZE 160// максимальный размер вектора
int top;
char stack[ST_SIZE];
int push (char n); 
int pop (char *a);
void alg (char*, char*, int a);

typedef struct Item {
	char data;
	struct Item *next;
}Item;

typedef struct st {
 	Item *head;
} st;

st* make_empty_stack_ptr();
void pushs(st *head, char a);
int pops(st *head, char *a);
void algs(char*,char*, int a);

int getin (char*);
int number_of(char *a, int);
void shoose_algo(int *flag);
#endif
