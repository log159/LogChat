#include "usertextedit.h"

UserTextEdit::UserTextEdit(QWidget *parent) : QTextEdit(parent)
{
    init();

}

void UserTextEdit::init()
{
    this->setStyleSheet(
        "QTextEdit {"
        "  color: #333333;"                // 文字颜色
        "  background-color: #ffffff;"     // 背景颜色
        "  border: 1px solid #cccccc;"     // 边框颜色和样式
        "  border-radius: 5px;"            // 边框圆角
        "  padding: 8px;"                  // 内边距
        "  font-family: 'Arial';"          // 字体
        "  font-size: 14px;"               // 字体大小
        "}"
        "QScrollBar:vertical {"
        "  width: 10px;"
        "  background-color: #F5F5F5;"
        "  margin: 0px 0px 0px 0px;"
        "  border-radius: 5px;"
        "}"
        "QScrollBar::handle:vertical {"
        "  background-color: #CCCCCC;"
        "  min-height: 20px;"
        "  border-radius: 5px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "  background-color: #BBBBBB;"
        "  border-radius: 5px;"
        "}"
        "QScrollBar::add-line:vertical {"
        "  height: 0px;"
        "  subcontrol-position: bottom;"
        "  subcontrol-origin: margin;"
        "}"
        "QScrollBar::sub-line:vertical {"
        "  height: 0px;"
        "  subcontrol-position: top;"
        "  subcontrol-origin: margin;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "  background-color: #F5F5F5;"
        "  border-radius: 5px;"
        "}"
    );


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
