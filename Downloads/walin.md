#include<stdio.h>
#include<string.h>
int main()
{
    char str[] = "12321";
    int len = strlen(str);
    int start = 0;
    int end = len-1;
    int i = 0;
   for(int i=0;i<len;i++)
   {
       if(str[start] != str[end])
       {
           printf("not palindrome\n");
           return 0;
       }
       start++;
       end--;
   }
   printf("palindrome");
}
___________________________________________________
2)#include<stdio.h>
#include<string.h>
int palindrome(char str[],int start,int end);
int main()
{
    char str[] = "12321";
    int len = strlen(str);
    int start = 0;
    int end = len-1;
    int res=palindrome(str,start,end);
    if(res!=0)
    {
        printf("palindrome\n");
    }
    else
    {
        printf("not");
    }
}

int palindrome(char str[],int start,int end)
{
    if (start >= end)
        return 1;
    if(str[start] != str[end])
           return 0;
    return palindrome(str,start+1,end-1);
}
_______________________________
3)#include <stdio.h>

unsigned int next_power_of_2(unsigned int n) {
    if (n == 0) return 1;

    n--;                // Step 1
    n |= n >> 1;        // Step 2: fill bits
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;       // Step 3
}

int main() {
    unsigned int num = 132;
    unsigned int result = next_power_of_2(num);
    printf("Next power of 2 after %d is %u\n", num, result);
    return 0;
}
____________________________________________________
