#include<stdio.h>
#include<conio.h>
 int main()
 {
  float f,c;
  clrscr();
  printf("ENTER THE TEMPERATURE:");
  scanf("%f",&f);
  c=(f-32)*(5.0/9.0);
  printf("/nRESULT IS: %0.2f",c);
  scanf("%f",&c);
  return 0;
  }
