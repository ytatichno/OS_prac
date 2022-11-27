#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char ** argv){
  bool s = false;
  if(argc<=1){
    fprintf(stderr,"operand missed\n");
    return EXIT_FAILURE;
  }
  char * target = argv[1];
  char * lin = argv[2];
  if(*argv[1]=='-'&&*(argv[1]+1)=='s'){
    if(argc!=3){
      fprintf(stderr,"operand missed\n");
      return EXIT_FAILURE;
    }
    s = true;
    target = argv[2];
    lin = argv[3];
  }
  if(s){
    if(symlink(target, lin)==-1){
      fprintf(stderr,"symbolic linking error: %s\n",strerror(errno));
      return EXIT_FAILURE;
    }
  } else{
    if(link(target, lin)==-1){
      fprintf(stderr,"hard linking error: %s\n",strerror(errno));
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
