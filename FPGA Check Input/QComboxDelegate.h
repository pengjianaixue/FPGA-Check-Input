#pragma once

#include <QItemDelegate>
#include <QWidget>
class QComboxDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	QComboxDelegate(QWidget * parent);
	~QComboxDelegate();
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;
	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const;

};
