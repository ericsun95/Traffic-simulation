/*
 *  
 *  Header File:   Gap
 *
 */
#ifndef gap_
#define gap_

#include "globals.h"
// extern int num_light；


void        gap_car_calculation     (int** road, int i, int j, int distance, int** gap_car);

void        gap_light_calculation   (int** road, int i, int j, int *light_location, int** gap_light);

void        all_gap                 (int** road, int lane, int distance, int *light_location, int** gap_car, int** gap_light);


#endif // gap_
