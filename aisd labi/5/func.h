typedef struct Node{
	int x;
	int y;
	struct Node *next;
	struct Smezh *sm;
	int num;
} Node;

typedef struct Edge{
	struct Node *par;
	struct Node *child;
	struct Edge *next;
	double weight;
} Edge;

typedef struct Smezh{
	int x;
	int y;
	struct Node *par;
	struct Smezh *next;
	struct Edge *ed;
} Smezh;

typedef struct Graf{
	struct Node *graf;
	int num_ver;
	int num_ed;
} Graf;

typedef struct Find{
	struct Node *graf;
	int colour;
	int d;
	struct Node *pred;
} Find;

typedef struct Dec{
	struct Node *graf;
	double d;
	struct Node *pred;	
} Dec;

typedef struct Dfs{
	struct Node *graf;
	int visit;
	int time;
	struct Node *pred;	
} Dfs;

void initgraf_zeroes(Graf* gr);
int dialog(Graf* gr);
int check_int(int *a);
void add_ver(Graf* gr);
Node* find_ver(Graf* gr, int x, int y);
void add_ed(Graf* gr);
void find_way(Graf* gr);
void short_find(Graf *gr);
void del_ver(Graf* gr);
void deled(Graf* gr, int x1, int y1, int x2, int y2);
void del_ed(Graf* gr);
void show(Graf* gr);
