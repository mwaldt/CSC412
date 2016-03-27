/* Prints Hello and hello alternatively */ 
/* The number of repetitions is specified by the user */
/* e.g., invoke as: writer 10 */
/* to print Hello and hello ten times each */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   int count; /* number of repetitions */
   int i; /* loop control variable */

   if (argc != 2) 
   {
      printf("usage: writer count\n");
      return -1;
   }
   else count = atoi(argv[1]);

   for (i = 0; i < count; i++) 
   {
      printf("Hello");
      printf("hello");
   }
   return 0; 
}