#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


/*
* vigenere.c
*
* Jaizon Lubaton
* jahskee@yahoo.com
*
* Vigenere cipher - problem set 02
*
*/

int main(int argc, char *argv[])
{
    // 1. get the k value
    if (argc != 2)
    { 
        printf("error #1: vigenere requires only 1 argument\n");
        return 1;
    }
    
    
    char* keytext = argv[1];
    for (int i=0, len = strlen(keytext); i < len; i++)
    {
        if (!isalpha(keytext[i]))
        {
            printf("error #2: vigenere requires alphabet only argument\n");
            return 1;
        }
        
    }
    
    // 3. get the plain text 
    string ptext;
    
    ptext = GetString();
    
    int len = strlen(ptext);
    char* cipher = malloc(sizeof(char) * len);
    char currkey;
    int shift;

    int keylen = strlen(keytext);
    int keyindex = 0;
    
    for (int i=0; i < len; i++)
    {
        if (!isalpha(ptext[i]))
        {
            cipher[i] = ptext[i];        
        }else
        {
            // rotate current key
            currkey = keytext[keyindex];
            shift = (int) tolower(currkey) - (int) 'a';
            int pkey = ((int) tolower(ptext[i]) - (int) 'a') + shift;
            
            if (pkey >= 26)
            {
                pkey = pkey % 26;  
            }
            cipher[i] = ((int) 'a') + pkey; 
            
            if (isupper(ptext[i]))
            {
                cipher[i] = toupper(cipher[i]);
            }
            
            keyindex = (keyindex < keylen - 1 ? keyindex + 1: 0);
            
        }
    }
    
    printf("%s\n", cipher);
    free(cipher);
}
