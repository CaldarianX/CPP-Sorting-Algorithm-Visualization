#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>
#include <random> 
#include <chrono>
#include <unctrl.h>
#include <thread> 
#include <vector>

void LunaRectangleHori(cv::Mat &source,float xstart,float ystart,float width,float height){
    cv::Point topLeft(xstart,ystart);
    cv::Point bottomRight(xstart+width,ystart+height);
    cv::Scalar rectangleColor(255, 129, 255);
    int thickness = 2;
    cv::rectangle(source, topLeft, bottomRight, rectangleColor,-1);
}
void LunaRectangleVerti(cv::Mat &source,float xstart,float ystart,float width,float height){
    cv::Point topLeft(xstart,ystart);
    cv::Point bottomRight(xstart+width,ystart-height);
    cv::Scalar rectangleColor(255, 255, 255);
    int thickness = 2;
    cv::rectangle(source, topLeft, bottomRight, rectangleColor,-1);
}
void LunaRectangleVertiWithHilight(cv::Mat &source,float xstart,float ystart,float width,float height,cv::Scalar rectangleColor){
    cv::Point topLeft(xstart,ystart);
    cv::Point bottomRight(xstart+width,ystart-height);
    int thickness = 2;
    cv::rectangle(source, topLeft, bottomRight, rectangleColor,-1);
}
void LunaDisplayArray(int* arr, int size, cv::Mat &source, int windowHeight, int windowWidth,int indexHilight) {
    // Calculate width and height for each rectangle
    int widthPerElement = windowWidth / (size + 1);  // Adjust space for better visualization
    int maxHeight = windowHeight - 200;  // Set the max height for the largest rectangle
    int heightPerStep = maxHeight / size;

    for (int i = 0; i < size; i++) {
        int xstart = 100 + i * widthPerElement;  // Space the rectangles evenly across the width
        int ystart = windowHeight - 100;  // Bottom of the window
        int rectHeight = (arr[i]) * heightPerStep;  // Scale rectangle height based on array value

        // std::cout << "Drawing rectangle at: (" << xstart << ", " << ystart << ") Height: " << rectHeight << std::endl;
        if(i==indexHilight){
            cv::Scalar green(0,0,255);
            LunaRectangleVertiWithHilight(source, xstart, ystart, widthPerElement, rectHeight,green);
            continue;
        }
        // Draw the rectangle using the corrected height
        LunaRectangleVerti(source, xstart, ystart, widthPerElement, rectHeight);
    }
}
void LunaDisplayVector(std::vector<int> arr, cv::Mat &source, int windowHeight, int windowWidth,int indexHilight) {
    // Calculate width and height for each rectangle
    float widthPerElement = windowWidth / float((arr.size() + 1));  // Adjust space for better visualization
    float maxHeight = windowHeight - 200;  // Set the max height for the largest rectangle
    float heightPerStep = maxHeight / float(arr.size());

    for (int i = 0; i < arr.size(); i++) {
        float xstart = 100 + i * widthPerElement;  // Space the rectangles evenly across the width
        float ystart = windowHeight - 100;  // Bottom of the window
        float rectHeight = (arr[i]) * heightPerStep;  // Scale rectangle height based on array value

        // std::cout << "Drawing rectangle at: (" << xstart << ", " << ystart << ") Height: " << rectHeight << std::endl;
        if(i==indexHilight){
            cv::Scalar green(0,0,255);
            LunaRectangleVertiWithHilight(source, xstart, ystart, widthPerElement, rectHeight,green);
            continue;
        }
        // Draw the rectangle using the corrected height
        LunaRectangleVerti(source, xstart, ystart, widthPerElement, rectHeight);
    }
}
int* NewSortedArray(int size){
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = i+1;
    }
    return arr;
}
void ShuffleArray(int arr[], int n)
{
 
    // To obtain a time-based seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
 
    // Shuffling our array
    shuffle(arr, arr + n, std::default_random_engine(seed));
 
    // Printing our array
    for (int i = 0; i < n; ++i)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}
void Display(cv::Mat &source,std::string title){
    cv::imshow(title, source);
    cv::waitKey(0);
}
void ClearImage(cv::Mat &image) {
    image.setTo(cv::Scalar(0, 0, 0));  // Reset the image to black
}
void VisualizationMat(cv::Mat source,std::vector<int> v,int windowHeight, int windowWidth,int indexHilight,std::string title){
    ClearImage(source);
    LunaDisplayVector(v,source,windowHeight,windowWidth,indexHilight);
    cv::imshow(title,source);
    cv::waitKey(1);
}
void BubbleSort(int* arr, int size,cv::Mat source,int windowHeight,int windowWidth) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            // Swap if the current element is greater than the next element
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                if(j%1 == 0){
                    ClearImage(source);
                    LunaDisplayArray(arr,size,source,windowHeight,windowWidth,j+1);
                    cv::imshow("BubbleSort",source);
                    cv::waitKey(1);
                }
                // std::this_thread::sleep_for(std::chrono::milliseconds(200));
                // Display(source,"BubbleSort");
            }
        }
    }
}
void BucketSort(int arr[], int size, cv::Mat &source, int windowHeight, int windowWidth) {
    // Find the maximum element to determine the range of the buckets
    int max_value = *std::max_element(arr, arr + size);

    // Create buckets (each bucket is a vector)
    std::vector<int> buckets[size];

    // Scatter: Put array elements into different buckets based on value
    for (int i = 0; i < size; i++) {
        int bucket_index = (size * arr[i]) / (max_value + 1);  // Index of the bucket
        buckets[bucket_index].push_back(arr[i]);

        // Visualize after placing each element into a bucket

        ClearImage(source);
        LunaDisplayArray(arr, size, source, windowHeight, windowWidth, i);
        cv::imshow("BucketSort", source);
        cv::waitKey(100);  // Small delay for visualization
    }

    // Sort each bucket individually and gather the results
    int index = 0;
    for (int i = 0; i < size; i++) {
        std::sort(buckets[i].begin(), buckets[i].end());

        // Gather: Concatenate all sorted buckets into the original array
        for (int j = 0; j < buckets[i].size(); j++) {
            arr[index++] = buckets[i][j];

            // Visualize after placing each element back into the array
            ClearImage(source);
            LunaDisplayArray(arr, size, source, windowHeight, windowWidth, index - 1);
            cv::imshow("BucketSort", source);
            cv::waitKey(100);  // Small delay for visualization
        }
    }
}
// void Merge(std::vector arr, int left, int mid, int right, cv::Mat &source, int windowHeight, int windowWidth) {
//     int n1 = mid - left + 1;
//     int n2 = right - mid;
//     int Size = 300;
//     // Create temp arrays
//     std::vector leftArr(n1);
//     std::vector rightArr(n2);
//     // int* leftArr = new int[n1];
//     // int* rightArr = new int[n2];

