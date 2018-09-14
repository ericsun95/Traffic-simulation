/*
 *  
 *  Header File:    Global Variables
 *
 */
#ifndef TRAFFIC_LIGHT_H_
#define TRAFFIC_LIGHT_H_

#include "globals.h"

void    initializeLight 	(int distance, int* light_location);

void    traffic_light   	(int t, int* light_condition);

int     pass_or_wait    	(int i,int j, int distance, int** gap_light, int* light_condition);

#endif // MATRIX_H_