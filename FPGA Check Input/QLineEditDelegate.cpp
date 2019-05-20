#include "stdafx.h"
#include "QLineEditDelegate.h"

QLineEditDelegate::QLineEditDelegate(QWidget *parent, QValidator *InputValidator, const QString& InputMask)
	: QItemDelegate(parent), m_InputValidator(InputValidator), m_InputMask(InputMask)
{
	

}

QLineEditDelegate::~QLineEditDelegate()
{

}

QWidget * QLineEditDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{

	QLineEdit *editor = new QLineEdit(parent);
	editor->setValidator(m_InputValidator);
	editor->setPlaceholderText(m_InputMask);
	//editor->setAlignment(Qt::AlignCenter);
	editor->setStyleSheet("background-color:rgba(193, 205, 205)");
	return editor;
}

void QLineEditDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const
{
	QString value = index.model()->data(index, Qt::EditRole).toString();
	QLineEdit *LableEditor = static_cast<QLineEdit*>(editor);
	LableEditor->setText(value);
}

void QLineEditDelegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const
{
	QLineEdit *LableEditor = static_cast<QLineEdit*>(editor);
	QString value = LableEditor->text();
	model->setData(index, value, Qt::EditRole);
}

void QLineEditDelegate::updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	editor->setGeometry(option.rect);
}
