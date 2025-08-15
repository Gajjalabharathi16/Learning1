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
```c
//sorting of an array using bubble sort
#include<stdio.h>
int main()
{
    int arr[20];
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
   for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - 1 - i; j++) {
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
}
```
```c
// Capitalize the first letter of each word
#include<stdio.h>
int main()
{
    char str[100];
    fgets(str,100,stdin);
    for(int i=0;str[i]!='\0';i++)
    {
        if(i==0)
        {
            str[i]=str[i]-32;
        }
        if(str[i]==' ' || str[i]=='.' || str[i]==',')
        {
            if(str[i+1]>'a' && str[i+1]<'z')
            {
                str[i+1]=str[i+1]-32;
            }
        }
    }
    printf("%s",str);
}
```
```c
//Multiply a number by 2 without * using switch case
#include<stdio.h>
#include<stdlib.h>
int main()
{
    while(1)
    {
    int choice;
    printf("enter choice: \n 0 to exit\n 1 to multiply\n 2 to divide\n ");
    scanf("%d",&choice);
    switch(choice)
    {
        case 0:
            printf("exited\n");
            exit(0);
        case 1:
            int num;
            printf("enter number\n");
            scanf("%d",&num);
            int res=num<<1;
            printf("%d\n",res);
            break;
        case 2:
            int num1;
            printf("enter number\n");
            scanf("%d",&num1);
            int res1=num1>>1;
            printf("%d\n",res1);
            break;
        default:
            printf("choose valid option 0 to exit,1 to multiply,2 to divide\n");
        
    }    
    }
}

                                                  or

#include<stdio.h>
int main()
{
    int num;
    scanf("%d",&num);
    int res=num<<1;
    printf("%d",res);
}
```

```c
//Print characters with their frequencies
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    char str[100];
    int count=0;
    fgets(str,100,stdin);
    str[strcspn(str, "\n")] = '\0';
    int visited[100]={0};
    
    for(int i=0;str[i]!='\0';i++)
    {
        count=0;
        if(visited[i]==1)
        {
            continue;
        }
        for(int j=0;str[j]!='\0';j++)
        {
            if(str[i]==str[j])
            {
                count++;
                visited[j]=1;
            }
        }
        printf("count of %c is %d\n",str[i],count);
    }
}
```
```c
// to print leading (or leader) elements from right to left in an array 
#include<stdio.h>
#include<limits.h>
int main()
{
    //int arr[]={2,9,4,1,8};
    int arr[100];
    int n;
    int num=INT_MIN;
    int prev=INT_MIN;
    printf("enter no of elements\n");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("the leader elements are:");
    for(int i=n-1;i>=0;i--)
    {
        if(arr[i]>=num)
        {
            prev=num;
            num=arr[i];
            printf("%d ",num);
        }
    }
    
}
```
```c
// even bits and odd bits count in a number
#include<stdio.h>
int main()
{
    int num;
    int even_count=0;
    int odd_count=0;
    scanf("%d",&num);
    int even=num&0x55555555;
    int odd=num&0xAAAAAAAA;
    while(even>0)
    {
        even_count+=even&1;
        even>>=1;
    }
    while(odd>0)
    {
        odd_count+=odd&1;
        odd>>=1;
    }
   printf("Even bit count: %d\n", even_count);
   printf("Odd bit count : %d\n", odd_count);

}
```
```c
#include <stdio.h>

int main(void)
{
  int num=0,even=0,odd=0;
  printf("Enter Number:");
  scanf("%d",&num);
  if(num>0)
  {
    while(num)
    {
      if(num & 1 )
      {
        even++;
      }
      else
      {
        odd++;
      }
      num >>= 1;
    }
    if(even==odd)
    {
      printf("Even and Odd Bits are Equal\n");
    }
    else
    {
      (even > odd) ? printf("Even bits=%d\n",even) : printf("Odd bits=%d\n",odd);
    }
  }
  else
  {
    printf("Enter Positive Number\n");
  }
  return 0;
}
```
```c
//Program to convert decimal to binary without bitwise
#include<stdio.h>
int main()
{
    int num;
    int r;
    int bin[32];
    scanf("%d",&num);
    int i=0;
    while(num>0)
    {
        r=num%2;
        bin[i++]=r;
        num=num/2;
    }
    for(int j=i-1;j>=0;j--)
    {
        printf("%d",bin[j]);
        
    }
}
```
```c
//highest frequency character in a sentence
#include<stdio.h>
#include<string.h>
int main()
{
    char str[100];
    fgets(str,100,stdin);
    char maxchar;
    str[strcspn(str,"\n")]='\0';
    //scanf("%s",str);
    int visited[100]={0};
    int max=0;
    for(int i=0;str[i]!='\0';i++)
    {
        if(str[i]==' ')
        {
            continue;
        }
        if(visited[i]==1)
        {
            continue;
        }
        int count=0;
        for(int j=0;str[j]!='\0';j++)
        {
            if(str[i]==str[j])
            {
                count++;
                visited[j]=1;
            }
        }
        if(count>max)
        {
            max=count;
            maxchar=str[i];
        }
    }
      printf("%c count is %d\n",maxchar,max);
}
```
```c
//Move all zeros to the end
#include<stdio.h>
int main()
{
    int arr[]={1,0,2,4,0,3};
    int count=0;
    int n=sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i<n-count;i++)
    {
        if(arr[i]==0)
        {
            for(int j=i;j<n-1;j++)
            {
            arr[j]=arr[j+1];
            }
            arr[n - 1] = 0;  
            count++;         
            i--;
        }
        
    }
    for(int i=0;i<n;i++)
    {
        printf("%d",arr[i]);
    }
}
```
```c
//Find position of rightmost set bit
#include<stdio.h>
int main()
{
    int num;
    scanf("%d",&num);
    int pos=0;
    while(num>0)
    {
        if(num&1)
        {
            printf("the position of rightmost set bit is %d",pos);
            break;
        }
        pos++;
        num=num>>1;
    }
}
```

