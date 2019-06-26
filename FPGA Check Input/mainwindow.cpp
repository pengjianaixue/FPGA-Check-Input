#include "stdafx.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), m_isLegalFlag(true), m_DataisChanged(false),
										 m_pAddressInputDelegate(nullptr), m_pBitWidthInputDelegate(nullptr), 
										 m_pTargetVauleInputDelegate(nullptr), m_pJugementChooseDelegate(nullptr),
										 m_pCleanCmdChooseDelegate(nullptr), m_pRecordCmdChooseDelegate(nullptr),
										 m_pAddressInputValidator(nullptr), m_pBitWidthInputValidator(nullptr),
										 m_pTargetVauleInputValidator(nullptr), m_pSaveFileToXmlDirDialog(nullptr),
										 m_pXmlDataReader(nullptr),m_pXmlDataWirter(nullptr)

{
	ui.setupUi(this);
	InitandCreaterVar();
}

MainWindow::~MainWindow()
{
	delete m_pAddressInputDelegate;
	delete m_pJugementChooseDelegate;
	delete m_pBitWidthInputDelegate;
	delete m_pTargetVauleInputDelegate;
	delete m_pAddressInputValidator;
	delete m_pBitWidthInputValidator;
	delete m_pTargetVauleInputValidator;
	delete m_pXmlDataWirter;
	delete m_pXmlDataReader;
	delete m_pCleanInputDelegate;
	delete m_pCleanInputValidator;

}
void  MainWindow::RegisterCheckEditFinish(QStandardItem *Item)
{
	disconnect(&this->m_RegisterItemModel, &QStandardItemModel::itemChanged, this, &MainWindow::RegisterCheckEditFinish);
	int colunum =  Item->column();
	int row		=  Item->row();
	//Set content align to center
	if (!Item->text().isEmpty())
	{
		Item->setTextAlignment(Qt::AlignCenter);
	}
	// add 0x prefix to content
	if ((colunum == 0 || colunum == 3) && !Item->text().isEmpty() && !Item->text().startsWith("0x"))
	{
		QString data = Item->text();
		Item->setText("0x" + Item->text());
	}
	// Set target vaule is can't edit when Judgement is change or constant
	if (colunum==2 && (Item->text()=="change" || Item->text() == "constant"))
	{
		QStandardItem *Targetitem = new QStandardItem;
		Targetitem->setEditable(false);
		Targetitem->setText("constant/change");
		Item->model()->setItem(row, 3, Targetitem);
	}
	else
	{
		if (Item->model()->item(row,3))
		{
			Item->model()->item(row, 3)->setEditable(true);
		}
		else
		{
			QStandardItem *Targetitem = new QStandardItem;
			Targetitem->setEditable(true);
			Item->model()->setItem(row, 3, Targetitem);
		}
	}
	// Check the bit width input
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
	// Set the check item empty
	if (itemcontentcount == 0)
	{
		Item->model()->item(row, 4)->setText("");
		Item->model()->item(row, 4)->setBackground(QBrush(QColor(qRgb(255, 255, 255))));
		m_isLegalFlag = true;
	}
	// Set the check item is Need Complete status
	else if (itemcontentcount!=4)
	{
		Item->model()->item(row, 4)->setText("Need Complete");
		Item->model()->item(row, 4)->setBackground(QBrush(QColor(qRgb(255, 0, 0))));
		m_isLegalFlag = false;
	}
	// Set the check item is legal status
	else
	{
		Item->model()->item(row, 4)->setText("legal");
		m_isLegalFlag = true;
		Item->model()->item(row, 4)->setBackground(QBrush(QColor(qRgb(40, 200, 11))));
	}
	connect(&this->m_RegisterItemModel, &QStandardItemModel::itemChanged, this, &MainWindow::RegisterCheckEditFinish);
}
void MainWindow::InitandCreaterVar()
{
	m_pCleanInputValidator			=	new  QRegExpValidator(QRegExp("[0-9]{0,},[0-9]{0,}"));
	m_pAddressInputValidator		=	new  QRegExpValidator(QRegExp("[0-9|A-F|a-f]{,16}"));
	m_pBitWidthInputValidator		=	new  QRegExpValidator(QRegExp(R"(([0-9]|[1-5][0-9]|6[0-3])-([0-9]|[1-5][0-9]|6[0-3]))"));
	m_pTargetVauleInputValidator	=	new	 QRegExpValidator(QRegExp("[0-9|A-F|a-f]{,16}"));
	m_pCleanInputDelegate			=	new  QLineEditDelegate(this, m_pCleanInputValidator);
	m_pAddressInputDelegate			=	new	 QLineEditDelegate(this, m_pAddressInputValidator);
	m_pBitWidthInputDelegate		=	new	 QLineEditDelegate(this, m_pBitWidthInputValidator,"63-15");
	m_pTargetVauleInputDelegate		=	new  QLineEditDelegate(this, m_pTargetVauleInputValidator);
	m_pSaveFileToXmlDirDialog		=	new  QFileDialog(this);
	m_pXmlDataReader				=	new	 XmlReader(this);
	m_pXmlDataWirter				=	new	 XmlWirter(this);
	this->statusBar()->setLayout(this->ui.gridLayout); 
	QMainWindow::statusBar()->setStyleSheet("color: rgb(255, 255, 255);background-color:rgb(40, 109, 11);");
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
	m_pJugementChooseDelegate = new QComboxDelegate(this, itemlist);
	itemlist.clear();
	itemlist.append("hwyFpga w");
	itemlist.append("");
	m_pCleanCmdChooseDelegate = new QComboxDelegate(this, itemlist);
	itemlist.clear();
	itemlist.append("vcaHandler txPowerRead");
	itemlist.append("lmclist");
	itemlist.append("pwrMeter MAP");
	itemlist.append("pwrMeter RXADC");
	itemlist.append("hwyFpga r");
	itemlist.append("hwyFpga dump");
	itemlist.append("");
	m_pRecordCmdChooseDelegate = new QComboxDelegate(this, itemlist);
	ui.tableView_CleanCmd->setModel(&m_CleanCmdListModel);
	ui.tableView_RecordCmd->setModel(&m_RecordCmdListModel);
	ui.tableView_CheckRegister->setModel(&m_RegisterItemModel);
	InitModel();
	ConnectSlots();

}

