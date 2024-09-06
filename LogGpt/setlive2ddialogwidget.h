#ifndef SETLIVE2DDIALOGWIDGET_H
#define SETLIVE2DDIALOGWIDGET_H

#include <QDialog>
#include <QProcess>
#include <QFileDialog>
#include <QCoreApplication>
#include <QProcess>
#include <QResizeEvent>
#include <QString>
#include <QVector>
#include <QString>
#include <QMessageBox>
#include <QSlider>
#include <QVector>
#include <QMap>
#include <QTimer>
#include <QDesktopServices>
#include <QUrl>
#include <QListWidgetItem>


#include "config.h"
#include "configwindow.h"
#include "live2dlistitemswidget.h"
#include "changelive2dwidget.h"
#include "netlive2d.h"
#include "timeinformation.h"

class ModelConfigItem;

namespace Ui {
class SetLive2DDialogWidget;
}

class SetLive2DDialogWidget : public QDialog
{
    Q_OBJECT
    typedef void (Live2DListItemsWidget::*SendPass)(ModelConfigItem);
    typedef void (QSlider::*SliderChange)(int);
public:
    static bool live2DIsOpen;
private:
    const int WIDTH      =1200;
    const int HEIGHT     =800;
private:
    static QProcess*   m_Live2dProcess;
    static int         m_Live2dOpenId;
    int                m_Live2dPassId   =-1;

public:
    explicit SetLive2DDialogWidget(QWidget *parent = nullptr);
    ~SetLive2DDialogWidget();

    static void closeProcess();

private:
    void init();
    void initConnect();
    void addListItem(const ModelConfigItem& modItem);
    void resizeEvent(QResizeEvent*event);
    void sendConfigHandle(const QString& str,int val);
    void sendWindowHandle(const QString& str);
    void initLineEdit();
    void updateForUi();
    void updateForUnity();
    void setLineEditText(QLineEdit* lineEdit,int value);
    void updateModelChange();

signals:
    void sendModelHandle(QString);
private:
    Ui::SetLive2DDialogWidget *ui;
};

#endif // SETLIVE2DDIALOGWIDGET_H
