/* COP 3502C Programming Assignment 3 
This program is written by: Heng Hong */ 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//#include "leak_detector_c.h"

typedef struct {
  int x;
  int y;
} Coordinate;

Coordinate myLocation;

Coordinate *ReadData(Coordinate arr[], int n) {

  for (int i = 0; i < n; i++) {   
    scanf("%d %d", &arr[i].x, &arr[i].y);
  }

  return arr;
}

int compareTo(Coordinate *ptrPt1, Coordinate *ptrPt2) {

  // find the distance by using Pythagorean theorem
  int d1 = (pow(myLocation.x - ptrPt1->x, 2) +pow(myLocation.y - ptrPt1->y, 2));
  int d2 = (pow(myLocation.x - ptrPt2->x, 2) +
                  pow(myLocation.y - ptrPt2->y, 2));
  if(d1 != d2) return d1-d2;
  if(ptrPt1->x != ptrPt2->x) return ptrPt1->x - ptrPt2->x;
  if(ptrPt1->y != ptrPt2->y) return ptrPt1->y - ptrPt2->y;
  return 0;
  
}


void insertionSort(Coordinate arr[], int l, int n) {
  int i, j;
  Coordinate item;
  for (i = l +1 ; i <= n; i++) {   
    item = arr[i];
    /* Move elements of arr[0..i-1], that are
      greater than key, to one position ahead
      of their current position */
    for (j = i - 1; j >= l; j--) {
      if (compareTo(&arr[j],&item) > 0)
        arr[j + 1] = arr[j];
      else
        break;
    }
    arr[j + 1] = item;
  }
}

void merge(Coordinate arr[], int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;
  /* create temp arrays */
  Coordinate *L = malloc(n1 * sizeof(Coordinate));
  Coordinate *R = malloc(n2 * sizeof(Coordinate));
  /* Copy data to temp arrays L[] and R[] */
  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];
  /* Merge the temp arrays back into arr[l..r]*/
  i = 0; // Initial index of first subarray
  j = 0; // Initial index of second subarray
  k = l; // Initial index of merged subarray
  while (i < n1 && j < n2) {
    if (compareTo(&L[i], &R[j]) < 0) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }
  /* Copy the remaining elements of L[], if there
     are any */
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }
  /* Copy the remaining elements of R[], if there
     are any */
  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
  free(L);
  free(R);
}


void mergeSort(Coordinate arr[], int l, int r, int t) {
    int n = (r - l);

  if (n <= t) {
    insertionSort(arr, l, r);
  } else if (l < r) {
    // get the mid point
    int m = (l + r) / 2;
    // Sort first and second halves
    mergeSort(arr, l, m, t);
    mergeSort(arr, m + 1, r, t);

    merge(arr, l, m, r);
  }
}

//determine which sort will use by t value
void sort(Coordinate arr[], int n, int t) {
  
    mergeSort(arr, 0, n - 1, t);
}

int binarySearch(Coordinate arr[], Coordinate item, int len) {
  int l = 0, h = len - 1;
  int mid;
  while (l <= h) {
    mid =  (h + l) / 2;

    int distance = compareTo(&item, &arr[mid]);
    // Check if item is present at mid
    if (distance == 0) {
      return mid;
    }
    // If item greater, ignore left half
    else if (distance > 0) {
      l = mid + 1;
    } else {
      h = mid - 1;
    }
  }
  return -1;
}

int main(void) {
  //atexit(report_mem_leak);

  int n, s, t;
  
  Coordinate item;

  //read in first line data
  scanf("%d %d %d %d %d", &myLocation.x, &myLocation.y, &n, &s, &t);
  
    Coordinate *arr = malloc(sizeof(Coordinate) * n);
  // check malloc successful 
  if (arr != NULL) {
    arr = ReadData(arr, n);

     //insertionSort(arr, 0, n);
     //mergeSort(arr, 0, n, t);
     //determine which sort will be use
    sort(arr, n, t);

    // loop print out all sorted data
    for (int i = 0; i < n; i++) {
      printf("%d %d", arr[i].x, arr[i].y);
      if (i != n - 1) {
        printf("\n");
      }
    }

    //BS part
    for (int j = 0; j < s; j++) {
        //read in blue part data
      scanf("%d %d", &item.x, &item.y);
        //get result after call bs
      int res = binarySearch(arr, item, n);
      if (res == -1) {
        printf("\n%d %d not found", item.x, item.y);
      } else {
        printf("\n%d %d found at rank %d", item.x, item.y, res + 1);
      }
    }
    printf("\n");
    free(arr);
  }
  
  return 0;
}
