#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#include <time.h>
 
//gcc find_time_md5.c -lcrypto -lssl -lz

char *generateRandomString(int len) {    
    static int randomSeed = 26021967;
    char *possibleChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t stringLength = strlen(possibleChars);        
    char *randomString = NULL;

    srand(time(NULL) * len + ++randomSeed);

    if (len < 1)   len = 1;

    randomString = malloc(sizeof(char) * (len +1));

    if (randomString) {
        short key = 0;

        for (int n = 0;n < len;n++) {            
            key = rand() % stringLength;          
            randomString[n] = possibleChars[key];
        }

        randomString[len] = '\0';

        return randomString;        
    }
    else exit(1);
}
 
int main()
{
    FILE *fptr;
    fptr = fopen("md5_output.txt", "w");
    if(fptr == NULL)
    {
        printf("Error opening the file!\n");
        exit(1);
    }
    unsigned char result[MD5_DIGEST_LENGTH];
    for(int i=1;i<10000;i++)
    {
        const unsigned char *string = generateRandomString(i);
        float t = clock();
        MD5(string, i, result);
        fprintf(fptr, "%d %f\n", i, (clock() - t) / CLOCKS_PER_SEC);
    }
}
