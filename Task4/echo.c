#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char ** argv){
  if (argc<=1){
    if(putchar('\n')==EOF||fflush(stdout)==EOF)
      return EXIT_FAILURE;
  }
  else{
    bool f = false;
    bool n = false;
    bool e = false;
    if(*argv[1]=='-'){
      f = true;
      char op = *(argv[1]+1);
      switch(op){
        case 'n':
          n = true;
          break;
        case 'e':
          e = true;
          break;
      }
    }
    int i = f?2:1;
    for(;i<argc;++i){
      if(printf("%s ",argv[i])<=0)
        return EXIT_FAILURE;
    }
    if(n?:putchar('\n') == EOF||fflush(stdout)==EOF)
      return EXIT_FAILURE;

    
  }
  return EXIT_SUCCESS;
}
