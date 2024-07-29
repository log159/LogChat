#ifndef SETCONFIGDIALOGWIDGET_H
#define SETCONFIGDIALOGWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QIcon>
#include <QCloseEvent>
#include <QDebug>
#include <QString>
#include <QCloseEvent>
#include <QSlider>
#include <QRegExpValidator>
#include <QRadioButton>

#include "config.h"

namespace Ui {
class SetConfigDialogWidget;
}

class SetConfigDialogWidget : public QDialog
{
    Q_OBJECT
    typedef void (QSlider::*SliderMoved)(int);
private:
    const int WIDTH      =700;
    const int HEIGHT     =500;
public:
    explicit SetConfigDialogWidget(QWidget *parent = nullptr);
    ~SetConfigDialogWidget()override;
private:
    void init();
    void initConnect();
    void closeEvent(QCloseEvent* event)override;
private:
    Ui::SetConfigDialogWidget *ui;
};

#endif // SETCONFIGDIALOGWIDGET_H
