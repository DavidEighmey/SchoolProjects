function [ newImg ] =  spatial_filter( img , filter )
%   spatial_filter       This function passes a filter 
%                           through a given input image.
%   Syntax:
%       [ newImg ] = spatil_filter(img,filter)
%
%   Input:
%       img    = an image of type double.
%       filter = filter of odd size you want to pass through image.
%
%   Output:
%       newImg     = image after filter passed through it.
%
%   History
%   Creator:    Jonathan Child  4/21/12

[x,y] = size(img);
%new blank image with the same size of img
newImg = repmat(double(0), x,y);
%finds the dimentions of the filter
[i,j] = size(filter);
%calculates how much padding is needed for the image so we can use the filter on the
%image
d = (i-1)/2;
%creates the padded image
padimg = padarray (img , [d,d]);

for a = 1:x
    for b = 1:y
        for s=1:i
            for t=1:j
            newImg(a,b) = (newImg(a,b))+ ((filter(s,t))*(padimg((a+s)-d,(b+t)-d)));
            end
        end
    end
end

end

