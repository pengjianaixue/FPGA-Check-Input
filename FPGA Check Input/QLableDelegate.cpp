#include "stdafx.h"
#include "QLableDelegate.h"

QLableDelegate::QLableDelegate(QWidget *parent,QValidator *InputValidator)
	: QItemDelegate(parent), m_InputValidator(InputValidator)
{
	

}

QLableDelegate::~QLableDelegate()
{

}

QWidget * QLableDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{

	QLineEdit *editor = new QLineEdit(parent);
	editor->setValidator(m_InputValidator);
	editor->setStyleSheet("background-color:rgba(193, 205, 205)");
	return editor;
}

void QLableDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const
{
	QString value = index.model()->data(index, Qt::EditRole).toString();
	QLineEdit *LableEditor = static_cast<QLineEdit*>(editor);
	LableEditor->setText(value);
}

void QLableDelegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const
{
	QLineEdit *LableEditor = static_cast<QLineEdit*>(editor);
	QString value = LableEditor->text();
	model->setData(index, value, Qt::EditRole);
}

void QLableDelegate::updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	editor->setGeometry(option.rect);
}
