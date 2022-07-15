#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include "func.h"

void inittree_zeroes(Node** tr){
	(*tr)->info = NULL;
	(*tr)->key = 0;
	(*tr)->release = 0;
	(*tr)->colour = 0;
	(*tr)->left = NULL;
	(*tr)->right = NULL;
	(*tr)->par = NULL;
}

void fileInput(Node** tr, FILE* f){
	char* info = (char*)malloc(10);
	int key;
	long int s;
	fseek (f, 0, SEEK_END);
	s = ftell(f);
	fseek (f, 0, SEEK_SET);
	while (ftell(f)+1 < s){
		fscanf (f, "%d%s", &key, info);
		insert_item (tr, info, key);
	}
	fclose(f);
}

void insert_item (Node** tr, char* info, int key){
	Node *x = (Node *)malloc(sizeof(Node));
	x->info = (char *) calloc(1, strlen(info));
	x->key = key;
	strcpy(x->info, info);
	Node *l = (Node *)malloc(sizeof(Node));
	l = &Elist;
	x->left = l;
	x->right = l;
	x->release = release (*tr, key);
	x->colour = 1;
	if ((*tr)->info == NULL){
		(*tr)->info = (char *) calloc(1, strlen(info));
		(*tr)->key = key;
		strcpy((*tr)->info, info);
		(*tr)->release = 1;
		(*tr)->left = l;
		(*tr)->right = l;
		(*tr)->par = l;
		(*tr)->colour = 0;
	}
	else{
		Node *tmp = (Node *)malloc(sizeof(Node));
		Node *par = (Node *)malloc(sizeof(Node));
		tmp = *tr;
		par = NULL;
		while (tmp != l){
			par = tmp;
			if (key < tmp->key)
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}
		x->par = par;
		if (key < par->key)
			par->left = x;
		else
			par->right = x;
	}
	rb_insert_fixup(x, tr);
}

