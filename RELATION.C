#include<stdio.h>
#include<conio.h>
void main()
{
 int a,b;
 clrscr();
 printf("Enter the two numbers:");
 scanf("%d%d",&a,&b);
 if(a<=b)
 {
  printf("A is Greater than or equal to B");
 }
 else
 {
  printf("B is Greater than or equal to  A");
 }
 getch();
}
