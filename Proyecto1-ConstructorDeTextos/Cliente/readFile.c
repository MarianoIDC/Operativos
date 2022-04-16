// C program to implement
// the above approach
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Driver code
int main()
{
	FILE* ptr;
	char ch;
    time_t t;
    struct tm *tm;
    char fechayhora[100];

	// Opening file in reading mode
	ptr = fopen("test.txt", "r");

	if (NULL == ptr) {
		printf("file can't be opened \n");
	}

	printf("Press Enter to read the file... \n");

	// Printing what is written in file
	// character by character using loop.
	do {
        char c = getchar();
        if (c==10)
        {
            ch = fgetc(ptr);
            t=time(NULL);
            tm=localtime(&t);
            strftime(fechayhora, 100, "%d/%m/%Y-%H:%M:%S", tm);
            printf ("Dato: %c, logtime>>> %s\n", ch, fechayhora);

            
        }
        
		// Checking if character is not EOF.
		// If it is EOF stop eading.
	} while (ch != EOF);

	// Closing the file
	fclose(ptr);
	return 0;
}
