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
	FILE* ptr_s;
	FILE* ptr_c;
	char ch;
    time_t t;
    struct tm *tm;
    char fechayhora[100];

	// Opening file in reading mode
	ptr = fopen("test.txt", "r");
	ptr_s = fopen("test.txt", "r");
	ptr_c = fopen("test.txt", "r");
	if (NULL == ptr) {
		printf("file can't be opened \n");
	}

	printf("Press Enter to read the file... \n");

	
	char ch_size;
	ch_size = fgetc(ptr_s);
	int size = 0;

	//largo del archivo
	while (ch_size != EOF)
    {
        ch_size = fgetc(ptr_s);
		size++;
    }


	//Creacion del char
	char ch_aux;
	char file[size+1];
	ch_aux = fgetc(ptr_c);
	int n = 0;

	for (int i = 0; i <= size; i++)
	{
		if (ch_aux == EOF)
		{
			break;
		}
		else{
			file[i] = ch_aux;
			ch_aux = fgetc(ptr_c);
		}
	}
    
	// Printing what is written in file
	// character by character using loop.
	int j = 1;
	while (ch != EOF) {
        char c = getchar();
        if (c==10)
        {
			printf("|--------------------------------------------------------|\n");
			if(j < size)
			{
				printf("%s\n", &file[j]);
			}
			j++;
            ch = fgetc(ptr);
            t=time(NULL);
            tm=localtime(&t);
            strftime(fechayhora, 100, "%d/%m/%Y-%H:%M:%S", tm);
            printf ("Dato: %c, logtime>>> %s\n", ch, fechayhora);
			printf("|--------------------------------------------------------|\n"); 
        }
        
		// Checking if character is not EOF.
		// If it is EOF stop eading.
	} 

	// Closing the file
	fclose(ptr);
	return 0;
}
