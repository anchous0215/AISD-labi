#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "func.h"
#define MSIZE2 10

void initTable_zeroes(Table* tab) {
	tab->ks1 = NULL;
	for (int i = 0; i < MSIZE2; i++)
	tab->ks2[i] = NULL;
}

void init_ks2_zeroes(Table* tab, int i) {
	tab->ks2[i] = (KeySpace2*)malloc(sizeof(KeySpace2));
	tab->ks2[i]->release = 0;
	tab->ks2[i]->info = NULL;		
	tab->ks2[i]->next = NULL;
}

void init_ks1_zeroes(Table* tab) {
	tab->ks1 = (KeySpace1*)malloc(sizeof(KeySpace1));
	tab->ks1->release = 0;
	tab->ks1->info = NULL;		
	tab->ks1->next = NULL;
}

void fileInput(Table* tab, FILE* f){
	char* key1 = (char*)malloc(10);
	char* inf = (char*)malloc(10);
	int key2;
	long int info;
	int k, l;
	long int s;
	fseek (f, 0, SEEK_END);
	s = ftell(f);
	fseek (f, 0, SEEK_SET);
	while (ftell(f)+1 < s)
	{
		fscanf (f, "%s%d", key1, &key2);
		insert1 (tab, key1);
		k = hash (key2);
		insert2 (tab, key2);
		info = ftell (f) + 1;
		fscanf (f, "%s", inf);
		l = strlen (inf);
		insert_item (tab, info, key1, key2, l);
		printf ("%ld\n", info);
		
	printf ("tut %ld\n", ftell(f));
	}
	fseek (f, 0, SEEK_END);
	printf ("%ld", ftell(f));
	fclose(f);
}


