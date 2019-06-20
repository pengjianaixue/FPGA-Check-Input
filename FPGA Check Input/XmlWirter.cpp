#include "stdafx.h"
#include "XmlWirter.h"

XmlWirter::XmlWirter(QObject *parent)
	: QObject(parent)
{
	
}

XmlWirter::~XmlWirter()
{

}

bool XmlWirter::EmptyXmlDoc()
{
	m_PugiXmlDocument.reset();
	return true;
}

void XmlWirter::FileStructInit()
{
	m_RootNode = m_PugiXmlDocument.append_child("root");
	pugi::xml_node pre = m_PugiXmlDocument.prepend_child(pugi::node_declaration);
	pre.append_attribute("version") = "1.0";
	pre.append_attribute("encoding") = "utf-8";

	
}

bool XmlWirter::WirteCleanCmdData(QList<QString> Cmdlist)
{
	
	//pugi::xml_node nodeRoot = m_PugiXmlDocument.find_child("root");
	pugi::xml_node nodeCommentBooks = m_RootNode.append_child(pugi::node_comment);
	nodeCommentBooks.set_value("All Clean Command");
	pugi::xml_node nodeCleanCMd = m_RootNode.append_child("Clean_Commands");
	for (size_t i = 0; i < Cmdlist.length(); ++i)
	{
		QString xmlitem = QString("Commands_%1").arg(i);
		pugi::xml_node nodeClean = nodeCleanCMd.append_child("Clean_Command");
		nodeClean.append_attribute(xmlitem.toStdString().c_str()).set_value(Cmdlist[i].toStdString().c_str());
	}
	return true;
}

bool XmlWirter::WirteRecordCmdData(QList<QString> Cmdlist)
{
	pugi::xml_node nodeCommentBooks = m_RootNode.append_child(pugi::node_comment);
	nodeCommentBooks.set_value("All Record Command");
	pugi::xml_node nodeRecordCmd = m_RootNode.append_child("Record_Commands");
	for (size_t i = 0; i < Cmdlist.length(); ++i)
	{
		QString xmlitem = QString("Commands_%1").arg(i);
		pugi::xml_node nodeRecord = nodeRecordCmd.append_child("Record_Command");
		nodeRecord.append_attribute(xmlitem.toStdString().c_str()).set_value(Cmdlist[i].toStdString().c_str());
	}
	return true;
}

bool XmlWirter::WirteRegisterCheckData(QList<QString> Cmdlist)
{
	pugi::xml_node nodeCommentBooks = m_RootNode.append_child(pugi::node_comment);
	nodeCommentBooks.set_value("All Register Check Data");
	pugi::xml_node nodeRegisterData = m_RootNode.append_child("Register_Check_Datas");
	for (size_t i = 0; i < Cmdlist.length(); ++i)
	{
		QString xmlitem = "Register_Address";
		QList<QString> checkdataitem = Cmdlist[i].split(",");
		pugi::xml_node nodeRegister = nodeRegisterData.append_child("Register_Check_Data");
		nodeRegister.append_attribute(xmlitem.toStdString().c_str()).set_value(checkdataitem[0].toStdString().c_str());
		xmlitem = "Bit_Width";
		nodeRegister.append_attribute(xmlitem.toStdString().c_str()).set_value(checkdataitem[1].toStdString().c_str());
		xmlitem = "Judgement";
		nodeRegister.append_attribute(xmlitem.toStdString().c_str()).set_value(checkdataitem[2].toStdString().c_str());
		xmlitem = "Target_Vaule";
		nodeRegister.append_attribute(xmlitem.toStdString().c_str()).set_value(checkdataitem[3].toStdString().c_str());
	}
	return true;
}

bool XmlWirter::SaveToFile(const QString& FilePath)
{
	m_PugiXmlDocument.save_file(FilePath.toStdWString().c_str(),"\t",1U,pugi::encoding_utf8);
	return false;
}


