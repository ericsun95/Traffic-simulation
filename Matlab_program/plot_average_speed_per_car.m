function plot_average_speed_per_car(matrix)
    plot(matrix);
    axis([0 200 0 2.8]); 
    set(gca,'YGrid','on')
    xlabel('Time','FontSize',16)
    ylabel('average speed per lane','FontSize',16)
    title('Average Speed Per Car','FontName','Roman','FontSize',20)
end
