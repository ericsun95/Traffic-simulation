/*
 *  
 *  Header File:    Matrix.h
 *
 *
 */
#ifndef MATRIX_H_
#define MATRIX_H_

int**       malloc_matrix   (int distance, int lane);
void        free_matrix     (int distance, int lane, int **a);
void        init_matrix     (int distance, int lane, int **a);
void        print_matrix    (int distance, int lane, int **a);

#endif // MATRIX_H_