#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include "LunaCV.hpp"
int main() {
    int width = 2000;
    int height = 1500;

    cv::Mat blankImage(height, width, CV_8UC3, cv::Scalar(0, 0, 0));
    // int Size = 300;
    std::vector<int> v = NewSortedVector(500);
    int size = 50;
    int* n = NewSortedArray(size);
    ShuffleVector(v);
    ShuffleArray(n,size);
    auto start = std::chrono::high_resolution_clock::now();

    // RadixSort(v,blankImage,height,width-200,true);
    // MergeSort(v, int 0,v.size()-1,blankImage,height,width);
    // std::sort(std::begin(v),std::end(v));
    BubbleSort(n,size,blankImage,height,width-200);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start);

    std::cout<<"Time : "<<double(duration.count()/double(1000000))<<" milliseconds\n";

    return 0;
}
