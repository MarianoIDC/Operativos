#include <stdio.h>

int main()
{
    char *filename = "base64.txt";
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    // reading line by line, max 256 bytes
    const unsigned MAX_LENGTH = 130000;
    char buffer[MAX_LENGTH];

    while (fgets(buffer, MAX_LENGTH, fp))
        //printf("%s", buffer);
    printf(buffer);
    // close the file
    fclose(fp);

    return 0;
}