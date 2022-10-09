#include <stdio.h>



int main(){
	int a;
	int b;
	scanf("%d %d", &a, &b);
	printf("\nres: %d\n\n",a % b);	
}
/*
 *  13  %  5 =  3
 * -13  %  5 = -3
 *  13  % -5 =  3
 * -13  % -5 = -3
 */

// a % b = a - k*b: 
// (k in int) and (abs(k*b) <= abs(a))




