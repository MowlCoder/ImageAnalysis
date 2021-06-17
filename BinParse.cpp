#include "BinParse.h"
#include <QImage>
#include <QVector>
#include <QRgb>

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
        return;
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
        for (const auto& v : value)
        {
            imgDataVector.push_back((unsigned char)(255 * v));
        }
    }
}

QImage BinParse::GenerateImage()
{
    uchar* imgData = reinterpret_cast<uchar*>(imgDataVector.data());

    QImage img(imgData, imgWidth, imgHeight, imgWidth, QImage::Format_Indexed8);

    QVector<QRgb> color_table;
    for(int i = 0; i < 256; ++i)
        color_table.append(qRgb(i,i,i));

    img.setColorTable(color_table);

    return img;
}

void BinParse::ShowImage() {}
