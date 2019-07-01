#include "stdafx.h"
#include "QLineEditDelegate.h"

QLineEditDelegate::QLineEditDelegate(QWidget *parent, QValidator *InputValidator, const QString  &InputMask,const QStringList  &PreInputContents, bool IsEnableClearButton)
	: QItemDelegate(parent), m_InputValidator(InputValidator), m_InputMask(InputMask), m_PreInputContents(PreInputContents),
	  m_ClearButtonIsEnable(IsEnableClearButton)
{
	
}

QLineEditDelegate::~QLineEditDelegate()
{

}

QWidget * QLineEditDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	QLineEdit *editor = new QLineEdit(parent);
	editor->setPlaceholderText(m_InputMask);
	editor->setValidator(m_InputValidator);
	//editor->setAlignment(Qt::AlignCenter);
	editor->setStyleSheet("background-color:rgba(193, 205, 205)");
	if (m_PreInputContents.length()!=0)
	{
		QCompleter *MyInfor = new QCompleter(m_PreInputContents);
		editor->setCompleter(MyInfor);
	}
	if (m_ClearButtonIsEnable)
	{
		editor->setClearButtonEnabled(true);
	}
	return editor;
}

void QLineEditDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const
{
	QString value = index.model()->data(index, Qt::EditRole).toString();
	QLineEdit *LableEditor = static_cast<QLineEdit*>(editor);
	/*LableEditor->setClearButtonEnabled(true);*/
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
