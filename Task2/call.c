#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TYPE int
 
typedef struct {
  TYPE as[64];
  char ops[64];
  short act_len;
  bool inited;
} d_queue;

void push_op(d_queue *ldq,char op);
void push_num(d_queue *ldq, TYPE num);

TYPE operate(TYPE op0,TYPE op1,char op);
char get_prior_op(char op);
TYPE read_num(char **s);
bool cmp_prior_op(char op0, char op1);
TYPE power(TYPE a, TYPE x);



int main(){

  int op_rel[6]= {0,0,0,0,0,0};

  size_t buf_size = 1024;
  char *input = calloc(buf_size,sizeof(char));
  unsigned int input_length =  getline(&input,&buf_size,stdin); 
  //printf("\n%s\n",input);
  d_queue dq;
  dq.act_len=0;
  char *p = input;
  char c;
  push_op(&dq,'f'); //f op
  while((c=*p)!=0){
   switch(c){
      case ' ':
      case '\t':
      case '\n':
        break;
      case '(': 
        ++op_rel[5];
        push_op(&dq,c);
        break;
      case ')':
        push_op(&dq,c);
        break;
      case '*':
        ++op_rel[1];
        push_op(&dq,c);
        break;
      case '/':
        ++op_rel[3];
        push_op(&dq,c);
        break;
      case '+':
        ++op_rel[0];
        push_op(&dq,c);
        break;
      case '-':
        ++op_rel[2];
        push_op(&dq,c);
        break;
      case '^':
        ++op_rel[4];
        push_op(&dq,c);
        break;

      default:
        if (c>='0' && c<='9'){
          push_num(&dq,read_num(&p));
        }
  
    }
    ++p;
    c=*p;
    /*
    printf("_\n");
    for(int i =0; i<dq.act_len;++i){
    printf("dq: %3d  %c\n",dq.as[i],dq.ops[i]);
    }
    printf("dq: %3d  x\n",dq.as[dq.act_len+1]);
    */
  
  }
  printf("--done\n");
  /*
for(int i =0; i<dq.act_len;++i){
    printf("dq: %3d  %c\n",dq.as[i],dq.ops[i]);
    }
*/
  push_op(&dq,'#'); //AKA flush operation ;)
  printf("%d \n",dq.as[0]);
  char op_min_rel= ' ';
  int op_min_rel_count = 1024;
  for(int i = 0; i<6;++i){
    if(op_rel[i]<op_min_rel_count && op_rel[i]>0){
      op_min_rel_count = op_rel[i];
      op_min_rel = i;
    }
  }
  switch (op_min_rel){
    case 0:
      printf("most unpopular op in your expression is +"); 
      break;
    case 1:
      printf("most unpopular op in your expression is *"); 
      break;
    case 2:
      printf("most unpopular op in your expression is -"); 
      break;
    case 3:
      printf("most unpopular op in your expression is /"); 
      break;
    case 4:
      printf("most unpopular op in your expression is ^"); 
      break;
    case 5:
      printf("most unpopular op in your expression is ()"); 
      break;

    default:
      printf("no operations in your expression, bro( ");      
      break;
  }
  if(op_min_rel_count!=1024)
    printf(" it occurs %d times\n",op_min_rel_count);
  //printf("%c  %c  %c \n",dq.ops[0],dq.ops[1],dq.ops[2]);
  free(input);
  return EXIT_SUCCESS;



}


TYPE power(TYPE a, TYPE x){
  TYPE b = a;
  if(!x) return 1;
  while(--x) a*=b;
  return a;  
}

TYPE read_num(char **s){
  short len = 0;
  char *p=*s;
  char c = *p;
  TYPE result=0;
  while(c>='0'&&c<='9'){
    result*=10;
    result+=c-'0';
    ++p;
    c=*p;
    ++len;
  }
  *s+=len-1;
  return result;

}
char get_prior_op(char op){
  switch(op){
    case '^':
      return 3;
    case '*':
    case '/':
      return 2;
    case '+':
    case '-':
    case '#':
      return 1;
    case '(':
      return 4;
    case ')':
      return 5;

  }
  return 1;
}
bool cmp_prior_op(char op0, char op1){ // p(op0)>=p(op1)?
  if (op0 =='(' || op1=='(' || op0=='f')//f op
    return false;
  if (op1==')'&&op0!='(')
    return true;
  if (op1=='^')
    return get_prior_op(op0)>get_prior_op(op1);

  return get_prior_op(op0)>=get_prior_op(op1);

}

TYPE operate(TYPE op0,TYPE op1,char op){

switch(op){ //ops

  case '*':

    return op0*op1;

  case '/':

    return op0/op1;

  case '+':

    return op0+op1;

  case '-':

    return op0-op1;

  case '^':

    return power(op0,op1);



  case '#':

    return op1;

}

return 0;

}



void push_op(d_queue *ldq,char op){
  //printf("-%c\n",op);
  short al = ldq->act_len;

  if(!al){

    ldq->ops[0]=op;

    ldq->act_len=++al;

  } else{

    while(cmp_prior_op(ldq->ops[al-1],op)&&al>1) {
      //printf("--%d %c %d  in %c\n",ldq->as[al-2],ldq->ops[al-1],ldq->as[al-1],op);

      ldq->as[al-2]=operate(ldq->as[al-2],ldq->as[al-1],ldq->ops[al-1]); //al-1
      ldq->as[al-1]=0; //
      ldq->act_len=--al;
     }

    if(op!='#' && op!=')'){ //if !#
      ldq->ops[al]=op;
      ldq->act_len=++al; //swaped

    }
    if(op==')'){
      ldq->as[al-2]=ldq->as[al-1];
      ldq->act_len=al-1;
      push_op(ldq,'#');

    }
  }
}

void push_num(d_queue *ldq, TYPE num){

  if(ldq->act_len)

    ldq->as[ldq->act_len-1]=num; //-

  else{

    ldq->as[0]=num;
  } //brackets


}
