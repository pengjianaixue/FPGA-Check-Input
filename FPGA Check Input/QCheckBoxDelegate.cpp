#include "stdafx.h"
#include "QCheckBoxDelegate.h"

QCheckBoxDelegate::QCheckBoxDelegate(QWidget *parent)
	: QItemDelegate(parent)
{


}

QCheckBoxDelegate::~QCheckBoxDelegate()
{

}

QWidget * QCheckBoxDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	QCheckBox *editor = new QCheckBox(parent);
	editor->setChecked(false);
	return editor;
}

void QCheckBoxDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const
{
	bool value = index.model()->data(index, Qt::EditRole).toBool();
	QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
	checkBox->setChecked(value);
}

void QCheckBoxDelegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const
{
	QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
	bool value = checkBox->isChecked();
	model->setData(index, value, Qt::EditRole);
}

void QCheckBoxDelegate::updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	editor->setGeometry(option.rect);
}
