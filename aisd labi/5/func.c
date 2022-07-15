#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include "func.h"

void initgraf_zeroes(Graf* gr){
	gr->graf = NULL;
	gr->num_ver = 0;
	gr->num_ed = 0;
}

int dialog(Graf* gr){
	printf("Make your choice: --> \n");
	printf("0 - Quit, 1 - Add, 2 - Find, 3 - Delete, 4 - Show\n");
	int c, n;
	check_int (&c);
	if (c==0)
		return 0;
	else{
		if (c==1){
			printf("What do you want add?\n");
			printf("0 - vertex, 1 - edge\n");
			check_int(&n);
			if (n == 0)
				add_ver(gr);
			if (n == 1)
				add_ed(gr);
		}
		if (c==2){
			printf("What do you want find?\n");
			printf("0 - way, 1 - shortest way\n");
			check_int(&n);
			if (n == 0)
				find_way(gr);
			if (n == 1)
				short_find(gr);
		}
		if (c==3){
			printf("What do you want delete?\n");
			printf("0 - vertex, 1 - edge\n");
			check_int(&n);
			if (n == 0)
				del_ver(gr);
			if (n == 1)
				del_ed(gr);
		}
		if (c==4)
			show(gr);
		/*if (c==5)
			comp(gr);*/
	return 1;
	}
}

int check_int(int *a){
	int n;
	int tmp;
	tmp = scanf("%d", &n);
	while(((int) n!= n)||(tmp <=0 )) {
		printf("%s","You are wrong; repeat, please!\n");
		scanf("%*c");
		tmp = scanf("%d", &n);
	}
	*a=n/1;
	return 0;
}

void add_ver(Graf* gr){
	int n = 1;
	int x, y;
	while (n == 1){
		printf("Enter coordinates\n");
		scanf("%d %d", &x, &y);
		if (find_ver(gr, x, y) != NULL){
			printf("such key already exists, please choose another\n");
			scanf("%*c");
		}
		else
			n = 0;
	}
	Node *new = (Node *)malloc(sizeof(Node));
	new->x = x;
	new->y = y;
	new->next = NULL;
	new->sm = NULL;
	new->num = gr->num_ver;
	if (gr->graf == NULL)
		gr->graf = new;
	else{
		new->next = gr->graf;
		gr->graf = new;
	}
	gr->num_ver++;
}

