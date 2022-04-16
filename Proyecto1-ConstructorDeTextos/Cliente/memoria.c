#include <stdio.h>

int main() {
  int *numero;

  for (int i = 0; i < 10; i++)
  {
      numero = &i;
      numero+=1;
      printf("El valo de numero es: %d\n", &numero);
  }
  
} 