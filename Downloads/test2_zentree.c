#include<stdio.h>
#include<string.h>
int main()
{
    char str[]="aeiouhello";
    int n=strlen(str);
    for(int i=0;str[i];i++)
    {
        if(str[i]=='a'||str[i]=='e'||str[i]=='i'||str[i]=='o'||str[i]=='u')
        {
            for(int j=i;str[j];j++)
            {
                str[j]=str[j+1];
            }
           i--;
        }
    }
    printf("%s",str);
}
