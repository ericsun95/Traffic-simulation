#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "trafficlight.h"

/*************************************
 *  initialize Light location
 * 
**************************************/
void initializeLight(int distance, int* light_location)
{
    int interval = 1;
    interval = distance/(num_light + 1);
	for(int j = 0; j < num_light; j++)
	{
		light_location[j] = interval*(j+1);
	}
}

/*************************************
 * traffic_light condition
 * 
**************************************/
void traffic_light(int t, int* light_condition)
{
    int k;
	for(int i = 0; i < num_light; i++)
	{
	    k = t/timeinterval;
        //printf("%d\n", k%2);

        if((k%2) == 0) //synchronized traffic light
		//if( ((k%2) == 0 && (i%2) == 0) || ((k%2) == 1 && (i%2) == 1) ) // asynchronized traffic light
		{
			light_condition[i] = -2; //the light is red
		}
		else
		{
			light_condition[i] = -1; //the light is green
		}
	}
}
/*************************************
 * the pass or wait of a car
 * 
**************************************/
int pass_or_wait(int i, int j, int distance, int** gap_light, int* light_condition)
{
    int k = 0;
    int interval = 1;
    interval = distance/(num_light + 1);
    k = j/interval - 1;			//get the number of the light
    // printf("the location of the light %d\n", k);
    if(light_condition[k] == -1)
    {
        return 1;//pass
        //printf(" green light");
    }
    else
    {
        return 0; //wait
    }
}
