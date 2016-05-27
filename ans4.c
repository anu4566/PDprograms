#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
long long int number_in_circle=0 ;
double grabRand();
int main() {
   long long int tosses;
   int thread_count, i;
   double x, y, distance;
   double pi ;
   printf("How many threads? ");
   scanf("%d", &thread_count);
   printf("Enter the number of tosses:");
   scanf("%llu",&tosses);

#  pragma omp parallel for num_threads(thread_count) \
      reduction(+: number_in_circle) private(x, y, distance)
   for (i = 0; i < tosses; i++) {
      x = grabRand(); 
      y = grabRand();
      distance = x*x + y*y;
      if (distance <= 1) {
         number_in_circle += 1;
      }
   }
   pi = 4*number_in_circle/((double)tosses);
   printf("Pi estimation = %.5f\n", pi);
   return 0;
} 
double grabRand() 
  {
  double div = RAND_MAX / 2;
  return -1 + (rand() / div);
  }
