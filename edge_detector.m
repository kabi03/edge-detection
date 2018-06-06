function edges = edge_detector (img , H, T, wndsz )
% Detect edges in an image.
%
% Inputs :
%   img
%       image being processed ( can be either greyscale or RGB )
%   H
%       the filtering kernel that approximates the horizontal
%       derivative
%   T [ optional ]
%       the threshold value used by the edge detector ( default is
%       0.1)
%   wndsz [ optional ]
%       the size of the NMS filter window ( default is 5)
%
% Outputs :
%   edges
%       a binary image where a value of ’1’ indicates an image edge

img = im2double ( img );

% if ‘img ’ is a colour image , convert it to greyscale first
if size (img ,3) > 1
    img = rgb2gray ( img );
end

% ‘nargin ’ returns the number of input arguments so you can set
% arguments that have not been provided
if nargin == 2
    T = 0.1;
    wndsz = 5;
end

% set last argument if missing
if nargin == 3
    wndsz = 5;
end

img_db = im2double(img);
V = transpose(H);
gradient_h = spatial_filter(img_db, H);
gradient_v = spatial_filter(img_db, V);
nms_h = non_max_suppress(gradient_h, wndsz, 1);
nms_v = non_max_suppress(gradient_v, 1, wndsz);
threshold_h = image_threshold(nms_h, T);
threshold_v = image_threshold(nms_v, T);
edges = or(threshold_h, threshold_v);

end

