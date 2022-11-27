#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>


enum month{янв, фев, мар, апр, май, июн, июл, авг, сен, окт, ноя, дек};
static const char *months[]={"янв", "фев", "мар", "апр", "май", "июн", "июл", "авг", "сен", "окт", "ноя", "дек"};

int not_dot(const struct dirent *e){
  return e->d_name[0]=='.'?0:1;
}
void strmode(mode_t mode,char * buf){
  const char chars[] = "rwxrwxrwx";
  for(size_t i = 0; i < 9; ++i){
    buf[i+1] = (mode & (1<<(8-i))) ? chars[i] : '-';
  }
  buf[0] = S_ISREG(mode)?'-':'d';
  buf[10] = 0; 
}
int main(int argc, char ** argv){
  bool l = false;
  bool g = false;
  bool R = false;
  if(argc>1){
    if(*(argv[1]+1)=='l')
      l = true;
    if(*(argv[1]+1)=='g'){
      g = true;
    }
    if(*(argv[1]+1)=='R')
      R = true;

  }
  DIR *dp;
  if(!(dp=opendir("."))){
    fprintf(stderr,"%s\n",strerror(errno));
    return EXIT_FAILURE;
  } 
  struct dirent *el;
  errno = 0;
  struct dirent **nl;
  int len = scandir(".",&nl,&not_dot,alphasort);
  if(len < 0){
    fprintf(stderr,"%s\n",strerror(errno));
    return EXIT_FAILURE;
  }
  //char *fullpath = calloc(4096,sizeof(char));
  char *sp = calloc(256,sizeof(char));
  struct tm * tms;
  sp[0]='.';
  sp[1]='/';
  struct stat sb;
  for(int i = 0; i<len; ++i){
    if(g||l){
      //int k = 0;
      //sprintf(1+fullpath + (k = sprintf(fullpath,"%s",getcwd(NULL,0))),"%s",nl[i]->d_name);
      //fullpath[k]='/';
      //printf("%s\n",fullpath);
      int ll = strlen(nl[i]->d_name);
      memmove(sp+2,nl[i]->d_name,ll);
      sp[ll+2]=0;
      if(stat(sp,&sb)==-1){
        fprintf(stderr,"%s\n",strerror(errno));
        return EXIT_FAILURE;
      }
      mode_t m = sb.st_mode;
      char smb[10];
      strmode(m,smb);
      char * uname = getpwuid(sb.st_uid)->pw_name;
      char * gname = getgrgid(sb.st_gid)->gr_name;
      char * month;
      time_t t = sb.st_atim.tv_sec;
      tms = localtime(&t);
      month = (char *)months[tms->tm_mon]; 
      int day = tms->tm_mday;
      int hour = tms->tm_hour;
      int minute = tms->tm_min; 
      if(l){
        printf("%s. %ld %s %s %7ld %s %2d %02d:%02d %s\n",
            smb, sb.st_nlink, uname, gname, sb.st_size, month, day, hour, minute, nl[i]->d_name);
      } else{ 
      printf("%s. %ld %s %7ld %s %2d %02d:%02d %s\n",
          smb, sb.st_nlink, uname, sb.st_size, month, day, hour, minute, nl[i]->d_name);
      }
      //printf("%s %s\n",smb,nl[i]->d_name);
    } else
      printf("%s ", nl[i]->d_name);
    free(nl[i]);
  }
  
  free(nl);
  free(sp);
  /*
  struct dirent **els = calloc
  while(el=readdir(dp)) {
    if(errno!=0){
      fprintf(stderr,"%s\n",strerror(errno));
      return EXIT_FAILURE;
    }
    if(el->d_name[0]!='.'){
      if(printf("%s ",el->d_name)<=0)
        return EXIT_FAILURE;
    }
    errno = 0;
  }
  */
  closedir(dp);
  putchar('\n');
  return EXIT_SUCCESS;
}
