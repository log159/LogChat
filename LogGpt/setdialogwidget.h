#ifndef SETDIALOGWIDGET_H
#define SETDIALOGWIDGET_H

#include <QDialog>
#include <QIcon>
#include <QCloseEvent>
#include <QComboBox>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QRadioButton>

#include "config.h"
#include "networkmanager.h"

namespace Ui {
class SetDialogWidget;
}

class SetDialogWidget : public QDialog
{
    Q_OBJECT
    typedef void(QComboBox::*CurrentIndexChanged)(int);
private:
    const int WIDTH      =900;
    const int HEIGHT     =600;
public:
    explicit SetDialogWidget(QWidget *parent = nullptr);
    ~SetDialogWidget()override;
private:
    void init();
    void initConnect();
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::SetDialogWidget *ui;
};

#endif // SETDIALOGWIDGET_H
