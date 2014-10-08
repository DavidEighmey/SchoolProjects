function [ grade ] = gradient_magnitude( img )
%   gradient_magnitude       passes sobel filter to 
%                           spatial_filter.m to find
%			    gradient magnitude of image
%   Syntax:
%       [ grade ] = gradient_magnitude(img)
%
%   Input:
%       img    = an image of type double.
%       
%
%   Output:
%       grade     = gradient magnitude of image.
%
%   History
%   Creator:    Jonathan Child  4/21/12




sobel_x = [-1,-2,-1;0,0,0;1,2,1];
sobel_y = [-1,0,1;-2,0,2;-1,0,1];

%passing the filters through the input image
gx = spatial_filter( img , sobel_x);
gy = spatial_filter( img , sobel_y);

grade = sqrt(gx.^2 + gy.^2);
%makeing sure the output is type double.
grade = double(grade);
end

