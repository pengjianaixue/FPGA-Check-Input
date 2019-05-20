#pragma once

#include <QObject>
#include <pugixml.hpp>
class XmlWirte : public QObject
{
	Q_OBJECT
	
public:
	XmlWirte(QObject *parent);
	~XmlWirte();
};
