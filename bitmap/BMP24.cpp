#include "BMP24.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

BMP24::BMP24() {}

BMP24::~BMP24() {}

void BMP24::displayBMP()
{
	for (vector<RGBTRIPLE> rows : pixelsData)
	{
		for (RGBTRIPLE pixel : rows)
		{
			if (pixel.rgbtBlue == 0 && pixel.rgbtGreen == 0 && pixel.rgbtRed == 0)
			{
				cout << "*";
			}
			else if (pixel.rgbtBlue == 255 && pixel.rgbtGreen == 255 && pixel.rgbtRed == 255)
			{
				cout << ".";
			}
			else { cout << "."; }
		}
		cout << endl;
	}
}

void BMP24::closeBMP()
{
	vector<vector<RGBTRIPLE>>().swap(pixelsData);
}

void BMP24::openBMP(const std::string& fileName)
{
	fstream fs(fileName);
	if (!fs.is_open()) { throw std::runtime_error("Error opening file"); }

	fs.read((char*)&fileHeader, sizeof(fileHeader));
	if (fileHeader.bfType != 0x4D42) { throw std::runtime_error("Error! Unrecognized file format."); }

	fs.read((char*)&infoHeader, sizeof(infoHeader));
	fs.seekg(fileHeader.bfOffBits, ios::beg);


	pixelsData.reserve(infoHeader.biHeight);
	int linePadding = countPadding();
	//Нужно только для 24-битных .bmp файлов, т.к. если кол-во пикселей по ширине не кратно 4,
	//то в конце каждой строки добавляются нулевые байты для выравнивания
	for (int i{ 0 }; i < infoHeader.biHeight; i++)
	{
		vector<RGBTRIPLE> temp;
		temp.reserve(infoHeader.biWidth);
		for (int j{ 0 }; j < infoHeader.biWidth; j++)
		{
			RGBTRIPLE bufer;
			fs.read((char*)&bufer, sizeof(bufer));
			temp.push_back(bufer);
		}
		fs.seekg(linePadding, ios::cur);
		pixelsData.insert(pixelsData.begin(), temp);
		// добавляем строку пикселей в начало,т.к. первая строка пикселей в файле - последняя строка пикселей изображения
	}
	fs.clear();
	fs.close();
}

void BMP24::printInfo()
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
