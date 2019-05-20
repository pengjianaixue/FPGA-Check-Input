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
#include "QLineEditDelegate.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();
private:
	void InitandCreaterVar();
	void InitModel();
	void ConnectSlots();
public slots:
	void RegisterCheckEditFinish(QStandardItem *item);
	void CleanAndRecordCmdEditFinish(QStandardItem *item);
	bool SaveToXmlFile();
	bool NewFile();
	bool DataChangedfalg();
	bool OpenFile();

protected:
	void keyPressEvent(QKeyEvent* event);
private:
	Ui::MainWindowClass		ui;
	QStandardItemModel		m_RegisterItemModel;
	QStandardItemModel 		m_CleanCmdListModel;
	QStandardItemModel 		m_RecordCmdListModel;
	QList<QStandardItem*>	m_itemlist;
	QLineEditDelegate		*m_AddressInputDelegate;
	QLineEditDelegate		*m_BitWidthInputDelegate;
	QLineEditDelegate		*m_TargetVauleInputDelegate;
	QComboxDelegate			*m_JugementChooseDelegate;
	QComboxDelegate			*m_CleanCmdChooseDelegate;
	QComboxDelegate			*m_RecordCmdChooseDelegate;
	QRegExpValidator        *m_AddressInputValidator;
	QRegExpValidator		*m_BitWidthInputValidator;
	QRegExpValidator        *m_TargetVauleInputValidator;
	QFileDialog				*m_SaveFileToXmlDirDialog;
	bool					 m_isLegalFlag;
	bool					 m_DataisChanged;
	QString					 m_strSaveFileName;

	


};
