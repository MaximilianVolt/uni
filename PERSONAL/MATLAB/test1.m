clc;

[xx, yy] = plane();
draw(xx, yy, atan(xx.^3 .* sin(yy)));




function [xx, yy] = plane(x, y, xshift, yshift, precision)

  % MAKEPLANE Generates a meshgrid plane with adjustable shifts and precision.
  %
  %   [xx, yy] = MAKEPLANE(x, y, xshift, yshift, precision) generates a
  %   meshgrid plane of size x-by-y, shifted by xshift and yshift, with the
  %   specified precision.
  %
  %   INPUTS:
  %   - x         : The X-axis interval size (default: 10)
  %   - y         : The Y-axis interval size (default: 10)
  %   - xshift    : Shift along the X-axis (default: 0)
  %   - yshift    : Shift along the Y-axis (default: 0)
  %   - precision : Spacing between points (default: (x + y) / 80)
  %
  %   OUTPUTS:
  %   - xx : X-coordinates of the generated plane
  %   - yy : Y-coordinates of the generated plane
  %
  %   EXAMPLE:
  %   [xx, yy] = makeplane(10, 10, 2, 3, 0.5);
  %   surf(xx, yy, zeros(size(xx))); % Visualizing the plane

  % Specifies default call arguments
  arguments
    x = 10;
    y = 10;
    xshift = 0;
    yshift = 0;
    precision = (x + y) / 80;
  end

  % Creates x and y intervals (xi and yi)
  xi = xshift - x : precision : xshift + x;
  yi = yshift - y : precision : yshift + y;

  % Creates the meshgrid and returns it
  % [xx, yy] matches the return expression
  [xx, yy] = meshgrid(xi, yi);
end



function [] = draw(x, y, f)

  % DRAW draws a prettified graph given two axes and a function.
  %
  %   [] = draw(xx, yy, f) draws a prettified graph given two axes and a function.
  %
  %   INPUTS:
  %   - xx        : The X-axis
  %   - yy        : The Y-axis
  %   - f         : The function to draw

  % Opens a new window
  figure;

  % Draws the function (3d)
  surf(x, y, f);

  % Manages the look of the graph
  shading interp;
  colormap jet;
  colorbar;
  grid on;

  % Adds labels to axes
  xlabel("x");
  ylabel("y");
  zlabel("z");
end 
