clear all;
accX=0;%accY=0;accZ=0;
str='';
sen=0;
j=1;
x=0;
s1=serial('COM11','Baudrate',9600);
figure;
grid on;
xlabel ('Time');
ylabel('Data');
try
        fopen(s1);
while(j<10000)
    str=fscanf(s1);
    sen=str2num(str);
    accX(j)=sen(1);
    %accY(j)=sen(2);
    %accZ(j)=sen(3);
    x(j)=j;
    if(j>200)
        x1=x(j-200:j);
        accX1=accX(j-200:j);
      % accY1=accY(j-200:j);
       %accZ1=accZ(j-200:j);
        xmin=j-200;
        xmax=j;
    else
        x1=x;
        accX1=accX;
     %  accY1=accY;
     %  accZ1=accZ;
        xmin=0;
        xmax=200;
    end
    
   % plot(x1,accX1,x1,accY1,x1,accZ1);
    line(x1,accX1);
    axis([xmin xmax 0 250]);
    drawnow;
    j=j+1;
end
fclose(s1);
delete(s1);
clear s1;

catch err
        fclose(instrfind);
        error('Make sure you select the correct COM Port where the Arduino is connected.');
end