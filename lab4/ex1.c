#include <unistd.h>
#include <sys/types.h> 
#include <stdio.h>
#include <errno.h>
int main () 
{
    pid_t pid = fork();
    printf (" My PID % d, Child ID %d \n" , getppid() , getpid());
    if ( pid < 0)
        return errno ;
    else if ( pid == 0){
        char * argv [] = {"ls", NULL };
        execve ("/bin/ls", argv , NULL );
        perror(NULL);
    }
    else {
        wait( NULL);
        printf("Child %d has finished\n", getpid());
  }

}