#pragma once
#include "qobject.h"
#include <QFile>
#include <memory>
class CommandTemplateLoad :public QObject
{
public:
	using COMMANDLISTDIC = QMap<QString, std::list<std::pair<QString, QString>>>;
public:
	CommandTemplateLoad();
	~CommandTemplateLoad();
	COMMANDLISTDIC fetchCommandListFromIni();
private:
	std::shared_ptr<QSettings>  m_SettingsFile = {nullptr};
	  
};

