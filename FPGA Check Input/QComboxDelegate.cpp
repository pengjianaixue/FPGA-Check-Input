#include "stdafx.h"
#include "QComboxDelegate.h"

QComboxDelegate::QComboxDelegate(QWidget *parent,const QStringList& Items):QItemDelegate(parent), m_ComboxItems(Items)
{
	
}

QComboxDelegate::~QComboxDelegate()
{
		
}

QWidget * QComboxDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{

	QComboBox *editor = new QComboBox(parent);
	
	editor->addItems(m_ComboxItems);
	return editor;
}

void QComboxDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const
{
	QString value = index.model()->data(index, Qt::EditRole).toString();
	QComboBox *ComBox = static_cast<QComboBox*>(editor);
	ComBox->setCurrentText(value);
	
}

void QComboxDelegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const
{
	QComboBox *ComBox = static_cast<QComboBox*>(editor);
	QString value = ComBox->currentText();
	model->setData(index, value, Qt::EditRole);
}

void QComboxDelegate::updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	editor->setGeometry(option.rect);
}
