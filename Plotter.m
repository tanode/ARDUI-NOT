    s1=serial('COM11','Baudrate',9600);

    accX=0;
    str='';
    x=0;

    try
        fopen(s1);
    catch err
        fclose(instrfind);
        error('Make sure you select the correct COM Port where the Arduino is connected.');
    end
    Tmax = 120; % Total time for data collection (s)
    figure;
    grid on;
    xlabel ('Time (s)');
    ylabel('Data');
    axis([0 Tmax+1 -10 300]);
    Ts = 0.5; % Sampling time (s)
    i = 0;
    t = 0;

    tic % Start timer
    while toc <= Tmax
        i = i + 1;
        %% Read buffer data
       str=fscanf(s1);
       accX(i)=str2num(str);
        %accY(i)=sen(2);


        %% Plot live data
        if i > 1
            line(toc,accX(i));
            drawnow;
        end
    end
    fclose(s1);    


