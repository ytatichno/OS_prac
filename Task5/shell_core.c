#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "smart_read.c"
#include "strmap.h"
#include "word_list.h"

extern char **environ;
enum state {on_awake,waiting,reading,structuring,processing,writing};
enum er_codes{hash_al};
enum type_of_next{NEXT,AND,OR};
typedef struct cmd_inf com;
struct cmd_inf{
  char ** argv;
  char * in;
  char * out;
  bool bg;
  bool append;
  enum type_of_next type;
  com * psubcmd;
  com * pipe;
  com * next;
};



//void fill_comlist(char ** comlist);
char * er_mes(enum er_codes);
com * parse_com(word_list * wl);

int main(int argc, char ** argv){
  enum state cstate = on_awake;
  char * username;
  word_list * ccom;
  char * comlist[256];
  StrMap *sm;
  char buf[256];
  int result;

  if(cstate == on_awake){
    username = getenv("USERNAME");
    
    //username = username?username:"-";
    cstate = waiting;
/*
    sm = sm_new(10);
    if (sm==NULL){
      fprintf(stderr,"%s\n",er_mes(hash_al));
      exit(1);
    }
    */
    //fill_comlist(comlist);
  }
  if(cstate == waiting){
    printf("[%s]$ ",username);
    fflush(stdout);
    cstate = reading;
  }
  if(cstate == reading){
    ccom = getcom(); 
    list_append(ccom,create_node(";",2,NULL));
    list_print(ccom);
    cstate = structuring;
  }
  if(cstate == structuring){
    //com * cc = parse_com(ccom); 
  }

  
}

//void fill_comlist(StrMap * sm){
//  sm_put(sm, "ls",)
//}
com * fill_one_com(node * start, node * end){
  com * res = calloc(1,sizeof(com));
  node * np = start;
  int i = 0;
  while(np->next!=end){
    if(np->value[0]=='<'&&np->next)
      res->in=np->next->value;
    if(np->value[0]=='>'&&np->next){
      if(np->value[1]=='>')
        res->append=true;
      res->out=np->next->value;
    }
    res->argv[i]=np->value;
    ++i;
    np=np->next;
  }
  res->argv[i]=NULL;
  return res;
}

com * parse_com(word_list * wl){
  node * rnp = wl->root;
  node * np = rnp;
  node * npp = rnp;
  com * rcp;
  com * cp = NULL;
  com * cpp = NULL;
  int nodes = 0;
  bool next_com = false;
  while(np){
    if(is_sep(np->value[0])){
      ++nodes;
      cpp = cp;
      cp = fill_one_com(npp,np->next);
      npp=np->next;
      if(cpp){
        char * sep = np->value;
        if(sep[0]==';'){
          cpp->next = cp;
          cpp->type = NEXT;
        }
        if(sep[0]=='|'){
          if(sep[1]=='|'){
            cpp->next = cp;
            cpp->type = OR;
          } else {
            cp->bg=cpp->bg;
            cpp->pipe=cp;
          }
        }
        if(sep[0]=='&'){
          if(sep[1]=='&'){
            cpp->next = cp;
            cpp->type = AND;
          } else {
            cpp->bg = true;
            cpp->next = cp;
            cpp->type = AND; 
          }
        }
        if(sep[0]=='('){
          cpp->psubcmd=cp;
        }
        if(sep[0]==')'){
          return rcp;
        }
      }
    }
    if(nodes == 1)
      rcp = cp;
    np=np->next;
  } 
  return rcp;
}


