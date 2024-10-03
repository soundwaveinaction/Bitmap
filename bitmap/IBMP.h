#pragma once
#include <string>
class IBMP {

public:
	~IBMP() {};
	virtual void displayBMP() = 0;

	virtual void closeBMP() = 0;

	virtual void openBMP(const std::string& fileName) = 0;

	virtual void printInfo() = 0;

};