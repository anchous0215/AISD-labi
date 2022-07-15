typedef struct Item {
	char* info;	// указатель на информацию
	char* key1;	// ключ элемента из 1­го пространства ключей
	int key2;	// ключ элемента из 2­го пространства ключей
	struct KeySpace2 *ks2;
} Item;

typedef struct KeySpace1 {
	char* key1;	// ключ элемента
	int release;	// номер версии элемента
	Item *info;	// указатель на информацию
	struct KeySpace1 *next;	// указатель на следующий элемент
} KeySpace1;

typedef struct KeySpace2 {
	int key2;	// ключ элемента
	int release;	// номер версии элемента
	Item* info;	// указатель на информацию
	struct KeySpace2 *next;	// указатель на следующий элемент
} KeySpace2;

typedef struct Table {
	KeySpace1 *ks1;	// указатель на первое пространство ключей
	KeySpace2 *ks2[MSIZE2];	// указатель на второе пространство ключей
	int msize2;	// размер области второго пространства 
} Table;



void initTable_zeroes (Table* tab);
int dialog (Table* tab);
void add (Table *table);
void insert1 (Table* tab, char* key);
int search_release1 (Table* tab, char* key);
int check_int (int *a);
int hash (int key);
void insert2 (Table *tab, int key);
int search_release2 (Table* tab, int key);
int search_fullkey (Table* tab, char* key1, int key2);
void insert_item (Table* tab, char* info, char* key1, int key2);
void find_item_fullkey (Table* tab);
void find_item_key1 (Table* tab);
void find_item_key2 (Table* tab);
void find_key1_release (Table* tab);
void find_key2_release (Table* tab);
void delete_fullkey (Table* tab);
void init_ks2_zeroes(Table* tab, int i);
void init_ks1_zeroes(Table* tab);
void show_table(Table* tab);
void del_key2(Table* tab, int n, int k);
void del_key1(Table* tab, int n);
void delete_key1 (Table *tab);
void del_key1_rel(Table* tab);
void delete_key2 (Table *tab);
void table_cleaning (Table* tab);
