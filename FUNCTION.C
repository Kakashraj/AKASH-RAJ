#include<stdio.h>
#include<conio.h>
float cel();
void main()
{
 clrscr();
 printf("Division of given number:%f",cel());
 getch();
}
 float cel()
{
 float a,b,c;
 printf("Enter the two numbers:");
 scanf("%f %f",&a,&b);
 c = a/b;
 return (c);
 }
