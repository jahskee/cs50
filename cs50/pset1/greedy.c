#include <cs50.h>
#include <stdio.h>
#include <math.h>

/*
 * greedy.c
 * 
 * Jaizon Lubaton
 * jahskee@yahoo.com
 * 
 * Compute number of coins as change.
 */

int main(void)
{
    
    int coins25 = 0, coins10 = 0, coins5 =0, coins1 = 0;
    
    float change = 0;
    int changeCents = 0;
    
    do
    {
        printf("How much change is owed?\n");
        change = GetFloat();
    }while(change < 0);
    
    // due to float imprecision, convert monetary value to cents..
    changeCents = round(change * 100);
 
    
    coins25 = (int) (changeCents) / 25;
    float modulo = fmod(changeCents,25);
    
    // get 10 cent coins
    if (modulo != 0)
    {
        coins10 = (int) (modulo / 10);
        modulo = fmod(modulo, 10);
    }
    
    // get 5 cent coins
    if (modulo != 0)
    {
        coins5 = (int) (modulo / 5);
        modulo = fmod(modulo, 5);
    }
    
    // get 1 cent coins
    if (modulo != 0)
    {
        coins1 = (int) (modulo);
    }

    // printf("coins25 = %i, coins10 = %i, coins5 = %i, coins1 = %i\n", 
    // coins25, coins10, coins5, coins1);
    int totalCoins = coins25 + coins10 + coins5 + coins1;
    printf("%i\n",totalCoins);
}