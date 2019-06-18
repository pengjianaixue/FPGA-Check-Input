#include "stdafx.h"
#include "XmlWirte.h"

XmlWirte::XmlWirte(QObject *parent)
	: QObject(parent)
{
	
}

XmlWirte::~XmlWirte()
{

}

bool XmlWirte::OpenFile(const QString & FileName)
{
	return m_PugiXmlDocument.load_file(FileName.toStdString().c_str(), pugi::parse_default, pugi::encoding_utf8).status == pugi::xml_parse_status::status_ok;
}

void XmlWirte::FileStructInit()
{
	pugi::xml_node nodeRoot = m_PugiXmlDocument.append_child("root");
	pugi::xml_node pre = m_PugiXmlDocument.prepend_child(pugi::node_declaration);
	pre.append_attribute("version") = "1.0";
	pre.append_attribute("encoding") = "utf-8";
	pugi::xml_node nodeCommentStudents = nodeRoot.append_child(pugi::node_comment);
	nodeCommentStudents.set_value("All clean Command");
	
}

bool XmlWirte::WirteCleanCmdData(QList<QString> Cmdlist)
{
	pugi::xml_node nodeRoot = m_PugiXmlDocument.append_child("root");
	pugi::xml_node nodeCommentBooks = nodeRoot.append_child(pugi::node_comment);
	nodeCommentBooks.set_value("All Clean Command");
	pugi::xml_node nodeBooks = nodeRoot.append_child("Clean Commands");
	for (size_t i = 0; i < Cmdlist.length(); ++i)
	{
		QString xmlitem = "Commands_%1";
		xmlitem.arg(i);
		pugi::xml_node nodeBook = nodeBooks.append_child("Clean Command");
		nodeBook.append_attribute(xmlitem.toStdString().c_str()).set_value(Cmdlist[i].toStdString().c_str());
	}
	return true;
}

bool XmlWirte::WirteRecordCmdData(QList<QString> Cmdlist)
{
	pugi::xml_node nodeRoot = m_PugiXmlDocument.append_child("root");
	pugi::xml_node nodeCommentBooks = nodeRoot.append_child(pugi::node_comment);
	nodeCommentBooks.set_value("All Record Command");
	pugi::xml_node nodeBooks = nodeRoot.append_child("Record Commands");
	for (size_t i = 0; i < Cmdlist.length(); ++i)
	{
		QString xmlitem = "Commands_%1";
		xmlitem.arg(i);
		pugi::xml_node nodeBook = nodeBooks.append_child("Record Command");
		nodeBook.append_attribute(xmlitem.toStdString().c_str()).set_value(Cmdlist[i].toStdString().c_str());
	}
	return true;
}

bool XmlWirte::WirteRegisterCheckData(QList<QString> Cmdlist)
{
	pugi::xml_node nodeRoot = m_PugiXmlDocument.append_child("root");
	pugi::xml_node nodeCommentBooks = nodeRoot.append_child(pugi::node_comment);
	nodeCommentBooks.set_value("All Register Check Data");
	pugi::xml_node nodeBooks = nodeRoot.append_child("Register Check Datas");
	for (size_t i = 0; i < Cmdlist.length(); ++i)
	{
		QString xmlitem = "Register Address";
		QList<QString> checkdataitem = Cmdlist[i].split(",");
		pugi::xml_node nodeBook = nodeBooks.append_child("Register Check Data");
		nodeBook.append_attribute(xmlitem.toStdString().c_str()).set_value(checkdataitem[0].toStdString().c_str());
		xmlitem = "Bit Width";
		nodeBook.append_attribute(xmlitem.toStdString().c_str()).set_value(checkdataitem[1].toStdString().c_str());
		xmlitem = "Judgement";
		nodeBook.append_attribute(xmlitem.toStdString().c_str()).set_value(checkdataitem[2].toStdString().c_str());
		xmlitem = "Target Vaule";
		nodeBook.append_attribute(xmlitem.toStdString().c_str()).set_value(checkdataitem[3].toStdString().c_str());
	}
	return true;
}

bool XmlWirte::SaveToFile(const QString& FilePath)
{
	m_PugiXmlDocument.save_file(FilePath.toStdWString().c_str(),"\t",1U,pugi::encoding_utf8);
	return false;
}


