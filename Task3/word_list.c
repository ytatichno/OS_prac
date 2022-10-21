#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFF_SIZE 8


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

bool consist_one_word(char *s){
  bool was_classic = false;
  bool was_special = false;
  char c = *s;
  while(c){
    switch(c){
      case EOF:
        return true;
      case ' ':
      case '\t':
      case '\n':
        if(was_special || was_classic)
          return true;
        else
          break;
      case '|':
      case '&':
      case ';':
      case '>':
      case '<':
      case '(':
      case ')':
        if(was_classic)
          return true;
        else{
          was_special = true;
          break;
        }
      case '$':
      case '_':
      case '/':
      case '.':
        if(was_special)
          return true;
        else{
        was_classic = true;
        break;
        }
      default:
        if((c>='0'&&c<='9')||(c>='a'&&c<='z')||(c>='A'&&c<='Z')){
          if(was_special)
            return true;
          else{
            was_classic = true;
            break;
          }
 
        }
    }
    ++s;
    c = *s;

  
  }
  return false;
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
int count_word(word_list *l, char *wrd){
  node *p=l->root;
  int c =0;
  while(p){
    if(!strcmp(wrd,p->value)) 
      ++c;
    p=p->next;
  }
  return c;
}
char *get_popular_word(word_list *l){
  int popular_count=0;
  int buf;
  char *popular_word;
  node *p=l->root;
  node *e=l->current;
  while(p){
    buf = count_word(l,p->value);
    if(popular_count<buf){
      popular_count = buf;
      popular_word = p->value;
    } 
    p=p->next;
  }
  return popular_word;
}

int main(){
  word_list wl;
  init_list(&wl);
  char c = 32;
  char *s = NULL;
  unsigned long l = 0;
  do{
    s = realloc(s,l+BUFF_SIZE); 
    l+=fread(s+l,sizeof(char),BUFF_SIZE,stdin);
    //list_append(&wl, create_node(s,l,NULL));
    char *w = malloc(l+1);//+1 for '\0'
    unsigned int total_to_free = 0;
    unsigned int to_free = 0;
    char *p = s;
    char c =*p;
    bool was_special = false;
    bool was_classic = false;
    bool unchanged = true;
    while(c){
      switch(c){
        case ' ':
        case '\t':
        case '\n':
          if(was_special || was_classic){
            strncpy(w,s+total_to_free,to_free);
            w[to_free]='\0';
            list_append(&wl,create_node(w,to_free+1,NULL));
            total_to_free+=to_free;
            was_special = false;
            was_classic = false;
            unchanged = false;
            ++total_to_free;
            to_free=0;
            break;
          }
          else
            ++total_to_free;
            break;
        case '|':
        case '&':
        case ';':
        case '>':
        case '<':
        case '(':
        case ')':
          if(was_classic){
            strncpy(w,s+total_to_free,to_free);
            w[to_free]='\0';
            list_append(&wl,create_node(w,to_free+1,NULL));
            total_to_free += to_free;
            was_classic = false;
            unchanged = false;
            to_free = 0;
            break;
          } else{
            was_special = true;
            ++to_free;
            break;
        }
        case '$':
        case '_':
        case '/':
        case '.':
          if(was_special){
            strncpy(w,s+total_to_free,to_free);
            w[to_free]='\0';
            list_append(&wl,create_node(w,to_free+1,NULL));
            total_to_free+=to_free;
            was_special = false;
            unchanged = false;
            to_free=0;
            break;
          }
          else{
            was_classic = true;
            ++to_free;
            break;
          }
        default:
          if((c>='0'&&c<='9')||(c>='a'&&c<='z')||(c>='A'&&c<='Z')){
            if(was_special){
            strncpy(w,s+total_to_free,to_free);
            w[to_free]='\0';
            list_append(&wl,create_node(w,to_free+1,NULL));
            total_to_free+=to_free;
            was_special = false;
            unchanged = false;
            to_free=0;
            break;
          }
            else{
              was_classic = true;
              ++to_free;
              break;
            }
 
          }
    }
      
      ++p;
      c=*p;
    }
    free(w);
    if (!unchanged){
    
    l-=total_to_free;
    }


  } while(l % BUFF_SIZE==0 && !feof(stdin));

  char *w= malloc(l+1);
  strncpy(w,s,l);
  w[l]='\0';
  list_append(&wl,create_node(w,l,NULL));

  printf("\n %ld    %s     %d\n",l,s,s[l-1]);
  
  list_print(&wl);
 /* 
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
  */
  /*
  printf("--there are %d word %s\n",count_word(&wl,wl.root->value),wl.root->value);
  char *pw = get_popular_word(&wl);
  printf("--most popular word is %s it occurs %d times",pw,count_word(&wl,pw));
  list_print(&wl);
  */
  list_free(&wl);
  free(s);
}


