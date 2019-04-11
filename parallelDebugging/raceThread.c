// Example borrowed from M. Golebiewski,
// https://confluence.csiro.au/display/SC/Frequent+parallel+programming+errors

#include "omp.h"
#include "stdio.h"

int main() 
{
  int n = 20;
  int a = 0;
  int i;

  // form a team of threads and distribute the loop repetitions among them
   #pragma omp parallel for default(shared)
   for (i = 0; i < n; i++) {
     a += 1;
   }
   // the value of a here may be anything between 1 and n

   printf("The value of a is %d \n", a);
   return 0;
}
