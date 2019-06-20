#pragma once

#include <QObject>
#include <pugixml.hpp>
class XmlWirter : public QObject
{
	Q_OBJECT
	
public:
	XmlWirter(QObject *parent);
	~XmlWirter();
	//API
	bool EmptyXmlDoc();
	void FileStructInit();
	bool WirteCleanCmdData(QList<QString> Cmdlist);
	bool WirteRecordCmdData(QList<QString> Cmdlist);
	bool WirteRegisterCheckData(QList<QString> Cmdlist);
	bool SaveToFile(const QString& FilePath);
private:
	pugi::xml_document	m_PugiXmlDocument;
	pugi::xml_node      m_RootNode;
};