int release (Node* tr, int key){
	int n = 1;
	Node *tmp = (Node *)malloc(sizeof(Node));
	tmp = tr;
	while (tmp != NULL){
		if (tmp->key == key)
			n++;
		if (tmp->key > key)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return n;
}

void rb_insert_fixup (Node *x, Node **tr){
	Node *p1, *pp, *p2;
	if (x->par != NULL)
		while(x->par->colour == 1){
			p1 = x->par; 
			pp = p1->par;
			if (p1 == pp->left){
				p2 = pp->right;
				if (p2->colour == 1){
					p1->colour = 0;
					p2->colour = 0;
					pp->colour = 1;
					x = pp;
				}
				else if(x == p1->right){
					left_rotate(p1, tr);
					x = p1;
					p1 = x->par;
				}
			    	else{
					p1->colour = 0;
					pp->colour = 1;
					right_rotate(pp, tr);
			    	}
			} 
			else{
			    	p2 = pp->left;
				if (p2->colour == 1){
					p1->colour = 0;
					p2->colour = 0;
					pp->colour = 1;
					x = pp;
			    	}
			   	else if(x == p1->left){
					right_rotate(p1, tr);
					x = p1;
					p1 = x->par;
			    	}
				else{
					p1->colour = 0;
					pp->colour = 1;
					left_rotate(pp, tr);
			    	}
			}
		}
	(*tr)->colour = 0;
}

void left_rotate(Node *x, Node **tr){
	Node *l = (Node *)malloc(sizeof(Node));
	l = &Elist;
	Node *y = (Node *)malloc(sizeof(Node));
	y = x->right; 
	Node *par = (Node *)malloc(sizeof(Node));
	par = x->par;
	x->right = y->left;
	if(y->left != l)
        	y->left->par = x;
	y->par = par;
	if(par == l)
        	*tr = y;
	else{
		if(par->left == x)
			par->left = y;
		else
			par->right = y;
	}
	y->left = x;
	x->par = y;
}

void right_rotate(Node *x, Node **tr){
	Node *l = (Node *)malloc(sizeof(Node));
	l = &Elist;
	Node *y = (Node *)malloc(sizeof(Node));
	y = x->left;
	Node *par = (Node *)malloc(sizeof(Node));
	par = x->par;
	x->left = y->right;
	if(y->right != l)
        	y->right->par = x;
	y->par = par;
	if(par == l)
        	*tr = y;
	else{
		if(par->left == x)
			par->left = y;
		else
			par->right = y;
	}
	y->right = x;
	x->par = y;
}

int dialog(Node** tr, FILE* f){
	printf("Make your choice: --> \n");
	printf("0 - Quit, 1 - Add, 2 - Find, 3 - Delete, 4 - Show, 5 - timing\n");
	int c, n;
	check_int (&c);
	if (c==0)
		return 0;
	else{
		if (c==1)
			add(tr);
		if (c==2){
			printf("What do you want find?\n");
			printf("0 - info, 1 - min key\n");
			check_int(&n);
			if (n == 0)
				find_item (*tr);
			if (n == 1)
				find_min (*tr);
		}
		if (c==3)
			delete(tr);
		if (c==4)
			show (tr);
		if (c==5)
			timing (tr);
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

void add(Node** tr){
	int n = 1;
	int key;
	char* info = (char*)malloc(10);
	printf ("Enter key\n");
	scanf ("%d", &key);
	printf ("Enter info for item\n");
	scanf ("%s", info);
	insert_item (tr, info, key);
}

void find_item (Node* tr){
	int n = 0;
	int key;
	while (n == 0){
		printf ("Enter key (number)\n");
		check_int(&key);
		Node *tmp = (Node *)malloc(sizeof(Node));
		tmp = tr;
		while (tmp != NULL){
			if (tmp->key == key){
				printf ("%d(%d) %s\n", tmp->key, tmp->release, tmp->info);
				n = 1;
			}
			if (tmp->key > key)
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}
		if  (n == 0)
			printf ("such key don't found, please choose another\n");
	}
}

void find_min (Node* tr){
	int n = 0;
	int key;
	int k;
	Node *tmp = (Node *)malloc(sizeof(Node));
	while (n == 0){
		printf ("Enter key (number)\n");
		check_int(&key);
		tmp = tr;
		while (tmp != NULL){
			if ((tmp->key <= key) && (tmp->info != NULL)){
				k = tmp->key;
				n = 1;
				break;
			}
			if (tmp->key > key)
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}
		if  (n == 0)
			printf ("such key don't found, please choose another\n");
	}
		while (tmp != NULL){
			if ((tmp->key > k)&&(tmp->key <= key))
				k = tmp->key;
			if (tmp->key >= key)
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}
		tmp = tr;
		while (tmp != NULL){
			if (tmp->key == k)
				printf ("%d(%d) %s\n", tmp->key, tmp->release, tmp->info);
			if (tmp->key > key)
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}
}

void delete(Node **tr){
	int n = 0;
	int key;
	int v = 1;
	Node *tmp = (Node *)malloc(sizeof(Node));
	while (n == 0){
		printf ("Enter key (number)\n");
		check_int(&key);
		tmp = *tr;
		while (tmp != NULL){
			if (tmp->key == key){
				n = 1;
				break;
			}
			if (tmp->key > key)
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}
		if  (n == 0)
			printf ("such key don't found, please choose another\n");
	}
	int r = release(*tr, key) - 1;
	n = 0;
	if (r != 1)
		while (n == 0){
			printf ("Wich release of key do you want delete?\n");
			check_int(&v);
			tmp = *tr;
			if (v <= r){
				n = 1;
				break;
			}
			if  (n == 0)
				printf ("such release don't found, please choose another\n");
		}
	Node *delete = *tr;
	printf ("%d\n", key);
	printf ("%d\n", delete->key);
	while (delete != NULL){
		if ((delete->key == key) && (delete->release == v))
			break;
        	if (key < delete->key)
            		delete = delete->left;
        	else
            		delete = delete->right;
        }
        printf ("%s\n", delete->info);
	Node *par;
   	Node *next;
    	int colour, lf;
	par = delete->par;
        if((delete->left == &Elist) && (delete->right == &Elist)){
            	if(par != &Elist){
			if (par->left == delete){
		            	par->left = &Elist;
		            	Elist.par = par;
                	} 
                	else if (par->right == delete){
		            	par->right = &Elist;
		            	Elist.par = par;
                	}
            	}
		colour = delete->colour;
            	delete->par = NULL;
           	free(delete);
            	if(colour == 0 && (par->right != &Elist || par->left != &Elist))
                	rb_delete_fixup(&Elist, tr);
            	if(par == &Elist)
                	*tr = NULL;
        }
        else if(delete->left == &Elist || delete->right == &Elist){
		if(delete->left == &Elist){
			if(par != &Elist) {
                    		if (par->left == delete) {
				        par->left = delete->right;
				        delete->right->par = par;
				        lf = 0;
                    		}
		            	else if (par->right == delete) {
					par->right = delete->right;
		                	delete->right->par = par;
		                	lf = 1;
                    		}
                	}
		        else{
		            	*tr = delete->right;
		            	delete->right->par = NULL;
		        }
            	}
            	else{
			if(par != &Elist){
                    		if (par->left == delete){
				        par->left = delete->left;
				        delete->left->par = par;
				        lf = 0;
                    	} 
		            	else if (par->right == delete) {
					par->right = delete->left;
		                	delete->left->par = par;
		                	lf = 1;
		            	}
                	}
		        else{
		            	*tr = delete->left;
		            	delete->left->par = NULL;
		        }
            	}
            	colour = delete->colour;
            	free(delete);
            	if(colour == 0){
			if (lf == 0)
                    		rb_delete_fixup(par->left, tr);
                	else
                    		rb_delete_fixup(par->right, tr);
            	}
        }
        else{
		next = search_nearest_next(*tr, key);
            	//delete->key = next->key;
            	if(next->par->left == next)
			next->par->left = next->right;
            	else
			next->par->right = next->right;
            	next->right->par = next->par;
		colour = next->colour;
            	par = next->right;
            	next->par = NULL;
            	free(next);
            	if(colour == 0)
                	rb_delete_fixup(par, tr);
        }
        printf("Element deleted\n");
}

void rb_delete_fixup(Node *x, Node **tr){
    	Node *p, *w;
    	while((x != *tr) && (x->colour == 0)){
		p = x->par;
		if(x == p->left){
            		w = p->right;
            		if(w->colour == 1){
                		w->colour = 0;
                		p->colour = 1;
                		left_rotate(p,tr);
                		w = p->right;
            		}
            		if((w->left->colour == 0) && (w->right->colour == 0)){
                		w->colour = 1;
                		x = p;
            		}
			else{
				if(w->right->colour == 0){
		            		w->colour = 1;
		            		w->left->colour = 0;
		            		right_rotate(w, tr);
		            		w = p->right;
		        	}
		        	else{
		            		w->colour = p->colour;
		            		p->colour = 0;
		            		w->right->colour = 0;
		            		left_rotate(p, tr);
		            		x = *tr;
		        	}
			}
        	}
        	else{
            		w = p->left;
            		if(w->colour == 1){
                		w->colour = 0;
				p->colour = 1;
				right_rotate(p, tr);
				w = p->left;
            		}
            		if((w->left->colour == 0) && (w->right->colour == 0)){
				w->colour = 1;
				x = p;
            		}
			else{
                		if(w->left->colour == 1){
                    			w->colour = 1;
                    			w->right->colour = 0;
                    			left_rotate(w, tr);
                    			w = p->left;
                		}
                		else{
                    			w->colour = p->colour;
                    			p->colour = 0;
                    			w->left->colour = 0;
                    			right_rotate(p, tr);
                    			x = *tr;
                		}
			}
        	}
	}
    	x->colour = 0;
}

Node * search_nearest_next (Node *tr, int key){
    	Node *ptr = tr, *next = NULL;
    	while(ptr != &Elist){
		if(key < ptr->key){
            		next = ptr;
            		ptr = ptr->left;
        	}
        	else{
            		ptr = ptr->right;
        	}
    	}
    	return next;
}

void show (Node** tr){
	Node *tmp = (Node *)malloc(sizeof(Node));
	tmp = *tr;
	int n = 0;
	showtree(tmp, n);
}

void showtree (Node* tmp, int n){
	int i = 0, k = 0;
	if (tmp == &Elist)
		return;
	if (tmp->right != &Elist){
		tmp = tmp->right;
		n++;
		showtree (tmp, n);
		k = 1;
	}
	if (k == 1){
		tmp = tmp->par;
		n--;
	}
	for (i = 0; i<n; i++)
		printf("     ");
	printf("%d, %d\n", tmp->key, tmp->colour);
	if (tmp->left != &Elist){
		tmp = tmp->left;
		n++;
		showtree (tmp, n);
	}
}	

int timing(Node ** tr){
	Node *tree = *tr;
	int n = 10, key[10000], k, cnt = 1000000, i, m;
	clock_t first, last;
	srand(time(NULL));
	while (n-- > 0){
		for (i = 0; i < 10000; ++i)
			key[i] = rand() * rand();
		for (i = 0; i < cnt; ){
			k = rand() * rand();
			insert_item(&tree, " ", k);
			i++;
		}
		m = 0;
		first = clock();
		for (i = 0; i < 10000; ++i)
			if (find_key(tree, key[i]))
				++m;
		last = clock();
		printf("%d items was found\n", m);
		printf("test #%d, number of nodes = %d, time = %2ld\n", 10 - n, (10 -n)*cnt, last - first);
	}
	return 1;
}

int find_key (Node* tr, int key){
	Node *tmp = (Node *)malloc(sizeof(Node));
	tmp = tr;
	while (tmp->info != NULL){
		if (tmp->key == key)
			return 1;
		else{
			if (tmp->key > key){
				if (tmp->left != NULL)
					tmp = tmp->left;
				else
					return 0;
			}
			else{
				if (tmp->right != NULL)
					tmp = tmp->right;
				else
					return 0;
			}
		}
	}
	return 0;
}
