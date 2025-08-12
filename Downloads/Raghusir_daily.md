```c
```To interleave words from two files into 3rd file

file1:this is viven training
file2:is embedded institute
file3:this is viven embedded training institiute```

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    int fd3 = open("file3.txt",O_RDWR|O_CREAT,0666);
    char ch, ch1;
    int ret, ret1;

    while (1) {
        if ((ret = read(fd, &ch, 1)) > 0)
        {
            while (ret > 0 && ch != ' ' && ch != '\n' && ch != '\t')
            {

                    //printf("%c", ch);
                write(fd3,&ch,1);
                ret = read(fd, &ch, 1);
            }
            write(fd3," ",1);
            //printf(" ");
        }

        if ((ret1 = read(fd2, &ch1, 1)) > 0)
        {
            while (ret1 > 0 && ch1 != ' ' && ch1 != '\n' && ch1 != '\t')
            {
                //printf("%c", ch1);
                write(fd3,&ch1,1);
                ret1 = read(fd2, &ch1, 1);
            }
            write(fd3, " ",1);
            //printf(" ");
        }
        if (ret <= 0 && ret1 <= 0)
            break;
    }

    printf("\n");

    close(fd);
    close(fd2);
    return 0;
}

```
