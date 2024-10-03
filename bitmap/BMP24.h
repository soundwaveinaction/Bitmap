#pragma once
#include"ibmp.h"
#include <Windows.h>
#include <vector>
using namespace std;
class BMP24 :public IBMP
{
private:
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	vector<vector<RGBTRIPLE>> pixelsData;
	long countPadding()
	{
		return (4 - (3 * infoHeader.biWidth) % 4) % 4;
	}
public:
	// Inherited via IBMP
	BMP24();
	~BMP24();
	void displayBMP() override;
	void closeBMP() override;
	void openBMP(const std::string& fileName) override;
	void printInfo() override;
};