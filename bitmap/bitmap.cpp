#include <iostream>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <string>
#include "BMP32.h"
#include "BMP24.h"

using namespace std;


int main(int argc, char* argv[])
{
	//const string fileName = argv[0];
	const string fileName("24bit_satisfying_width.bmp");
	//24bit_need_padding.bmp
	//24bit_satisfying_width.bmp
	//32bit.bmp
	fstream fs(fileName);

	if (!fs.is_open()) { throw std::runtime_error("Error opening file"); }

	fs.seekg(sizeof(BITMAPFILEHEADER), ios::beg);

	BITMAPINFOHEADER bitCountCheck;

	fs.read((char*)&bitCountCheck, sizeof(bitCountCheck));
	fs.clear();
	fs.close();

	IBMP* image;

	if (bitCountCheck.biBitCount == 24)
	{
		image = new BMP24();
	}
	else if (bitCountCheck.biBitCount == 32)
	{
		image = new BMP32();
	}
	else { throw runtime_error("Error!Programm supports only 24 and 32 bit bitmap!"); }

	image->openBMP(fileName);

	image->displayBMP();

	image->printInfo();

	image->closeBMP();

	delete image;

	return 1;
}

