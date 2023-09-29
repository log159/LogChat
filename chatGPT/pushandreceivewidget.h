#ifndef PUSHANDRECEIVEWIDGET_H
#define PUSHANDRECEIVEWIDGET_H

#include <QWidget>
#include <QProcess>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QIcon>
#include <QPixmap>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDir>
#include <QFile>
#include <QSound>


#include "listitemswidget.h"
#include "botitemswidget.h"
#include "useritemswidget.h"
#include "config.h"


namespace Ui {
class PushAndReceiveWidget;
}

class PushAndReceiveWidget : public QWidget
{
    Q_OBJECT

    typedef void (QProcess::*FinishedFunc)(int,QProcess::ExitStatus);
private:
    QVector<QString>    m_OldUserTextVector;
    QVector<QString>    m_OldAssistantTextVector;

private:
    const int _Width    =450;
    const int _Height   =600;

    bool information_coming=false;

public:
    explicit PushAndReceiveWidget(QWidget *parent = nullptr);
    ~PushAndReceiveWidget();


    void initItemsStyle();

private slots:

    void handle_user_information();

    void handle_bot_information();

    void handle_bot_sound(const QString& str);

    void play_sound(const QString& str);

    //ui 信号槽
    void on_pushButton_send_clicked();

private:
    Ui::PushAndReceiveWidget *ui;
};

#endif // PUSHANDRECEIVEWIDGET_H
