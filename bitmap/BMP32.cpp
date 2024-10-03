#include "BMP32.h"

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <string>

BMP32::BMP32() {}

BMP32::~BMP32() {}

void BMP32::displayBMP()
{
	for (vector<RGBQUAD> rows : pixelsData)
	{
		for (RGBQUAD pixel : rows)
		{
			if (pixel.rgbBlue == 0 && pixel.rgbGreen == 0 && pixel.rgbRed == 0)
			{
				cout << "*";
			}
			else if (pixel.rgbBlue == 255 && pixel.rgbGreen == 255 && pixel.rgbRed == 255)
			{
				cout << ".";
			}
			else { cout << "."; }
		}
		cout << endl;
	}
}

void BMP32::closeBMP()
{
	vector<vector<RGBQUAD>>().swap(pixelsData);
}

void BMP32::openBMP(const std::string& fileName)
{
	fstream fs(fileName);
	if (!fs.is_open()) { throw std::runtime_error("Error opening file"); }

	fs.read((char*)&fileHeader, sizeof(fileHeader));
	if (fileHeader.bfType != 0x4D42) { throw std::runtime_error("Error! Unrecognized file format."); }

	fs.read((char*)&infoHeader, sizeof(infoHeader));
	fs.seekg(fileHeader.bfOffBits, ios::beg);


	pixelsData.reserve(infoHeader.biHeight);

	for (int i{ 0 }; i < infoHeader.biHeight; i++)
	{
		vector<RGBQUAD> temp;
		temp.reserve(infoHeader.biWidth);
		for (int j{ 0 }; j < infoHeader.biWidth; j++)
		{
			RGBQUAD bufer;
			fs.read((char*)&bufer, sizeof(bufer));
			temp.push_back(bufer);
		}
		pixelsData.insert(pixelsData.begin(), temp);
		// добавляем строку пикселей в начало,т.к. первая строка пикселей в файле - последняя строка пикселей изображения
	}
	fs.clear();
	fs.close();
}

void BMP32::printInfo()
{
	cout << "<<<<<<<<<BITMAPFILEHEADER>>>>>>>>>" << endl;
	cout
		<< "bfType:      " << hex << this->fileHeader.bfType << endl
		<< "bfSize:      " << dec << this->fileHeader.bfSize << endl
		<< "bfOffBits:   " << this->fileHeader.bfOffBits << endl;
	cout << "<<<<<<<<<BITMAPINFOHEADER>>>>>>>>>" << endl;
	cout
		<< "Size:      " << this->infoHeader.biSize << endl
		<< "Width:      " << this->infoHeader.biWidth << endl
		<< "Height: " << this->infoHeader.biHeight << endl
		<< "BitCount:   " << this->infoHeader.biBitCount << endl
		<< "SizeImage:   " << this->infoHeader.biSizeImage << endl
		<< "Colors Used: " << this->infoHeader.biClrUsed;
}
