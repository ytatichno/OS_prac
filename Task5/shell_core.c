#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "smart_read.c"
#include "strmap.h"
#include "word_list.h"

extern char **environ;
enum state {on_awake,waiting,reading,processing,writing};
enum er_codes{hash_al};


//void fill_comlist(char ** comlist);
char * er_mes(enum er_codes);

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
    list_print(ccom);
  }
  
}

//void fill_comlist(StrMap * sm){
//  sm_put(sm, "ls",)
//}



