/*--------------------------------------------------
Project: Algorithms: Design and Analysis, Part 1
File:    merge_sort.c
Author:  Yurii Potsiluienko
Version: 2022-06-07
--------------------------------------------------
*/

#include "merge_sort.h"
#include <stdio.h>
#include <stdlib.h>

// ============= Auxiliary functions =============
// displays integer array as [ a(1) a(2) ... a(length - 1) ]
static void display_array(int *array, int length){
	printf("[ ");
	for (int i = 0; i < length; ++i) printf("%d ", array[i]);
	printf("]\n");
}

// copies array from start to end (inclusive) into a new dynamically allocated array and returns a pointer to the copy
static int *copy_array(int *array, int start, int end){
	int size = end - start + 1;
	int *copy = (int *)malloc(sizeof(int) * size);
	int i = start;
	int j = 0;
	while(i <= end){
		copy[j] = array[i];
		++i;
		++j;	
	}
	return copy;
}

// merges a1 and a2 into dest in increasing order
static void merge_arrays(int *dest, int size_dest, int *a1, int size_a1, int *a2, int size_a2){
	int i;
	int i_a1 = 0;
	int i_a2 = 0;
	for (i = 0; i < size_dest; ++i){
		if(i_a1 < size_a1 && i_a2 < size_a2){
			if (a1[i_a1] <= a2[i_a2]) {
				dest[i] = a1[i_a1];
				++i_a1;
			} else {
				dest[i] = a2[i_a2];
				++i_a2;
			}	
		} else if (i_a1 == size_a1){
			while(i_a2 < size_a2){
				dest[i] = a2[i_a2];
				++i;
				++i_a2;
			}
			break;
			
		} else {  // if (i_a1 == size_a1)
			while(i_a1 < size_a1){
				dest[i] = a1[i_a1];
				++i;
				++i_a1;
			}
			break;
		}
	}
}
// ===============================================

// classic recursive merge sort algorithm
// time: O(nlogn)
// space: O(n)
void merge_sort_recursive(int *array, int length){
	// base cases
	if (length < 2) return;
	else if (length == 2){
		if (array[0] > array[1]){
			int temp = array[0];
			array[0] = array[1];
			array[1] = temp;
		}
		return;
	} else {
		// create left and right subarrays
		int middle_index = length / 2;
		int length_left = middle_index;
		int length_right = length - length_left;
		int *left_subarray = copy_array(array, 0, middle_index - 1);
		int *right_subarray = copy_array(array, middle_index, length - 1);
		// recursively sort left and right subarrays
		merge_sort_recursive(left_subarray, length_left);
		merge_sort_recursive(right_subarray, length_right);
		// merge left and right (now sorted) subarrays
		merge_arrays(array, length, left_subarray, length_left, right_subarray, length_right);
		free(left_subarray);
		free(right_subarray);
	}
}

int main(){
	printf("Testing merge sort\n");
	int size = 100;
	int lower_limit = 0;
	int upper_limit = 100;
	int my_array[size];
	for (int i = 0; i < size; ++i) my_array[i] = (rand() % (upper_limit - lower_limit + 1)) + lower_limit;
	printf("Unsorted array: ");
	display_array(my_array, size);
	merge_sort_recursive(my_array, size);
	printf("Sorted array:   ");
	display_array(my_array, size);
	return 0;
}
