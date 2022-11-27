#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

void er(){
  fprintf(stderr,"%s\n",strerror(errno));
  fflush(stderr);
  _exit(EXIT_FAILURE);
}

int main(int argc, char **argv){
  if(argc <2){
    fprintf(stderr,"wrong operands\n");
    fflush(stderr);
  }
  bool b = false;
  FILE *f;
  if(*(argv[1])=='-'){
    b = true;
    if(!(f = fopen(argv[2],"r")))
      er();
  } else{
    if(!(f = fopen(argv[1],"r")))
      er();
  }
  size_t bufs = 10;
  char * buf = calloc(bufs+1, sizeof(char));
  size_t len = 0;
  size_t k =0;
  while((k=fread(buf,sizeof(char),bufs,f))>0){
    buf[k]=0;
    printf("%07lo",len);
    for(int i =0;i<10;++i) {
      if(buf[i]==0)
        break;
      if(!b){
        if(buf[i]=='\t')
          printf("  \\t");
        else if(buf[i]=='\n')
          printf("  \\n");
        else
          printf(" %3c",buf[i]);
      } else{
        printf(" %03o",buf[i]); 
      }
    }
    printf("\n");
    fflush(stdout);
    len+=k;
  }
  len+=k;
  printf("%07lo\n",len);

    free(buf);
    fclose(f);
    return EXIT_SUCCESS; 

}
