#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argc, char **argv){
  if(argc<3){
    fprintf(stderr,"operand missing\n");
    return EXIT_FAILURE;
  }
  size_t bufs = 256;
  size_t *pbufs = &bufs;
  char * buf1 = calloc(bufs,sizeof(char));
  char * buf2 = calloc(bufs,sizeof(char));
  FILE *f1 = fopen(argv[1],"r");
  FILE *f2 = fopen(argv[2],"r");
  if(!f1||!f2){
    fprintf(stderr, "cann't open file\n");
    free(buf1);
    free(buf2);
    return EXIT_FAILURE;
  }
  long line = 0;
  while(getline(&buf1,pbufs,f1)!=-1&&getline(&buf2,pbufs,f2)!=-1){
    char c1;
    char c2;
    for(off_t i =0; i<bufs;++i){
      if(buf1[i]!=buf2[i]){
        printf("%s differs from %s: line %ld  char %ld \n", argv[1],argv[2],line,i);
        fclose(f1);
        fclose(f2);
        free(buf1);
        free(buf2);
        return EXIT_SUCCESS;
      }
    }
    ++line;
  }
  ++line;
  for(off_t i =0; i<bufs;++i){
    if(buf1[i]!=buf2[i]){
        printf("%s differs from %s: line %ld  char %ld \n", argv[1],argv[2],line,i);
        fclose(f1);
        fclose(f2);
        free(buf1);
        free(buf2);
        return EXIT_SUCCESS;
    }
  }
  printf("%s not differs from %s\n",argv[1],argv[2]);

  free(buf1);
  free(buf2);
  fclose(f1);
  fclose(f2);
  return EXIT_SUCCESS;
}
