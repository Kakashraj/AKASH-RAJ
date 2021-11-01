#include<stdio.h>
#include<conio.h>
void main()
{
  int a,b;
  clrscr();
  printf("Enter the two numbers:");
  scanf("%d%d",&a,&b);
  printf("\nAddition of two numbers:%d",a+b);
  printf("\nSubraction of two numbers:%d",a-b);
  printf("\nMultiplication of two numbers:",a*b);
  printf("\ndivision of two numbers:%d",a/b);
  printf("\nModulas of two numbers:%d",a%b);
  getch();
}
