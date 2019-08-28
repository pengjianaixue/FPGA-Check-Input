#include "stdafx.h"
#include "CommandTemplateLoad.h"


CommandTemplateLoad::CommandTemplateLoad()
{
	m_SettingsFile = std::make_shared<QSettings>("./CommandTemplate.ini", QSettings::IniFormat);
}

CommandTemplateLoad::~CommandTemplateLoad()
{

}

QMap<QString, std::list<std::pair<QString, QString>>> CommandTemplateLoad::fetchCommandListFromIni()
{
	COMMANDLISTDIC cmdvaulelist;
	QStringList cmdGrounps  = m_SettingsFile->childGroups();
	Q_FOREACH(QString grounpitem, cmdGrounps)
	{
		m_SettingsFile->beginGroup(grounpitem);
		QStringList cmdKeyList = m_SettingsFile->childKeys();
		std::list<std::pair<QString, QString>> cmdgrounpvaulelist;
		Q_FOREACH(QString item, cmdKeyList)
		{
			cmdgrounpvaulelist.push_back({item,m_SettingsFile ->value(item).toString()});
		}
		cmdvaulelist.insert(grounpitem, cmdgrounpvaulelist);
		m_SettingsFile->endGroup();
	
	}
	return cmdvaulelist;
}
