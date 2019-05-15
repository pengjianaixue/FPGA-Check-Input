#pragma once

#include <QtWidgets\QMainWindow>
#include <QtWidgets\QTableView>
#include <QtCore\QStringListModel>
#include <QtGui\QStandardItemModel>
#include <qabstractitemdelegate.h>
#include <QItemDelegate>
#include <QStyledItemDelegate>

#include "ui_mainwindow.h"
#include "QComboxDelegate.h"
#include "QLableDelegate.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();
private:
	void StarupInit();
	void ConnectSlots();
public slots:
	void EditFinish(QStandardItem *item);
	bool SaveToXmlFile();
protected:
	void SaveKeyEvent(QKeyEvent* event);
private:
	Ui::MainWindowClass		ui;
	QStandardItemModel		m_RegisterItemModel;
	QStandardItemModel 		m_CleanCmdListModel;
	QStandardItemModel 		m_RecordCmdListModel;
	QList<QStandardItem*>	m_itemlist;
	QLableDelegate			*m_AddressInputDelegate;
	QLableDelegate			*m_BitWidthInputDelegate;
	QLableDelegate			*m_TargetVauleInputDelegate;
	QComboxDelegate			*m_JugementChooseDelegate;
	QComboxDelegate			*m_CleanCmdChooseDelegate;
	QComboxDelegate			*m_RecordCmdChooseDelegate;
	QRegExpValidator        *m_AddressInputValidator;
	QIntValidator			*m_BitWidthInputValidator;
	QRegExpValidator        *m_TargetVauleInputValidator;

	


};
