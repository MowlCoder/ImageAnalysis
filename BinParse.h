#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <iomanip>
#include <QImage>

class BinParse
{
private:
    std::string filename;
    std::ifstream input;
    uint32_t imgWidth;
    uint32_t imgHeight;
    std::map<int, std::vector<double>> imgLinesValue;
    std::vector<unsigned char> imgDataVector;
public:
    BinParse(std::string filePath);
    ~BinParse();
    void Parse();
    void ShowImage();
    QImage GenerateImage();
};
