clc;

x = -5 : .1 : 5;
y = -5 : .1 : 5;

[xx, yy] = meshgrid(x, y);

figure;

plot3(xx, yy, x.^2 + y);

% plot(y);