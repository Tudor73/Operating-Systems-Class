#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

#define MAX_RESOURCES 5
#define NO_THREADS 4
int available_resources = MAX_RESOURCES ;


pthread_mutex_t mtx;


int decrease_count ( int count )
{
      if ( available_resources < count )
          return -1;
      else
      {
          available_resources -= count ;
        printf("Got %d resources %d remaining\n", count, available_resources);
      }
      return 0;
}
int increase_count ( int count )
{
    available_resources += count ;
  printf("Released %d resources %d remaining\n", count, available_resources);
    return 0;
}
void* allocateResources(void * arg)
{
  pthread_mutex_lock(&mtx);

  int* resources = (int *) arg;
  int decrease = decrease_count(*resources);
  if(decrease == -1) 
  {
    printf("No resources available\n");
    return NULL;
  }
  increase_count(*resources);
  pthread_mutex_unlock (& mtx);
  return NULL;

}

int main ()
{


  printf("MAX RESOURCES ");
  printf("%d\n", available_resources);

  pthread_t thread_id[NO_THREADS];

  int resources[NO_THREADS];


  for(int i = 0; i< NO_THREADS; i++)
  {
    resources[i] = rand() % (MAX_RESOURCES-1) + 1;
    pthread_create(&thread_id[i], NULL, allocateResources, &resources[i]);
  } 

  for(int i = 0; i< NO_THREADS; i++)
  {
    pthread_join(thread_id[i], NULL);
  }
  pthread_mutex_destroy (& mtx );



}