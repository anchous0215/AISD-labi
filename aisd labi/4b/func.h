typedef struct Node {
	int key;
	int release;
	int colour;
	char* info;
	struct Node *left;
	struct Node *right;
	struct Node *par;
} Node;

Node Elist = {0, 0, 0, NULL, NULL, NULL, NULL};

void inittree_zeroes (Node** tree);
void fileInput (Node** tr, FILE* f);
void insert_item (Node** tr, char* info, int key);
int release (Node* tr, int key);
void rb_insert_fixup (Node *x, Node **tr);
void left_rotate (Node *x, Node **tr);
void right_rotate (Node *x, Node **tr);
int dialog (Node** tr, FILE* f);
int check_int (int *a);
void add (Node** tr);
void find_item (Node* tr);
void find_min (Node* tr);
void delete (Node **tr);
void rb_delete_fixup(Node *x, Node **tr);
Node * search_nearest_next (Node *tr, int key);
void show (Node** tr);
void showtree (Node* tmp, int n);
int timing(Node **);
int find_key (Node* tr, int key);
