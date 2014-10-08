function [ equ_img ] = equalize( img )
%   equalize        This takes an input image and transforms it into an
%                   equalized image. prints out the mean and STD of the 
%                   new image and the original image. Also plots the 
%                   histogram of the new image and equalized image.
%   Syntax:
%       [ equ_img ] = equalize( img )
%
%   Input:
%       img     =   an input image you want to equalize
%                   
%   Output:
%       equ_img =   the input image equalized.
%
%   History:
%       Jonathan Child      03/20/2012
% 
[rows,cols] = size(img);
hist = compute_histogram(img);
equ_img = zeros(rows,cols);

plot_histogram(hist);
figure;
T = histogram_transform(hist);

%computes the mean and STD
img = double(img);
img_mean = mean(img(:));
img_std = std(img(:));
disp('Mean of original image:');
disp(img_mean);
disp('STD of original image:');
disp(img_std);
%

img = uint8(img);

%Transforming the image to and equalized image.
for i = 1:rows
    for j = 1:cols
        equ_img(i,j) = T(img(i,j)+1);
    end
end

%computing and ploting the histogram of the equalized image
new_hist = compute_histogram(equ_img);
plot_histogram(new_hist);
%computing the mean and STD of the equalized image
equ_img = double(equ_img);
Nimg_mean = mean(equ_img(:));
Nimg_std = std(equ_img(:));
disp('Mean of equalized image:');
disp(Nimg_mean);
disp('STD of equalized image:');
disp(Nimg_std);

equ_img = uint8(equ_img);
end

