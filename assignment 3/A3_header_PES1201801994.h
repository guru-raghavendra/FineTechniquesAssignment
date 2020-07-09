#ifndef LIST
#define LIST



struct state
{
    int A;
    int B;
    int C;
	int fn_index;
	
};
typedef struct state state;


struct node
{
	state st;
	struct node* prev;
	struct node* next;
};
typedef struct node node;


struct list
{
	node* head;
	node* tail;
};
typedef struct list list;


void set_state(state* ptr_state, int A, int B, int C);
void disp_state(const state* ptr_state);

void moveA2B(const state* src, state *dst,const int size_A,const int size_B,const int size_C);
void moveA2C(const state* src, state *dst,const int size_A,const int size_B,const int size_C);
void moveB2A(const state* src, state *dst,const int size_A,const int size_B,const int size_C);
void moveB2C(const state* src, state *dst,const int size_A,const int size_B,const int size_C);
void moveC2A(const state* src, state *dst,const int size_A,const int size_B,const int size_C);
void moveC2B(const state* src, state *dst,const int size_A,const int size_B,const int size_C);





int are_same(const state* lhs, const state* rhs);
int is_valid(const state* ptr_state,const int size_A,const int size_B,const int size_C);








void init_list(list *ptr_list);
void add_at_end(list *ptr_list, const state *ptr_state);
void remove_at_end(list *ptr_list);
void disp_list(const list *ptr_list);
int is_repeated(const list *ptr_list, const state *ptr_state);



#endif

