#define BUFF_SIZE 256
#ifndef INCL_WORD_LIST
#define INCL_WORD_LIST



typedef struct node {
  char *value;
  struct node *next;
} node;

typedef struct {
  node *root;
  node *current;
  unsigned long length;
  bool has_special;
} word_list;


size_t ceil_blocked(size_t i, size_t block_size);
node* create_node(char *str,size_t str_len, node *next);

void list_append(word_list *l,node *n);
void list_free(word_list *l);
void list_print(word_list *l);
void init_list(word_list *l);
int count_word(word_list *l, char *wrd);
char *get_popular_word(word_list *l);
///return number of passed 0s
size_t mystrncpy(char *dest, char* src, size_t n);


void list_append_spec_seq(word_list *wl, char *w,size_t l);

node * push_min(word_list *wl, int (*comp)(char*a,char*b));

void read_to_list_from_file(word_list *list,FILE *f);
int lexi_comp(char *a,char *b);
void insert_list_sorted(word_list *wl, node *n, int(*comp)(char *, char *));
void insert_lexi(word_list *wl, node *n);

void _insert_sorted_after(node *after, node *n, int(*comp)(char *,char*));

void sort(word_list *wl,int (*comp)(char *a,char *b));

#endif 

