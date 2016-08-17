
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
int isFileExist(const char* filename)
{
  FILE* fptr = fopen(filename, "r");
  if (fptr != NULL)
  {
    fclose(fptr);
    printf("File exists\n");
    return 1;
  }
  printf("File doesnt exist\n");
  return 0;
}

int main(int argc, char *argv[])
{
    char* file = "/home/ubuntu/workspace/pset6/public/hello.php";
    if(isFileExist(file)!=0){
        printf("\nit exist\n");    
    }
    
}