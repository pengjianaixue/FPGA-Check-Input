#pragma once

#include <QCheckBox>
#include <QItemDelegate>
class QLineEditDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	QLineEditDelegate(QWidget *parent, QValidator *InputValidator,const QString& InputMask="");
	~QLineEditDelegate();
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;
	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
	QValidator *m_InputValidator;
	QString     m_InputMask;
};
