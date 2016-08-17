#include <cs50.h>
#include <stdio.h>

/*
 * mario.c
 *
 * Jaizon Lubaton
 * jahskee@yahoo.com
 *
 * Create a half pyramid 
 *
 */
 
int main(void)
{
    int height = 0;
    
    do
    {
        printf("Height: ");
        height = GetInt();
    }while(height < 0 || height > 23);
    
    // initial number of blocks
    int blocks = 2; 
    
    // compute half pyramid width
    int width = height + 1; 
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j >= (width - blocks))
            {
                printf("#");    
            }else
            {
                printf(" ");  
            }
        }
        printf("\n");  
        blocks++;
    }
}