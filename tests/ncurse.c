#include <stdio.h>
#include <stdlib.h>
int main()
{
  char c;  
c = getc();
	putchar('a');
  while ((c = getchar()) != EOF)
    putchar(c);
  return 0;
}