void MainWindow::InitModel()
{
	ui.tableView_CleanCmd->horizontalHeader()->setStretchLastSection(true);
	ui.tableView_RecordCmd->horizontalHeader()->setStretchLastSection(true);
	ui.tableView_CleanCmd->setItemDelegateForColumn(0, m_pCleanCmdChooseDelegate);
	ui.tableView_CleanCmd->setItemDelegateForColumn(1, m_pCleanInputDelegate);
	ui.tableView_RecordCmd->setItemDelegateForColumn(0, m_pRecordCmdChooseDelegate);
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
	ui.tableView_CheckRegister->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	//ui.tableView_CheckRegister->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
	ui.tableView_CheckRegister->horizontalHeader()->setMinimumSectionSize(80);
	m_RegisterItemModel.setRowCount(40);
	m_RegisterItemModel.setColumnCount(5);
	ui.tableView_CleanCmd->setColumnWidth(0, 300);
	ui.tableView_RecordCmd->setColumnWidth(0, 300);
	int j = m_RegisterItemModel.rowCount();

	for (size_t i = 0; i < m_RegisterItemModel.rowCount() - 1; i++)
	{
		QStandardItem *legalItem = new QStandardItem;
		legalItem->setEditable(false);
		legalItem->setTextAlignment(Qt::AlignCenter);
		m_RegisterItemModel.setItem(i, 4, legalItem);
	}
	ui.tableView_CheckRegister->setItemDelegateForColumn(0, m_pAddressInputDelegate);
	ui.tableView_CheckRegister->setItemDelegateForColumn(1, m_pBitWidthInputDelegate);
	ui.tableView_CheckRegister->setItemDelegateForColumn(2, m_pJugementChooseDelegate);
	ui.tableView_CheckRegister->setItemDelegateForColumn(3, m_pTargetVauleInputDelegate);
	ui.tableView_CheckRegister->horizontalHeader()->setStretchLastSection(true);
	ui.tableView_CheckRegister->doItemsLayout();
	ui.tableView_CheckRegister->resizeColumnsToContents();
	m_strSaveFileName = QString();
}

