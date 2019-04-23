#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(){

    //Read image
    Mat image = imread("../assets/putin.jpg");

    //Orignal x-axis values
    float originalValue[] = {0, 50, 100, 150, 200, 255};
    //changed points on Y-axis for red and blue channel
    float blueValues[] = {0, 80, 150, 190, 220, 255};
    float redValues[] = {0, 20, 40, 75, 150, 255};

    //spliting the channels
    vector<Mat> channels(3);
    split(image, channels);

    //create lookup table for red channel
    Mat redLookupTable(1, 256, CV_8U);
    uchar* lut = redLookupTable.ptr();
    //apply interpolation and create red channel lookup table
    for(int i=0; i<256; i++){
        int j=0;
        float a = (float)i;
        while(a > originalValue[j]){
            j++;
        }
        if(a == originalValue[j]){
            lut[i] = redValues[j];
            continue;
        }
        float slope = ((float)(redValues[j] - redValues[j-1]))/((float)(originalValue[j] - originalValue[j-1]));
        float constant = redValues[j] - slope * originalValue[j];
        lut[i] = slope*a + constant;
    }

    //create lookup table for blue channel
    Mat blueLookupTable(1, 256, CV_8U);
    lut = blueLookupTable.ptr();
    //apply interpolation and create blue channel lookup table
    for(int i=0; i<256; i++){
        int j=0;
        float a = (float)i;
        while(a > originalValue[j]){
            j++;
        }
        if(a == originalValue[j]){
            lut[i] = blueValues[j];
            continue;
        }
        float slope = ((float)(blueValues[j] - blueValues[j-1]))/((float)(originalValue[j] - originalValue[j-1]));
        float constant = blueValues[j] - slope * originalValue[j];
        lut[i] = slope*a + constant;
    }

    //Apply mapping for red channel
    LUT(channels[2], redLookupTable, channels[2]);

    //Apply mapping for blue channel
    LUT(channels[0], blueLookupTable, channels[0]);

    Mat result;
    merge(channels, result);

    //create windows to display image
    namedWindow("image", WINDOW_NORMAL);
    namedWindow("result", WINDOW_NORMAL);

    //display images
    imshow("image", image);
    imshow("result", result);

    //press esc to exit the program
    waitKey(0);

    //close all the opened windows
    destroyAllWindows();

    return 0;
}