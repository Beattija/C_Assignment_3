/*
 * ASSIGNMENT # 3 - Part 2 - SORTING ALGORITHM COMPARISON
 * "Manuel Sanchez Moyano" <sancmanu@sheridan.desire2learn.com> 
 * "Jason Beattie" <beattija@sheridan.desire2learn.com> 
 * 
----------------------------------------------------------------------
 */

/* 
 * File:   main.c
 * Author: Manuel Sanchez <sancmanu@sheridan.desire2learn.com>
 * 
 *
 * Created on July 18, 2020, 12:04 a.m.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Input and output file names list
#define INPUT_FILE                  "test_dat.txt"
#define OUT_SELECTION_SORT          "G1sorted.txt"
#define OUT_BUBBLE_SORT             "G2sorted.txt"
#define OUT_QUICK_SORT              "G3sorted.txt"
#define OUT_SELECTION_SORT_RANDOM   "G1random.txt"
#define OUT_BUBBLE_SORT_RANDOM      "G2random.txt"
#define OUT_QUICK_SORT_RANDOM       "G3random.txt"

//Define maximum length for arrays
#define SIZE 10000

//Implement Bubble Sort
void bubbleSort(int arr[], int);

//Implement Selection Sort
void selectionSort(int arr[], int);

//Implement Quick Sort
void quickSort(int[], int, int);

//Implement Partition method for Quick Sort
int partition(int[], int, int);

//Save array content into a file
void write_out(int[], size_t, const char*);

//Read from file and store in array
void read_in(int[]);

//Implement algorithm to swap array elements
void swap(int*, int*);

//Perform algorithm comparison between Bubble, Selection and Quick Sort
//using random numbers
void random_Numbers_Measurement();

//Perform algorithm comparison between Bubble, Selection and Quick Sort
//using a file with numbers
void file_Numbers_Measurement();

//Time measurement variables
clock_t start, end;
double timeElapsed;

int main() {
    
    printf("Timings taken sorting %d random numbers: \n", SIZE);
    random_Numbers_Measurement();
    
    printf("\n");
    
    printf("Timings taken sorting %d numbers from a file: \n", SIZE);
    file_Numbers_Measurement();
    
    return (EXIT_SUCCESS);
}

void random_Numbers_Measurement() {
    int arr[SIZE];
    
    for (int i = 0; i < SIZE; i++) {
            arr[i] = rand() % SIZE;
    }

//    write_out(arr, SIZE, "random_test_dat.txt");

    //Bubble Sort
    start = clock();
    bubbleSort(arr, SIZE);
    end = clock();

    timeElapsed = ((double) (end - start) / CLOCKS_PER_SEC);
    printf("Time in seconds taken by Bubble sort: %f\n", timeElapsed);
    timeElapsed = 0.0;

    write_out(arr, SIZE, OUT_BUBBLE_SORT_RANDOM);

    //Selection Sort
    start = clock();
    selectionSort(arr, SIZE);
    end = clock();

    timeElapsed = ((double) (end - start) / CLOCKS_PER_SEC);
    printf("Time in seconds taken by Selection sort: %f\n", timeElapsed);
    timeElapsed = 0.0;

    write_out(arr, SIZE, OUT_SELECTION_SORT_RANDOM);

    //Quick Sort
    start = clock();
    quickSort(arr, 0, SIZE - 1);
    end = clock();

    timeElapsed = ((double) (end - start) / CLOCKS_PER_SEC);
    printf("Time in seconds taken by Quick sort: %f\n", timeElapsed);
    timeElapsed = 0.0;

    write_out(arr, SIZE, OUT_QUICK_SORT_RANDOM);
}

void file_Numbers_Measurement() {
    int arr[SIZE];

    //Bubble Sort
    read_in(arr);
    start = clock();
    bubbleSort(arr, SIZE);
    end = clock();

    timeElapsed = ((double) (end - start) / CLOCKS_PER_SEC);
    printf("Time in seconds taken by Bubble sort: %f\n", timeElapsed);
    timeElapsed = 0.0;

    write_out(arr, SIZE, OUT_BUBBLE_SORT);

    //Selection Sort
    read_in(arr);
    start = clock();
    selectionSort(arr, SIZE);
    end = clock();

    timeElapsed = ((double) (end - start) / CLOCKS_PER_SEC);
    printf("Time in seconds taken by Selection sort: %f\n", timeElapsed);
    timeElapsed = 0.0;

    write_out(arr, SIZE, OUT_SELECTION_SORT);

    //Quick Sort
    read_in(arr);
    start = clock();
    quickSort(arr, 0, SIZE - 1);
    end = clock();

    timeElapsed = ((double) (end - start) / CLOCKS_PER_SEC);
    printf("Time in seconds taken by Quick sort: %f\n", timeElapsed);
    timeElapsed = 0.0;

    write_out(arr, SIZE, OUT_QUICK_SORT);
}

void bubbleSort(int arr[], int length) {
    size_t i, j;

    for (i = 1; i < length; i++) {
        for (j = 0; j < length - 1; j++) {

            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void selectionSort(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        int min = i;

        for (int j = i + 1; j < length; j++) {

            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        swap(&arr[min], &arr[i]);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // pivot 
    int i = low; // Index of smaller element 

    for (int j = low; j <= high - 1; j++) {

        // If current element is smaller than the pivot 
        if (arr[j] <= pivot) {
            swap(&arr[i], &arr[j]);
            i++; // increment index of smaller element 
        }
    }
    swap(&arr[i], &arr[high]);
    
    return i;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void write_out(int arr[], size_t size, const char* fileName) {
    //write to a file
    FILE *fwp;
    if ((fwp = fopen(fileName, "w")) == NULL) {
        perror("Could not open the file\n");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        fprintf(fwp, "%d\n", arr[i]);
    }
    fclose(fwp);
}

void read_in(int arr[]) {
    //Read from file
    FILE *fp;
    fp = fopen(INPUT_FILE, "r");
    if (fp == NULL) {
        printf("Error opening file %s", INPUT_FILE);
        exit(1);
    }

    //create array size according to user input and read values into array
    for (int i = 0; i < SIZE; i++) {
        fscanf(fp, "%d", &arr[i]);
    }
    fclose(fp);
}

void swap(int* a, int* b) {
    int tmp = *b;
    *b = *a;
    *a = tmp;
}
