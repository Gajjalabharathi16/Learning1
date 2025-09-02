```c
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
