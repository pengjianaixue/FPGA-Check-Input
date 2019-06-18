#pragma once

#include <QObject>
#include <pugixml.hpp>
class XmlWirte : public QObject
{
	Q_OBJECT
	
public:
	XmlWirte(QObject *parent);
	~XmlWirte();
	//API
	bool OpenFile(const QString& FileName);
	void FileStructInit();
	bool WirteCleanCmdData(QList<QString> Cmdlist);
	bool WirteRecordCmdData(QList<QString> Cmdlist);
	bool WirteRegisterCheckData(QList<QString> Cmdlist);
	bool SaveToFile(const QString& FilePath);
private:
	pugi::xml_document	m_PugiXmlDocument;
};
