#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define TYPE long long
//TYPE freadone(FILE *file, bool *suctab)

typedef struct node {
  TYPE value;
  int f_ind;
  struct node *next;
} node;

typedef struct {
  node *root;
  node *current;
  int length;

} list;


bool isReading(bool *terms, int n){
  for(int t = 0; t<n; ++t)
    if(terms[t]==false)
      return true;
  return false;

}

node* create_node(TYPE el,int f_ind, node *next){
  node *n = calloc(1,sizeof(node));
  n->value = el;
  n->f_ind = f_ind;
  n->next = next;
  return n;
}

void append_list (list *l, TYPE el, int f_ind){
  l->current->next = create_node(el,f_ind,NULL);
  l->current=l->current->next;
  ++l->length;
}
int compare(TYPE a, TYPE b){
  return a-b;
}
void srtd_insert_list(list *l, TYPE el, int f_ind){
  if(!l->root){
    l->root = create_node(el,f_ind,NULL);
    l->current= l->root;
    l->length = 1;
  } else{
    node *n = l->root;
    node *p = n;
    //TYPE min_val;
    while(n && compare(el,n->value)>=0){
      p=n;
      n=n->next;
    }
    if(n==l->root)
      l->root = create_node(el,f_ind,l->root);
    else
      p->next = create_node(el,f_ind,n);
    
    ++l->length;
  }
}

void print_list(list *l){
 // printf("\nur list with %d elements\n", l->length);
  node *n = l->root;
  while(n){
    printf("%lld ",n->value);
  }
  printf("\n");
}
/*
TYPE pop_min_list(list *l){
  TYPE min_val;
  node *pmin;
  node *n = l->root;

  while(n){
     
    n=n->next
  }

}
*/

node * pop_list(list *l){
  node *n = l->root;
  --l->length;
  l->root=n->next;
  return n;
}

void free_list(list *l){
  node *n = l->root;
  node *nn;
  while(n){
    nn=n->next;
    free(n);
    n=nn;
  }

}

void close_files(FILE **fs, int n){
  
  for(int i=0;i<n;++i){
    if(fs[i])
      fclose(fs[i]);
  }

}
int main(int argc, char *argv[]){
  FILE *f_pths[argc-1];// not a path exactly
  //TYPE f_objs[argc-1];
  list l;
  l.root = NULL;
  l.current = NULL;
  l.length =0;
  bool f_read_interrupted[argc-1];
  bool f_reading = true;
  printf("\n");
  if(argc==1){
  exit(1);
  }
  for(int i = 0; i<argc-1; ++i){
  if( (f_pths[i] = fopen(argv[i+1],"r")) ==  NULL){
    close_files(f_pths,i);
    exit(1);

  }
    TYPE element;
     f_read_interrupted[i] = fscanf(f_pths[i],"%lld",&element) == EOF;
//f_read_interrupted[i] = fread(&element,sizeof(TYPE),1,f_pths[i]) <= 0 ;
    if(!f_read_interrupted[i]){
      srtd_insert_list(&l,element,i);
    }
    else {
      f_reading = isReading(f_read_interrupted,argc-1);
    }
  }
  while(f_reading){
    node *to_print= pop_list(&l);
    if(!to_print)
      exit(1);
    printf("%lld ",to_print->value);
    TYPE element;
    int f_ind = to_print->f_ind;
    f_read_interrupted[f_ind] = fscanf(f_pths[f_ind],"%lld",&element) == EOF;
    free(to_print);
 //   f_read_interrupted[f_ind] = fread(&element,sizeof(TYPE),1,f_pths[f_ind]) <= 0 ;
    if(!f_read_interrupted[f_ind])
      srtd_insert_list(&l,element,f_ind);
    else
      f_reading = isReading(f_read_interrupted,argc-1);
/*
    for(int i = 0; i<argc-1; ++i){
      if(!f_read_interrupted[i]){
        TYPE element;
        fscanf(f_pths[i],"%d",&element);
        //fread(&element,sizeof(TYPE),1,f_pths[i]);
        srtd_insert_list(&l, element,i);

      }
    
    }
*/

  
  }  
  //print_list(&l);
  printf("\n");

  for(int i = 1; i<argc; ++i){
    fclose(f_pths[i-1]);
  }
  free_list(&l);

  return 0;
}
