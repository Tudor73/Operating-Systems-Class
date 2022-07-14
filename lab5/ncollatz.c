#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char * argv[]) 
{
    int shm_fd;
    int *memory;
    int page_size = getpagesize();
    int size = (argc - 1)* page_size * sizeof(int);
    char shm_name[] = "zona";
    if(argc == 1) 
        exit(-1);
    
    shm_fd = shm_open(shm_name, O_RDWR| O_CREAT, S_IRUSR | S_IWUSR);
    if(shm_fd == -1) {
        perror("shm");
        exit(-1);
    }
    if(ftruncate(shm_fd, size) == -1) {
        perror("trunchiere");
        exit(-1);
    }
    printf("Starting parent %d \n", getpid());
    for(int i = 0; i< argc-1; i++ ){
        int n = atoi(argv[i+1]);
        int pid = fork();
        if(pid < 0 )
        {
            perror("eroare creare copil");
            exit(-1); 
        }
        else if(pid == 0) {
            int *ptr;
            int entry_size = page_size * sizeof(int);
            int j = 0;
            ptr = mmap(NULL, entry_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, i *entry_size );
            if (ptr == MAP_FAILED) 
            {
                perror("mapare zona");
                exit(-1);
            }
            memcpy(ptr + j, &n,sizeof n);
             while(n != 1) {
                if (n % 2 == 0)
                    n = n/2;
                else
                    n = 3*n + 1;
                j++;
                memcpy(ptr + j, &n,sizeof n);
            }
            printf("Done parent %d Me %d has finished\n",getppid(), getpid());
            exit(0);
        }
    }
    for(int i = 0; i< argc-1; i++) 
        wait(NULL);


    for(int i = 0; i< argc-1; i++) 
    {
        int entry_size = page_size * sizeof(int);
            memory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, i*entry_size);
            int *head = memory;
            if(memory == MAP_FAILED) 
            {
                perror("mapare zona");
                exit(-1);
            }
            int x = *memory;
            printf("%d: ", x);
            while(x != 1) {
                memory++;
                x = *memory;
                printf("%d ", x);
            }
            if(munmap(head, size) == -1) {
                perror("UNLINK");
                exit(-1);
        }
        printf("\n");
    }
    
    if(shm_unlink(shm_name) == -1){
        perror("Unlink");
        exit(-1);
    }
    printf("Done parent %d Me %d has finished\n",getppid(), getpid());
}