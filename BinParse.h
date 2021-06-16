#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <iomanip>

class BinParse
{
private:
    std::string filename;
    std::ifstream input;
    uint32_t imgWidth;
    uint32_t imgHeight;
    std::map<int, std::vector<double>> imgLinesValue;
    std::vector<std::vector<double>> imgMatrix;
public:
    BinParse(std::string filePath);
    ~BinParse();
    void Parse();
    void ShowImage();
    void PrintImageMatrix();
};
