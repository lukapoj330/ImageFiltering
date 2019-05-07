#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QMimeDatabase>
#include <stdlib.h>
#include <OriginImage.h>
#include <Filters.h>
#include <ImageParams.h>
#include <VirtualClass.h>
#include <vector>


class MainWindow : public QMainWindow, public VirtualClass
{
	Q_OBJECT

public:
	QString fromWhere;		//global variable, holds the name and destination
	QString destination;	//global variable, holds the place where to create filteres image
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

private:
	Ui::MainWindowClass ui;
	
public slots:
	void filtering(); 

	//it save place where the user want to have an image
	QString toStrFile();

	//get the image to filtered
	void fromFile();

	//exit the app
	void cancel();

	//main function, use to filtrating image
	void done();

	//sort of help, describe what formats can be used
	void formatImage();

	void help();
};
