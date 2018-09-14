% input file must be in the matrix form: [(t*lane),distance] 
% E.X celve(10*10,100) means 10 timestep, 10 lanes and 10 distance
function dove_film(celve,t,lane,distance)
    v = VideoWriter('name.avi');
    %t = 50;
    %lane = 2;
    %distance = 100;
    mat = [
    1 1 1
    1 0 0 
    0 1 0
    0.5 0.5 0.5
    0 0.1 0.9
    1 1 0
    0 0 0]; 
    B = cell(lane,distance);
    for j = 1:t
        B{j} = celve(1+(j-1)*lane:j*lane,:);
    end
    open(v);
    M(t) = struct('cdata',[],'colormap',[]);
    for j = 1:t
        %pcolor(B{j})
        width = 1000;
        height = 200;
        left = 200;
        bottem = 100;
        imagesc(B{j})
        axis([1 distance 1 lane])
        %set(gca,'XTick',1:distance);
        set(gca,'YGrid','on');
        %set(gca,'YTick',0:1:lane)
        set(gca,'YTicklabel',0:lane - 1)
        set(gcf,'position',[left,bottem,width,height])
        xlabel('Distance','FontSize',16)
        ylabel('Lane','FontSize',20)
        title('Simulation','FontName','Roman','FontSize',20)
        colormap(mat)
        M(j) = getframe(gcf);
        writeVideo(v,M(j));
    end
    close(v);
end