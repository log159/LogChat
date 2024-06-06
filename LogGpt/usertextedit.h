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


protected:
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void adjustHeight() ;
signals:
    void returnSend();

public slots:
};

#endif // USERTEXTEDIT_H
