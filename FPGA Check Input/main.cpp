#include "stdafx.h"
#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);
	QApplication::setStyle(QStyleFactory::create("Fusion"));
	MainWindow w;
	w.setWindowTitle("FPGA Self-Check Input Tool");
	w.setMinimumSize(200, 150); 
	w.show();
	return a.exec();
}