void MainWindow::ConnectSlots()
{
	if	(
			!(
				connect(&this->m_RegisterItemModel, &QStandardItemModel::itemChanged, this, &MainWindow::RegisterCheckEditFinish)
				&& connect(&this->m_RecordCmdListModel, &QStandardItemModel::itemChanged, this, &MainWindow::CleanAndRecordCmdEditFinish)
				&& connect(&this->m_CleanCmdListModel, &QStandardItemModel::itemChanged, this, &MainWindow::CleanAndRecordCmdEditFinish)
				&& connect(&this->m_CleanCmdListModel, &QStandardItemModel::dataChanged, this, &MainWindow::DataChangedfalg)
				&& connect(&this->m_RecordCmdListModel, &QStandardItemModel::dataChanged, this, &MainWindow::DataChangedfalg)
				&& connect(&this->m_RegisterItemModel, &QStandardItemModel::dataChanged, this, &MainWindow::DataChangedfalg)
				&& connect(this->ui.action_Save, &QAction::triggered, this, &MainWindow::SaveToXmlFile)
				&& connect(this->ui.actionNew, &QAction::triggered, this, &MainWindow::NewFile)
				&& connect(this->ui.actionopen, &QAction::triggered, this, &MainWindow::OpenFile)
				&& connect(this->ui.actionSave_As, &QAction::triggered, this, &MainWindow::SaveFileAs)
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
			&& !item->text().startsWith(item->model()->item(item->row(), 0)->text()) && item->model() == &m_CleanCmdListModel)
		{
			QString  addressdata;
			QString  Vaule;
			if (item->model()->item(item->row(), 0)->text()=="hwyFpga w")
			{
				QList<QString> datatemp = item->text().split(",");
				if (datatemp.length() != 2)
				{
					QMessageBox::critical(this, "Input Error", "The input data have illegal item,the input must be two digtal number between a symbol ,");
				}
				addressdata = datatemp[0];
				Vaule	= datatemp[1];
				addressdata = "0x" + addressdata;
				Vaule = "0x" + Vaule;
				item->setText(item->model()->item(item->row(), 0)->text() + " " + addressdata + " " + Vaule);
			}
			else
			{
				item->setText(item->model()->item(item->row(), 0)->text());
			}
			
		}
		if (item->model()->item(item->row(), 0) && !item->model()->item(item->row(), 0)->text().isEmpty()
			&& !item->text().startsWith(item->model()->item(item->row(), 0)->text()) && item->model() == &m_RecordCmdListModel)
		{
			QString  addressdata;
			QString  Vaule;
			if (item->model()->item(item->row(), 0)->text() == "hwyFpga r")
			{
				addressdata = "0x" + item->text();
				item->setText(item->model()->item(item->row(), 0)->text() + " " + addressdata);
			}
			else if (item->model() == &m_RecordCmdListModel && item->model()->item(item->row(), 0)->text() == "hwyFpga dump")
			{
				QList<QString> datatemp = item->text().split(",");
				if (datatemp.length() != 2)
				{
					QMessageBox::critical(this, "Input Error", "The input data have illegal item,the input must be two digtal number between a symbol ,");
				}
				addressdata = datatemp[0];
				Vaule = datatemp[1];
				addressdata = "0x" + addressdata;
				Vaule = "0x" + Vaule;
				item->setText(item->model()->item(item->row(), 0)->text() + " " + addressdata + " " + Vaule);
			}
			else
			{
				item->setText(item->model()->item(item->row(), 0)->text());
			}
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

bool MainWindow::SaveToXmlFile(int n_SaveMode)
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
		/*QFileInfo fileInfo(m_strSaveFileName);
		if (fileInfo.isFile())
		{
			QFile file(m_strSaveFileName);
			file.open(QFile::WriteOnly | QFile::Truncate);
			file.close();
		}*/
		m_pXmlDataWirter->EmptyXmlDoc();
		m_pXmlDataWirter->FileStructInit();
		QList<QString> CleanCmddata;
		QList<QString> RecordCmddata;
		QList<QString> RegisterCmddata;
		QString RegisterDatajoinStr;
		for (size_t i = 0; m_CleanCmdListModel.item(i, 1); i++)
		{
			CleanCmddata.append(m_CleanCmdListModel.item(i, 1)->text());
		}
		for (size_t i = 0; m_RecordCmdListModel.item(i, 1); i++)
		{
			RecordCmddata.append(m_RecordCmdListModel.item(i, 1)->text());
		}
		for (size_t i = 0; m_RegisterItemModel.item(i, 0); i++)
		{
			bool appendflag = true;
			for (size_t j = 0; j < 4; j++)
			{
				if (m_RegisterItemModel.item(i, j))
				{
					RegisterDatajoinStr += m_RegisterItemModel.item(i, j)->text();
					RegisterDatajoinStr += j < 3 ? "," : "";
				}
				else
				{
					appendflag = false;
					break;
				}
			}
			if (appendflag)
			{
				RegisterCmddata.append(RegisterDatajoinStr);
			}
			RegisterDatajoinStr.clear();
		}
		if (CleanCmddata.length() == 0 && CleanCmddata.length() == 0 && RegisterCmddata.length() == 0 )
		{
			QMessageBox::critical(this, "Save Info", "The input data is empty,there  is nothing save to file");
			return false;
		}
		m_pSaveFileToXmlDirDialog->setAcceptMode(QFileDialog::AcceptMode::AcceptSave);//
		m_pSaveFileToXmlDirDialog->setFileMode(QFileDialog::FileMode::AnyFile);//
		if (m_strSaveFileName.isEmpty() || n_SaveMode == 1)
		{
			m_strSaveFileName = m_pSaveFileToXmlDirDialog->getSaveFileName(this, tr("save File"), "/Radio_XXXX_BXX", tr("XML File(*.xml)"));
			if (m_strSaveFileName.isEmpty())
			{
				return false;
			}
		}
		if (CleanCmddata.length()> 0)
		{
			m_pXmlDataWirter->WirteCleanCmdData(CleanCmddata);
		}
		if (RecordCmddata.length()> 0)
		{
			m_pXmlDataWirter->WirteRecordCmdData(RecordCmddata);
		}
		if (RegisterCmddata.length()> 0)
		{
			m_pXmlDataWirter->WirteRegisterCheckData(RegisterCmddata);
		}
		m_pXmlDataWirter->SaveToFile(m_strSaveFileName);
		QMainWindow::statusBar()->showMessage("Data have saved to file", 10000);
		return true;
	}
}

bool MainWindow::SaveFileAs()
{
	SaveToXmlFile(1);
	return true;
}

bool MainWindow::NewFile()
{

	if (m_DataisChanged)
	{
		QMessageBox::StandardButton rb =  QMessageBox::question(this, "operation info", "the data is not save ,did you need save the current file",  QMessageBox::Yes| QMessageBox::No, QMessageBox::No);
		if (rb = QMessageBox::Yes)
		{
			SaveToXmlFile(1);
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
	return true;
}

bool MainWindow::OpenFile()
{
	m_pSaveFileToXmlDirDialog->setAcceptMode(QFileDialog::AcceptMode::AcceptOpen);//
	m_pSaveFileToXmlDirDialog->setFileMode(QFileDialog::FileMode::ExistingFile);//
	QString  fileselect = m_pSaveFileToXmlDirDialog->getOpenFileName(this,"Open File","Radio_XXXX_BXX", tr("XML File(*.xml)"));
	QFileInfo fileInfo(fileselect);
	if (fileInfo.isFile())
	{
		m_strSaveFileName = fileselect;
	}
	else if (fileselect.isEmpty())
	{
		return false;
	}
	else
	{
		QMessageBox::critical(this, "Open File Info", "Your choose  is not a , please chooose a xml file");
		return false;
	}
	QList<QString> CleanCmddata;
	QList<QString> RecordCmddata;
	QList<QString> RegisterCmddata;
	if (!m_pXmlDataReader->OpenFile(m_strSaveFileName))
	{
		//QMessageBox::critical(this, "Open File Info", "Open file fail");
		//return false;
	}
	m_pXmlDataReader->GetCleanCmdData(CleanCmddata);
	m_pXmlDataReader->GetRecordCmdData(RecordCmddata);
	m_pXmlDataReader->GetRegisterCheckData(RegisterCmddata);
	m_CleanCmdListModel.clear();
	m_RecordCmdListModel.clear();
	m_RegisterItemModel.clear();
	InitModel();
	for (size_t i = 0; i < CleanCmddata.length(); i++)
	{
		QStandardItem *item = new QStandardItem();
		//m_itemResourceKeepList.append(item);
		item->setText(CleanCmddata[i]);
		m_CleanCmdListModel.setItem(i,1,item);
	}
	for (size_t i = 0; i < RecordCmddata.length(); i++)
	{
		QStandardItem *item = new QStandardItem();
		//m_itemResourceKeepList.append(item);
		item->setText(RecordCmddata[i]);
		m_RecordCmdListModel.setItem(i, 1, item);
	}
	for (size_t i = 0; i < RegisterCmddata.length(); i++)
	{
		for (size_t j = 0; j < RegisterCmddata[i].split(",").length(); j++)
		{
			QStandardItem *item = new QStandardItem();
			//m_itemResourceKeepList.append(item);
			QString temp = RegisterCmddata[i].split(",")[j];
			item->setText(RegisterCmddata[i].split(",")[j]);
			m_RegisterItemModel.setItem(i, j, item);
		}
	}
	QMainWindow::statusBar()->showMessage("File have loaded", 10000);
	return true;
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_S && (event->modifiers() & Qt::ControlModifier))
	{
		SaveToXmlFile(0);
	}
	
}
