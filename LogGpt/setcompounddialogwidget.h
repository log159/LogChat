#ifndef SETCOMPOUNDDIALOGWIDGET_H
#define SETCOMPOUNDDIALOGWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QIcon>
#include <QSound>
#include <QButtonGroup>
#include <QList>
#include <QRadioButton>
#include <QDesktopServices>
#include <QSharedPointer>
#include <QDir>
#include <QFile>
#include <QLineEdit>
#include <QList>
#include <QTimer>


#include "regexpchar.h"
#include "vitsfactory.h"
#include "vitsbase.h"
#include "configconstway.h"

namespace Ui {
class SetCompoundDialogWidget;
}

class SetCompoundDialogWidget : public QDialog
{
    Q_OBJECT
private:
    const int _Width      =800;
    const int _Height     =600;
private:
    QSharedPointer<QSound>  m_MySound;
    QList<QString>          m_RankTextList;
    QTimer*                 m_ListenTimer   =nullptr;
    bool                    m_CanPause      =false;
    int                     m_Rule          =0;
public:
    explicit SetCompoundDialogWidget(QWidget *parent = nullptr);
    ~SetCompoundDialogWidget();

private:
    void init();
    void initConnect();

    void handleText();
    void saveSound(const QString& path);
public:
    static QList<QString> getHandleText(const QString& str);
private slots:

private:
    Ui::SetCompoundDialogWidget *ui;
};

#endif // SETCOMPOUNDDIALOGWIDGET_H
