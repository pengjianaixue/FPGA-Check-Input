#pragma once

#include <QObject>

class XmlReader : public QObject
{
	Q_OBJECT

public:
	XmlReader(QObject *parent);
	~XmlReader();
};
