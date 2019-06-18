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
	return m_PugiXmlDocument.load_file(FileName.toStdString().c_str(), pugi::parse_default, pugi::encoding_utf8).status == pugi::xml_parse_status::status_ok;
}

bool XmlReader::GetCleanCmdData(QList<QString>& CleanCmdGetFromFile)
{

	pugi::xml_node nodeRoot = m_PugiXmlDocument.child("root");
	int childcounter = 0;
	for (pugi::xml_node node = nodeRoot.child("Clean Command").first_child(); node; node = node.next_sibling())
	{
		
		QString xmlitem = "Commands_%1";
		xmlitem.arg(childcounter);
		CleanCmdGetFromFile.append(node.attribute(xmlitem.toStdString().c_str()).value());
		childcounter++;
	}
	return true;
}

bool XmlReader::GetRecordCmdData(QList<QString>& RecordCmdGetFromFile)
{
	pugi::xml_node nodeRoot = m_PugiXmlDocument.child("root");
	int childcounter = 0;
	for (pugi::xml_node node = nodeRoot.child("Record Command").first_child(); node; node = node.next_sibling())
	{
		QString xmlitem = "Commands_%1";
		xmlitem.arg(childcounter);
		RecordCmdGetFromFile.append(node.attribute(xmlitem.toStdString().c_str()).value());
		childcounter++;
	}
	return true;
}

bool XmlReader::GetRegisterCheckData(QList<QString>& RegisterCheckDataGetFromFile)
{
	pugi::xml_node nodeRoot = m_PugiXmlDocument.child("root");
	for (pugi::xml_node node = nodeRoot.child("Register Check Data").first_child(); node; node = node.next_sibling())
	{
		std::stringstream DataJoinStr;
		DataJoinStr << node.attribute("Register Address").value()<<",";
		DataJoinStr << node.attribute("Bit Width").value() << ",";
		DataJoinStr << node.attribute("Judgement").value() << ",";
		DataJoinStr << node.attribute("Target Vaule").value() << endl;
		std::string DataStr;
		DataJoinStr >> DataStr;
		RegisterCheckDataGetFromFile.append(QString(DataStr.c_str()));
	}
	return true;
}
