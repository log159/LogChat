#ifndef SETCONFIGDIALOGWIDGET_H
#define SETCONFIGDIALOGWIDGET_H

#include <QObject>
#include <QDialog>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QIcon>
#include <QCloseEvent>
#include <QDebug>
#include <QString>

#include "config.h"

class SetConfigDialogWidget : public QDialog
{
    Q_OBJECT
private:
    const int _Width      =500;
    const int _Height     =300;
    QTextEdit* m_TextEdit   =nullptr;
public:
    explicit SetConfigDialogWidget(QWidget *parent = nullptr);
    ~SetConfigDialogWidget()override;
private:
    void init();
    void closeEvent(QCloseEvent* event)override;
};

#endif // SETCONFIGDIALOGWIDGET_H
