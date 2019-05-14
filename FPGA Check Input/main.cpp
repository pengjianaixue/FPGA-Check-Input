#include "stdafx.h"
#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);
	QApplication::setStyle(QStyleFactory::create("Fusion"));
	MainWindow w;
	w.setWindowTitle("FPGA Check Input");
	w.show();
	return a.exec();
}
