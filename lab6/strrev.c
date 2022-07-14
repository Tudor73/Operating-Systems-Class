#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

void *reverse_string(void * arg)
{
    char* argString = (char *)arg;

    char* start = argString;
    char* end = start + strlen(argString) -1;
    char temp;
    while (end > start )
    {
        temp = *start;
        *start = *end;
        *end = temp;

        start ++;
        end--;
    }
    printf("%s\n", argString);
    return NULL;
}

int main(int argc, char*argv[]) 
{
    pthread_t thread_id ;
    pthread_create(&thread_id, NULL, reverse_string, argv[1]);
    if ( pthread_join (thread_id , NULL )) {
        perror (NULL);
        return errno ;
    }

    return 0;
}