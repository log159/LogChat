#include "setconfigdialogwidget.h"

SetConfigDialogWidget::SetConfigDialogWidget(QWidget *parent):
    QDialog (parent)
{
    init();
}

SetConfigDialogWidget::~SetConfigDialogWidget()
{

}

void SetConfigDialogWidget::init()
{
    this->resize(_Width,_Height);
    this->setWindowTitle("角色设定");
    this->setWindowIcon(QIcon(":/res/u77.svg"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QHBoxLayout* m_HBoxLayout=new QHBoxLayout(this);
    m_TextEdit=new QTextEdit(this);
    m_TextEdit->setText(Config::get_CHARACTER_CONFIG());
    m_TextEdit->show();

    m_HBoxLayout->addWidget(m_TextEdit);
    this->setLayout(m_HBoxLayout);
}
void SetConfigDialogWidget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    qDebug()<<"角色配置更新成功！";
    QString str=m_TextEdit->toPlainText();
    Config::set_CHARACTER_CONFIG(str);
}
