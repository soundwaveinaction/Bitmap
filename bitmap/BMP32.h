#pragma once
#pragma once
#include"ibmp.h"
#include <Windows.h>
#include <vector>
using namespace std;
class BMP32 :public IBMP {
	// Inherited via IBMP
private:
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	vector<vector<RGBQUAD>> pixelsData;
	long countPadding()
	{
		return (4 - (3 * infoHeader.biWidth) % 4) % 4;
	}
public:
	BMP32();
	~BMP32();
	void displayBMP() override;
	void closeBMP() override;
	void openBMP(const std::string& fileName) override;
	void printInfo() override;
};