int dialog(Table* tab, FILE* f){
	printf("Make your choice: --> \n");
	printf("0 - Quit, 1 - Add, 2 - Find, 3 - Delete, 4 - Show\n");
	int c, n;
	check_int (&c);
	if (c==0)
		return 0;
	else{
		if (c==1)
			add(tab, f);
		if (c==2){
			printf("What do you want find?\n");
			printf("0 - fullkey, 1- key1, 2 - key2, 3 - key1(realise), 4 - key2(realise)\n");
			check_int (&n);
			if (n==0)
				find_item_fullkey(tab, f);
			if (n==1)
				find_item_key1(tab, f);
			if (n==2)
				find_item_key2(tab, f);
			if (n==3)
				find_key1_release(tab, f);
			if (n==4)
				find_key2_release(tab, f);
		}
		if (c==3){
			printf("What do you want delete?\n");
			printf("0 - fullkey, 1- key1, 2 - key2, 3 - key1(realise), 4 - table cleaning\n");
			check_int (&n);
			if (n==0)
				delete_fullkey(tab);
			if (n==1)
				delete_key1(tab);
			if (n==2)
				delete_key2(tab);
			if (n==3)
				del_key1_rel(tab);
			if (n==4)
				table_cleaning (tab);
		}
		if (c==4)
			show_table(tab, f);
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





void add(Table* tab, FILE* f){
	int key2;
	char* key1 = (char*)malloc(10);
	char* inf = (char*)malloc(10);
	long int info;
	int l, lk;
	int n = 1;
	while (n == 1){
		printf ("Enter key 1(str)\n");
		scanf ("%s", key1);
		printf ("Enter key 2(number)\n");
		check_int(&key2);
	 	if (search_fullkey(tab, key1, key2) == 1){
			printf ("such a composite key already exists, please choose another\n");
			scanf("%*c");
		}
		else
			n = 0;
	}
	n = 1;
	insert1 (tab, key1);
	insert2 (tab, key2);
	printf ("Enter info for item\n");
	scanf ("%s", inf);
	f = fopen("tab","r+");
	fseek (f, 0, SEEK_END);
	l = strlen(inf);
	lk = strlen(key1);
	printf ("num%d\n", lk);
	fprintf(f, "%s ", key1);
	fprintf(f, "%d", key2);
	info = ftell (f);
	fprintf (f, " %s\n", inf);
	insert_item (tab, info, key1, key2, l);
	fclose (f);
}

void insert1(Table *tab, char* key){
	int i = search_release1(tab, key);
	KeySpace1 *tmp = (KeySpace1 *)malloc(sizeof(KeySpace1));
	 tmp->key1 = (char*)malloc(10*sizeof(char));
	strcpy (tmp->key1, key);
	tmp->release = i++;			
	if (tab->ks1 == NULL){
		init_ks1_zeroes(tab);
		tmp->next = NULL;
		tab->ks1 = tmp;
	}
	else{		
		tmp->next = tab->ks1;
		tab->ks1 = tmp;
	}
}

int search_release1(Table* tab, char* key){
	int i = 0;
	if (tab->ks1 != NULL){
		KeySpace1 *tmp = (KeySpace1 *)malloc(sizeof(KeySpace1));
		tmp = tab->ks1;
		while (tmp != NULL){
			if (strcmp(tmp->key1,key) == 0)
				i++;
			tmp = tmp->next; 
		}
	}
	return i;
}

void insert2(Table *tab, int key){
	int i = search_release2(tab, key);
	int k = hash(key);
	KeySpace2 *tmp = (KeySpace2 *)malloc(sizeof(KeySpace2));
	tmp->key2 = key;
	tmp->release = i++;			
	if (tab->ks2[k] == NULL){
		init_ks2_zeroes(tab, k);
		tmp->next = NULL;
		tab->ks2[k] = tmp;
	}
	else{		
		tmp->next = tab->ks2[k];
		tab->ks2[k] = tmp;
	}
}


int search_release2(Table* tab, int key){
	int i = 0;
	int k = hash(key);
	if (tab->ks2[k] != NULL){	
			KeySpace2 *tmp = (KeySpace2 *)malloc(sizeof(KeySpace2));
			tmp = tab->ks2[k];
			while (tmp != NULL){
				if (tmp->key2 == key)
					i++;
				tmp = tmp->next;
			}
	}	
	return i;
}
	
int hash(int key) {
	int n = key % MSIZE2;
	return n;
}

int search_fullkey (Table* tab, char* key1, int key2){
	if (tab->ks1 != NULL){
		KeySpace1 *tmp = (KeySpace1 *)malloc(sizeof(KeySpace1));
		tmp = tab->ks1;
		while (tmp != NULL){
			if (strcmp(tmp->key1,key1) == 0)
				if (tmp->info->key2 == key2)
					return 1;
			tmp = tmp->next; 
		}
	}
	return 0;
}

void insert_item(Table* tab, long int inf, char* key1, int key2, int leng){
	Item *tmp = (Item *)malloc(sizeof(Item));
	tmp->info = inf;
	tmp->key1 = tab->ks1->key1;
	tmp->leng = leng;
	int k = hash (key2);
	tmp->key2 = tab->ks2[k]->key2;
	tmp->ks2 = tab->ks2[k];
	tab->ks2[k]->info = tmp;
	tab->ks1->info = tmp;
}

void show_table(Table* tab, FILE* f){
	printf("{key1(release), key2(release), info}\n");
	int i1, i2, k, l;
	char* inf = (char*)malloc(10);
	KeySpace1 *tmp1 = (KeySpace1 *)malloc(sizeof(KeySpace1));
	tmp1 = tab->ks1;
	f = fopen("tab","r");
	while (tmp1 != NULL){
		i1 = tmp1->release+1;
		k = hash(tmp1->info->key2);
		KeySpace2 *tmp2 = (KeySpace2 *)malloc(sizeof(KeySpace2));
		tmp2 = tab->ks2[k];
		while (tmp1->info->info != tmp2->info->info)
			tmp2 = tmp2->next;
		i2 = tmp2->release+1;
		fseek (f, tmp1->info->info, SEEK_SET);
		fscanf (f, "%s", inf);
		printf ("%s(%d), %d(%d), %s\n", tmp1->key1, i1, tmp2->key2, i2, inf);
		tmp1 = tmp1->next;
	}
}

void find_item_fullkey (Table* tab, FILE* f){
	int n =0;
	int key2;
	char* key1 = (char*)malloc(10);
	char* inf = (char*)malloc(10);
	while (n==0){
		printf ("Enter key 1(str)\n");
		scanf ("%s", key1);
		printf ("Enter key 2(number)\n");
		check_int(&key2);
		KeySpace1 *tmp = (KeySpace1 *)malloc(sizeof(KeySpace1));
		tmp = tab->ks1;
		f = fopen("tab","r");
		while (tmp != NULL){
			if (strcmp(tmp->key1,key1) == 0){
				if (tmp->info->key2 == key2){
					fseek (f, tmp->info->info, SEEK_SET);
					fscanf (f, "%s", inf);
					printf("%s\n", inf);
					n++;
				}
			}
			tmp = tmp->next; 
		}
		if (n==0)
			printf ("Sorry, this key wasn't foud, please try again\n");
	}
}

void find_item_key1 (Table* tab, FILE* f){
	int n = 0; int l;
	char* key1 = (char*)malloc(10);
	char* inf = (char*)malloc(10);
	while (n==0){
		printf ("Enter key 1(str)\n");
		scanf ("%s", key1);
		KeySpace1 *tmp = (KeySpace1 *)malloc(sizeof(KeySpace1));
		tmp = tab->ks1;
		f = fopen("tab","r");
		while (tmp != NULL){
			if (strcmp(tmp->key1,key1) == 0){
				fseek (f, tmp->info->info, SEEK_SET);
				fscanf (f, "%s", inf);
				printf ("%s(%d) {%s}\n", tmp->key1, tmp->release, inf);
				n++;
			}
			tmp = tmp->next; 
		}
		if (n==0)
			printf ("Sorry, this key wasn't foud, please try again\n");
	}
}
	
void find_item_key2 (Table* tab, FILE* f){
	int n = 0;
	int key2;
	char* inf = (char*)malloc(10);
	while (n==0){
		printf ("Enter key 2(number)\n");
		check_int(&key2);
		int k = hash(key2);
		KeySpace2 *tmp = (KeySpace2 *)malloc(sizeof(KeySpace2));
		tmp = tab->ks2[k];
		f = fopen("tab","r");
		while (tmp != NULL){
			if (tmp->key2 == key2){
				fseek (f, tmp->info->info, SEEK_SET);
				fscanf (f, "%s", inf);
				printf ("%d(%d) {%s}\n", tmp->key2, tmp->release, inf);
				n++;
			}
			tmp = tmp->next; 
		}
		if (n==0)
			printf ("Sorry, this key wasn't foud, please try again\n");
	}
}

void find_key1_release (Table* tab, FILE* f){
	int n = 0;
	char* key1 = (char*)malloc(10);
	char* inf = (char*)malloc(10);
	int i;
	while (n==0){
		printf ("Enter key1(str)\n");
		scanf ("%s", key1);
		printf ("Enter number of release\n");
		check_int(&i);
		KeySpace1 *tmp = (KeySpace1 *)malloc(sizeof(KeySpace1));
		tmp = tab->ks1;
		f = fopen("tab","r");
		while (tmp != NULL){
			if ((strcmp(tmp->key1,key1) == 0) && (tmp->release == i)){
				fseek (f, tmp->info->info, SEEK_SET);
				fscanf (f, "%s", inf);
				printf ("%s(%d) {%s}\n", tmp->key1, tmp->release, inf);
				n++;
			}
			tmp = tmp->next;
		}
	}
}

void find_key2_release (Table* tab, FILE* f){
	int n = 0;
	int key2;
	int i;
	char* inf = (char*)malloc(10);
	while (n==0){
		printf ("Enter key2(number)\n");
		check_int(&key2);
		printf ("Enter number of release\n");
		check_int(&i);
		int k = hash(key2);
		KeySpace2 *tmp = (KeySpace2 *)malloc(sizeof(KeySpace2));
		tmp = tab->ks2[k];
		f = fopen("tab","r");
		while (tmp != NULL){
			if ((tmp->key2 == key2) && (tmp->release == i)){
				fseek (f, tmp->info->info, SEEK_SET);
				fscanf (f, "%s", inf);
				printf ("%d(%d) {%s}\n", tmp->key2, tmp->release, inf);
				n++;
			}
			tmp = tmp->next; 
		}
		if (n==0)
			printf ("Sorry, this key wasn't foud, please try again\n");
	}
}

void delete_fullkey (Table* tab){
	int i = 0, j = 0;
	int n = 0;
	int key2;
	char* key1 = (char*)malloc(10);
	while (n==0){
		printf ("Enter key 1(str)\n");
		scanf ("%s", key1);
		printf ("Enter key 2(number)\n");
		check_int(&key2);
		if ((search_release2(tab, key2) == 0) && (search_release1(tab, key1) == 0))
			n = 0;
		else{
			KeySpace1 *tmp1 = (KeySpace1 *)malloc(sizeof(KeySpace1));
			tmp1 = tab->ks1;
			while (strcmp(tmp1->key1,key1) != 0){
				tmp1 = tmp1->next;
				i++;
			}
			int k = hash(key2);
			KeySpace2 *tmp2 = (KeySpace2 *)malloc(sizeof(KeySpace2));
			tmp2 = tab->ks2[k];
			while (tmp2->key2 != key2){
				tmp2 = tmp2->next;
				j++;
			}
			del_key1 (tab, i);
			del_key2 (tab, j, k);
			n++;
		}	
		if (n==0)
			printf ("Sorry, this key wasn't foud, please try again\n");			
	}
}

void del_key1(Table* tab, int n) // n - позиция удаляемого элемента
{
        // Mass - объекты, которые хранятся в списке
	KeySpace1 *temp = (KeySpace1 *)malloc(sizeof(KeySpace1));
	KeySpace1 *helping = (KeySpace1 *)malloc(sizeof(KeySpace1));
	temp = tab->ks1;
	helping = tab->ks1;
        for (int i = 0; i < n; i++)
        {
            helping = temp; // предыдущее значение temp
            temp = temp->next;
        }

        if (temp == tab->ks1) // если элемент который надо удалить первый
        {
            tab->ks1 = temp->next;
        }
        else
        {
            helping->next = temp->next;
        }
        free(temp);// уменьшаем размер списка
}

void del_key2(Table* tab, int n, int k) // n - позиция удаляемого элемента
{
        // Mass - объекты, которые хранятся в списке
	KeySpace2 *temp = (KeySpace2 *)malloc(sizeof(KeySpace2));
	KeySpace2 *helping = (KeySpace2 *)malloc(sizeof(KeySpace2));
	temp = tab->ks2[k];
	helping = tab->ks2[k];
        for (int i = 0; i < n; i++)
        {
            helping = temp; // предыдущее значение temp
            temp = temp->next;
        }

        if (temp == tab->ks2[k]) // если элемент который надо удалить первый
        {
            tab->ks2[k] = temp->next;
        }
        else
        {
            helping->next = temp->next;
        }
        free(temp);// уменьшаем размер списка
}

void delete_key1 (Table *tab){
	int i = 0, j = 0;
	int n = 0, c;
	char* key1 = (char*)malloc(10);
	while (n==0){
		printf ("Enter key1 (str)\n");
		scanf ("%s", key1);
		if (search_release1(tab, key1) == 0)
			n = 0;
		else{	
			KeySpace1 *tmp1 = (KeySpace1 *)malloc(sizeof(KeySpace1));
			tmp1 = tab->ks1;
			while (tmp1 != NULL){
				if (strcmp(tmp1->key1,key1) == 0){
					int k = hash(tmp1->info->key2);
					KeySpace2 *tmp2 = (KeySpace2 *)malloc(sizeof(KeySpace2));
					tmp2 = tab->ks2[k];
					c = 0;
					while ((tmp2 != NULL)&&(c == 0)){
						if (tmp1->info->info == tmp2->info->info){
							del_key1 (tab, i);
							del_key2 (tab, j, k);
							n++;
							c++;
							i--;
							j--;
						}
						tmp2 = tmp2->next;
						j++;
					}
				}
				tmp1 = tmp1->next;
				i++;
			}
		}
		if (n==0)
			printf ("Sorry, this key wasn't foud, please try again\n");
		
	}
}

void delete_key2 (Table *tab){
	int i = 0, j = 0;
	int n = 0, c;
	int key2;
	while (n==0){
		printf ("Enter key2 (str)\n");
		check_int(&key2);
		if (search_release2(tab, key2) == 0)
			n = 0;
		int k = hash(key2);
		KeySpace2 *tmp2 = (KeySpace2 *)malloc(sizeof(KeySpace2));
		tmp2 = tab->ks2[k];
		while (tmp2 != NULL){
			if (tmp2->key2 == key2){
				KeySpace1 *tmp1 = (KeySpace1 *)malloc(sizeof(KeySpace1));
				tmp1 = tab->ks1;
				c = 0;
				while ((tmp1 != NULL)&&(c == 0)){
						if (tmp1->info->info == tmp2->info->info){
							del_key1 (tab, i);
							del_key2 (tab, j, k);
							n++;
							c++;
							i--;
							j--;
						}
					tmp1 = tmp1->next;
						i++;
				}
				tmp2 = tmp2->next;
				j++;
			}
		}
		if (n==0)
			printf ("Sorry, this key wasn't foud, please try again\n");
		
	}
}

void del_key1_rel(Table* tab){
	int i = 0, j = 0;
	int n = 0, rel;
	char* key1 = (char*)malloc(10);
	while (n==0){
		printf ("Enter key 1(str)\n");
		scanf ("%s", key1);
		printf ( "Enter number of release");
		check_int(&rel);
		KeySpace1 *tmp1 = (KeySpace1 *)malloc(sizeof(KeySpace1));
		tmp1 = tab->ks1;
		while (((strcmp(tmp1->key1,key1) != 0) || (tmp1->release != rel)) && (tmp1 != NULL)){
			tmp1 = tmp1->next;
			i++;
		}
		int k = hash(tmp1->info->key2);
		KeySpace2 *tmp2 = (KeySpace2 *)malloc(sizeof(KeySpace2));
		tmp2 = tab->ks2[k];
		while (tmp1->info->info == tmp2->info->info){
			tmp2 = tmp2->next;
			j++;
		}
		del_key1 (tab, i);
		del_key2 (tab, j, k);
		n++;
		if (n==0)
			printf ("Sorry, this key wasn't foud, please try again\n");
	}
}

void table_cleaning (Table* tab){
	int j = 1;
	for (int k = 0; k<MSIZE2; k++){
		KeySpace2 *tmp2 = (KeySpace2 *)malloc(sizeof(KeySpace2));
		tmp2 = tab->ks2[k];
		while (tmp2 != NULL){
			KeySpace2 *tmp22 = (KeySpace2 *)malloc(sizeof(KeySpace2));
			tmp22 = tab->ks2[k]->next;
			while (tmp22 != NULL){
				if (tmp2->key2 == tmp22->key2){
					int i = 1;
					KeySpace1 *tmp1 = (KeySpace1 *)malloc(sizeof(KeySpace1));
					tmp1 = tab->ks1->next;
					int c = 0;
					while ((tmp1 != NULL)&&(c == 0)){
						if (tmp1->info->info == tmp22->info->info){
							del_key1 (tab, i);
							del_key2 (tab, j, k);
							i--;
							j--;
							c++;
						}
						if (tmp1 != NULL){
						tmp1 = tmp1->next;
							i++;
						}
					}
				if (tmp22 != NULL){
					tmp22 = tmp22->next;
					j++;
				}
				}
			}
			if (tmp2 != NULL)
			tmp2 = tmp2->next;
		}
	}
}

void show_tab (Table* tab, FILE* p, FILE* f){
	int i1, i2, k, l;
	char* inf = (char*)malloc(10);
	KeySpace1 *tmp1 = (KeySpace1 *)malloc(sizeof(KeySpace1));
	tmp1 = tab->ks1;
	f = fopen("tab","rb");
	while (tmp1 != NULL){
		i1 = tmp1->release+1;
		k = hash(tmp1->info->key2);
		KeySpace2 *tmp2 = (KeySpace2 *)malloc(sizeof(KeySpace2));
		tmp2 = tab->ks2[k];
		while (tmp1->info->info != tmp2->info->info)
			tmp2 = tmp2->next;
		i2 = tmp2->release+1;
		fseek (f, tmp1->info->info, SEEK_SET);
		fscanf (f, "%s", inf);
		fprintf (p, "%s(%d), %d(%d), %s\n", tmp1->key1, i1, tmp2->key2, i2, inf);
		tmp1 = tmp1->next;
	}
}
