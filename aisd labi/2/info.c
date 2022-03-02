#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "info.h"

int getin (char *a)
{
	int n;
	scanf("%s",a);
	n=strlen(a);
	return n;
}

int number_of(char *a, int k)
{
	int n=0;
	for (int i=0; i<k; i++,*a++)
	if (*a=='(')
		n=n+2;
return n;
}

void shoose_algo(int *flag)
{
	printf ("-s :prog sends the algo through the list\n");
	printf ("-v :prog sends the algo through the VECTOR\n");
	printf ("please write what you want\n");
	char tmp[2];
	while  (*flag==-1)
	{
		scanf ("%s", tmp);
		scanf ("*c");
		if (!strcmp(tmp,"-v"))
			*flag=0;
		else
		if (!strcmp(tmp,"-s"))
			*flag=1;
		else
			printf ("you are wrong: Try again");
	}
}

int push(char new)
{
	if (top >= ST_SIZE)
		return 1;
	stack[top]=new;
	top = top + 1;
	return 0;
}

int pop(char *a)
{
	if (top <=0 )
		return 1;
	top = top - 1;
	*a=stack[top];
	return 0;
}

void alg (char *exp, char *res, int len)
{	
	top=0;
	for (int i=0; i<len; i++, exp++)
	{
		if(('a'<=*exp) && (*exp<='z'))
		{
			*res=*exp;
			res++;
		}
		if((*exp=='+')||(*exp=='-')||(*exp=='*')||(*exp=='/'))
		{
			if ((top==0)||(stack[top-1]=='('))
				push(*exp);
			else
				if((((*exp=='*')||(*exp=='/'))&&((stack[top-1]=='+')||(stack[top-1]=='-'))))
					push(*exp);
				else
					if(((((*exp=='+')||(*exp=='-'))&& ((stack[top-1]=='*')||(stack[top-1]=='/')))) || ((((*exp=='*')||(*exp=='/'))&&((stack[top-1]=='*')||(stack[top-1]=='/')))) || ((((*exp=='+')||(*exp=='-'))&&((stack[top-1]=='+')||(stack[top-1]=='-')))))
					{
						if (((*exp=='*')||(*exp=='/')))
						{
							while (((stack[top-1]!='-')||(stack[top-1]!='+')||(stack[top-1]!='('))&&((top-1)>=0))
							{
								pop (res);
								res++;
							}
							push(*exp);
						}
						if (((*exp=='-')||(*exp=='+')))
						{
							while ((stack[top-1]!='(')&&((top-1)>=0))
							{
								pop (res);
								res++;
							}
							push (*exp);
						}
					}
		}
		if (*exp=='(')
			push (*exp);
		if (*exp==')')
		{
			while (stack[top-1]!='(')
			{
				pop (res);
				res++;
				
			}
			top=top-1;
		}
	}
	pop (res);
}


void pushs(st *stack, char a)
{
	Item *tmp = (Item *)malloc(sizeof(Item));
	tmp->data = a;

	if (stack->head == NULL)
	{
		tmp->next = NULL;
		stack->head = tmp;
	}
	else
	{
		tmp->next = stack->head;
		stack->head = tmp;
	}
}

int pops(st *stack, char *a)
{
	if (stack->head == NULL)
	{
		return 1;
	}

	char val;
	val = stack->head->data;
	*a = val;
	Item *old_head = stack->head;
	stack->head = old_head->next;

	free(old_head);
	return 0;
}

st* make_empty_stack_ptr() {
    st* stack = (st*)malloc(sizeof(st));
    stack->head = NULL;

    return stack;
}

char stack_top(st* stack) {
	return stack->head->data;
}

int isEmpty(st* stack) {
	return stack->head == NULL;
}

void algs(char *exp, char *res1, int len)
{
	st *stack = make_empty_stack_ptr();

	for (int i = 0; i < len; i++, exp++)
	{
		if (('a' <= *exp) && (*exp <= 'z'))
		{
			*res1 = *exp;
			res1++;
		}

		if ((*exp == '+') || (*exp == '-') || (*exp == '*') || (*exp == '/'))
		{
			if ((isEmpty(stack)) || (stack_top(stack) == '('))
				pushs(stack, *exp);
			else if (((*exp == '*') || (*exp == '/')) && ((stack_top(stack)== '+') || (stack_top(stack) == '-')))
				pushs(stack, *exp);
			else if (((((*exp == '+') || (*exp == '-')) && ((stack_top(stack) == '*') || (stack_top(stack) == '/')))) || ((((*exp == '*') || (*exp == '/')) && ((stack_top(stack) == '*') || (stack_top(stack) == '/')))) || ((((*exp == '+') || (*exp == '-')) && ((stack_top(stack) == '+') || (stack_top(stack) == '-')))))
			{
				if (((*exp == '*') || (*exp == '/')))
				{
					while (((stack_top(stack) != '-') || (stack_top(stack) != '+') || (stack_top(stack) != '(')) && (!isEmpty(stack)))
					{
						pops(stack, res1);
						res1++;
					}
					pushs(stack, *exp);
				}
				if (((*exp == '-') || (*exp == '+')))
				{
					while ((stack_top(stack) != '(') && (!isEmpty(stack)))
					{
						pops(stack, res1);
						res1++;
					}
					pushs(stack, *exp);
				}
			}
		}
		if (*exp == '(')
			pushs(stack, *exp);
		if (*exp == ')')
		{
			while (stack_top(stack) != '(')
			{
				pops(stack, res1);
				res1++;
			}
			Item *head = stack->head;
			stack->head = head->next;
		}
	}
	pops(stack, res1);

}

