#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


void divide_sort(int *array,int n); 
void merge(int *array,int *left,int left_ct,int *right,int right_ct); 
void print_array(int *array, int size);


int main() {
	/* Code to test the MergeSort function. */
	
	int array[] = {6,2,3,1,9,10,15,13,12,17,4,5,29,7,8, 11, 14}; // creating an array of integers. 
	int i, size;

    size = sizeof(array)/sizeof(array[0]); 

	
	divide_sort(array,size);

	
	for(i = 0;i < size;i++) printf("%d ",array[i]);
	printf("\n");
	return 0;
}

void divide_sort(int *array,int n) {
    
	int mid,i, *left, *right;
	if(n < 2) return; 

    // find the mid index. 
	mid = n/2;  

	// allocate left and right arrays in heap
	left = (int*)malloc(mid*sizeof(int)); 
	right = (int*)malloc((n- mid)*sizeof(int)); 
	
	for(i = 0;i<mid;i++) left[i] = array[i]; 
	for(i = mid;i<n;i++) right[i-mid] = array[i]; 

	divide_sort(left,mid);  
	divide_sort(right,n-mid);  
	merge(array,left,mid,right,n-mid);  // merge left and right into input array
  
    free(left);
    free(right);
}


void merge(int *array,int *left,int left_ct,int *right,int right_ct) {
	int i,j,k;

	i = 0; j = 0; k =0;

	while(i<left_ct && j< right_ct) {
		if(left[i]  < right[j]) array[k++] = left[i++];
		else array[k++] = right[j++];
	}
	while(i < left_ct) array[k++] = left[i++];
	while(j < right_ct) array[k++] = right[j++];
}

void print_array(int *array, int size){
    for(int i = 0;i < size; i++) printf("%d ",array[i]);
	printf("\n");
}
