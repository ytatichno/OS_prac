#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <limits.h>




int main(int argc, char ** argv){
  bool l = false;
  if(argc > 1||*(argv[1]+1)=='L')
    l = true;
  DIR *dp;
  if(!(dp=opendir("."))){
    fprintf(stderr,"%s\n",strerror(errno));
    fflush(stderr);
    return EXIT_FAILURE;
  }
  struct dirent * dbuf;
  errno = 0;
  while(dbuf = readdir(dp)){
    if(PATH_MAX)
    
  }




   
  return EXIT_SUCCESS;
}
