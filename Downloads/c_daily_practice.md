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
//2nd way
#include<stdio.h>
int add(int a,int b);
int main()
{
    int a;
    printf("enter a number to get next number\n");
    scanf("%d",&a);
    int b=1;
    int c=add(a,b);
    printf("%d",c);
}
int add(int a,int b)
{
    while(b!=0)
    {
        int carry=a&b;
        a=a^b;
        b=carry<<1;
    }
    return a;
}
```
```c
//Q)write a program to replace all spaces with hypens
#include<stdio.h>
#include<string.h>
int main()
{
    char str[100];
    fgets(str,100,stdin);
    int replace_with='-';
    for(int i=0;i<strlen(str);i++)
    {
        if(str[i]==' ')
        {
            str[i]=replace_with;
        }
    }
    printf("%s",str);
    
}
```

```c
//Q)write a c program to remove spaces in a given string without using another array
#include<stdio.h>
#include<string.h>
int main()
{
    char str[100];
    fgets(str,100,stdin);
    int len=strlen(str);
    for(int i=0;i<len;i++)
    {
        if(str[i]==' ')
        {
        for(int j=i;j<len-1;j++)
        {
            str[j]=str[j+1];
        }
        i--;
        len--;
    }
    }
    printf("%s",str);
}
```

```c
//Q)write a c program to print all subsets of an array eg:{1,2,3,4,5}
12 13 14 15 23 24 25
123 124 125 134 135...etc

#include <stdio.h>

int main() {
    int arr[100], n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            printf("%d%d ", arr[i], arr[j]);
        }
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            for (int k = j+1; k < n; k++) {
                printf("%d%d%d ", arr[i], arr[j], arr[k]);
            }
        }
    }
    printf("\n");
    return 0;
}
```
```c
//Q)write a c program to replace 0's with 1's in a given number
#include<stdio.h>
#include<stdlib.h>

int main()
{
    int num,digit,res = 0,place = 1;
    printf("enter the number:\n");
    scanf("%d",&num);
    
    if(num == 0)
    {
        num = 1;
    }
    else
    {
        digit=num;
        while(digit> 0)
        {
            res = digit %10;
            if(res == 0)
            {
                num += place;
            }
            place *= 10;
            digit = digit/10;
        }
    }
    printf("result:%d\n",num);   
}
```
