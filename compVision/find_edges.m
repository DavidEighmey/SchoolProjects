function [ newimg ] = find_edges( img, scaler )
%   find_edges      finds the edges of an image using
%                   sobel filter.
%   Syntax:
%       [ newimg ] = find_edges( img, scaler )
%
%   Input:
%       img    = an image of type uint8.
%       scaler = a threshold value
%
%   Output:
%       newimg     = the image highlighting the edges.
%
%   History
%   Creator:    Jonathan Child  4/21/12

%changes the input image to type double.
img = double(img);
%finds the gradient magnitude of image.
img = gradient_magnitude(img);

%creates new image to store values
[x,y] = size(img);
newimg = repmat(uint8(0), x,y);

%compare values in image to threshold value.
for i=1:x
    for j=1:y
        if(img(i,j)>= scaler)
            newimg(i,j) = 255;
        else
            newimg(i,j)=0;
        end
    end
end

end

