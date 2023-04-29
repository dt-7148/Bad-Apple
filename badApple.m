% This directory contains every frame of Bad Apple
srcFiles = dir('C:\Me\projects\apple\frames\*.png');

% There are 6572 frames in this animation (from ffmpeg)
x = 6572

iterationTime = 1 / 30;

for i = 1:x

    tic;

    % Gets file name for iteration
    filename = strcat('C:\Me\projects\apple\frames\',srcFiles(i).name);

    % Image file is saved to variable I, in grayscale form
    I = rgb2gray(imread(filename));

    % Image converted to binary image
    BW = imbinarize(I);

    % Get trace of image
    trace = edge(BW);
    
    % If you wanted a white background, use imshow(imcomplement(trace))
    imshow(trace)

    t = toc

    while t < iterationTime
        % do nothing  
    end
end

%{
todo:
find out how to speed up for loop
currently running at ~15 fps, want that doubled
find out how to speed up a for loop 
%}