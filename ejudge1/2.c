#include <stdio.h>

int main(void){
  char c;
  long long res=0;
  while( scanf("%c",&c)!=EOF){
    if (c>='0'&&c<='9')
      res+=c-'0';
    if (c>='a'&&c<='f')
      res+=(c-'a')+10;
    if (c>='A'&&c<='F')
      res+=(c-'A')+10; 
  }
  printf("\n%lld\n",res);
  return 0;
}
