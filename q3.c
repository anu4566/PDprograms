#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define thread_count 	4
#define ASCIIs		127		//ASCII characters from 0 to 127
#define atmost		1000
  
char letters[atmost+1]; //extra location for '\0'. atmost must be divisible by thread_count
int count[ASCIIs], h;	//h holds the length of the segment
pthread_mutex_t mutex[ASCIIs];
int n=0;

void *task(void* rank);
int main(){
  pthread_t* thread_handles;
  int i ,thread;
  
  for(i =0; i< ASCIIs; i++)
  {
    count[i] =0;
  }
  printf("Enter a line:");
  scanf("%[^\n]%*c", letters);
  
  int length = strlen(letters);
  int remainder = length%thread_count;
  if(remainder != 0)
  { 
    for(i =0;i<thread_count-remainder; i++)
    {
      strcat(letters, " ");
    }
    length = strlen(letters);
  }

  thread_handles = malloc(thread_count*sizeof(pthread_t));
  h = length/thread_count;
  for (i = 0; i < ASCIIs; i++)
  {
   pthread_mutex_init(&mutex[i], NULL);
  }
  for (thread = 0; thread < thread_count; thread++)
  {
   pthread_create(&thread_handles[thread], NULL, task,NULL);
  }
  for (thread = 0; thread < thread_count; thread++)
  {
   pthread_join(thread_handles[thread], NULL);
  }
  pthread_mutex_destroy(mutex);
  free(thread_handles);

  for(i = 33; i < ASCIIs; i++)
  {
   if(count[i] != 0)
   {
    printf("Number of %c is: %d\n", i, count[i]);
   }
  }
  return 0;
}

void *task(void* rank){
 int i, index =0;
 for(i = 0; i < h; i++)
 {
  index = ((int)(letters[n])); 
  pthread_mutex_lock(&mutex[index]);
  (count[index])++;
  ++n;
  pthread_mutex_unlock(&mutex[index]);
 }
 return NULL;  
}

