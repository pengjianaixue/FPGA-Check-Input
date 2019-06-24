#include "stdafx.h"
#include "XmlReader.h"

XmlReader::XmlReader(QObject *parent)
	: QObject(parent)
{

	
}

XmlReader::~XmlReader()
{
	
}

bool XmlReader::OpenFile(const QString& FileName)
{
	m_PugiXmlDocument.reset();
	int res = m_PugiXmlDocument.load_file(FileName.toStdString().c_str(), pugi::parse_default, pugi::encoding_utf8);
	return res  == pugi::xml_parse_status::status_ok;
}

bool XmlReader::GetCleanCmdData(QList<QString>& CleanCmdGetFromFile)
{

	pugi::xml_node nodeRoot = m_PugiXmlDocument.child("root");
	pugi::xml_node nodeClean_Command = nodeRoot.child("Clean_Commands");
	int childcounter = 0;
	for (pugi::xml_node node = nodeClean_Command.first_child(); node; node = node.next_sibling())
	{
		
		QString xmlitem = QString("Command");
		CleanCmdGetFromFile.append(node.attribute(xmlitem.toStdString().c_str()).value());
		childcounter++;
	}
	return true;
}

bool XmlReader::GetRecordCmdData(QList<QString>& RecordCmdGetFromFile)
{
	pugi::xml_node nodeRoot = m_PugiXmlDocument.child("root");
	pugi::xml_node nodeRecord_Commands = nodeRoot.child("Record_Commands");
	int childcounter = 0;
	for (pugi::xml_node node = nodeRecord_Commands.first_child(); node; node = node.next_sibling())
	{
		QString xmlitem = QString("Command");
		RecordCmdGetFromFile.append(node.attribute(xmlitem.toStdString().c_str()).value());
		childcounter++;
	}
	return true;
}

bool XmlReader::GetRegisterCheckData(QList<QString>& RegisterCheckDataGetFromFile)
{
	pugi::xml_node nodeRoot = m_PugiXmlDocument.child("root");
	pugi::xml_node nodeRegister_Check_Datas = nodeRoot.child("Register_Check_Datas");
	for (pugi::xml_node node = nodeRegister_Check_Datas.first_child(); node; node = node.next_sibling())
	{
		std::stringstream DataJoinStr;
		DataJoinStr << node.attribute("Register_Address").value()<<",";
		DataJoinStr << node.attribute("Bit_Width").value() << ",";
		DataJoinStr << node.attribute("Judgement").value() << ",";
		DataJoinStr << node.attribute("Target_Vaule").value();
		std::string DataStr;
		DataJoinStr >> DataStr;
		RegisterCheckDataGetFromFile.append(QString(DataStr.c_str()));
	}
	return true;
}
