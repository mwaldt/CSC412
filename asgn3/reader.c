/* Reads characters until EOF from standard input and */
/* displays on screen.  The number of characters per */
/* line is controlled by the defined constant LINELENGTH*/

#include <stdio.h>
#define LINELENGTH 50

int main()
{
   int count; /* number of characters in the line */
   int c; /* input read */

   count = 0; 
   while ((c = getchar())!= EOF) 
   {
      putchar(c); count++;
      if (count == LINELENGTH) 
      {
         putchar('\n'); count = 0;
      }
   }
   if (count > 0) 
      putchar('\n');
   return 0;
}