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

node* create_node(char *str,size_t str_len, node *next);

bool consist_one_word(char *s);

void list_append(word_list *l,node *n);
void list_free(word_list *l);
void list_print(word_list *l);
void init_list(word_list *l);
int count_word(word_list *l, char *wrd);
char *get_popular_word(word_list *l);
///return number of passed 0s
size_t mystrncpy(char *dest, char* src, size_t n);

size_t ceil_blocked(size_t i, size_t block_size);
void list_append_spec_seq(word_list *wl, char *w,size_t l);


void read_to_list_from_file(word_list *list,FILE *f);
int lexi_comp(char *a,char *b);
void insert_list_sorted(word_list *wl, node *n, int(*comp)(char *, char *));
void insert_lexi(word_list *wl, node *n);

void _insert_sorted_after(node *after, node *n, int(*comp)(char *,char*));

void sort(word_list *wl,int (*comp)(char *a,char *b));

int main(){
  word_list wl;
  init_list(&wl);
  char c = 32;
  char *s = NULL;
  unsigned long l = 0;
  unsigned int total_to_free = 0;
  char *w;
  do{ //every iteration extends input buffer, normally it runs once
      
    s = realloc(s,l+BUFF_SIZE); 
    l += fread(s+l,sizeof(char),BUFF_SIZE,stdin);
    //printf("\n>%s",s);
    //list_append(&wl, create_node(s,l,NULL));
    w = realloc(w,l+1);//+1 for '\0'
    unsigned int to_free = 0;
    char *p = s;
    char c;
    bool was_special = false;
    bool was_classic = false;
    bool unchanged = true;

    for(int i =0; i<l;++i){
      c=*p;
      switch(c){
        case ' ':
        case '\t':
        case '\n':
          if(was_special || was_classic){
            memmove(w,s+total_to_free,to_free);
            w[to_free]='\0';
            if(was_special)
              list_append_spec_seq(&wl,w,to_free);
            else
              insert_lexi(&wl,create_node(w,to_free+1,NULL));
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
            memmove(w,s+total_to_free,to_free);
            w[to_free]='\0';
            insert_lexi(&wl,create_node(w,to_free+1,NULL));
            total_to_free += to_free;
            was_classic = false;
            unchanged = false;
            to_free = 0;
          }
          was_special = true;
          ++to_free;
          break;
        
        case '$':
        case '_':
        case '/':
        case '.':
          if(was_special){
            memmove(w,s+total_to_free,to_free);
            w[to_free]='\0';
            list_append_spec_seq(&wl,w,to_free);
            total_to_free+=to_free;
            was_special = false;
            unchanged = false;
            to_free=0;
          }
          
          was_classic = true;
          ++to_free;
          break;
         
        default:
          if((c>='0'&&c<='9')||(c>='a'&&c<='z')||(c>='A'&&c<='Z')){
            if(was_special){
              memmove(w,s+total_to_free,to_free);
              w[to_free]='\0';
              list_append_spec_seq(&wl,w,to_free);
              total_to_free+=to_free;
              was_special = false;
              unchanged = false;
              to_free=0;
          }
            was_classic = true;
            ++to_free;
            break;
 
          }
    }
      
      ++p;
    }
    if (!unchanged){
    
      l-=total_to_free;
      memmove(s,s+total_to_free,l);
      s[l+total_to_free-1]='\0';
      total_to_free = 0; 
      unchanged = true;

    }


  } while(!feof(stdin));

  free(w);

  printf("\n%ld  %d  %s\n",l,total_to_free, s);
  //char *w= malloc(l+1);
  //strncpy(w,s,l);
  //w[l]='\0';
  if(s[0]=='&'
      ||s[0]=='|'
      ||s[0]=='<'
      ||s[0]=='>'
      ||s[0]==';'
      ||s[0]=='('
      ||s[0]==')')
    list_append_spec_seq(&wl,s,l);
  else
    insert_lexi(&wl,create_node(s,l,NULL));

  printf("\n %ld    %s     %d\n",l,s,s[l-1]);
  
  list_print(&wl);
  //printf("\n %d  %d  \n", wl.root->value[0],wl.root->next->value[0]);
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
node* create_node(char *str,size_t str_len, node *next){
  if(str[0]=='\0')
    return NULL;
  node *n = calloc(sizeof(node),1);
  n->value=calloc(sizeof(char),str_len+1);// with \0
  memmove(n->value,str,str_len);
  n->value[str_len]=0;
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
  if(n==NULL)
    return;
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
  printf("\n");
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
///return number of passed 0s
size_t mystrncpy(char *dest, char* src, size_t n){
  size_t zer_numb;
  for(int i =0; i<n;++i){
    if(src[i])
      src[i+zer_numb]=dest[i];
    else 
      ++zer_numb;
  }
  return zer_numb;
}

size_t ceil_blocked(size_t i, size_t block_size){
  return i%block_size?i+(block_size-i%block_size):i;
}
void list_append_spec_seq(word_list *wl, char *w,size_t l){
  char *real_word = calloc(2,sizeof(char));
  char c = *w;
  for(int i = 0;i<l&&c;++i){
    real_word[0]=c;
    if((c=='&'&&*(w+1)=='&')
        ||(c=='|'&&*(w+1)=='|')
        ||(c=='<'&&*(w+1)=='<')
        ||(c=='>'&&*(w+1)=='>')
        ){
      real_word[1]=c;
      insert_lexi(wl,create_node(real_word,2,NULL));
      ++w;
    } else{
      insert_lexi(wl,create_node(real_word,1,NULL));
    }

      ++w;
      c=*w;
  }
  free(real_word);

}


void read_to_list_from_file(word_list *list,FILE *f){
  //allocate buffer 
  //do read in empty part of buffer
  //  if there is at least 1 word
  //    append words from buffer to list
  //    align uncompleted word in buffer to left
  //    end it with '\0'
  //  else 
  //    allocate bigger buffer
  //
  //
  //while !eof
  char *s = NULL; //buffer
  size_t l = BUFF_SIZE; //actual size of buffer
  bool one_word;
  char *read_here = s; //ptr to empty part of buffer
  char c;
  do{
    s = realloc(s,ceil_blocked(l,BUFF_SIZE));
    l += fread(s,sizeof(char),BUFF_SIZE,f);
     
    c=*s;
    while(c) {
      one_word=true;
      //

    }
  
  }while(!feof(f));
  


}
int lexi_comp(char *a,char *b){
  char ac;
  char bc = ac = 0;
  while(ac&&bc){
    if(ac>bc)
      return 1;
    if(ac<bc)
      return -1;
  }
  if(ac>bc)
    return 1;
  if(ac<bc)
    return -1;
  
  return 0;
}
/*
node *find_min(node *node_from, int(*comp)(char *a,char*b)){
  if(node_from->value==NULL||node_from->value[0]=='\0')
    exit(2);
  node *np = node_from;
  node *nmin=np;
  while(np){
    if(comp(nmin->value,np->value)>=1) 
      nmin = np;
  }
  return nmin

}
*/
void insert_list_sorted(word_list *wl, node *n, int(*comp)(char *, char *)){
  ++wl->length;
  if(wl->length==1){
    wl->root=n;
    wl->current=n;
    return;
  }
if(comp(wl->root->value,n->value)>=1){

}
  node *np = wl->root;
  while(np&&comp(np->value,n->value)<=-1){
    np=np->next;
  }
}
void insert_lexi(word_list *wl, node *n){
  insert_list_sorted(wl,n,lexi_comp);
}

void _insert_sorted_after(node *after, node *n, int(*comp)(char *,char*)){
  if(n==after&&comp(after->value,after->next->value)<=-1)
    return;
  node *np = after;
  node *npp;
  while(comp(np->value,n->value)<=-1&&np->next){
    npp = np;
    np=np->next;
  }
  if(comp(np->value,n->value)<=-1){
    np->next=n;
    n->next= NULL;   
  } else{
    npp->next = n;
    n->next = np;
  }

}

void sort(word_list *wl,int (*comp)(char *a,char *b)){
  node *n_after=wl->root;
  while(n_after){
    _insert_sorted_after(n_after,n_after,lexi_comp);
    n_after=n_after->next;
  }
}


