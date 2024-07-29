#ifndef ABOUTSOFTWAREDIALOGWIDGET_H
#define ABOUTSOFTWAREDIALOGWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QIcon>
#include <QString>
#include <QFont>
#include <QFile>

namespace Ui {
class AboutSoftwareDialogWidget;
}

class AboutSoftwareDialogWidget : public QDialog
{
    Q_OBJECT
private:
    const int WIDTH      =700;
    const int HEIGHT     =500;
public:
    explicit AboutSoftwareDialogWidget(QWidget *parent = nullptr);
    ~AboutSoftwareDialogWidget();

private:
    void init();
private:
    Ui::AboutSoftwareDialogWidget *ui;
};

#endif // ABOUTSOFTWAREDIALOGWIDGET_H
