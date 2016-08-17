/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdint.h>


typedef uint8_t BYTE;


int main(void)
{   
    FILE* file = fopen("card.raw", "r");
    
    // check file permission
    if (file == NULL)
    {
        fclose(file); 
        printf("Fatal error cannot recoover file from card.raw \n");
        return 1;
    }

    // ctr
    int ctr = 0; 
   
    
    BYTE buffer[512];
   
    // 3-digit decimal number from 000 on up
    char lname[10]; 
   
    // temporary file output
    FILE* temp = NULL; 
    
    
    
    // infinite loop  until end of file
    while (!feof(file))
    {
       
        // check signature sequence
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // if exist, close file
            if (temp != NULL)
            {
                fclose(temp);
                
            }
            
            // label the files with three digits
            sprintf(lname, "%03d.jpg", ctr);
            
            
            temp = fopen(lname, "w");
            ctr++;
            
            // write buffer to file
            fwrite(buffer, sizeof(buffer), 1, temp);
        }
        else if (ctr > 0)
        {
            // jpeg to temp 
            fwrite(buffer, sizeof(buffer), 1, temp);            
            
        }
        fread(buffer, sizeof(buffer), 1, file);
        
    }
  
    
    // close the file
    fclose(file);

    // that's all folks
    return 0;
}