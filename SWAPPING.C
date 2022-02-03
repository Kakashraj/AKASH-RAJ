#include<stdio.h>
#include<conio.h>
int main()
{
 int a,b;
 printf("\nENTER 2 NO's:");
 scanf("%d%d",&a,&b);
 printf("\nA:%d  B:%d",a,b);
 a=a+b;
 b=a-b;
 a=a-b;
 printf("\nA:%d B:%d",a,b);
 return 0;
}