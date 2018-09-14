
%change the path to the place where you store the program 
road = textread('/Users/eric_sun/Desktop/program6010/C_program/road_condition.txt');
velocity = textread('/Users/eric_sun/Desktop/program6010/C_program/velocity_car.txt');

% The last 3 input of the average_call is timestep, number of the lane and
% the distance 
[trafficflow,Averagespeedpercar] = average_cal(road, velocity, 200, 6, 100);

% The last 3 input of the dove_film is the lane + 1 and the distance

dove_film(road,200,7,100)
% subplot(1,2,1);
% plot_traffic_flow(trafficflow)
% subplot(1,2,2);
% plot_average_speed_per_car(Averagespeedpercar)
