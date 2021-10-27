#include<stdio.h>
#include<conio.h>
void input();

void main()
{
 clrscr();
 input();
 getch();
}
void input()
{
 int a,b,c;
 printf("Enter two numbers:");
 scanf("%d %d",&a,&b);
 c = a+b;
 printf(" The Addition is:%d",c);
}
