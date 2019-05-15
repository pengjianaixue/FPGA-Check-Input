#pragma once

#include <QObject>

class XmlWirte : public QObject
{
	Q_OBJECT

public:
	XmlWirte(QObject *parent);
	~XmlWirte();
};
