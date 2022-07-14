#include <unistd.h>
#include <sys/types.h> 
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    printf("Starting parent %d \n", getpid());
    for(int i = 1; i<= argc-1; i++) {
        int pid = fork();
        if(pid < 0) 
        {
            perror("Eroare creare fiu");
            exit(-1);
        }
        else if (pid == 0) 
        {
            int number = atoi(argv[i]);
            printf("%d: ", number);
            while(number != 1) {
                if (number % 2 == 0) 
                    number = number/2;
                else 
                    number = 3*number + 1;
                printf("%d ", number);
            }
            printf("\n");
            printf("Done parent %d Me %d has finished\n",getppid(), getpid());
            exit(0);
        }
    }
    for(int i = 1; i <= argc-1; i++) 
        wait(NULL);
    printf("Done parent %d Me %d has finished\n",getppid(), getpid());
}