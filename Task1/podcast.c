#include<stdio.h>

int main(){
	long long number = 0;
	scanf("%d",&number);
	printf(
		"char(%d): %d\n"
		"iunsigned char(%d): %d\n"
		"signed char(%d): %d\n"
		"short(%d): %d\n"
		"unsigned short(%d): %d\n"
 		"int(%d): %d\n"
		"unsigned char(%d): %d\n"
		"long(%d): %d\n"
		"unsigned long(%d): %d\n"
		,sizeof((char)number),(char)number
		,sizeof((unsigned char)number),(unsigned char)number
		,sizeof((signed char)number),(signed char)number
		,sizeof((short)number),(short)number
		,sizeof((unsigned short)number),(unsigned short)number
		,sizeof((int)number),(int)number
		,sizeof((unsigned int)number),(unsigned int)number
		,sizeof((long)number),(long)number
		,sizeof((unsigned long)number),(unsigned long)number);
		
}
