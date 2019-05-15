#include "stdafx.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	StarupInit();
}

MainWindow::~MainWindow()
{

	delete m_AddressInputDelegate;
	delete m_JugementChooseDelegate;
	delete m_BitWidthInputDelegate;
	delete m_TargetVauleInputDelegate;
	delete m_AddressInputValidator;
	delete m_BitWidthInputValidator;
	delete m_TargetVauleInputValidator;
}
void  MainWindow::EditFinish(QStandardItem *Item)
{
	disconnect(&this->m_RegisterItemModel, &QStandardItemModel::itemChanged, this, &MainWindow::EditFinish);
	int colunum =  Item->column();
	int row		=  Item->row();
	if ((colunum == 0 || colunum == 3) && !Item->text().isEmpty() && !Item->text().startsWith("0x"))
	{
		QString data = Item->text();
		Item->setText("0x" + Item->text());
	}
	unsigned int itemcontentcount = 0;
	for (size_t i = 0; i < 4; i++)
	{
		
		if (Item->model()->item(row, i))
		{
			if (!Item->model()->item(row, i)->text().isEmpty())
				itemcontentcount++;

		}
		
	}
	if (itemcontentcount!=4)
	{
		Item->model()->item(row, 4)->setText("Need Complete");
		Item->model()->item(row, 4)->setBackground(QBrush(QColor(qRgb(255, 0, 0))));
	}
	else if (itemcontentcount==4)
	{

	
		Item->model()->item(row, 4)->setText("legal");
		Item->model()->item(row, 4)->setBackground(QBrush(QColor(qRgb(0, 255, 0))));
	}
	else if (itemcontentcount == 0)
	{
		Item->model()->item(row, 4)->setText("");
		Item->model()->item(row, 4)->setBackground(QBrush(QColor(qRgb(255, 255, 255))));
	

	}
	connect(&this->m_RegisterItemModel, &QStandardItemModel::itemChanged, this, &MainWindow::EditFinish);
}
void MainWindow::StarupInit()
{

	m_AddressInputValidator		=	new  QRegExpValidator(QRegExp("[0-9|A-F|a-f]{,16}"));
	m_BitWidthInputValidator	=	new  QIntValidator(0,63,this);
	m_TargetVauleInputValidator =	new	 QRegExpValidator(QRegExp("[0-9|A-F|a-f]{,16}"));
	m_AddressInputDelegate		=	new	 QLableDelegate(this, m_AddressInputValidator);
	m_BitWidthInputDelegate		=	new	 QLableDelegate(this, m_BitWidthInputValidator);
	m_TargetVauleInputDelegate  =	new  QLableDelegate(this, m_TargetVauleInputValidator);
	QStringList itemlist;
	itemlist.append("<=");
	itemlist.append(">=");
	itemlist.append("<");
	itemlist.append(">");
	itemlist.append("==");
	itemlist.append("!=");
	itemlist.append("change");
	itemlist.append("constant");
	m_JugementChooseDelegate = new QComboxDelegate(this, itemlist);
	itemlist.clear();
	itemlist.append("");
	itemlist.append("hwyFpga w");
	m_CleanCmdChooseDelegate = new QComboxDelegate(this, itemlist);
	itemlist.clear();
	itemlist.append("");
	itemlist.append("vcaHandler txPowerRead");
	itemlist.append("lmclist");
	itemlist.append("pwrMeter MAP");
	itemlist.append("pwrMeter RXADC");
	itemlist.append("hwyFpga r");
	itemlist.append("hwyFpga dump");
	m_RecordCmdChooseDelegate = new QComboxDelegate(this, itemlist);
	ui.tableView_CleanCmd->horizontalHeader()->setStretchLastSection(true);
	ui.tableView_RecordCmd->horizontalHeader()->setStretchLastSection(true);
	ui.tableView_CleanCmd->setItemDelegateForColumn(0, m_CleanCmdChooseDelegate);
	ui.tableView_RecordCmd->setItemDelegateForColumn(0, m_RecordCmdChooseDelegate);
	m_CleanCmdListModel.setRowCount(40);
	m_CleanCmdListModel.setColumnCount(2);
	m_RecordCmdListModel.setRowCount(40);
	m_RecordCmdListModel.setColumnCount(2);
	m_CleanCmdListModel.setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("Command recommend item")));
	m_RecordCmdListModel.setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("Command recommend item")));
	m_CleanCmdListModel.setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("Clean Command")));
	m_RecordCmdListModel.setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("Record Command")));
	ui.tableView_CleanCmd->setEditTriggers(QAbstractItemView::EditTrigger::DoubleClicked);
	ui.tableView_RecordCmd->setEditTriggers(QAbstractItemView::EditTrigger::DoubleClicked);
	m_RegisterItemModel.setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("Register Address"))); 
	m_RegisterItemModel.setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("Bit Width"))); 
	m_RegisterItemModel.setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("Judgement"))); 
	m_RegisterItemModel.setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("Target Vaule"))); 
	m_RegisterItemModel.setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("Is legal")));
	m_RegisterItemModel.setRowCount(40);
	m_RegisterItemModel.setColumnCount(5);
	int j = m_RegisterItemModel.rowCount();

	for (size_t i = 0; i < m_RegisterItemModel.rowCount()-1; i++)
	{

		QStandardItem *legalItem = new QStandardItem;
		legalItem->setEditable(false);
		legalItem->setTextAlignment(Qt::AlignCenter);
		m_RegisterItemModel.setItem(i, 4, legalItem);
		
	}
	
	//m_RegisterItemModel.item(i, 4);
	//m_RegisterItemModel.findItems();
	/*m_RegisterItemModel.submit();*/
	
	ui.tableView_CheckRegister->setItemDelegateForColumn(0, m_AddressInputDelegate);
	ui.tableView_CheckRegister->setItemDelegateForColumn(1, m_BitWidthInputDelegate);
	ui.tableView_CheckRegister->setItemDelegateForColumn(2, m_JugementChooseDelegate);
	ui.tableView_CheckRegister->setItemDelegateForColumn(3, m_TargetVauleInputDelegate);
	ui.tableView_CheckRegister->horizontalHeader()->setStretchLastSection(true);
	ui.tableView_CheckRegister->doItemsLayout();
	//ui.tableView_CheckRegister->setDragEnabled(true);
	//ui.tableView_CheckRegister->setDragDropMode(QAbstractItemView::DragDropMode::InternalMove);
	//ui.tableView_CheckRegister->setDefaultDropAction(Qt::DropAction::CopyAction);
	ui.tableView_CleanCmd->setModel(&m_CleanCmdListModel);
	ui.tableView_RecordCmd->setModel(&m_RecordCmdListModel);
	ui.tableView_CheckRegister->setModel(&m_RegisterItemModel);
	ConnectSlots();
	
	
	
}

void MainWindow::ConnectSlots()
{
	if (
		!(

			connect(&this->m_RegisterItemModel, &QStandardItemModel::itemChanged, this, &MainWindow::EditFinish)
			/*&& connect(this->ui.action_SetPythonFileHome, &QAction::triggered, this, &MainWindows::SetPycaseFilehome)*/
			)
		)
	{

		throw(" connect signal and  slots faile in MainWindows ");

	}
}

bool MainWindow::SaveToXmlFile()
{
	return true;
}

void MainWindow::SaveKeyEvent(QKeyEvent * event)
{
	
}
