/*
Bad apple - c++

A rendition of the bad apple animation made using c++.
Completed on Nov. 6, 2023.

*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <stdlib.h> 

#include<unistd.h>

using namespace std;

// The original animation is run at 30fps (33.333 ms), but output is somewhat unstable at this framerate
// For recording purposes, the time per frame is set to half - 15fps (66.667 ms) with the recording being played at double speed
// For viewing purposes, the time for frame is set to 41.667 ms
#define TIME_FOR_1_FRAME 66.667

/*
The animation frames were separated into 60x45 bmp files
This file size was chosen to reduce the computation requirement of the program and allow
    for the translated ascii image to appear properly in the terminal
*/
char image[45][60];

int main(void) {

    // There is 6572 frames in this animation, starting from 1
    for (int frame = 1; frame <= 6572; frame++) {
        string start = "../frames/";
        string end = ".bmp";
        string num = to_string(frame);

        // Opens a specific file based on the frame count
        ifstream curFile(start + num + end);

        // Stores the current byte being read.
        char curByte;
        
        // The red, green, and blue values for a given pixel
        double r, g, b;

        // This is the calculated brightness of a pixel in the image
        double brightness;

        // This will be which ascii character represents a pixel in the image
        int rangeIndex;

        // Ignores header bytes to get to rbg content - header is 54 bytes
        for (int i = 0; i < 54; i++) {
            curFile.read(&curByte, 1);
        }

        // converting rgb data from bmp into an ascii character based on pixel brightness
        for (int i = 0; i < 45; i++) {
            for (int j = 0; j < 60; j++) {
                curFile.read(&curByte, 1);
                r = curByte;
                // Since curByte is a signed char, if it is below 0, then it should be converted to it's unsigned form
                // Signed char curByte is required since file.read only takes a signed char.
                if (r < 0) {r += 256;}

                curFile.read(&curByte, 1);
                g = curByte;
                if (g < 0) {g += 256;}

                curFile.read(&curByte, 1);
                b = curByte;
                if (b < 0) {b += 256;}

                // Formula from https://stackoverflow.com/questions/596216/formula-to-determine-perceived-brightness-of-rgb-color
                // Brightness is smaller for darker colors (0 for black) and larger for brighter colors (255 for white)
                brightness = sqrt((0.299* r*r) + (0.587 * g*g) + (0.114 * b*b));
                
                /* 
                The ascii character brightness range is 70 elements (0-69), but the brightness range is from 0-255
                This operation converts the 0-255 brightness range to the 0-69 ascii brightness range  
                The chosen ascii character is what will represent the specific pixel and is what will be output to the screen
                    It will be stored in rangeIndex, and will be sed to index a character from the ascii brightness range
                The ascii brightness range is: "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. "
                    It was taken from https://stackoverflow.com/questions/30097953/ascii-art-sorting-an-array-of-ascii-characters-by-brightness-levels-c-c 
                */ 
                int oldRange = 255 - 0;
                int newRange = 69 - 0;
                int rangeIndex = round((((brightness - 0) * newRange) / oldRange) + 0); 
                
                // This order of the range has black being highlighted and white being blank
                // image[i][j] ="$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. "[rangeIndex];
                
                // This order has black being blank and white being highlighted
                // Using a dark theme terminal, this order matches the original animation 
                image[i][j] = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"[rangeIndex];
            }
        }

        // Output of the image in ascii form
        // This loop starts at the highest row since bmp data starts from the bottom left pixel and goes across and up to the top right pixel
        for (int i = 44; i >= 0; i--) {
            for (int j = 0; j < 60; j++) {
                
                for (int l = 0; l < 2; l++) {
                    cout << image[i][j];
                }
            }
            cout << endl;
        }

        curFile.close();


        // usleep takes a time in microseconds, so the frame rate is multiplied by 1000 to compensate
        usleep(TIME_FOR_1_FRAME * 1000);
    }


    return 0;
}