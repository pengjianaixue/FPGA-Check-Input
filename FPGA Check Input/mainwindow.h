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
#include "QCheckBoxDelegate.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();
private:
	void StarupInit();
public slots:
	void EditFinish(const QModelIndex &index);
private:
	Ui::MainWindowClass		ui;
	QStandardItemModel		m_RegisterItemModel;
	QStringListModel		m_CleanCmdListModel;
	QStringListModel		m_RecordCmdListModel;
	QItemDelegate			m_JugementItemChooseDelegate;
	QItemDelegate			m_legalcheckboxDelegate;
	QItemEditorFactory		m_JugementItemChooseDelegateFactory;
	QItemEditorFactory		m_legalcheckboxFactory;
	QItemEditorCreatorBase  *m_DelegateBase;
	QItemEditorCreatorBase  *m_DelegateCheckboxBase;
	QList<QStandardItem*>	m_itemlist;
	QCheckBoxDelegate		*m_LegalcheckboxDelegate;
	QComboxDelegate			*m_JugementChooseDelegate;

	


};
