/**
 * Faster parallel mergesort
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mergesort.h"

#define MAX_LEVEL 4              // Max recursion depth for threads
#define MIN_SIZE_FOR_THREAD 100000  // Only create threads for big enough subarrays

int *A;
int *B;

struct argument {
    int left;
    int right;
    int level;
};

/* Merge using memcpy for the remaining elements */
void merge(int leftstart, int leftend, int rightstart, int rightend) {
    int i = leftstart;
    int j = rightstart;
    int k = leftstart;

    // Copy segment of A into B
    for (int x = leftstart; x <= rightend; x++)
        B[x] = A[x];

    while (i <= leftend && j <= rightend) {
        if (B[i] <= B[j])
            A[k++] = B[i++];
        else
            A[k++] = B[j++];
    }

    // Copy remaining left half
    if (i <= leftend)
        memcpy(A + k, B + i, (leftend - i + 1) * sizeof(int));
    // No need to copy right half: already in place
}

/* Sequential mergesort */
void my_mergesort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        my_mergesort(left, mid);
        my_mergesort(mid + 1, right);
        merge(left, mid, mid + 1, right);
    }
}

/* Build argument struct */
struct argument *buildArgs(int left, int right, int level) {
    struct argument *args = malloc(sizeof(struct argument));
    args->left = left;
    args->right = right;
    args->level = level;
    return args;
}

/* Parallel mergesort with adaptive thread spawning */
void *parallel_mergesort(void *arg) {
    struct argument *args = (struct argument *)arg;
    int left = args->left;
    int right = args->right;
    int level = args->level;
    free(args);

    if (left >= right) return NULL;

    int mid = left + (right - left) / 2;
    int size = right - left + 1;

    // Only spawn threads for large subarrays and shallow recursion
    if (level < MAX_LEVEL && size > MIN_SIZE_FOR_THREAD) {
        pthread_t t1, t2;

        pthread_create(&t1, NULL, parallel_mergesort, buildArgs(left, mid, level + 1));
        pthread_create(&t2, NULL, parallel_mergesort, buildArgs(mid + 1, right, level + 1));

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
    } else {
        my_mergesort(left, mid);
        my_mergesort(mid + 1, right);
    }

    merge(left, mid, mid + 1, right);
    return NULL;
}



///**
//  * This file implements parallel mergesort.
//  */

// #include <stdio.h>
// #include <string.h> /* for memcpy */
// #include <stdlib.h> /* for malloc */
// #include "mergesort.h"
// #define MAX_LEVEL 3

// int *A;
// int *B;

// /* this function will be called by mergesort() and also by parallel_mergesort(). */
// // Normal Merge Sort algo
// void merge(int leftstart, int leftend, int rightstart, int rightend) {
// 	int i = leftstart;
// 	int j = rightstart;
// 	int k = leftstart;
// 	int x = 0;
// 	// Copy the relevant part of A into B
// 	for (x = leftstart; x <= rightend; x++) {
// 		B[x] = A[x];
// 	}

// 	// Merge from B back into A
// 	while (i <= leftend && j <= rightend) {
// 		if (B[i] <= B[j]) {
// 			A[k++] = B[i++];
// 		} else {
// 			A[k++] = B[j++];
// 		}
// 	}

// 	// Copy remaining elements from the left half, if any
// 	while (i <= leftend) {
// 		A[k++] = B[i++];
// 	}
// }


// /* this function will be called by parallel_mergesort() as its base case. */
// void my_mergesort(int left, int right){
// 	if (left < right) {

// 		// Calculate the midpoint
// 		int mid = left + (right - left) / 2;

// 		// Sort first and second halves
// 		my_mergesort(left, mid);
// 		my_mergesort(mid + 1, right);

// 		// Merge the sorted halves
// 		merge(left, mid, mid + 1, right);
// 	}
// }

// /* this function will be called by the testing program. */
// void * parallel_mergesort(void *arg){
// 	struct argument *args = (struct argument *)arg;
// 	int left = args->left;
// 	int right = args->right;
// 	int level = args->level;

// 	if (left < right) {
// 		int mid = left + (right - left) / 2;

// 		if (level < MAX_LEVEL) {
// 			pthread_t t1, t2;
// 			struct argument *leftArgs = buildArgs(left, mid, level + 1);
// 			struct argument *rightArgs = buildArgs(mid + 1, right, level + 1);

// 			pthread_create(&t1, NULL, parallel_mergesort, leftArgs);
// 			pthread_create(&t2, NULL, parallel_mergesort, rightArgs);

// 			pthread_join(t1, NULL);
// 			pthread_join(t2, NULL);

// 			free(leftArgs);
// 			free(rightArgs);
// 		} else {
// 			// beyond threading depth — do normal mergesort
// 			my_mergesort(left, mid);
// 			my_mergesort(mid + 1, right);
// 		}
// 		merge(left, mid, mid + 1, right);
// 	}
// 	return NULL;
// }

// /* we build the argument for the parallel_mergesort function. */
// struct argument *buildArgs(int left, int right, int level) {
// 	struct argument *args = malloc(sizeof(struct argument));
// 	args->left = left;
// 	args->right = right;
// 	args->level = level;
// 	return args;
// }

