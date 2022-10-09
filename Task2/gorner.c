#include <stdio.h>

int main() {
  double a;
  double x;
  double s = 0;
  scanf("%lf",&x);
  double x1 = 1;
  while (scanf("%lf",&a)!=EOF){
    s*=x;
    s+=a;
  }
  printf("\nP(%lf) = %lf \n",x,s);
  return 0;
}
