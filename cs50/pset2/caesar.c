#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*
* caesar.c
*
* Jaizon Lubaton
* jahskee@yahoo.com
*
* Caesar cipher demo
*
*/

int main(int argc, char *argv[])
{
    // 1. get the k value
    if (argc != 2)
    { 
        printf("error #1: caesar requires only 1 argument\n");
        return 1;
    }
    
    // make sure input string are of integer format
    string numArg = argv[1];
    for (int i = 0, len = strlen(numArg); i < len; i++)
    {
        if (!isdigit(numArg[i]))
        {
            printf("error #2: \"%s\" cannot be parsed to integer.\n", numArg);
            return 2; 
        }
    }
    int k = atoi(numArg);

    // 2. get the plain text
    string text;
    text = GetString();
    
   // text = "Be sure to drink your Ovaltine";
    int len = strlen(text);
    char* cipher = malloc(sizeof(char) * len);
    
  
    for (int i = 0; i < len; i++)
    {   
        
        if (!isalpha(text[i]))
        {
            cipher[i] = text[i];        
        }else
        {
            int pkey = ((int) tolower(text[i]) - (int) 'a') + k;
            if (pkey >= 26)
            {
                pkey = pkey % 26;  
            }
           
            cipher[i] = ((int) 'a') + pkey; 
            if (isupper(text[i]))
            {
                cipher[i] = toupper(cipher[i]);
            }
            // disabled debugging code below
            // printf("%c = %i = %c\n",text[i], pkey, cipher[i]); 
            
        }
    }
    
    printf("%s\n", cipher);
    free(cipher);
}