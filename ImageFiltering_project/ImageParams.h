#pragma once
#include <OriginImage.h>
#include <memory>

class ImageParams : public OriginImage {
public:
	uchar* bits; //= image.bits(); // get pointer of the 1st uchar of bits table
	uchar* bitsEnd; //= bits + image.sizeInBytes(); // get pointer of the last uchar of bits table
};