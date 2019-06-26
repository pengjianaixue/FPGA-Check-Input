#pragma once

#include <QtWidgets\QMainWindow>
#include <QtWidgets\QTableView>
#include <QtCore\QStringListModel>
#include <QtGui\QStandardItemModel>
#include <qabstractitemdelegate.h>
#include <QItemDelegate>
#include <QStyledItemDelegate>

#include "XmlReader.h"
#include "XmlWirter.h"
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
	bool SaveToXmlFile(int n_SaveMode=0);
	bool SaveFileAs();
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
	QLineEditDelegate		*m_pCleanInputDelegate;
	QLineEditDelegate		*m_pAddressInputDelegate;
	QLineEditDelegate		*m_pBitWidthInputDelegate;
	QLineEditDelegate		*m_pTargetVauleInputDelegate;
	QComboxDelegate			*m_pJugementChooseDelegate;
	QComboxDelegate			*m_pCleanCmdChooseDelegate;
	QComboxDelegate			*m_pRecordCmdChooseDelegate;
	QRegExpValidator        *m_pCleanInputValidator;
	QRegExpValidator        *m_pAddressInputValidator;
	QRegExpValidator		*m_pBitWidthInputValidator;
	QRegExpValidator        *m_pTargetVauleInputValidator;
	QFileDialog				*m_pSaveFileToXmlDirDialog;
	bool					 m_isLegalFlag;
	bool					 m_DataisChanged;
	QString					 m_strSaveFileName;
	XmlReader				*m_pXmlDataReader;
	XmlWirter				*m_pXmlDataWirter;
	QList<QStandardItem*>	 m_itemResourceKeepList;

	


};
