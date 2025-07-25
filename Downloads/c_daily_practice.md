```c
//Q)write a c program to add 1 to a number using bitwise operators
input: 5
output: 6
#include<stdio.h>
#include<stdlib.h>

int main()
{
  int num;
  printf("enter a number:\n");
  scanf("%d",&num);
  
  for(int i = 0;i<32;i++)
  {
      int mask = 1<<i;
      if((num & mask) != 0) 
      {
          num = num & ~(mask);
      }
      else
      {
          num = num | mask;
          break;
      }
  }
  printf("result:%d\n",num);
}
```
