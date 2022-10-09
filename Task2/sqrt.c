#include <stdio.h>
#include <math.h>

double mysqrt(double x, double eps)
{
  double x1 = x, x2 = 1;
  while(fabs(x2 - x1) >= eps){
    x1 = x2;
    x2 = (x1 + x / x1) / 2;
  }
  return x2;
}

int main(void)
{
  double eps = 0.00001;
  double x;
  /*scanf("%lf", &eps);*/
  while(scanf("%lf", &x) == 1){
      printf("- %.10g\n", mysqrt(x, eps));
  }
  return 0;
}
