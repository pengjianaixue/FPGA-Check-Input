#pragma once

#include <QtWidgets\QMainWindow>
#include <QtWidgets\QTableView>
#include <QtCore\QStringListModel>
#include <QtGui\QStandardItemModel>
#include <qabstractitemdelegate.h>
#include <QItemDelegate>
#include <QStyledItemDelegate>
#include <functional>
#include <memory>
#include <map>
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
	using ITEMCALLBACKFUNC		= std::function<bool(MainWindow* ,QStandardItem*)>;
	using ITEMCALLBACKFUNCMAP	= std::map<int, ITEMCALLBACKFUNC>;
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
	bool AddItemProcessCallBackfunc(size_t TableType, size_t itemcontents, ITEMCALLBACKFUNC func);
	bool ExecItemInputProcess(size_t TableType, size_t column, QStandardItem *item);
	bool AboutActionDialog();
	/**********************************
			ItemCallBack function
	***********************************/
	//Register Input item callback 
	bool Add0xPrefixtonum(QStandardItem *item);
	bool CheckBitWidthInput(QStandardItem *item);
	bool legalJudgement(QStandardItem *item);
	bool SpecilJudgementConditionProc(QStandardItem *item);
	//clean and  record  Input item callback 
	bool AutoFillTheCommand(QStandardItem *item);
	bool AddDouble0xPrefixtonum(QStandardItem *item);
	

protected:
	void keyPressEvent(QKeyEvent* event);
private:
	Ui::MainWindowClass						ui;
	QStandardItemModel						m_RegisterItemModel;
	QStandardItemModel 						m_CleanCmdListModel;
	QStandardItemModel 						m_RecordCmdListModel;
	QList<QStandardItem*>					m_itemlist;
	std::shared_ptr<QLineEditDelegate>		m_pCleanInputDelegate;
	std::shared_ptr<QLineEditDelegate>		m_pAddressInputDelegate;
	std::shared_ptr<QLineEditDelegate>		m_pBitWidthInputDelegate;
	std::shared_ptr<QLineEditDelegate>		m_pTargetVauleInputDelegate;
	std::shared_ptr<QComboxDelegate>		m_pJugementChooseDelegate;
	std::shared_ptr<QComboxDelegate>		m_pCleanCmdChooseDelegate;
	std::shared_ptr<QComboxDelegate>		m_pRecordCmdChooseDelegate;
	std::shared_ptr<QRegExpValidator>		m_pCleanInputValidator;
	std::shared_ptr<QRegExpValidator>		m_pAddressInputValidator;
	std::shared_ptr<QRegExpValidator>		m_pBitWidthInputValidator;
	std::shared_ptr<QRegExpValidator>		m_pTargetVauleInputValidator;
	std::shared_ptr<QFileDialog>			m_pSaveFileToXmlDirDialog;
	/*QLineEditDelegate		*m_pAddressInputDelegate;
	QLineEditDelegate		*m_pBitWidthInputDelegate;
	QLineEditDelegate		*m_pTargetVauleInputDelegate;
	QComboxDelegate			*m_pJugementChooseDelegate;
	QComboxDelegate			*m_pCleanCmdChooseDelegate;
	QComboxDelegate			*m_pRecordCmdChooseDelegate;
	QRegExpValidator        *m_pCleanInputValidator;
	QRegExpValidator        *m_pAddressInputValidator;
	QRegExpValidator		*m_pBitWidthInputValidator;
	QRegExpValidator        *m_pTargetVauleInputValidator;
	QFileDialog				*m_pSaveFileToXmlDirDialog;*/
	bool									m_isLegalFlag;
	bool									m_DataisChanged;
	QString									m_strSaveFileName;
	std::shared_ptr<XmlReader>				m_pXmlDataReader;
	std::shared_ptr<XmlWirter>				m_pXmlDataWirter;
	QList<QStandardItem*>					m_itemResourceKeepList;
	ITEMCALLBACKFUNCMAP						m_RegisterCallBackFunctionumap;
	ITEMCALLBACKFUNCMAP						m_CleanAndRecordCallBackFunctionumap;

	


};
