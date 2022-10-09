#include <stdio.h>

unsigned long recursive(unsigned long i){

    if(i == 1) return 1UL;
    if(i == 0) return 0UL;
    return recursive(i-1)+recursive(i-2);

}
unsigned long iterative(unsigned long i){
  unsigned long f = 0;
  unsigned long fp = 0;
  unsigned long fpp = 1;
  
  for( unsigned long j = 1; j<=i; ++j){
    f = fp+fpp;
    fpp = fp;
    fp = f;
  }
  return f;
}
int main(){
  unsigned long i;
  while(scanf("%ld", &i)!=EOF){
    printf("iterative: %ld\n", iterative(i));
    printf("recursive: %ld\n", recursive(i));
  }
}
