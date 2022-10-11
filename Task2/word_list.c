#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  char *value;
  struct node *next;
} node;

typedef struct {
  node *root;
  node *current;
  unsigned long length;
} word_list;

node* create_node(char *str,size_t str_len, node *next){
  node *n = calloc(sizeof(node),1);
  n->value=calloc(sizeof(char),str_len+1);// with \0
  strcpy(n->value,str);
  //printf("\n %s  %ld \n ",n->value,strlen(n->value));
  return n;
}
void list_append(word_list *l,node *n){
  if(l->root){
    l->current->next = n;
    l->current = n;
    ++l->length;
  } else{
    l->root = n;
    l->current = n;
    ++l->length;
  
  }
}
void list_free(word_list *l){
  node *n = l->root;
  node *n0;
  while(n){
    n0 = n;
    free(n->value);
    n=n->next;
    free(n0);
  }
}
void list_print(word_list *l){
  printf("\nlength: %ld\n",l->length);
  node *n = l->root;
  while(n){
    printf("%s ",n->value);
    n=n->next;
  }
}
void init_list(word_list *l){
  l->length = 0;
  l->current = NULL;
  l->root = NULL;
}

int main(){
  char c = 32;
  char *s = calloc(sizeof(char), 255);
  unsigned long l;
  word_list wl;
  init_list(&wl);
  while( scanf(" %s%ln ",s,&l) !=EOF){

  //  printf("\n%ld   %s\n", l, s); 
    list_append(&wl, create_node(s,l,NULL));

  }

  list_print(&wl);
  node *end = wl.current;
  node *n = wl.root;
  node *n0;
  char *val = end->value;

  while(n!=end){
    if(strcmp(n->value,val) == 0){
      --wl.length;
      if(n==wl.root){
        wl.root = n->next;
        free(n->value);
        free(n);
        n = wl.root;
      } else{
        n0->next=n->next;
        free(n->value);
        free(n);
        n=n0->next;
      }
    } else{
      n0=n;
      n=n->next;
    }
  }
  
  list_print(&wl);
  list_free(&wl);
  free(s);
}


