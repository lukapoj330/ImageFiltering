#include <Filters.h>
#include <stdafx.h>

void invert(uchar* value)
{
	*value = 255 - (int)* value;
}


void addOrSubtraction(uchar* value, int add) 
{
	*value = (int)*value + add < 255 ? ((int)*value + add > 0 ? *value + add : 0) : 255;
}


void getColor(uchar * value)
{
	*value = (int)* value;
}

void reset(uchar * value)
{
	*value = 0;
}


