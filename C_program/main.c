#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "matrix.h"
#include "gap.h"
#include "trafficlight.h"

void        car_simulation  (int distance, int lane, int** road, int** velocity_car, int* light_location, int* light_condition, int** gap_car, int** gap_light, int* sum_out_of_scope);
void        car_generator   (int num_lanes, int** road, int** velocity_car);
int         min             (int a, int b);


int main(void) {

    //initialize the matrix
    int** road = malloc_matrix(r_distance, r_lane);
    int** velocity_car = malloc_matrix(r_distance, r_lane);
    int** gap_car = malloc_matrix(r_distance, r_lane);
    int** gap_light = malloc_matrix(r_distance, r_lane);

    int *light_location; 
    int *light_condition; 
    int *sum_out_of_scope;

    sum_out_of_scope = (int*)malloc(sizeof(int));

    *sum_out_of_scope = 0;

    light_condition = (int*)malloc(r_distance* sizeof(int));
    light_location = (int*)malloc(r_distance* sizeof(int));


    init_matrix(r_distance, r_lane, road);
    init_matrix(r_distance, r_lane, gap_car);
    init_matrix(r_distance, r_lane, gap_light);
    init_matrix(r_distance, r_lane, velocity_car);
    
    
    //initialize the traffic light condition
    //int num_light = 5, timeinterval = 5;
    
    initializeLight(r_distance, light_location);
    
    srand((unsigned)time(NULL));


    /*************************************
     *  file writing
     * 
    **************************************/
    FILE *ofp;
    ofp = fopen("road_condition.txt", "w");
    if(ofp == NULL){
        printf("outputfile io error\n\n");
        return EXIT_FAILURE;
    }
  
    FILE *ofp_gapcar;
    ofp_gapcar = fopen("roadgapcar.txt", "w");
    if(ofp_gapcar == NULL){
        printf("outputfile io error\n\n");
        return EXIT_FAILURE;
    }

    FILE *ofp_gaplight;
    ofp_gaplight = fopen("roadgaplight.txt", "w");
    if(ofp_gaplight == NULL){
        printf("outputfile io error\n\n");
        return EXIT_FAILURE;
    }

    FILE *ofp_velocitycar;
    ofp_velocitycar = fopen("velocity_car.txt", "w");
    if(ofp_velocitycar == NULL){
        printf("outputfile io error\n\n");
        return EXIT_FAILURE;
    }

    //fprintf(ofp, "%d\t %d\t %d\t\n", r_distance, r_lane, 1);
    // for(int i = 0; i < r_lane; i++){
    //     for(int j = 0; j < r_distance; j++) {

    //         fprintf(ofp, "%d\t", road[i][j]);
    //     }
    //     fprintf(ofp, "\n");
    // }   //write the initial road to file


    /*************************************
     *  main function
     * 
    **************************************/

    for(int i = 0; i < r_lane; i++){
        road[i][0] = 1;
        velocity_car[i][0] = car_start_speed;
        // printf(" ROAD initial = %d\n", road[i][0]);
    }

    for(int t = 1; t <= 200; t++)
    {
        traffic_light(t, light_condition);
     //    for(int i = 0; i < num_light; i++)
    	// {
    	// 	    printf("light condition =%d\n", light_condition[i]);
    	// 	    printf("light location %d = %d\n", i, light_location[i]);
    	// }

        printf("=============\n car simulation\n =============\n");
        printf("simulation time = %d\n", t);
        car_generator(r_lane, road, velocity_car);
        init_matrix(r_distance, r_lane, gap_car);
        init_matrix(r_distance, r_lane, gap_light);
        car_simulation(r_distance, r_lane, road, velocity_car, light_location, light_condition, gap_car, gap_light, sum_out_of_scope);

        //fprintf 3 files
        for(int i = 0; i < r_lane; i++){
            for(int j = 0; j < r_distance; j++) {
                fprintf(ofp_gapcar, "%d\t",gap_car[i][j]);
            }
            fprintf(ofp_gapcar, "\n");
        }

        for(int i = 0; i < r_lane; i++){
            for(int j = 0; j < r_distance; j++) {
                fprintf(ofp_gaplight, "%d\t",gap_light[i][j]);
            }
            fprintf(ofp_gaplight, "\n");
        }

        for(int i = 0; i < r_lane; i++){
            for(int j = 0; j < r_distance; j++) {
                fprintf(ofp_velocitycar, "%d\t",velocity_car[i][j]);
            }
            fprintf(ofp_velocitycar, "\n");
        }
        //end of fprintf 
        for(int k = 0; k < r_distance; k++){
            int record = 0;
            for(int j = 0; j < num_light; j++){
                // printf("num_light j =%d\n", j);
                if(light_location[j] == k)
                {
                    fprintf(ofp, "%d\t",light_condition[j]);
                    break;
                }
                else 
                {
                    record++;
                    if(record == num_light)
                    {
                        fprintf(ofp, "%d\t",-3);
                        break;
                        //printf("write the space to the file");
                    }
                }               
            }        
        }
        fprintf(ofp, "\n");
        //write the traffic light condition to the road
        for(int i = 0; i < r_lane; i++){
            for(int j = 0; j < r_distance; j++) {
                fprintf(ofp, "%d\t",road[i][j]);
            }
            fprintf(ofp, "\n");
        }
    }

    return 0;
}


