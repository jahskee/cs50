#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
      


void print_array(int *array, int size);
void print_portion_array(int *array, int low, int high);
void bubble_sort(int* array, int size);
bool binary_search(int key, int* haystack, int low, int high);


int main(){
    int size;
    
    int key=1;
    int haystack[]={6,2,3,1,9,10,15,13,12,17,4,5,29,7,8, 11,14,30,45,2,312,12}; 
	
	size=sizeof(haystack)/sizeof(haystack[0]); 


    print_array(haystack,size);
    bubble_sort(haystack,size);

    printf("search for key = %d in\n", key);
  

    binary_search(key, haystack, 0, size);

    
}



bool binary_search(int key, int* haystack, int low, int high){
    printf("low=%d, high=%d \n", low, high);
      
    print_portion_array(haystack, low, high);
    
    if((high-low)==1){
        if(key==haystack[high-1]){
            return true;
        }
    
        printf("key %d not found\n", key);
        return false;
    }
    
    int mid = (int)(low+high)/2;
    printf("mid = %d+%d/2 = %d index, value = %d\n", low, high, mid, haystack[mid]);
    
    if(key == haystack[mid]){
        printf("key %d found in haystack at index %d.\n", key, mid);
        return true;
    }
    
    //keep searching
    if(key < haystack[mid]){
        //search left
        high = mid;
    }else{
        //search right
        low = mid;
    }
    
    printf("search left, low=%d, high=%d \n", low, high);
    return binary_search(key, haystack, low, high);
  
}

void bubble_sort(int* array, int size){
    for(int j=0; j < size; j++){
        for(int i=0; i < size-1; i++){    
            if(array[i] > array[i+1]){
                int store = array[i];
                array[i] = array[i+1];
                array[i+1] = store;
            }
        }
    }
}


void print_array(int *array, int size){
    for(int i = 0;i < size; i++) printf("%d ",array[i]);
	printf("\n");
}

void print_portion_array(int *array, int low, int high){
    for(int i = low;i < high; i++) printf("%d ",array[i]);
	printf("\n");
}

