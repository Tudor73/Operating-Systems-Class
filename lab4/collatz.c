#include <unistd.h>
#include <sys/types.h> 
#include <stdio.h>
#include <errno.h>

int main (int argc, char *argv[])
{
    pid_t pid = fork();
    if(pid < 0) 
        return errno;
    else if (pid == 0) {
        int number = atoi(argv[1]);
        printf("%d: ", number);
        while(number != 1) {
            if (number % 2 == 0) 
                number = number/2;
            else 
                number = 3*number + 1;
            printf("%d ", number);
        }
        printf("\n");
    }
    else {
        wait(NULL);
        printf("Child %d has finished\n", getpid());
    }
}