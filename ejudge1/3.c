#include <stdio.h>

int main(void){
  int a;
  int b;
  unsigned int n;
  scanf("%d %d %ud",&a,&b,&n);
  printf("%*c",n,' ');
  for(int j = a; j<b;++j){
      printf(" %*lld",n,(long long) j);
    }
  

  for(int i = a; i<b;++i){
    printf("\n%*lld",n,(long long) i);
    for(int j = a; j<b;++j){
      printf(" %*lld",n,(long long) i*j);
    }
  }
  printf("\n");

  return 0;
}
