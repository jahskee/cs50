/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */
 
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dictionary.h"

typedef struct node{
  char* word;
  struct node* next;
}node;

int word_count;

node *hashT[HT_SIZE];

int hash(const char* key);
int hash2(const char* key);
/**
 * Returns true if word is in dictionary else false. m,
 */
bool check(const char* word)
{
    unsigned int hv = hash(word);
    node* htnode = hashT[hv];
    
   while(htnode != NULL) 
    {
        if (strcasecmp(word, htnode->word) == 0)
        {
	        return true;
        }
        htnode = htnode->next;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
// get dictionary from text file
bool load(const char *dictionary)
{
    FILE *fp = NULL;
    int hv;
 
    for (int i = 0; i < HT_SIZE; i++) 
    {
        hashT[i] = NULL;
    }

    if (!(fp = fopen(dictionary, "r")))
    {
        return false;
    }
  
    char word[LENGTH+1];
    while (fscanf(fp,"%s\n",word) != EOF)
    {
        node *hnode = malloc(sizeof(node));
        hnode->word = malloc(strlen(word) +1);
        strcpy(hnode->word,word);
    
        hv = hash(word);
  
        word_count++;
    
    if(hashT[hv] == NULL)
    {
    	hashT[hv] = hnode;
	    hnode->next = NULL;
    }
    else 
    {
	    hnode->next = hashT[hv];
	    hashT[hv] = hnode;
    }
  }
  
  return true;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return word_count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    node* delnode=NULL;
    for(int i=0; i < HT_SIZE; i++){
        //inspect htnode
        node* htnode = hashT[i];
        if(htnode!=NULL){
           
           while(htnode->next!=NULL){
              delnode = htnode;
              htnode = htnode->next;
              
              free(delnode->word);
	          free(delnode);
              
           }
           free(htnode->word);
	       free(htnode);
           hashT[i]=NULL;       
        }
    }
   
    return true;
}

//  get the hash value
int hash(const char *word) 
{
    int len = strlen(word);
    int hash = 0;

    for(int i = 0; i < len; i++){
        int x = word[i];
        if (x > 64 && x < 91)
        {
            hash += word[i] + 32;
        }
        else
        {
            hash += word[i];
        }
    }
    return hash % HT_SIZE; 
}


int hash2(const char* key) {
	int hash = 0;
	int len = strlen(key);
	
	for(int i=0; i<len; i++) {
		hash = hash*3 + (hash << 16) + (hash<<13)+ key[i]+1;	
	}
		
	hash = hash % HT_SIZE;	
	return hash;
}


void viewHashTable(){
     
    int used_bucket=0;
    int unused_bucket=0;
    int collisions=0;
    for(int i=0; i < HT_SIZE; i++){
      
        //inspect htnode
        node* htnode = hashT[i];
        if(htnode!=NULL){
           used_bucket++;
           
           while(htnode->next!=NULL){
      
              htnode = htnode->next;
              collisions++;
           }
           
    
        }
    }
    unused_bucket = HT_SIZE-used_bucket;
    printf("\nused bucket: %i, unused bucket: %i, collisions: %i\n",used_bucket, unused_bucket, collisions);
}


