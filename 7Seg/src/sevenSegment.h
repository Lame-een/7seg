#pragma once

class SevSeg
{

private:
	static const unsigned int segmentList[7][12];

	static const bool encodedSegments[16][7];

public:
	static void retIBO(unsigned int* IBO, unsigned int& iboSize, int inNum);
};