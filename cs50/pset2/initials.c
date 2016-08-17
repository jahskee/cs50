#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
* initials.c
*
* Jaizon Lubaton
* jahskee@yahoo.com
*
* Prints out the initials of name
*
*/

#define INTLS_MAX_SIZE 10

int main(void)
{

    // 10 bytes in dynamic heap
    char* initials = malloc(sizeof(char) * INTLS_MAX_SIZE);
    
    string name = GetString();
    if (name[0] == '\0')
    {
        printf("name is blank.\n");
        return 1;
    }

    // initials counter
    int ctr=0;
    
    for (int i = 0, len = strlen(name); i < len; i++)
    {
        // if first char position or previous char is blank, 
        // this char is initial
        if (i == 0 || isblank(name[i - 1]))
        {
            if (isalpha(name[i]))
            {
                initials[ctr] = toupper(name[i]);    
                ctr++;
            }
        }
    }
    printf("%s\n", initials);
    free(initials);
    
}