#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char ** argv){
  char *str;
  if(!(str = getcwd(NULL,0)))
    fprintf(stderr,"%s\n",strerror(errno));
  else
    printf("%s\n",str);
  free(str);
  return EXIT_SUCCESS;
}
