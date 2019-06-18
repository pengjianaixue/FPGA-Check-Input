#include "stdafx.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), m_isLegalFlag(true), m_DataisChanged(false),
										 m_AddressInputDelegate(nullptr), m_BitWidthInputDelegate(nullptr), 
										 m_TargetVauleInputDelegate(nullptr), m_JugementChooseDelegate(nullptr),
										 m_CleanCmdChooseDelegate(nullptr), m_RecordCmdChooseDelegate(nullptr),
										 m_AddressInputValidator(nullptr), m_BitWidthInputValidator(nullptr),
										 m_TargetVauleInputValidator(nullptr), m_SaveFileToXmlDirDialog(nullptr)

{
	ui.setupUi(this);
	
	InitandCreaterVar();
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
void  MainWindow::RegisterCheckEditFinish(QStandardItem *Item)
{
	disconnect(&this->m_RegisterItemModel, &QStandardItemModel::itemChanged, this, &MainWindow::RegisterCheckEditFinish);
	int colunum =  Item->column();
	int row		=  Item->row();
	if (!Item->text().isEmpty())
	{
		Item->setTextAlignment(Qt::AlignCenter);
	}
	if ((colunum == 0 || colunum == 3) && !Item->text().isEmpty() && !Item->text().startsWith("0x"))
	{
		QString data = Item->text();
		Item->setText("0x" + Item->text());
	}
	if (colunum == 1 && !Item->text().isEmpty())
	{
		QStringList num  = Item->text().split('-');
		if (num.count()!=2)
		{
			QMessageBox::critical(this, "Input error", "The Bit Width input is must be two number");
			Item->setText("");
		}
		if (num[0].toUInt()<num[1].toUInt())
		{
			QMessageBox::critical(this, "Input error", "The Bit Width input is must the order by high bit to low bit");
			Item->setText("");
		}
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
	if (itemcontentcount == 0)
	{
		Item->model()->item(row, 4)->setText("");
		Item->model()->item(row, 4)->setBackground(QBrush(QColor(qRgb(255, 255, 255))));
		m_isLegalFlag = true;
	}
	else if (itemcontentcount!=4)
	{
		Item->model()->item(row, 4)->setText("Need Complete");
		Item->model()->item(row, 4)->setBackground(QBrush(QColor(qRgb(255, 0, 0))));
		m_isLegalFlag = false;
	}
	else
	{
		Item->model()->item(row, 4)->setText("legal");
		m_isLegalFlag = true;
		Item->model()->item(row, 4)->setBackground(QBrush(QColor(qRgb(0, 255, 0))));
	}
	connect(&this->m_RegisterItemModel, &QStandardItemModel::itemChanged, this, &MainWindow::RegisterCheckEditFinish);
}
void MainWindow::InitandCreaterVar()
{
	m_AddressInputValidator		=	new  QRegExpValidator(QRegExp("[0-9|A-F|a-f]{,16}"));
	m_BitWidthInputValidator	=	new  QRegExpValidator(QRegExp(R"(([0-9]|[1-5][0-9]|6[0-3])-([0-9]|[1-5][0-9]|6[0-3]))"));
	m_TargetVauleInputValidator =	new	 QRegExpValidator(QRegExp("[0-9|A-F|a-f]{,16}"));
	m_AddressInputDelegate		=	new	 QLineEditDelegate(this, m_AddressInputValidator);
	m_BitWidthInputDelegate		=	new	 QLineEditDelegate(this, m_BitWidthInputValidator,"63-15");
	m_TargetVauleInputDelegate  =	new  QLineEditDelegate(this, m_TargetVauleInputValidator);
	m_SaveFileToXmlDirDialog	=	new  QFileDialog(this);
	this->statusBar()->setLayout(this->ui.gridLayout);
	QMainWindow::statusBar()->setStyleSheet("color: rgb(0, 170, 0);background - color: rgb(246, 255, 243);");
	QMainWindow::statusBar()->showMessage("Ready",0xFFFFFFFF);
	QStringList itemlist;
	itemlist.append("<=");
	itemlist.append(">=");
	itemlist.append("<");
	itemlist.append(">");
	itemlist.append("==");
	itemlist.append("!=");
	itemlist.append("change");
	itemlist.append("constant");
	itemlist.append("");
	m_JugementChooseDelegate = new QComboxDelegate(this, itemlist);
	itemlist.clear();
	itemlist.append("hwyFpga w");
	itemlist.append("");
	m_CleanCmdChooseDelegate = new QComboxDelegate(this, itemlist);
	itemlist.clear();
	itemlist.append("vcaHandler txPowerRead");
	itemlist.append("lmclist");
	itemlist.append("pwrMeter MAP");
	itemlist.append("pwrMeter RXADC");
	itemlist.append("hwyFpga r");
	itemlist.append("hwyFpga dump");
	itemlist.append("");
	m_RecordCmdChooseDelegate = new QComboxDelegate(this, itemlist);
	ui.tableView_CleanCmd->setModel(&m_CleanCmdListModel);
	ui.tableView_RecordCmd->setModel(&m_RecordCmdListModel);
	ui.tableView_CheckRegister->setModel(&m_RegisterItemModel);
	ConnectSlots();
	InitModel();

}

void MainWindow::InitModel()
{
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
	
	ui.tableView_CleanCmd->setColumnWidth(0, 200);
	ui.tableView_RecordCmd->setColumnWidth(0, 200);
	int j = m_RegisterItemModel.rowCount();

	for (size_t i = 0; i < m_RegisterItemModel.rowCount() - 1; i++)
	{
		QStandardItem *legalItem = new QStandardItem;
		legalItem->setEditable(false);
		legalItem->setTextAlignment(Qt::AlignCenter);
		m_RegisterItemModel.setItem(i, 4, legalItem);
	}
	ui.tableView_CheckRegister->setItemDelegateForColumn(0, m_AddressInputDelegate);
	ui.tableView_CheckRegister->setItemDelegateForColumn(1, m_BitWidthInputDelegate);
	ui.tableView_CheckRegister->setItemDelegateForColumn(2, m_JugementChooseDelegate);
	ui.tableView_CheckRegister->setItemDelegateForColumn(3, m_TargetVauleInputDelegate);
	ui.tableView_CheckRegister->horizontalHeader()->setStretchLastSection(true);
	ui.tableView_CheckRegister->doItemsLayout();
	m_strSaveFileName = "";
}

void MainWindow::ConnectSlots()
{
	if (
		!(
			connect(&this->m_RegisterItemModel, &QStandardItemModel::itemChanged, this, &MainWindow::RegisterCheckEditFinish)
			&& connect(&this->m_RecordCmdListModel, &QStandardItemModel::itemChanged, this, &MainWindow::CleanAndRecordCmdEditFinish)
			&& connect(&this->m_CleanCmdListModel, &QStandardItemModel::itemChanged, this, &MainWindow::CleanAndRecordCmdEditFinish)
			&& connect(&this->m_CleanCmdListModel, &QStandardItemModel::dataChanged, this, &MainWindow::DataChangedfalg)
			&& connect(&this->m_RecordCmdListModel, &QStandardItemModel::dataChanged, this, &MainWindow::DataChangedfalg)
			&& connect(&this->m_RegisterItemModel, &QStandardItemModel::dataChanged, this, &MainWindow::DataChangedfalg)
			&& connect(this->ui.actionSave, &QAction::triggered, this, &MainWindow::SaveToXmlFile)
			&& connect(this->ui.actionNew, &QAction::triggered, this, &MainWindow::NewFile)
			&& connect(this->ui.actionopen, &QAction::triggered, this, &MainWindow::OpenFile)
		)
		)
	{

		throw(" connect signal and  slots faile in MainWindows ");

	}
}

void MainWindow::CleanAndRecordCmdEditFinish(QStandardItem * item)
{
	if (item->column()==1 )
	{
		if (item->model() && item->model() == &this->m_RecordCmdListModel)
		{
			disconnect(&this->m_RecordCmdListModel, &QStandardItemModel::itemChanged, this, &MainWindow::CleanAndRecordCmdEditFinish);
		}
		else if (item->model() && item->model() == &this->m_CleanCmdListModel)
		{
			disconnect(&this->m_CleanCmdListModel, &QStandardItemModel::itemChanged, this, &MainWindow::CleanAndRecordCmdEditFinish);
		}
		if (item->model()->item(item->row(), 0) && !item->model()->item(item->row(),0)->text().isEmpty() 
			&& !item->text().startsWith(item->model()->item(item->row(), 0)->text()))
		{
			if (item->model()== &m_CleanCmdListModel && item->model()->item(item->row(), 0)->text()=="hwyFpga w")
			{
				QString data = item->text();
				item->setText("0x" + item->text());
			}
			item->setText(item->model()->item(item->row(), 0)->text() + " " + item->text());
		}
		if (item->model() && item->model() == &this->m_RecordCmdListModel)
		{
			connect(&this->m_RecordCmdListModel, &QStandardItemModel::itemChanged, this, &MainWindow::CleanAndRecordCmdEditFinish);
		}
		else if (item->model() && item->model() == &this->m_CleanCmdListModel)
		{
			connect(&this->m_CleanCmdListModel, &QStandardItemModel::itemChanged, this, &MainWindow::CleanAndRecordCmdEditFinish);
		}
 	}
	
}

bool MainWindow::SaveToXmlFile()
{
	if (!m_isLegalFlag)
	{
		QMessageBox::critical(this, "Save Info", "The input data have illegal item,please correct it before save data");
		return false;
	}
	else
	{
		m_CleanCmdListModel.submit();
		m_RecordCmdListModel.submit();
		m_RegisterItemModel.submit();
		m_DataisChanged = false;
		m_SaveFileToXmlDirDialog->setAcceptMode(QFileDialog::AcceptMode::AcceptSave);//
		m_SaveFileToXmlDirDialog->setFileMode(QFileDialog::FileMode::AnyFile);//
		if (m_strSaveFileName.isEmpty())
		{
			m_strSaveFileName = m_SaveFileToXmlDirDialog->getSaveFileName(this, tr("save File"), "/home", tr("XML File(*.xml)"));
		}
		QMainWindow::statusBar()->showMessage("Data have saved", 10000);
		return true;
	}
}

bool MainWindow::NewFile()
{

	if (m_DataisChanged)
	{
		QMessageBox::StandardButton rb =  QMessageBox::question(this, "operation info", "the data is not save ,did you need save the current file",  QMessageBox::Yes| QMessageBox::No, QMessageBox::No);
		if (rb = QMessageBox::Yes)
		{
			SaveToXmlFile();
		}
	}
	m_CleanCmdListModel.clear();
	m_RecordCmdListModel.clear();
	m_RegisterItemModel.clear();
	InitModel();
	QMainWindow::statusBar()->showMessage("Ready", 1000);
	return false;
}

bool MainWindow::DataChangedfalg()
{
	m_DataisChanged = true;
	return false;
}

bool MainWindow::OpenFile()
{
	m_SaveFileToXmlDirDialog->setAcceptMode(QFileDialog::AcceptMode::AcceptOpen);//
	m_SaveFileToXmlDirDialog->setFileMode(QFileDialog::FileMode::ExistingFile);//
	m_SaveFileToXmlDirDialog->getOpenFileName(this,"Open File","fpga data", tr("XML File(*.xml)"));
	return true;
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_S && (event->modifiers() & Qt::ControlModifier))
	{
		SaveToXmlFile();
	}
	
}
