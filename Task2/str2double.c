#include <stdio.h>
#include <stdbool.h>

double str2double( char str[]){
  double res = 0;
  char *p = str;
  bool exp = false;
  bool frac = false;
  bool sign = false;
  bool exp_sign = false;
  short pw1 = 0;
  short pw2 = 0;
  int k=0;
  char c;
  while(c = *p){
    switch(c){
      case '-':
        if (exp)
          exp_sign=true;
        else
          sign = true;
        break;
      case '.': 
        frac = true;
        break;
      case 'E':
      case 'e':
        frac = false;
        exp = true; 
        break;
      default:
        ++k;
        if (exp){
          pw2*=10;
          if (exp_sign)
            pw2-=c-'0';
          else
            pw2+=c-'0';

        } else{
          res*=10;
          res+=c-'0';
          if(frac) --pw1;
        }
        break; 
    }
    ++p;
  } 
  pw1 = pw1 + pw2;
  for(int i = 0; i<pw1; ++i) res*=10;
  for(int i = 0; i>pw1; --i) res/=10;
  return sign ? -res : res;
}

int main(){
  char *s; 
  scanf("%s",s);
  printf(" %.10g \n", str2double(s));


return 0;
}
