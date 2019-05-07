#include "stdafx.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.Done, SIGNAL(released()), this, SLOT(done()));
	connect(ui.Cancel, SIGNAL(released()), this, SLOT(cancel()));
	connect(ui.fromFile, SIGNAL(released()), this, SLOT(fromFile()));
	connect(ui.toFile, SIGNAL(released()), this, SLOT(toStrFile()));
	connect(ui.formatImage, SIGNAL(triggered()), this, SLOT(formatImage()));
	connect(ui.getHelp, SIGNAL(triggered()), this, SLOT(help()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::fromFile()
{
	//create filter to right formats of pictures
	std::ostringstream oss;
	oss << "Images (*.jpg *.jpeg *.bmp *.png *.pbm *.pgm *.ppm *.xbm *.xpm)";
	std::string filterString = oss.str();
	std::vector<QString> filter;
	filter.emplace_back(QString::fromStdString(filterString));
	QString tmp = filter[0];
	

	//search for your image from files in your computer, and choose right format of picture
	QString imageName = QFileDialog::getOpenFileName(this, "Choose your image", "C://", tmp);
	filter.clear();
	//
	////show info about properly used image format, or show an error
	//QMimeDatabase searchForImage;
	//QMimeType search = searchForImage.mimeTypeForFile(imageName);
	//if(search.inherits("image / bmp")|| search.inherits("image / jpeg")|| search.inherits("image / gif")|| search.inherits("image / png") || search.inherits("image / x-portable-bitmap") || search.inherits("image / x-portable-graymap") || search.inherits("image /x - portable - pixmap") || search.inherits("image / x-xbitmap") || search.inherits("image / x - xpixmap") || search.inherits("image / svg + xml"))
		QMessageBox::information(this, "Name of your image", imageName);
	//else
	//	QMessageBox::information(this, "Error", "The current file is not an image or it is unable to open,\nplease check the valid format of image.");
	
	//get name of picture u want to use 
	fromWhere = imageName;
}

QString MainWindow::toStrFile()
{
	//set your destination, where you want to have your filterred image
	QString destinationOfImage = QFileDialog::getSaveFileName(this, "Choose where to save your image", "C://");
	QMessageBox::information(this, "Destination of image", destinationOfImage);

	destination = destinationOfImage;
	return 0;
}

void MainWindow::filtering()
{
}



void MainWindow::cancel()
{
	
	[&]() {QMessageBox::information(this, "Info", "Your program is ending."); };

	exit(0);
}

void MainWindow::done()
{
	//create class of image, that is chosen by user
	QImage image(fromWhere);


		//get info about image
		ImageParams params;
		params.h = image.height();
		params.w = image.width();
		params.bits = image.bits();
		params.bitsEnd = params.bits + image.sizeInBytes();

		//use negation on image
		if (ui.Filters->currentText() == "Invert")
		{
			for (uchar* index = params.bits; index < params.bitsEnd; index += 4)
			{
				invert(index);
				invert(index + 1);
				invert(index + 2);
			}
		};

		//gaussian blur 3x3
		if (ui.Filters->currentText() == "Gaussian Filter")
		{
			QMatrix3x3 kernel;
			kernel(0, 0) = 1; kernel(0, 1) = 2; kernel(0, 2) = 1;
			kernel(1, 0) = 2; kernel(1, 1) = 4; kernel(1, 2) = 2;
			kernel(2, 0) = 1; kernel(2, 1) = 2; kernel(2, 2) = 1;
			float kernel_sum = 16.0;


			for (int i = 1; i < image.width() - 1; i++)
			{
				for (int j = 1; j < image.height() - 1; j++)
				{
					float red = 0, green = 0, blue = 0;

					// *****************************************************
					red =
						kernel(0, 0) * qRed(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qRed(image.pixel(i, j + 1)) +
						kernel(0, 2) * qRed(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qRed(image.pixel(i + 1, j)) +
						kernel(1, 1) * qRed(image.pixel(i, j)) +
						kernel(1, 2) * qRed(image.pixel(i - 1, j)) +

						kernel(2, 0) * qRed(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qRed(image.pixel(i, j - 1)) +
						kernel(2, 2) * qRed(image.pixel(i - 1, j - 1));

					// *****************************************************
					green =
						kernel(0, 0) * qGreen(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qGreen(image.pixel(i, j + 1)) +
						kernel(0, 2) * qGreen(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qGreen(image.pixel(i + 1, j)) +
						kernel(1, 1) * qGreen(image.pixel(i, j)) +
						kernel(1, 2) * qGreen(image.pixel(i - 1, j)) +

						kernel(2, 0) * qGreen(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qGreen(image.pixel(i, j - 1)) +
						kernel(2, 2) * qGreen(image.pixel(i - 1, j - 1));

					// *****************************************************
					blue =
						kernel(0, 0) * qBlue(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qBlue(image.pixel(i, j + 1)) +
						kernel(0, 2) * qBlue(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qBlue(image.pixel(i + 1, j)) +
						kernel(1, 1) * qBlue(image.pixel(i, j)) +
						kernel(1, 2) * qBlue(image.pixel(i - 1, j)) +

						kernel(2, 0) * qBlue(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qBlue(image.pixel(i, j - 1)) +
						kernel(2, 2) * qBlue(image.pixel(i - 1, j - 1));

					image.setPixel(i, j, qRgb(red / kernel_sum, green / kernel_sum, blue / kernel_sum));

				}
			}
		}

		//filtrated image is blurred in diagonal
		if (ui.Filters->currentText() == "Motion Blur")
		{
			QMatrix3x3 kernel;
			kernel(0, 0) = 1; kernel(0, 1) = 0; kernel(0, 2) = 0;
			kernel(1, 0) = 0; kernel(1, 1) = 1; kernel(1, 2) = 0;
			kernel(2, 0) = 0; kernel(2, 1) = 0; kernel(2, 2) = 1;
			float kernel_sum = 3.0;


			for (int i = 1; i < image.width() - 1; i++)
			{
				for (int j = 1; j < image.height() - 1; j++)
				{
					float red = 0, green = 0, blue = 0;

					// *****************************************************
					red =
						kernel(0, 0) * qRed(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qRed(image.pixel(i, j + 1)) +
						kernel(0, 2) * qRed(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qRed(image.pixel(i + 1, j)) +
						kernel(1, 1) * qRed(image.pixel(i, j)) +
						kernel(1, 2) * qRed(image.pixel(i - 1, j)) +

						kernel(2, 0) * qRed(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qRed(image.pixel(i, j - 1)) +
						kernel(2, 2) * qRed(image.pixel(i - 1, j - 1));

					// *****************************************************
					green =
						kernel(0, 0) * qGreen(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qGreen(image.pixel(i, j + 1)) +
						kernel(0, 2) * qGreen(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qGreen(image.pixel(i + 1, j)) +
						kernel(1, 1) * qGreen(image.pixel(i, j)) +
						kernel(1, 2) * qGreen(image.pixel(i - 1, j)) +

						kernel(2, 0) * qGreen(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qGreen(image.pixel(i, j - 1)) +
						kernel(2, 2) * qGreen(image.pixel(i - 1, j - 1));

					// *****************************************************
					blue =
						kernel(0, 0) * qBlue(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qBlue(image.pixel(i, j + 1)) +
						kernel(0, 2) * qBlue(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qBlue(image.pixel(i + 1, j)) +
						kernel(1, 1) * qBlue(image.pixel(i, j)) +
						kernel(1, 2) * qBlue(image.pixel(i - 1, j)) +

						kernel(2, 0) * qBlue(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qBlue(image.pixel(i, j - 1)) +
						kernel(2, 2) * qBlue(image.pixel(i - 1, j - 1));

					image.setPixel(i, j, qRgb(red / kernel_sum, green / kernel_sum, blue / kernel_sum));

				}
			}
		}

		//filtrated image shows edges on image
		if (ui.Filters->currentText() == "Find Edges")
		{
			QMatrix3x3 kernel;
			kernel(0, 0) = 0; kernel(0, 1) = -1; kernel(0, 2) = 0;
			kernel(1, 0) = 0; kernel(1, 1) = 2; kernel(1, 2) = 0;
			kernel(2, 0) = 0; kernel(2, 1) = 0; kernel(2, 2) = 0;
			float kernel_sum = 1.0;


			for (int i = 1; i < image.width() - 1; i++)
			{
				for (int j = 1; j < image.height() - 1; j++)
				{
					float red = 0, green = 0, blue = 0;

					// *****************************************************
					red =
						kernel(0, 0) * qRed(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qRed(image.pixel(i, j + 1)) +
						kernel(0, 2) * qRed(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qRed(image.pixel(i + 1, j)) +
						kernel(1, 1) * qRed(image.pixel(i, j)) +
						kernel(1, 2) * qRed(image.pixel(i - 1, j)) +

						kernel(2, 0) * qRed(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qRed(image.pixel(i, j - 1)) +
						kernel(2, 2) * qRed(image.pixel(i - 1, j - 1));

					// *****************************************************
					green =
						kernel(0, 0) * qGreen(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qGreen(image.pixel(i, j + 1)) +
						kernel(0, 2) * qGreen(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qGreen(image.pixel(i + 1, j)) +
						kernel(1, 1) * qGreen(image.pixel(i, j)) +
						kernel(1, 2) * qGreen(image.pixel(i - 1, j)) +

						kernel(2, 0) * qGreen(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qGreen(image.pixel(i, j - 1)) +
						kernel(2, 2) * qGreen(image.pixel(i - 1, j - 1));

					// *****************************************************
					blue =
						kernel(0, 0) * qBlue(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qBlue(image.pixel(i, j + 1)) +
						kernel(0, 2) * qBlue(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qBlue(image.pixel(i + 1, j)) +
						kernel(1, 1) * qBlue(image.pixel(i, j)) +
						kernel(1, 2) * qBlue(image.pixel(i - 1, j)) +

						kernel(2, 0) * qBlue(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qBlue(image.pixel(i, j - 1)) +
						kernel(2, 2) * qBlue(image.pixel(i - 1, j - 1));

					image.setPixel(i, j, qRgb(red / kernel_sum, green / kernel_sum, blue / kernel_sum));

				}
			}
		}

		//filtrated image shows edges on image
		if (ui.Filters->currentText() == "Sharpen")
		{
			QMatrix3x3 kernel;
			kernel(0, 0) = -1 / 8; kernel(0, 1) = -1 / 8; kernel(0, 2) = -1 / 8;
			kernel(1, 0) = -1 / 8; kernel(1, 1) = 16 / 8; kernel(1, 2) = -1 / 8;
			kernel(2, 0) = -1 / 8; kernel(2, 1) = -1 / 8; kernel(2, 2) = -1 / 8;
			float kernel_sum = 2.0;


			for (int i = 1; i < image.width() - 1; i++)
			{
				for (int j = 1; j < image.height() - 1; j++)
				{
					float red = 0, green = 0, blue = 0;

					// *****************************************************
					red =
						kernel(0, 0) * qRed(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qRed(image.pixel(i, j + 1)) +
						kernel(0, 2) * qRed(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qRed(image.pixel(i + 1, j)) +
						kernel(1, 1) * qRed(image.pixel(i, j)) +
						kernel(1, 2) * qRed(image.pixel(i - 1, j)) +

						kernel(2, 0) * qRed(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qRed(image.pixel(i, j - 1)) +
						kernel(2, 2) * qRed(image.pixel(i - 1, j - 1));

					// *****************************************************
					green =
						kernel(0, 0) * qGreen(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qGreen(image.pixel(i, j + 1)) +
						kernel(0, 2) * qGreen(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qGreen(image.pixel(i + 1, j)) +
						kernel(1, 1) * qGreen(image.pixel(i, j)) +
						kernel(1, 2) * qGreen(image.pixel(i - 1, j)) +

						kernel(2, 0) * qGreen(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qGreen(image.pixel(i, j - 1)) +
						kernel(2, 2) * qGreen(image.pixel(i - 1, j - 1));

					// *****************************************************
					blue =
						kernel(0, 0) * qBlue(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qBlue(image.pixel(i, j + 1)) +
						kernel(0, 2) * qBlue(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qBlue(image.pixel(i + 1, j)) +
						kernel(1, 1) * qBlue(image.pixel(i, j)) +
						kernel(1, 2) * qBlue(image.pixel(i - 1, j)) +

						kernel(2, 0) * qBlue(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qBlue(image.pixel(i, j - 1)) +
						kernel(2, 2) * qBlue(image.pixel(i - 1, j - 1));

					image.setPixel(i, j, qRgb(red / kernel_sum, green / kernel_sum, blue / kernel_sum));

				}
			}
		}

		//filtrated image shows edges on image, embossing effect
		if (ui.Filters->currentText() == "Emboss")
		{
			QMatrix3x3 kernel;
			kernel(0, 0) = 0; kernel(0, 1) = -1; kernel(0, 2) = 0;
			kernel(1, 0) = 0; kernel(1, 1) = 2; kernel(1, 2) = 0;
			kernel(2, 0) = 0; kernel(2, 1) = -1; kernel(2, 2) = 0;
			float kernel_sum = 1.0;


			for (int i = 1; i < image.width() - 1; i++)
			{
				for (int j = 1; j < image.height() - 1; j++)
				{
					float red = 0, green = 0, blue = 0;

					// *****************************************************
					red =
						kernel(0, 0) * qRed(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qRed(image.pixel(i, j + 1)) +
						kernel(0, 2) * qRed(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qRed(image.pixel(i + 1, j)) +
						kernel(1, 1) * qRed(image.pixel(i, j)) +
						kernel(1, 2) * qRed(image.pixel(i - 1, j)) +

						kernel(2, 0) * qRed(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qRed(image.pixel(i, j - 1)) +
						kernel(2, 2) * qRed(image.pixel(i - 1, j - 1));

					// *****************************************************
					green =
						kernel(0, 0) * qGreen(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qGreen(image.pixel(i, j + 1)) +
						kernel(0, 2) * qGreen(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qGreen(image.pixel(i + 1, j)) +
						kernel(1, 1) * qGreen(image.pixel(i, j)) +
						kernel(1, 2) * qGreen(image.pixel(i - 1, j)) +

						kernel(2, 0) * qGreen(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qGreen(image.pixel(i, j - 1)) +
						kernel(2, 2) * qGreen(image.pixel(i - 1, j - 1));

					// *****************************************************
					blue =
						kernel(0, 0) * qBlue(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qBlue(image.pixel(i, j + 1)) +
						kernel(0, 2) * qBlue(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qBlue(image.pixel(i + 1, j)) +
						kernel(1, 1) * qBlue(image.pixel(i, j)) +
						kernel(1, 2) * qBlue(image.pixel(i - 1, j)) +

						kernel(2, 0) * qBlue(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qBlue(image.pixel(i, j - 1)) +
						kernel(2, 2) * qBlue(image.pixel(i - 1, j - 1));

					image.setPixel(i, j, qRgb(red / kernel_sum, green / kernel_sum, blue / kernel_sum));

				}
			}
		}

		//filtrated image shows median filtered image
		if (ui.Filters->currentText() == "Median Filter")
		{
			QMatrix3x3 kernel;
			kernel(0, 0) = 1; kernel(0, 1) = 1; kernel(0, 2) = 1;
			kernel(1, 0) = 1; kernel(1, 1) = 1; kernel(1, 2) = 1;
			kernel(2, 0) = 1; kernel(2, 1) = 1; kernel(2, 2) = 1;
			float kernel_sum = 9.0;


			for (int i = 1; i < image.width() - 1; i++)
			{
				for (int j = 1; j < image.height() - 1; j++)
				{
					float red = 0, green = 0, blue = 0;

					// *****************************************************
					red =
						kernel(0, 0) * qRed(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qRed(image.pixel(i, j + 1)) +
						kernel(0, 2) * qRed(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qRed(image.pixel(i + 1, j)) +
						kernel(1, 1) * qRed(image.pixel(i, j)) +
						kernel(1, 2) * qRed(image.pixel(i - 1, j)) +

						kernel(2, 0) * qRed(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qRed(image.pixel(i, j - 1)) +
						kernel(2, 2) * qRed(image.pixel(i - 1, j - 1));

					// *****************************************************
					green =
						kernel(0, 0) * qGreen(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qGreen(image.pixel(i, j + 1)) +
						kernel(0, 2) * qGreen(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qGreen(image.pixel(i + 1, j)) +
						kernel(1, 1) * qGreen(image.pixel(i, j)) +
						kernel(1, 2) * qGreen(image.pixel(i - 1, j)) +

						kernel(2, 0) * qGreen(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qGreen(image.pixel(i, j - 1)) +
						kernel(2, 2) * qGreen(image.pixel(i - 1, j - 1));

					// *****************************************************
					blue =
						kernel(0, 0) * qBlue(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qBlue(image.pixel(i, j + 1)) +
						kernel(0, 2) * qBlue(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qBlue(image.pixel(i + 1, j)) +
						kernel(1, 1) * qBlue(image.pixel(i, j)) +
						kernel(1, 2) * qBlue(image.pixel(i - 1, j)) +

						kernel(2, 0) * qBlue(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qBlue(image.pixel(i, j - 1)) +
						kernel(2, 2) * qBlue(image.pixel(i - 1, j - 1));

					image.setPixel(i, j, qRgb(red / kernel_sum, green / kernel_sum, blue / kernel_sum));

				}
			}
		}

		//
		if (ui.Filters->currentText() == "Gaussian Smoothing")
		{
			QMatrix3x3 kernel;
			kernel(0, 0) = 1; kernel(0, 1) = 4; kernel(0, 2) = 1;
			kernel(1, 0) = 4; kernel(1, 1) = 7; kernel(1, 2) = 4;
			kernel(2, 0) = 1; kernel(2, 1) = 4; kernel(2, 2) = 1;
			float kernel_sum = 27.0;


			for (int i = 1; i < image.width() - 1; i++)
			{
				for (int j = 1; j < image.height() - 1; j++)
				{
					float red = 0, green = 0, blue = 0;

					// *****************************************************
					red =
						kernel(0, 0) * qRed(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qRed(image.pixel(i, j + 1)) +
						kernel(0, 2) * qRed(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qRed(image.pixel(i + 1, j)) +
						kernel(1, 1) * qRed(image.pixel(i, j)) +
						kernel(1, 2) * qRed(image.pixel(i - 1, j)) +

						kernel(2, 0) * qRed(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qRed(image.pixel(i, j - 1)) +
						kernel(2, 2) * qRed(image.pixel(i - 1, j - 1));

					// *****************************************************
					green =
						kernel(0, 0) * qGreen(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qGreen(image.pixel(i, j + 1)) +
						kernel(0, 2) * qGreen(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qGreen(image.pixel(i + 1, j)) +
						kernel(1, 1) * qGreen(image.pixel(i, j)) +
						kernel(1, 2) * qGreen(image.pixel(i - 1, j)) +

						kernel(2, 0) * qGreen(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qGreen(image.pixel(i, j - 1)) +
						kernel(2, 2) * qGreen(image.pixel(i - 1, j - 1));

					// *****************************************************
					blue =
						kernel(0, 0) * qBlue(image.pixel(i + 1, j + 1)) +
						kernel(0, 1) * qBlue(image.pixel(i, j + 1)) +
						kernel(0, 2) * qBlue(image.pixel(i - 1, j + 1)) +

						kernel(1, 0) * qBlue(image.pixel(i + 1, j)) +
						kernel(1, 1) * qBlue(image.pixel(i, j)) +
						kernel(1, 2) * qBlue(image.pixel(i - 1, j)) +

						kernel(2, 0) * qBlue(image.pixel(i + 1, j - 1)) +
						kernel(2, 1) * qBlue(image.pixel(i, j - 1)) +
						kernel(2, 2) * qBlue(image.pixel(i - 1, j - 1));

					image.setPixel(i, j, qRgb(red / kernel_sum, green / kernel_sum, blue / kernel_sum));

				}
			}
		}

		//get brither image, by constant adding value
		if (ui.Filters->currentText() == "Brightening")
		{
			for (uchar* index = params.bits; index < params.bitsEnd; index += 4)
			{
				addOrSubtraction(index, 50);
				addOrSubtraction(index + 1, 50);
				addOrSubtraction(index + 2, 50);
			}
		}

		//get darker image, by constant substraction
		if (ui.Filters->currentText() == "Darkening")
		{
			for (uchar* index = params.bits; index < params.bitsEnd; index += 4)
			{
				addOrSubtraction(index, -50);
				addOrSubtraction(index + 1, -50);
				addOrSubtraction(index + 2, -50);
			}
		}

		//get only red color
		if (ui.Filters->currentText() == "Only Red")
		{
			for (uchar* index = params.bits; index < params.bitsEnd; index += 4)
			{
				getColor(index);
				reset(index + 1);
				reset(index + 2);
			}
		}

		//get only green color
		if (ui.Filters->currentText() == "Only Green")
		{
			for (uchar* index = params.bits; index < params.bitsEnd; index += 4)
			{
				reset(index);
				getColor(index + 1);
				reset(index + 2);
			}
		}

		//get only blue color
		if (ui.Filters->currentText() == "Only Blue")
		{
			for (uchar* index = params.bits; index < params.bitsEnd; index += 4)
			{
				reset(index);
				reset(index + 1);
				getColor(index + 2);
			}
		}


		//QImageReader reader(fromWhere); 
		
		QImageReader reader(fromWhere);

		QString formatOfImage = reader.format();
		QString fullName = destination + "." + formatOfImage;
		
		image.save(fullName);

		QMessageBox::information(this, "Info", "Your image is ready.");
		
		//QMessageBox::information(this, "Info", "There is error in filtrating image, please try again\nor use another image.");	
}



void MainWindow::formatImage()
{
	QMessageBox::information(this, "Available formats of image", "You can use those formats to filtering the image:\n- *.jpg\n- *.bmp\n- *.tif\n- *.png");
}

void MainWindow::help()
{
	QMessageBox::information(this, "Help", "To proper use this app:\n 1. Click 'Choose your image' to pick image.\n 2. Click 'Choose where to save your image' to pick destination.\n 3. Choose one of available filters.\n 4. To confirm click 'Let's do it!'.");
}
