#pragma once

#include <QCheckBox>
#include <QItemDelegate>
class QCheckBoxDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	QCheckBoxDelegate(QWidget *parent);
	~QCheckBoxDelegate();
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;
	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const;
};
