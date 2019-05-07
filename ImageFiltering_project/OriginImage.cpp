#include "stdafx.h"
#include "OriginImage.h"

QString OriginImage::toStrFile()
{
	std::ostringstream oss;
	oss <<  "Images (*.jpg *.jpeg *.bmp *.gif *.png *.pbm *.pgm *.ppm *.xbm *.xpm)" ;	
	std::string filter = oss.str();
	QString end = QString::fromStdString(filter);
	return end;
}
