#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypes for the functions
void findChecksum(int, unsigned int long *, char *);
void readFile(char *, int);
unsigned int long findBitMask(int, char *);

// Function to read in a file and get the checksum value and size
void readFile(char * file, int checkSum)
{
    FILE * input;

    int length = checkSum / 8 + 1;
    int count = 0;
    int value = 0;

    // reserve memory for checksum variable and initialize it to 0
    unsigned int long * checksum = (unsigned int long *) calloc(1, sizeof(unsigned int long));
    
    // reserve memory for the file string
    char * characters = (char *) malloc(sizeof(char) * length);

    input = fopen(file, "r");

    int i = 0;
    int j = 0;
    int k = 0;

    // Primary loop to get checksum and count how many characters are in the input file
    while (value != EOF)
    {
        // if there is only 1 character left in the word
        if (length - i == 1)
        {
            // set the null terminator
            characters[i] = '\0';
            printf("%s", characters);

            // Call function to calculate the checksum
            findChecksum(checkSum, checksum, characters);
            j++;  
            i = 0;

            // Format the string to be 80 characters by creating a newline when length is equal to 80
            if (j * (length - 1) == 80)
                printf("\n");
        }

    else
    {
        // read in number of characters from file
        value = fgetc(input);

        if (value == EOF)
        {
            if (checkSum == 16 || checkSum == 32) 
            {
                if (length - i != 1 && length - i != length) 
                {
                    k = 0;

                    while (length - i != 1 && length - i != length) 
                    {
                        characters[i] = 'X';
                        i++;
                        k++;
                    }

                    characters[i] = '\0';

                    printf("%s", characters);

                    findChecksum(checkSum, checksum, characters);

                    j++;
                    count += k - 1;
                    i = 0;

                    if (j * (length - 1 == 80))
                        printf("\n");
                    }

                    else break;
                }

                else break;
            }

            else
                characters[i] = value;
            
            count++;
            i++;
        }
    }

    fclose(input);
    printf("\n");

    printf("%2d bit checksum is %8lx for all %4d chars\n", checkSum, *checksum, count);
}

void findChecksum(int checkSum, unsigned int long * checksum, char * characters) 
{
    unsigned int long bits;

    bits = findBitMask(checkSum, characters);

    * checksum = bits + * checksum;
    * checksum = * checksum << (64 - checkSum);
    * checksum = * checksum >> (64 - checkSum);
}

unsigned int long findBitMask(int checkSum, char * characters) 
{
    int i = 0;

    unsigned int long bits;

    bits = characters[i];
    checkSum -= 8;

    while (checkSum != 0) 
    {
        bits = (bits << 8) + characters[i + 1];
        checkSum -= 8;
        i++;
    }

    return bits;
}

int main(int argc, char * argv[])
{
    char * file = (char *) malloc(sizeof(char) * 30);
    int checkSum;

    strcpy(file, argv[1]);

    checkSum = atoi(argv[2]);

    if (checkSum != 8 && checkSum != 16 && checkSum != 32) 
    {
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
    }

    readFile(file, checkSum);

    getchar();
    getchar();
    return 0;
}