function [ h ] = compute_histogram(img)
%   compute_histogram       This function computes a histogram
%                           for a given input image.

%   Syntax:
%       [ h ] = compute_histogram(img)
%
%   Input:
%       img   = an image of type uint8.
%
%   Output:
%       h     = the histogram of img.
%
%   History:
%       Jonathan Child          03/20/2012
%

%gets the # of rows and cols of the img
[rows,cols] = size(img);

%creates an array of zeros of size 1 through 256
count (1:256) = 0;
%finds how many of each number are in the image
for p = 0:255
    for i = 1:rows
        for j = 1:cols
            if img (i,j) == p
                count(p+1) = count(p+1) + 1;
            end
        end
    end
end
h = count/(rows*cols);
end

