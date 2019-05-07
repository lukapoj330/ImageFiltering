#pragma once
#include <sstream>
#include <VirtualClass.h> 

class OriginImage : public VirtualClass{
public:
	int w; //width of image
	int h; //high of image

	QString toStrFile();
};

