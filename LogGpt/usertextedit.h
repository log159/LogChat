#ifndef USERTEXTEDIT_H
#define USERTEXTEDIT_H

#include <QWidget>
#include <QTextEdit>
#include <QKeyEvent>

class UserTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit UserTextEdit(QWidget *parent = nullptr);
private:
    void init();
protected:
    void keyPressEvent(QKeyEvent *event) override;
signals:
    void returnSend();

public slots:
};

#endif // USERTEXTEDIT_H
