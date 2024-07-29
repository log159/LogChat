#ifndef WINDOWBUTTON_H
#define WINDOWBUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QIcon>

class WindowButton : public QPushButton
{
    Q_OBJECT
public:
    static const int BUTTON_SIZE   =30;
public:
    explicit WindowButton(QWidget *parent = nullptr);

    void setSelfIcon(const QString& path);
private:
    void init();
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
signals:
    void entered();
    void left();


public slots:
};

#endif // WINDOWBUTTON_H
