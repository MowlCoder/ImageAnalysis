#include "BinParse.h"

#include <QDebug>

BinParse::BinParse(std::string filePath)
{
    filename = filePath;
    input.open(filename, std::ios::binary);

    if (!input.is_open())
    {
        std::cout << "Failed to open " << filename << '!' << std::endl;
    }
}

BinParse::~BinParse()
{
    input.close();
}

void BinParse::Parse()
{
    if (!input.is_open())
    {
        std::cout << "File: " << filename << " not opened" << '!' << std::endl;
    }

    input.seekg(76, std::ios::beg);
    input.read(reinterpret_cast<char *>(&imgWidth), sizeof(imgWidth));
    input.read(reinterpret_cast<char *>(&imgHeight), sizeof(imgHeight));

    input.seekg(2072, std::ios::beg);

    for (unsigned int y = 0; y < imgHeight + 5; y++)
    {
        input.seekg(16, std::ios::cur);
        uint16_t strNumber;
        input.read(reinterpret_cast<char *>(&strNumber), sizeof(strNumber));

        input.seekg(26, std::ios::cur);

        for (unsigned int i = 0; i < imgWidth * 2; i += 2) {
            uint16_t pixelValue;
            input.read(reinterpret_cast<char *>(&pixelValue), sizeof(pixelValue));
            imgLinesValue[strNumber].push_back((double)(pixelValue / (pow(2, 16) - 1)));
        }
    }

    for (const auto& [key, value] : imgLinesValue)
    {
        imgMatrix.push_back(value);
    }
}

void BinParse::PrintImageMatrix()
{
    for (const auto& line : imgMatrix)
    {
        for (const auto& value : line)
        {
            std::cout << std::setw(8) << value << '\t';
        }

        std::cout << '\n';
    }
}

void BinParse::ShowImage() {}
