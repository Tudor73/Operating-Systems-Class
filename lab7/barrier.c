#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>


#define NO_THREADS 5

sem_t sem ;
pthread_mutex_t mtx;
int threadsAtBarrier = 0;


void barrier_point()
{
  pthread_mutex_lock(&mtx);
  threadsAtBarrier++;
  pthread_mutex_unlock(& mtx);

  if(threadsAtBarrier == NO_THREADS)
  {
    for(int i = 1; i< threadsAtBarrier; i++) 
    {
      sem_post(&sem);
    }
    return;
  }
  else
    sem_wait(&sem);
  return;
}

void* tfun ( void * v )
{
    int* tid = (int *) v ;
    printf ("%d reached the barrier\n" , * tid );
    barrier_point();
    printf ("%d passed the barrier\n" , *tid );
    return NULL;
}


int main ()
{
  sem_init(&sem, 0,0);
  pthread_t thread_id[NO_THREADS];
  int ids[NO_THREADS];

  for(int i = 0; i< NO_THREADS; i++) 
  {
    ids[i] = i;
    pthread_create(&thread_id[i], NULL, tfun, &ids[i]);
  }
  for(int j = 0; j< NO_THREADS; j++)
  {
    pthread_join(thread_id[j], NULL);
  }

  pthread_mutex_destroy (& mtx );
  sem_destroy (& sem );

}