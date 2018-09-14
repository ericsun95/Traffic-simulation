#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "matrix.h"

#define WARNING "There is a problem when running your code, check the pointers \n"
/*************************************
 *  malloc the matrix
 * 
**************************************/
int **malloc_matrix(int distance, int lane) {
    int **mat = NULL;      // pointer to the matrix
    //check for the invalid input
    if((distance > 0) && (lane > 0)){
        mat = malloc(lane * sizeof(int *)); //use malloc to allocate memory for the array of pointers
        for(int i =0; i < lane; i++){
        mat[i] = (int*) malloc(sizeof(int) * distance); // use loop to allocate memory for the array of data point
        }
    }

    else{
        printf(WARNING);
        exit(EXIT_FAILURE);
    }
    return mat;
}

/*************************************
 *  free the matrix
 * 
**************************************/
void free_matrix(int distance, int lane, int **a) {

    //check for invalid inputs.
    if((distance > 0) && (lane > 0) && (a != NULL)){
        for(int i = 0; i < distance; i++){
            free(a[i]);  //use loop to free the memory
        }
    }

    else{
        printf(WARNING);
        exit(EXIT_FAILURE);
    }
}

/*************************************
 *  initialize the matrix
 * 
**************************************/

void init_matrix(int distance, int lane, int **a) {

    //check for invalid inputs
    if((distance > 0) && (lane > 0) && (a != NULL))
    {
        //each location has 40% probability to generate a RED citizen

        //set every 20 meter have one traffic light
        for(int i = 0; i < lane; i++) {
            for(int j = 0; j < distance; j++) {
                a[i][j] = 0;
            }
        }
    }
    else{
        printf(WARNING);
        exit(EXIT_FAILURE);
    }
}

/*************************************
 *  print the matrix
 * 
**************************************/
void print_matrix(int distance, int lane, int **a) 
{
    //check for the invalid inputs
    if((distance > 0) && (lane > 0) && (a != NULL)){
        for(int i = 0; i < lane; i++)
        {
            for(int j = 0; j < distance; j++){
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
    }
}
