%average sum calcuation
function [A,C] = average_cal(celve1, celve2, t, lane, distance)
  A = eye(1,t);
  B = cell(lane,distance);
  C = eye(1,t);
  D = cell(lane,distance); 
  % calculate the number of cars in road
  for j = 1:t
     B{j} = celve1(2*j+(j-1)*(lane -1) : 2*j+j*(lane - 1),:);
     A(1,j) = sum(sum(B{j}>0));
  end
  %calculate the average velocity of the cars in road
  for j = 1:t
     D{j} = celve2(1 + (j-1)*lane : j*lane,:); 
     C(1,j) = sum(D{j}(:))/A(1,j);
  end
  car_average = sum(A(40:t))/(t - 40);
  v_average = mean(C(:));
  disp("traffic flow: ");disp(car_average)
  disp("average car speed: ");disp(v_average)
end
%   for j = 1:t
%       disp(A(1,j))
%   end
 