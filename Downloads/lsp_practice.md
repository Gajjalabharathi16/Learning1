```c

//write a code to restart the child process that was aborted.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int attempts = 0;

    while (attempts < 3) {
        pid_t pid = fork();

        if (pid == 0) {
            printf("Child running\n");
            sleep(2);
            printf("Child aborting\n");
            abort();
        } else {

            int status;
            waitpid(pid, &status, 0);

            if (WIFSIGNALED(status)) {
                printf("Child crashed. Restarting...\n");
                attempts++;
            } else {
                printf("Child exited normally.\n");
                break;
            }
        }
    }

    printf("Everything done.\n");
    return 0;
}

```
```c
//using recursion
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int attempts=0;
void restart()
{
            printf("Child running\n");
            sleep(2);
              if(attempts==5)
              {
                      exit(0);
              }
            printf("Child aborting\n");
            abort();
}
int main() {
//static int attempts = 0;
while(attempts<=5)
{

        int pid = fork();

        if (pid == 0)
            {
                restart();
            }
            int status;
            waitpid(pid, &status, 0);

            if (WIFSIGNALED(status))
            {
                printf("Child crashed. Restarting...\n");
                attempts++;
            } else
            {
                printf("Child exited\n");
                break;
            }

}
printf("Everything done.\n");
return 0;
}
```
