#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
  char prev = 0;

  while(1)
  {
    char c = getchar();
    printf("Se ha precionado %d\n", c);
  }

  return 0;
}