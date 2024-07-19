#ifndef SETCOMPOUNDDIALOGWIDGET_H
#define SETCOMPOUNDDIALOGWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QIcon>
#include <QSound>
#include <QButtonGroup>
#include <QList>
#include <QRadioButton>

#include "vitsfactory.h"
#include "vitsbase.h"

namespace Ui {
class SetCompoundDialogWidget;
}

class SetCompoundDialogWidget : public QDialog
{
    Q_OBJECT
private:
    const int _Width      =720;
    const int _Height     =600;
private:
    VITSBase*   m_Vits      =nullptr;
    QSound*     m_MySound   =nullptr;

    bool isReturn           =false;

    QString     path;
public:
    explicit SetCompoundDialogWidget(QWidget *parent = nullptr);
    ~SetCompoundDialogWidget();

private:
    void init();

    void initConnect();
private slots:
    void save_sound(const QString& str);

private:
    Ui::SetCompoundDialogWidget *ui;
};

#endif // SETCOMPOUNDDIALOGWIDGET_H
