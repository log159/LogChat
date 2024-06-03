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
//            if(!isCursorVisible()){

//                ensureCursorVisible();
//            }
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

bool UserTextEdit::isCursorVisible() {
    QRect rect = cursorRect();
    QPoint topLeft = rect.topLeft();
    QPoint bottomRight = rect.bottomRight();
    QPoint viewportTopLeft = viewport()->mapToParent(viewport()->rect().topLeft());
    QPoint viewportBottomRight = viewport()->mapToParent(viewport()->rect().bottomRight());

    return topLeft.y() >= viewportTopLeft.y() && bottomRight.y() <= viewportBottomRight.y();
}
void UserTextEdit::scrollContentsBy(int dx, int dy) {

    Q_UNUSED(dx)
    Q_UNUSED(dy)
//    qDebug()<<dx<<" "<<dy;
}
