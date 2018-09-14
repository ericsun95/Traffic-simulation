%plot the graph
function plot_traffic_flow(matrix)
    plot(matrix);
    axis([0 200 0 180]); 
    set(gca,'YGrid','on')
    set(gca,'YTick',0:20:180)
    set(gca,'YTicklabel',0:20:180)
    xlabel('Time','FontSize',16)
    ylabel('traffic flow','FontSize',16)
    title('Traffic Flow','FontName','Roman','FontSize',20)
end