```c
// Toggle all characters of a string
#include<stdio.h>
int main()
{
    char str[100];
    fgets(str,100,stdin);
    for(int i=0;str[i]!='\0';i++)
    {
        if(str[i]==' ')
        {
            continue;
        }
        if(str[i]>='A' && str[i]<='Z')
        {
            str[i]=str[i]+32;
        }
        else
        {
            str[i]=str[i]-32;
        }
    }
    printf("%s",str);
}
```
```c
//Remove characters except alphabets
#include<stdio.h>
#include<string.h>
int main()
{
    char str[100];
    fgets(str,100,stdin);
    for(int i=0;str[i]!='\0';i++)
    {
        if(str[i]!=' ' && (str[i]>='a' && str[i]<='z' || str[i]>='A' && str[i]<='Z'))
        {
            printf("%c",str[i]);
        }
    }
}
```
```c
//write a c program to find pairs with given sum

// Find pair with given sum
#include<stdio.h>
int main()
{
    int arr[100];
    int n;
    int sum;
   
    printf("enter the elements count\n");
    scanf("%d",&n);
    printf("enter sum\n");
    scanf("%d",&sum);
    printf("enter array elements\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("the pairs found are:\n");
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if((arr[i]+arr[j])==sum)
            {
                printf("%d %d\n",arr[i],arr[j]);
            }
        }
    }
}
```
<img width="334" height="274" alt="Screenshot 2025-08-02 123610" src="https://github.com/user-attachments/assets/cbaea2af-67e4-45e2-a51c-b0802a3b3dea" />

```c
//Clear all bits from MSB to a given bit position
#include <stdio.h>

// Function to print binary (8 bits)
void printBinary(int num) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

int main()
{
    int num;
    printf("Enter number: ");
    scanf("%d", &num);

    int pos = 2;

    printf("Original binary: ");
    printBinary(num);

    // Create mask with lower bits set (pos bits and below)
    int mask = (1 << pos) - 1;

    num = num & mask;

    printf("Modified binary: ");
    printBinary(num);

    printf("Modified decimal: %d\n", num);

    return 0;
}

```
```c
#include<stdio.h>
int main()
{
    int arr[]={1,2,3,4,5,6,7,8};
    int n=sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i<n;i++)
    {
        if(arr[i]%2!=0)
        {
            int temp=arr[n-1-i];
            arr[n-1-i]=arr[i];
            arr[i]=temp;
        }
    }
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    
    
}
```
```c
//Q))write a c program to sort all odd numbers to left side of an array and even numbers to right side of an array
//Note:Don't use extra array and temp variable 
#include<stdio.h>
int main()
{
    int arr[]={1,2,3,4,5,6,7,8};
    int n=sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i<n;i++)
    {
        if(arr[i]%2!=0)
        {
           arr[i] = arr[i] + arr[n-1-i];
           arr[n-1-i] = arr[i] - arr[n-1-i];
           arr[i] = arr[i] - arr[n-1-i];

        }
    }
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    ```
```c
#include <stdio.h>
#include <string.h>

int main() {
    char str1[100], str2[100];
    int count[256] = {0}; // ASCII character count

    printf("Enter first string: ");
    scanf("%s", str1);
    printf("Enter second string: ");
    scanf("%s", str2);

    if (strlen(str1) != strlen(str2)) {
        printf("Not an anagram\n");
        return 0;
    }

    for (int i = 0; str1[i]; i++) {
        count[(unsigned char)str1[i]]++;
        count[(unsigned char)str2[i]]--;
    }

    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) {
            printf("Not an anagram\n");
            return 0;
        }
    }

    printf("Anagram\n");
    return 0;
}
```c
 //4.write a c program to find the number/word is a palindrome and explain the logic
//using strings
#include<stdio.h>
#include<string.h>
int main()
{
   char num[100];
   scanf("%s",num);
   int len=strlen(num);
   char str[100];
   strcpy(str,num);
   for(int i=0;i<len/2;i++)
   {
       char temp=str[i];
       str[i]=str[len-i-1];
       str[len-i-1]=temp;
   }
   if(strcmp(num,str)==0)
   {
       printf("palindrome");
   }
   else
   {
       printf("not");
   }
}

//using numbers
//4.write a c program to find the number/word is a palindrome and explain the logic 
#include<stdio.h>
int main()
{
    int num;
    scanf("%d",&num);
    int temp=num;
    int r=0;
    int res=0;
    while(temp>0)
    {
        r=temp%10;
        res=res*10+r;
        temp=temp/10;
    }
    if(res==num)
    {
        printf("palindrome");
    }
    else
    {
        printf("not");
    }
}
```
