#ifndef ABOUTSOFTWAREDIALOGWIDGET_H
#define ABOUTSOFTWAREDIALOGWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QIcon>
#include <QString>
#include <QFont>

namespace Ui {
class AboutSoftwareDialogWidget;
}

class AboutSoftwareDialogWidget : public QDialog
{
    Q_OBJECT
private:
    const int _Width      =700;
    const int _Height     =500;
public:
    explicit AboutSoftwareDialogWidget(QWidget *parent = nullptr);
    ~AboutSoftwareDialogWidget();

private:
    void init();
private:
    Ui::AboutSoftwareDialogWidget *ui;
};

#endif // ABOUTSOFTWAREDIALOGWIDGET_H
