/*--------------------------------------------------
Project: Algorithms: Design and Analysis, Part 1
File:    merge_sort.c
Author:  Yurii Potsiluienko
Version: 2022-06-05
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Auxiliary functions
void display_array(int *array, int length){
	printf("[ ");
	for (int i = 0; i < length; ++i) printf("%d ", array[i]);
	printf("]\n");
}

// classic recursive merge sort algorithm
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
		int length_left = length - middle_index - length % 2;
		int length_right = length - length_left;
		assert(length_left + length_right == length);
		int *left_subarray = (int *)malloc(sizeof(int) * length_left);
		int i;
		for (i = 0; i < middle_index; ++i) left_subarray[i] = array[i];
		int *right_subarray = (int *)malloc(sizeof(int) * length_right);
		for (i = middle_index; i < length; ++i) right_subarray[i - middle_index] = array[i];
		// recursively sort left and right subarrays
		merge_sort_recursive(left_subarray, length_left);
		merge_sort_recursive(right_subarray, length_right);
		// merge left and right (now sorted) subarrays
		int i_left = 0, i_right = 0;
		for (i = 0; i < length; ++i) {
			if (i_left == length_left) {
				for(int j = i_right; j < length_right; ++j){
					array[i] = right_subarray[j];
					++i;
					++j;
				}
				return;
			} else if (i_right == length_right){
				for(int j = i_left; j < length_left; ++j){
					array[i] = left_subarray[j];
					++i;
					++j;
				}
				return;
			} else {
				if (left_subarray[i_left] <= right_subarray[i_right]) {
					array[i] = left_subarray[i_left];
					++i_left;
				} else {
					array[i] = right_subarray[i_right];
					++i_right;
				}
			}
		}
		free(left_subarray);
		free(right_subarray);
	}
}

int main(){
	int size = 10;
	int lower_limit = 0;
	int upper_limit = 20;
	int my_array[size];
	for (int i = 0; i < size; ++i) my_array[i] = (rand() % (upper_limit - lower_limit + 1)) + lower_limit;
	printf("Unsorted array: ");
	display_array(my_array, size);
	merge_sort_recursive(my_array, size);
	printf("Sorted array: ");
	display_array(my_array, size);
	return 0;
}
