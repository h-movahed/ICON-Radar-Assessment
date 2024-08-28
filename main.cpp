#include <opencv2/opencv.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

std::vector<cv::Point3f> readCSV(const std::string& filename) {
    std::vector<cv::Point3f> data;
    std::ifstream file(filename);
    std::string line;
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string value;
        float x, y, confidence;
        
        std::getline(ss, value, ',');
        x = std::stof(value);
        std::getline(ss, value, ',');
        y = std::stof(value);
        std::getline(ss, value, ',');
        confidence = std::stof(value);
        
        data.push_back(cv::Point3f(x, y, confidence));
    }
    file.close();
    return data;
}
cv::Mat plotData(const std::vector<cv::Point3f>& data) {
    // Find the range of x and y coordinates
    float minX = FLT_MAX, maxX = -FLT_MAX, minY = FLT_MAX, maxY = -FLT_MAX;
    for (const auto& point : data) {
        minX = std::min(minX, point.x);
        maxX = std::max(maxX, point.x);
        minY = std::min(minY, point.y);
        maxY = std::max(maxY, point.y);
    }
    
    // Create an image
    int width = 800;
    int height = 600;
    cv::Mat image(height, width, CV_8UC3, cv::Scalar(0, 0, 0));
    
    // Plot points
    for (const auto& point : data) {
        int x = static_cast<int>((point.x - minX) / (maxX - minX) * (width - 1));
        int y = height - 1 - static_cast<int>((point.y - minY) / (maxY - minY) * (height - 1));
        
        // Use confidence for color (blue to red)
        int blue = static_cast<int>((1 - point.z) * 255);
        int red = static_cast<int>(point.z * 255);
        cv::circle(image, cv::Point(x, y), 2, cv::Scalar(blue, 0, red), -1);
    }
    
    return image;
}
int main() {
    std::string filename = "C:/Users/hmova/Documents/Icon_Radar/OGM.csv";
    std::vector<cv::Point3f> data = readCSV(filename);
    cv::Mat image = plotData(data);
    
    cv::imshow("Radar Data", image);
    cv::waitKey(0);
    
    return 0;
}