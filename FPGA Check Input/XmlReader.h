#pragma once

#include <QObject>
#include <pugixml.hpp>
#include <sstream>
class XmlReader : public QObject
{
	Q_OBJECT
	
public:
	XmlReader(QObject *parent);
	~XmlReader();
	//API
	bool OpenFile(const QString& FileName);
	bool GetCleanCmdData(QList<QString>& CleanCmdGetFromFile);
	bool GetRecordCmdData(QList<QString>& RecordCmdGetFromFile);
	bool GetRegisterCheckData(QList<QString>& RegisterCheckDataGetFromFile);
private:
	pugi::xml_document	m_PugiXmlDocument;
};
