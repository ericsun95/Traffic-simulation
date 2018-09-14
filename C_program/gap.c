#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "globals.h"
#include "gap.h"

/*************************************
 * calculate the distance between 
 * the car and its front car
**************************************/

void gap_car_calculation(int** road, int i, int j, int distance, int** gap_car)
{
    int w = 0;
    //printf("%d\n", distance);
    if(j == distance - 1)
    {
        gap_car[i][j] = 1000;
    }
    else
    {
        for(int k = j + 1; k < distance; k++)
        {
            if(road[i][k] >= 1)
            {
                gap_car[i][j] = k - j; 
                //printf("gap_car = %d\n", gap_car[i][j]);
                break;
            }
            else
            {
                w ++;
                if( w == distance - j - 1)
                {
                    gap_car[i][j] = 1000;
                    printf("no car in front, gap car = %d\n", gap_car[i][j]);
                }
            }
        }
    }
}

/*************************************
 * calculate the distance between 
 * the car and its front light
**************************************/

void gap_light_calculation(int** road, int i, int j, int *light_location, int** gap_light)
{
    int front_light = 0;

    if (j <= light_location[0])
    {
        front_light = light_location[0]; 
        //printf("front light = %d\n", front_light);
    }    
    else if(j > light_location[num_light - 1])
    {
        front_light = 1000;
    }
    else
    {
        for(int m = 0; m < num_light - 1; m++)
        {
            if(j > light_location[m] && j <= light_location[m+1])
            {
                front_light = light_location[m+1]; 
                //printf("front light = %d\n", front_light);
                break;
            }
        }
    }

    //printf("front light = %d\n", front_light);
    gap_light[i][j] = front_light - j;
    //printf("gap_light = %d\n", gap_light[i][j]);
}
/*************************************
 * calculate the all the gaps
 * of the cars and the lights
**************************************/
void all_gap(int** road, int lane, int distance, int *light_location, int** gap_car, int** gap_light) 
{
    for(int i = 0; i < lane; i++)
    {
        for(int j = 0; j < distance; j++)
        {
            if(road[i][j] >= 1)
            {
                gap_car_calculation(road, i, j, distance, gap_car);
                //printf("there is gap car calculation\n");
                gap_light_calculation(road, i, j, light_location, gap_light);
                //printf("there is gap light calculation\n");
            }
        }
    }
} 