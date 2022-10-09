#include <stdio.h>

int main() {
  double a;
  double x;
  double eps = 0.00001;
  double s1 = 0;
  double s2 = 0;
  double derivative = 0;
  scanf("%lf",&x);
  double x1 = 1;
  while (scanf("%lf",&a)!=EOF){
    s1*=x+eps;
    s1+=a;
    s2*=x-eps;
    s2+=a;
  }
  derivative = (s1-s2)/(2*eps);
  printf("\nP(%lf) = %lf \n",x,(s1+s2)/2);
  printf("P'(%lf) = %lf \n",x,derivative);
  
  return 0;
}
