#include <stdio.h>
#include <cs50.h>

/*
 * water.c
 * 
 * Jaizon Lubaton
 * jahskee@yahoo.com
 * 
 * Compute number of bottles.
 */


/* computations: 
     1.5 gal water/min 
            1 gal = 128 oz.
     1.5gal x 128 oz = 192 oz /min 
            typical 1 bottle = 16 oz.
     =12 bottles /min         
*/
int main(void)
{
    
    int mins=0, bottles = 0;
    
    printf("minutes: ");
    mins = GetInt();
    
    bottles = 12 * mins;
    
    printf("bottles: %d \n", bottles);
}