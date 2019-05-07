/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *formatImage;
    QAction *getHelp;
    QWidget *centralWidget;
    QComboBox *Filters;
    QLabel *label;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *fromFile;
    QPushButton *toFile;
    QSplitter *splitter;
    QPushButton *Cancel;
    QPushButton *Done;
    QMenuBar *menuBar;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(600, 401);
        formatImage = new QAction(MainWindowClass);
        formatImage->setObjectName(QString::fromUtf8("formatImage"));
        formatImage->setCheckable(false);
        formatImage->setChecked(false);
        getHelp = new QAction(MainWindowClass);
        getHelp->setObjectName(QString::fromUtf8("getHelp"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Filters = new QComboBox(centralWidget);
        Filters->addItem(QString());
        Filters->addItem(QString());
        Filters->addItem(QString());
        Filters->addItem(QString());
        Filters->addItem(QString());
        Filters->addItem(QString());
        Filters->addItem(QString());
        Filters->addItem(QString());
        Filters->addItem(QString());
        Filters->addItem(QString());
        Filters->addItem(QString());
        Filters->addItem(QString());
        Filters->addItem(QString());
        Filters->setObjectName(QString::fromUtf8("Filters"));
        Filters->setGeometry(QRect(141, 224, 301, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(141, 192, 181, 21));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(140, 20, 301, 131));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        fromFile = new QPushButton(layoutWidget);
        fromFile->setObjectName(QString::fromUtf8("fromFile"));

        verticalLayout->addWidget(fromFile);

        toFile = new QPushButton(layoutWidget);
        toFile->setObjectName(QString::fromUtf8("toFile"));

        verticalLayout->addWidget(toFile);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(310, 280, 186, 28));
        splitter->setOrientation(Qt::Horizontal);
        Cancel = new QPushButton(splitter);
        Cancel->setObjectName(QString::fromUtf8("Cancel"));
        splitter->addWidget(Cancel);
        Done = new QPushButton(splitter);
        Done->setObjectName(QString::fromUtf8("Done"));
        splitter->addWidget(Done);
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menuHelp->menuAction());
        menuHelp->addAction(formatImage);
        menuHelp->addAction(getHelp);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", nullptr));
        formatImage->setText(QApplication::translate("MainWindowClass", "Available formats", nullptr));
        getHelp->setText(QApplication::translate("MainWindowClass", "Get Help", nullptr));
        Filters->setItemText(0, QApplication::translate("MainWindowClass", "Brightening", nullptr));
        Filters->setItemText(1, QApplication::translate("MainWindowClass", "Darkening", nullptr));
        Filters->setItemText(2, QApplication::translate("MainWindowClass", "Emboss", nullptr));
        Filters->setItemText(3, QApplication::translate("MainWindowClass", "Find Edges", nullptr));
        Filters->setItemText(4, QApplication::translate("MainWindowClass", "Gaussian Filter", nullptr));
        Filters->setItemText(5, QApplication::translate("MainWindowClass", "Gaussian Smoothing", nullptr));
        Filters->setItemText(6, QApplication::translate("MainWindowClass", "Invert", nullptr));
        Filters->setItemText(7, QApplication::translate("MainWindowClass", "Median Filter", nullptr));
        Filters->setItemText(8, QApplication::translate("MainWindowClass", "Motion Blur", nullptr));
        Filters->setItemText(9, QApplication::translate("MainWindowClass", "Only Blue", nullptr));
        Filters->setItemText(10, QApplication::translate("MainWindowClass", "Only Green", nullptr));
        Filters->setItemText(11, QApplication::translate("MainWindowClass", "Only Red", nullptr));
        Filters->setItemText(12, QApplication::translate("MainWindowClass", "Sharpen", nullptr));

        label->setText(QApplication::translate("MainWindowClass", "Choose your image filter...", nullptr));
        fromFile->setText(QApplication::translate("MainWindowClass", "Choose your image", nullptr));
        toFile->setText(QApplication::translate("MainWindowClass", "Choose where to save your image", nullptr));
        Cancel->setText(QApplication::translate("MainWindowClass", "Cancel", nullptr));
        Done->setText(QApplication::translate("MainWindowClass", "Let's do it!", nullptr));
        menuHelp->setTitle(QApplication::translate("MainWindowClass", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
