//Program of Fibonacci series
import java.util.Scanner;
public class fibonacci{
public Static void main(String args[])
{
 Scanner in = new Scanner(System.in);
System.out.println("Enter the number:");
int n = in.nextInt();
int a=-1;b=1;c;
for(int i=1;i<=n;i++)
{
 c=a+b;
 a=b;
 b=c;
System.out.println(c);
}
}
}