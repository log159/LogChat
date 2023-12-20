#ifndef SETPUSHBUTTON_H
#define SETPUSHBUTTON_H

#include <QObject>
#include <QPushButton>

class SetPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit SetPushButton(QWidget *parent = nullptr);

private:
    void init();

    void setNormalStyle();
    void setEnterStyle();

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);


signals:
    void sendButtonEnter();
    void sendButtonNormal();

public slots:
};

#endif // SETPUSHBUTTON_H