/*************************************
 * the max of the two integer
 * 
**************************************/
int min(int a, int b)
{
    if(a>b) 
        return b;
    return a;
}


/*************************************
 * the change of the velocity of the car matrix
 * 
**************************************/
void change_velocity_car(int** velocity_car, int lane, int distance, int** road, int** gap_car, int** gap_light, int* light_condition)
{
    int v_max = 0;
    int v_max2 = 0;
    int w = 0;
    for(int i = 0; i < lane; i++)
    {
        for(int j = distance - 1; j >= 0; j--)
        {
            //printf("j ====== %d\n",j);
            if(road[i][j] >= 1)
            {
                gap_car_calculation(road, i, j, distance, gap_car);
                // printf("gap_car[%d][%d] = %d\n", i, j, gap_car[i][j]);
                if(gap_light[i][j] == 0)//wait before the traffic light
                {
                    w = pass_or_wait(i, j, distance, gap_light, light_condition);
                    // printf("w = %d\n", w);
                    if (w == 1)
                    {
                        velocity_car[i][j] = car_restart_speed + road[i][j];
                        printf("restart the car\n");
                    }
                    else
                    {
                        velocity_car[i][j] = 0;
                        printf("wait in line\n");
                    }
                }
                else if(gap_light[i][j] > 0 && velocity_car[i][j] == 0)
                {
                    v_max = min(gap_light[i][j],(gap_car[i][j] - 1));
                    // printf("v_max = %d\n",v_max);
                    velocity_car[i][j] = v_max;
                }
                else
                {
                    v_max = min(gap_light[i][j],(gap_car[i][j] - 1));
                    v_max2 = min(velocity_car[i][j],v_max);
                    v_max2 = min(v_max2, 6);
                    velocity_car[i][j] = v_max2;
                    // printf("v_max 2 = %d\n",v_max2);
                    //velocity_car[i][j] = rand()%(v_max - v_max2 + 1) + v_max - 1;    
                    //velocity_car[i][j] = 0;
                }
            }
        }
    }
}

/*************************************
 * the change of the road condition
 * 
**************************************/
void car_simulation(int distance, int lane, int** road, int** velocity_car, int* light_location, int* light_condition, int** gap_car, int** gap_light, int* sum_out_of_scope)
{
    int move_forward = 0;
    //int sum_out_of_scope = 0;
    
    all_gap(road, lane, distance, light_location, gap_car, gap_light);

   // printf("hhhhhhhh\n");

    change_velocity_car(velocity_car, lane, distance, road, gap_car, gap_light, light_condition);

    //printf("change\n");
    for(int i = 0; i < lane; i++)
    {
        for(int j = distance - 1; j >= 0; j--)
        {
            if(road[i][j] >= 1)
            {
                move_forward = velocity_car[i][j];
                if(move_forward != 0)
                {
                    //printf("there is a move_forward action\n");
                    if((j + move_forward) < distance - 1)
                    {
                        road[i][j+move_forward] = road[i][j];
                        velocity_car[i][j+move_forward] = velocity_car[i][j];
                        road[i][j] = 0;
                        velocity_car[i][j] = 0;// car move forward
                    }
                    else if((j + move_forward) >= distance - 1)
                    {
                        road[i][j] = 0; // car move out of the scope
                        velocity_car[i][j] = 0;
                        *sum_out_of_scope = *sum_out_of_scope + 1;
                       // printf("out of the scope\n");
                    }
                }
            }
        }
    }// update the road and the car condition
    printf("sum_out_of_scope = %d\n", *sum_out_of_scope);
    //print the sum of cars which are out of scope
}


/*************************************
 * U_random
 * 
**************************************/
double U_Random(){  // generate and return a random variable between 0 and 1

        double f;
        f = (float)(rand() % 100);
        //printf("%.2f \t", f);
        return f/100;
}


/*************************************
 * car generator
 * 
**************************************/
void car_generator (int num_lanes, int** road, int** velocity_car){
    int type = 0;
    for (int i = 0; i < num_lanes; i++){
        if(road[i][0] == 0)
        {
            double u = U_Random();
            if (u < 0.5) 
            {
                type = rand()%3 + 1;
                road[i][0] = type;
                velocity_car[i][0] = car_start_speed + type;
            }
            else
            {
                 road[i][0] = 0;
            }
        }
    }
}









