function [T] = histogram_transform( hist )
%   histogram_transform     This function creates a look up table given
%                           a histogram input where it will create
%                           an equalized histogram
%
%   Syntax:
%       [T] = histogram_transform( hist )
%
%   Input:
%       hist        = The histogram you want to create a equalized table
%                     for
%   Output:
%       T           = The look up table to transform an image to an
%                     equalized image
%   History:
%       Jonathan Child          03/20/2012
%

L = 256;

T = zeros(256,1);
for i = 1:L
    if(i ==1)
        T(i) = (hist(i) * (L-1));
    else
        T(i) = (T(i-1)+(hist(i) * (L-1)));
    end
end
T = round(T);
end

