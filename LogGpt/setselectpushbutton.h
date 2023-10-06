#ifndef SETSELECTPUSHBUTTON_H
#define SETSELECTPUSHBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QAbstractAnimation>
#include <QPropertyAnimation>

class SetSelectPushButton : public QPushButton
{
    Q_OBJECT
private:
    bool m_ZoomId       =false;
public:
    explicit SetSelectPushButton(QWidget *parent = nullptr);
private:
    void init();
public:
    void zoom();
private:
    void zoom1();
    void zoom2();
signals:

public slots:
};

#endif // SETSELECTPUSHBUTTON_H
