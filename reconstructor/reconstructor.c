#include <stdio.h>
#include <stdlib.h>

// gcc reconstructor.c -o test
// ./test
#define SIZE 50
int* memory;
const char * filename= "reconstructor.txt";

void createMemory(){
   memory = (int*)malloc(SIZE * sizeof(int));
}

void fillMemory(){
    int i;
    if (memory == NULL) {
		printf("Memory not allocated.\n");
		exit(0);
	}
	else {

		// Memory has been successfully allocated
		printf("Memory successfully allocated using malloc.\n");

		// Get the elements of the array
		for (i = 0; i < SIZE; ++i) {
			memory[i] = i + 1;
		}
	}

}

void printMemory(){
    int i;
    if (memory == NULL) {
		printf("Memory not allocated.\n");
		exit(0);
	}
	else {

	// Print the elements of the array
		printf("The elements of the array are: ");
		for (i = 0; i < SIZE; ++i) {
			printf("%d, ", memory[i]);
		}
	}

}


int main()
{
    
    //Eliminar archivo 
    remove(filename);
    createMemory();
	fillMemory();
    printMemory();

	return 0;
}
