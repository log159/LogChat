#ifndef SETDIALOGWIDGET_H
#define SETDIALOGWIDGET_H

#include <QDialog>
#include <QIcon>
#include <QCloseEvent>

#include "config.h"

namespace Ui {
class SetDialogWidget;
}

class SetDialogWidget : public QDialog
{
    Q_OBJECT
private:
    const int _Width      =800;
    const int _Height     =500;
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