Node* find_ver(Graf* gr, int x, int y){
	Node *tmp = (Node *)malloc(sizeof(Node));
	tmp = gr->graf;
	while (tmp != NULL){
		if ((tmp->x == x) && (tmp->y == y))
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

void add_ed(Graf* gr){
	int x1, y1, x2, y2;
	int n = 1;
	while (n == 1){
		printf("Enter coordinates of start\n");
		scanf("%d %d", &x1, &y1);
		if (find_ver(gr, x1, y1) == NULL){
			printf("such vertex doesn't exist, please choose another\n");
			scanf("%*c");
		}
		else
			n = 0;
	}
	n = 1;
	while (n == 1){
		printf("Enter coordinates of end\n");
		scanf("%d %d", &x2, &y2);
		if (find_ver(gr, x2, y2) == NULL){
			printf("such vertex doesn't exist, please choose another\n");
			scanf("%*c");
		}
		else
			n = 0;
	}
	double s = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(x1-x2));
	Edge *new = (Edge *)malloc(sizeof(Edge));
	new->weight = s;
	new->par = find_ver(gr, x1, y1);
	new->child = find_ver(gr, x2, y2);
	new->next = NULL;
	Node *tmp = (Node *)malloc(sizeof(Node));
	tmp = gr->graf;
	while (tmp != find_ver(gr, x1, y1))
		tmp = tmp->next;
	Smezh *news = (Smezh *)malloc(sizeof(Smezh));
	news->par = tmp;
	news->next = NULL;
	news->ed = new;
	news->x = x2;
	news->y = y2;
	if (tmp->sm == NULL)
		tmp->sm = news;
	else{
		news->next = tmp->sm;
		tmp->sm = news;
	}
	gr->num_ed++;
}

void find_way(Graf* gr){
	int x1, y1, x2, y2;
	int n = 1;
	while (n == 1){
		printf("Enter coordinates of start\n");
		scanf("%d %d", &x1, &y1);
		if (find_ver(gr, x1, y1) == NULL){
			printf("such vertex doesn't exist, please choose another\n");
			scanf("%*c");
		}
		else
			n = 0;
	}
	n = 1;
	while (n == 1){
		printf("Enter coordinates of end\n");
		scanf("%d %d", &x2, &y2);
		if (find_ver(gr, x2, y2) == NULL){
			printf("such vertex doesn't exist, please choose another\n");
			scanf("%*c");
		}
		else
			n = 0;
	}
	Find m[gr->num_ver];
	Node *tmp = (Node *)malloc(sizeof(Node));
	tmp = gr->graf;
	for (int i = 0; i < gr->num_ver; i++){
		m[gr->num_ver-i-1].colour = 0;
		m[gr->num_ver-i-1].d = 0xffffffff;
		m[gr->num_ver-i-1].pred = 0;
		m[gr->num_ver-i-1].graf = tmp;
		tmp = tmp->next;
	}
	tmp = find_ver(gr, x1, y1);
	m[tmp->num].colour = 1;
	m[tmp->num].d = 0;
	int i = 0, j = 1;
	Find Q[gr->num_ver];
	Q[i] = m[tmp->num]; 
	n = 0;
	Smezh *tmps = (Smezh *)malloc(sizeof(Smezh));
	while ((i < j) && (n == 0)){
		tmps = Q[i].graf->sm;
		while ((tmps != NULL) && (n==0)){
			tmp = find_ver(gr, tmps->x, tmps->y);
			if (m[tmp->num].colour == 0){
				m[tmp->num].colour = 1;
				m[tmp->num].d = Q[i].d + 1;
				m[tmp->num].pred = Q[i].graf;
				Q[j] = m[tmp->num];
				j++;
				if ((tmps->x == x2) && (tmps->y == y2))
					n = 1;
			}
			tmps = tmps->next;
		}
		i++;
	}
	if ((x1 == x2) && (y1 == y2))
		n = 1;
	if (n == 0)
		printf("Sorry, this way doesn't exist\n");
	else{
		Find *t = (Find *)malloc(sizeof(Find));
		t = &m[tmp->num];
		printf("way equal %d: ", t->d);
		printf("(%d, %d)", t->graf->x, t->graf->y);
		while (t->pred != NULL){
			t = &m[t->pred->num];
			printf("<-(%d, %d)", t->graf->x, t->graf->y);
		}
	}
	printf("\n");
}

void short_find(Graf *gr){
	int x1, y1, x2, y2;
	int n = 1;
	while (n == 1){
		printf("Enter coordinates of start\n");
		scanf("%d %d", &x1, &y1);
		if (find_ver(gr, x1, y1) == NULL){
			printf("such vertex doesn't exist, please choose another\n");
			scanf("%*c");
		}
		else
			n = 0;
	}
	n = 1;
	while (n == 1){
		printf("Enter coordinates of end\n");
		scanf("%d %d", &x2, &y2);
		if (find_ver(gr, x2, y2) == NULL){
			printf("such vertex doesn't exist, please choose another\n");
			scanf("%*c");
		}
		else
			n = 0;
	}
	Dec Q[gr->num_ver];
	Node *tmp = (Node *)malloc(sizeof(Node));
	tmp = gr->graf;
	for (int i = 0; i < gr->num_ver; i++){
		Q[gr->num_ver-i-1].d = 0xffffffff;
		Q[gr->num_ver-i-1].pred = NULL;
		Q[gr->num_ver-i-1].graf = tmp;
		tmp = tmp->next;
	}
	tmp = find_ver(gr, x1, y1);
	Dec c;
	c = Q[tmp->num];
	Q[tmp->num] = Q[0];
	Q[0] = c;
	Q[0].d = 0;
	Dec S[gr->num_ver];
	Dec u;
	int j = gr->num_ver - 1;
	int i = 0, k = 0;
	while (j >= 0){
		u = Q[0];
		Q[0] = Q[j];
		j--;
		S[k] = u;
		k++;
		Smezh *tmps = (Smezh *)malloc(sizeof(Smezh));
		tmps = u.graf->sm;
		while (tmps != NULL){
			tmp = find_ver(gr, tmps->x, tmps->y);
			i = 0;
			while (Q[i].graf != tmp)
				i++;
			if (Q[i].d > u.d + tmps->ed->weight){
				Q[i].d = u.d + tmps->ed->weight;
				Q[i].pred = u.graf;
			}
			tmps = tmps->next;
		}
		i = 0; n = 0;
		while ((i*2+1 <= j) && (n == 0)){
			if ((Q[i].d > Q[i*2 + 1].d) || ((Q[i].d > Q[i*2 + 2].d) && (i*2 + 2 <= j))){
				if ((Q[i*2 + 2].d < Q[i*2 + 2].d) && (i*2 + 2 <= j)){
					c = Q[i];
					Q[i] = Q[i*2+2];
					Q[i*2+2] = Q[i];
					i = i*2+2;
				}
				else{
					c = Q[i];
					Q[i] = Q[i*2+1];
					Q[i*2+1] = c;
					i = i*2+1;
				}}
			else
				n = 1;
		}
	}
	double d = 0xffffffff;
	n = 0; j = 0;
	for (i = 0; i < k; i++)
		if ((S[i].d < d) && (S[i].graf->x == x2) && (S[i].graf->y == y2)){
			d = S[i].d;
			j = i;
			n = 1;
		}
	if ( n == 0)
		printf("Sorry, this way doesn't exist\n");
	else{
		Dec *t = (Dec *)malloc(sizeof(Dec));
		t = &S[j];
		printf("way equal %f: ", d);
		printf("(%d, %d)", t->graf->x, t->graf->y);
		while (t->pred != NULL){
			tmp = gr->graf;
			i = 0;
			while (t->pred != S[i].graf)
				i++;
			t = &S[i];
			printf("<-(%d, %d)", t->graf->x, t->graf->y);
		}
	}
	printf("\n");
}

void del_ver(Graf* gr){
	int x, y;
	int n = 1, j = 0;
	while (n == 1){
		printf("Enter coordinates of start\n");
		scanf("%d %d", &x, &y);
		if (find_ver(gr, x, y) == NULL){
			printf("such vertex doesn't exist, please choose another\n");
			scanf("%*c");
		}
		else
			n = 0;
	}
	Node* tmp = (Node *)malloc(sizeof(Node));
	tmp  = gr->graf;
	while ((tmp->x != x) && (tmp->y != y)){
		tmp = tmp->next;
		j++;
	}
	Node *helping = (Node *)malloc(sizeof(Node));
	tmp = gr->graf;
	helping = gr->graf;
        for (int i = 0; i < j; i++)
        {
            helping = tmp;
            tmp = tmp->next;
        }
        if (tmp == gr->graf)
            gr->graf = tmp->next;
        else
            helping->next = tmp->next;
        tmp = gr->graf;
        Smezh *tmps = (Smezh *)malloc(sizeof(Smezh));
        while(tmp != NULL){
        	tmps = tmp->sm;
        		while(tmps != NULL){
        			if ((tmps->x == x) && (tmps->y == y))
        				deled(gr, tmp->x, tmp->y, tmps->x, tmps->y);
        			tmps = tmps->next;
        		}
        	tmp = tmp->next;
        }
        free(tmp);
}

void deled(Graf* gr, int x1, int y1, int x2, int y2){
	int j = 0;
	Node* tmp = (Node *)malloc(sizeof(Node));
	tmp  = gr->graf;
	while ((tmp->x != x1) && (tmp->y != y1))
		tmp = tmp->next;
	Smezh *tmps = (Smezh *)malloc(sizeof(Smezh));
	tmps = tmp->sm;
	while ((tmps->x != x2) && (tmps->y != y2)){
		tmps = tmps->next;
		j++;
	}
	Smezh *helping = (Smezh *)malloc(sizeof(Smezh));
	tmps = tmp->sm;
	helping = tmp->sm;
        for (int i = 0; i < j; i++)
        {
            helping = tmps;
            tmps = tmps->next;
        }
        if (tmps == tmp->sm)
            tmp->sm = tmps->next;
        else
            helping->next = tmps->next;
        free(tmps);
}

void del_ed(Graf* gr){
	int x1, y1, x2, y2;
	int n = 1;
	while (n == 1){
		printf("Enter coordinates of start\n");
		scanf("%d %d", &x1, &y1);
		if (find_ver(gr, x1, y1) == NULL){
			printf("such vertex doesn't exist, please choose another\n");
			scanf("%*c");
		}
		else
			n = 0;
	}
	n = 1;
	while (n == 1){
		printf("Enter coordinates of end\n");
		scanf("%d %d", &x2, &y2);
		if (find_ver(gr, x2, y2) == NULL){
			printf("such vertex doesn't exist, please choose another\n");
			scanf("%*c");
		}
		else
			n = 0;
	}
	n = 0;
	Node* tmp = (Node *)malloc(sizeof(Node));
	tmp  = gr->graf;
	while ((tmp->x != x1) && (tmp->y != y1))
		tmp = tmp->next;
	Smezh *tmps = (Smezh *)malloc(sizeof(Smezh));
	tmps = tmp->sm;
	while (tmps != NULL){
		if((tmps->x == x2) && (tmps->y == y2))
			n = 1;
		tmps = tmps->next;
	}
	if (n == 0)
		printf("such edge doesn't exist, please choose another\n");
	else
		deled(gr, x1, y1, x2, y2); 	
}

void show(Graf* gr){
	printf ("vertex, adjacent vertices\n");
	Node* tmp = (Node *)malloc(sizeof(Node));
	tmp  = gr->graf;
	Smezh* tmps = (Smezh *)malloc(sizeof(Smezh));
	while (tmp != NULL){
		printf("(%d, %d)", tmp->x, tmp->y);
		tmps = tmp->sm;
		if (tmps != NULL)
			printf("->");
		while (tmps != NULL){
			printf("(%d, %d)", tmps->x, tmps->y);
			tmps = tmps->next;
		}
		printf("\n");
		tmp = tmp->next;
	}
}
