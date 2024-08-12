#include "usertextedit.h"

UserTextEdit::UserTextEdit(QWidget *parent) : QTextEdit(parent)
{
    init();

}

void UserTextEdit::init()
{
    this->setStyleSheet(QString("background-color: rgba(255, 255, 255, %1);").arg(0));
}

void UserTextEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        if (event->modifiers() & Qt::ShiftModifier)
        {
            this->insertPlainText("\r");
            QTextEdit::keyPressEvent(event);

        }
        else
        {
            emit returnSend();
        }
    }
    else
    {
        QTextEdit::keyPressEvent(event);
    }
}



void UserTextEdit::resizeEvent(QResizeEvent *event) {
    QTextEdit::resizeEvent(event);
    adjustHeight();
}

void UserTextEdit::adjustHeight() {
    int docHeight = static_cast<int>(document()->size().height());
    int newHeight = qBound(50, docHeight, 500);
    setFixedHeight(newHeight);
}
