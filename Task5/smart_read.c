#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "word_list.h"





bool consist_one_word(char *s);

word_list * getcom(){
  word_list * wlp = calloc(1,sizeof(word_list));
  init_list(wlp);
  size_t total_to_free = 0;
  size_t *bs = calloc(1,sizeof(size_t));
  *bs = BUFF_SIZE;
  char * comstr = calloc(BUFF_SIZE,sizeof(char));
  if(getline(&comstr,bs,stdin)<=0){
    fprintf(stderr,"input error\n");
    fflush(stdin);
    exit(1);
  }
  size_t l = *bs;
  char * word = calloc(l,sizeof(char));
  size_t to_free = 0;
  char *p = comstr;
  char c;
  bool was_special = false;
  bool was_classic = false;
  bool gona_stop = false;
  bool gona_repl = false;
  bool unchanged = true;
  bool shield = false;
  for(size_t i = 0; i < l; ++i){
    c = *p;
    if(gona_stop)
      break;
    switch(c){
      case '#':
        gona_stop = true;
      case ' ':
      case '\t':
      case '\n':
        if(was_special || was_classic){
          memmove(word,comstr+total_to_free,to_free);
          word[to_free]='\0';
          if(was_special)
            list_append_spec_seq(wlp,word,to_free);
          else{
            if(gona_repl){
              gona_repl=false;
              list_append_repl(wlp,word,to_free+1);
            } else{
              list_append(wlp,create_node(word,to_free+1,NULL));
            }
          }
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
          memmove(word,comstr+total_to_free,to_free);
          word[to_free]='\0';
          if(gona_repl){
            gona_repl=false;
            list_append_repl(wlp,word,to_free+1);
          } else{
            list_append(wlp,create_node(word,to_free+1,NULL));
          }
          total_to_free += to_free;
          was_classic = false;
          unchanged = false;
          to_free = 0;
        }
        was_special = true;
        ++to_free;
        break;
      case '$':
        gona_repl = true;  
      case '_':
      case '/':
      case '.':
        if(was_special){
          memmove(word,comstr+total_to_free,to_free);
          word[to_free]='\0';
          list_append_spec_seq(wlp,word,to_free);
          total_to_free+=to_free;
          was_special = false;
          unchanged = false;
          to_free=0;
        }
          
        was_classic = true;
        ++to_free;
        break;
      case '\\':
        shield = true;
        break;
      default:
        if((c>='0'&&c<='9')||(c>='a'&&c<='z')||(c>='A'&&c<='Z')){
          if(was_special){
            memmove(word,comstr+total_to_free,to_free);
            word[to_free]='\0';
            list_append_spec_seq(wlp,word,to_free);
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

 return wlp; 

}

int task3(){
  //printf("%d\n",lexi_comp("bd","ab"));
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
    //de
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
            memmove(w,s+total_to_free,to_free);
            w[to_free]='\0';
            list_append(&wl,create_node(w,to_free+1,NULL));
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
  list_print(&wl);

  } while(!feof(stdin));

  free(w);

  //printf("\n%ld  %d  %s\n",l,total_to_free, s);
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
    list_append(&wl,create_node(s,l,NULL));

  //printf("\n %ld    %s     %d\n",l,s,s[l-1]);
  
  //list_print(&wl);
  //strange_reverse(&wl);
  
  //printf("\n %d  %d  \n", wl.root->value[0],wl.root->next->value[0]);
 
  list_free(&wl);
  free(s);
  return 0;
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




