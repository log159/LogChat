#ifndef USERTEXTEDIT_H
#define USERTEXTEDIT_H

#include <QWidget>
#include <QTextEdit>
#include <QKeyEvent>
#include <QDebug>

class UserTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit UserTextEdit(QWidget *parent = nullptr);
private:
    void init();
public:
    bool isCursorVisible();
    void scrollContentsBy(int dx, int dy) override;
protected:
    void keyPressEvent(QKeyEvent *event) override;
signals:
    void returnSend();

public slots:
};

#endif // USERTEXTEDIT_H
