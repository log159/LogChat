#include "usertextedit.h"

UserTextEdit::UserTextEdit(QWidget *parent) : QTextEdit(parent)
{
    init();

}

void UserTextEdit::init()
{
    this->setFixedSize(730,80);
    this->setStyleSheet("border: none; background-color: white; color: #333333; padding: 5px;");
}

void UserTextEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        if (event->modifiers() & Qt::ShiftModifier)
        {
            // 如果按下Shift+回车键，则插入换行符
            this->insertPlainText("\n");
        }
        else
        {
            // 如果只按下回车键，则发送信号或执行其他操作
            emit returnSend();
        }
    }
    else
    {
        // 处理其他按键事件
        QTextEdit::keyPressEvent(event);
    }
}
