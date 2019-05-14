#include "stdafx.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), m_LegalcheckboxDelegate( new QCheckBoxDelegate(this))
	  , m_JugementChooseDelegate(new QComboxDelegate(this))
{
	ui.setupUi(this);
	StarupInit();
}

MainWindow::~MainWindow()
{
	delete m_LegalcheckboxDelegate;
	delete m_JugementChooseDelegate;
	

}

void MainWindow::StarupInit()
{

	m_CleanCmdListModel.setHeaderData(0,Qt::Orientation::Vertical, QObject::tr("Clean Command List"));
	m_RecordCmdListModel.setHeaderData(0, Qt::Orientation::Vertical, QObject::tr("Record Command List"));

	m_RegisterItemModel.setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("Register Address"))); 
	m_RegisterItemModel.setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("Bit Width"))); 
	m_RegisterItemModel.setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("Judgement"))); 
	m_RegisterItemModel.setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("Target Vaule"))); 
	m_RegisterItemModel.setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("Is legal")));
	m_RegisterItemModel.setRowCount(40);
	m_RegisterItemModel.setColumnCount(5);
	ui.tableView_CheckRegister->setItemDelegateForColumn(2, m_JugementChooseDelegate);
	ui.tableView_CheckRegister->setItemDelegateForColumn(4, m_LegalcheckboxDelegate);
	ui.tableView_CheckRegister->horizontalHeader()->setStretchLastSection(true);
	ui.tableView_CheckRegister->doItemsLayout();
	//ui.tableView_CheckRegister->setDragEnabled(true);
	//ui.tableView_CheckRegister->setDragDropMode(QAbstractItemView::DragDropMode::InternalMove);
	//ui.tableView_CheckRegister->setDefaultDropAction(Qt::DropAction::CopyAction);
	ui.listView_CleanCmd->setModel(&m_CleanCmdListModel);
	ui.listView_RecordCmd->setModel(&m_RecordCmdListModel);
	ui.tableView_CheckRegister->setModel(&m_RegisterItemModel);
	/*for (size_t i = 0; i < 40; i++)
	{
		m_itemlist.clear();
		m_itemlist.append(new QStandardItem());
		m_RegisterItemModel.appendRow(m_itemlist);
	}*/
	
	
	
}
