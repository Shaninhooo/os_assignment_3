/**
 * Faster parallel mergesort
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "mergesort.h"

void merge(const int leftStart, const int leftEnd, const int rightStart, const int rightEnd) {
    int i = leftStart, j = rightStart, k = leftStart;

    // Copy relevant part into B
    memcpy(B + leftStart, A + leftStart, (rightEnd - leftStart + 1) * sizeof(int));

    while (i <= leftEnd && j <= rightEnd) {
        if (B[i] <= B[j]) A[k++] = B[i++];
        else A[k++] = B[j++];
    }

    if (i <= leftEnd) {
        memcpy(A + k, B + i, (leftEnd - i + 1) * sizeof(int));
    }
}

/* Sequential mergesort */
void my_mergesort(const int left, const int right) {
    if (left < right) {
        const int mid = left + (right - left) / 2;
        my_mergesort(left, mid);
        my_mergesort(mid + 1, right);
        merge(left, mid, mid + 1, right);
    }
}

/* Build argument struct */
struct argument *buildArgs(const int left, const int right, const int level) {
    struct argument *args = malloc(sizeof(struct argument));
    args->left = left;
    args->right = right;
    args->level = level;
    return args;
}

/* Parallel mergesort with adaptive thread spawning */
void *parallel_mergesort(void *arg) {
    struct argument *args = arg;
    const int left = args->left;
    const int right = args->right;
    const int level = args->level;

    if (left >= right) return NULL;

    const int mid = left + (right - left) / 2;
    const int size = right - left + 1;

    // Spawn Next Threads for next level if below cutoff
    if (level < cutoff) {
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

