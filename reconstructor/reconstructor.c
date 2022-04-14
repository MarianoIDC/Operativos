#include <stdio.h>
#include <stdlib.h>

// gcc reconstructor.c -o test
// ./test
#define SIZE 50
char* memory;
const char * filename= "reconstructor.txt";

void createMemory(){
   memory = (char*)malloc(SIZE * sizeof(char));
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
void fillMemoryChars(){
    int i;
    if (memory == NULL) {
		printf("Memory not allocated.\n");
		exit(0);
	}
	else {

		// Memory has been successfully allocated
		printf("Memory successfully allocated using malloc.\n");
        memory[0] ='A';
        memory[1] ='B';
        memory[2] ='C';
        memory[3] ='D';
        memory[4] ='E';
        memory[5] ='F';
        memory[6] ='G';
        memory[7] ='H';
        memory[8] ='I';
        memory[9] ='J';
        memory[10] ='K';
        memory[11] ='L';
        memory[12] ='M';
        memory[13] ='N';
        memory[14] ='O';
        memory[15] ='P';
        memory[16] ='Q';
        memory[17] ='R';
        memory[18] ='S';
        memory[19] ='T';
        memory[20] ='U';
        memory[21] ='V';
        memory[22] ='W';
        memory[23] ='X';
        memory[24] ='Y';
        memory[25] ='Z';
        memory[26] ='A';
        memory[27] ='B';
        memory[28] ='C';
        memory[29] ='D';
        memory[30] ='E';
        memory[31] ='F';
        memory[32] ='G';
        memory[33] ='H';
        memory[34] ='I';
        memory[35] ='J';
        memory[36] ='K';
        memory[37] ='L';
        memory[38] ='M';
        memory[39] ='N';
        memory[40] ='O';
        memory[41] ='P';
        memory[42] ='Q';
        memory[43] ='R';
        memory[44] ='S';
        memory[45] ='T';
        memory[46] ='U';
        memory[47] ='V';
        memory[48] ='W';
        memory[49] ='X';

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
            //printf(memory[i]);
			printf("%c, ", memory[i]);
		}
	}

}
void rebuildFile(){
    int i;
    if (memory == NULL) {
		printf("Memory not allocated.\n");
		exit(0);
	}
	else {

	// Print the elements of the array
        
		for (i = 0; i < SIZE; ++i) {
            printf("\n Press ENTER key to Continue\n"); 
            getchar();
            printf("Memory address: 0x%08x with value %c\n", &memory+i,memory[i]);
            FILE *fp = fopen(filename, "ab");
            if(NULL == fp)
            {
                printf("[-]Error opening file.");
                //return 0;
            }
            fputc(memory[i],fp);
            fclose(fp);
            memory[i]=NULL;
            readFile(filename);
            //concatChar(filename,memory[i]);
			//printf("%d, ", memory[i]);
		}
	}

}
int concatChar(const char * filename, char* value){
    /* Create file where data will be stored */
    FILE *fp = fopen(filename, "ab");
    if(NULL == fp)
    {
        printf("[-]Error opening file.");
        return 0;
    }
    fputc(*value,fp);
    fclose(fp);
    return 1;
}
int concatInt(const char * filename, int value){
    /* Create file where data will be stored */
    FILE *fp = fopen(filename, "ab");
    if(NULL == fp)
    {
        printf("[-]Error opening file.");
        return 0;
    }
    char c=value;
    fputc(c,fp);
    fclose(fp);
    return 1;
}
int readFile(const char * filename){
    /* Create file where data will be stored */
    char ch;
    FILE *fp = fopen(filename, "r");
    if(NULL == fp)
    {
        printf("[-]Error opening file.");
        return 0;
    }
    printf("****************************************\n");
    printf("**************NEW FILE******************\n");
    printf("****************************************\n");
    do {
        ch = fgetc(fp);
        printf("%c", ch);
 
        // Checking if character is not EOF.
        // If it is EOF stop eading.
    } while (ch != EOF);
    fclose(fp);
    return 1;
}

int main()
{
    
    //Eliminar archivo 
    remove(filename);
    createMemory();
	fillMemoryChars();
    //printf("Press ENTER key to Continue\n"); 
    //getchar();
    //printMemory();
    //concatChar(filename,'s');
    //concatChar(filename,'a');
    rebuildFile();
    printMemory();

	return 0;
}