//     // Copy data to temp arrays
//     for (int i = 0; i < n1; i++)
//         leftArr[i] = arr[left + i];
//     for (int i = 0; i < n2; i++)
//         rightArr[i] = arr[mid + 1 + i];

//     // Merge the temp arrays back into arr[left..right]
//     int i = 0, j = 0, k = left;
//     while (i < n1 && j < n2) {
//         if (leftArr[i] <= rightArr[j]) {
//             arr[k] = leftArr[i];
//             i++;
//         } else {
//             arr[k] = rightArr[j];
//             j++;
//         }

//         // Visualize after each merge step
//         ClearImage(source);
//         LunaDisplayVector(arr, Size, source, windowHeight, windowWidth, k);
//         cv::imshow("MergeSort Visualization", source);
//         cv::waitKey(1);  // Small delay to visualize the process
//         k++;
//     }

//     // Copy the remaining elements of leftArr[], if any
//     while (i < n1) {
//         arr[k] = leftArr[i];
//         i++;
//         k++;

//         // Visualize after each merge step
//         ClearImage(source);
//         LunaDisplayArray(arr, Size, source, windowHeight, windowWidth, k - 1);
//         cv::imshow("MergeSort Visualization", source);
//         cv::waitKey(1);  // Small delay to visualize the process
//     }

//     // Copy the remaining elements of rightArr[], if any
//     while (j < n2) {
//         arr[k] = rightArr[j];
//         j++;
//         k++;

//         // Visualize after each merge step
//         ClearImage(source);
//         LunaDisplayArray(arr, Size, source, windowHeight, windowWidth, k - 1);
//         cv::imshow("MergeSort Visualization", source);
//         cv::waitKey(1);  // Small delay to visualize the process
//     }

//     // Clean up
//     // delete[] leftArr;
//     // delete[] rightArr;
// }

// void MergeSort(std::vector arr, int left, int right, cv::Mat &source, int windowHeight, int windowWidth) {

//     if (left >= right)
//         return;  // Base case: if the array has one or zero elements

//     int mid = left + (right - left) / 2;

//     // Recursively sort first and second halves
//     MergeSort(arr, left, mid, source, windowHeight, windowWidth);
//     MergeSort(arr, mid + 1, right, source, windowHeight, windowWidth);

//     // Merge the sorted halves with visualization
//     Merge(arr, left, mid, right, source, windowHeight, windowWidth);
// }
int getNumOfDigits(int maxValue) {
    if (maxValue == 0) return 1;
    return std::floor(std::log10(maxValue)) + 1;
}
int getNumAtPosition(int Value,int position){
    if(getNumOfDigits(Value)<position){
        return 0;
    }
    for(int i =0;i<position-1;i++){
        Value /=10;
    }
    return Value%10;
}
std::vector<int> Vector2DTo1D(std::vector<std::vector<int> > bins){
    std::vector<int> newVec;
    for(int i =0;i<bins.size();i++){
        for(int j=0;j<bins[i].size();j++){
            newVec.push_back(bins[i][j]);
        }
    }
    return newVec;
}
std::vector<int> NewSortedVector(int size){
    std::vector<int> v;
    for(int i =1;i<size;i++){
        v.push_back(i);
    }
    return v;
}
void ShuffleVector(std::vector<int> &v){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(std::begin(v),std::end(v), std::default_random_engine(seed));
}
void PrintVector(std::vector<int> v){
    for(int i =0;i<v.size();i++){
        std::cout<<v[i]<<" ";
    }
    std::cout<<"\n";
}
void RadixSort(std::vector<int> &v,cv::Mat source,int windowHeight, int windowWidth,bool IsDisplay){
    int round = getNumOfDigits(v.size());
    std::string Title = "RadixSort";

    for(int i =1;i<=round;i++){
        std::vector<std::vector<int> > bins(10);
        for(int j=0;j<v.size();j++){
            bins[getNumAtPosition(v[j],i)].push_back(v[j]);
            if(j%10==0 && IsDisplay) VisualizationMat(source,v,windowHeight,windowWidth,j,Title);
        }
        std::vector<int> tmp = v;
        int index = 0;
        for(int i =0;i<bins.size();i++){
            for(int j=0;j<bins[i].size();j++){
                tmp[index] = bins[i][j];
                if(index%10==0 && IsDisplay) VisualizationMat(source,tmp,windowHeight,windowWidth,index,Title);
                index++;
            }
        }
        v = tmp;
    }
}




