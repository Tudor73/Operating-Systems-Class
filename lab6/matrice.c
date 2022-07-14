#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

int n = 2, m =2;
int A[2][2] = {{1,2},{3,4}};
int B[2][2] = {{1,1},{2,2}};
int C[2][2];


struct Coordinate{
    int x;
    int y;
} poz;

void *multiply(void * arg)
{
    struct Coordinate *poz = (struct Coordinate*) arg;
    int x = poz->x ;
    int y = poz->y;
    int s = 0;
    for(int i = 0; i< n; i++)
    {
      s = s + A[x][i] * B[i][y];
    }
    C[x][y] = s;
    return NULL;
}

int main(int argc, char*argv[]) 
{
    pthread_t thread_id[4][4] ;

    struct Coordinate pozitii[2][2];
    for(int i = 0; i < n; i++) {
        for(int j = 0;j< m; j++){
            pozitii[i][j].x = i;
            pozitii[i][j].y = j;
            if(pthread_create(&thread_id[i][j], NULL, multiply, &pozitii[i][j])){
              perror (NULL);
              return errno ;
            };
        }     
    }
    for(int i =0 ;i<n; i++) {
      for(int j = 0; j< m; j++)
      {
        if ( pthread_join ( thread_id[i][j], NULL )) {
              perror (NULL);
              return errno ;
            }
      }
    }

    for(int i = 0; i< n; i++)
    {
      for(int j = 0; j< m; j++) {
        printf("%d ", C[i][j]);
      }
    }


    return 0;
}