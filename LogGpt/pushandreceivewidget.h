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
#include <QSound>
#include <QVector>
#include <QListWidget>
#include <QPushButton>
#include <QFrame>
#include <QMessageBox>


#include "listitemswidget.h"
#include "botitemswidget.h"
#include "useritemswidget.h"
#include "config.h"
#include "baiduapi.h"
#include "usertextedit.h"

namespace Ui {
class PushAndReceiveWidget;
}

class PushAndReceiveWidget : public QWidget
{
    Q_OBJECT

    typedef void (QProcess::*FinishedFunc)(int,QProcess::ExitStatus);
    typedef void (BaiduApi::*ReplyFinishedData)(QString);
private:
    const int _Width    =840;
    const int _Height   =600;

    QList<QString>    m_OldUserTextList;
    QList<QString>    m_OldRobotTextList;
    bool              m_InformationComing      =false;
    QListWidget*      m_ListWidget             =nullptr;
    UserTextEdit*     m_UserTextEdit           =nullptr;
    QPushButton*      m_PushButtonSend         =nullptr;

public:
    explicit PushAndReceiveWidget(QWidget *parent = nullptr);
    ~PushAndReceiveWidget();

    void clearHistory();        //清除历史
private:

    void init();
    void initConnect();

    void addCharacterConfig();  //角色设定配置
    void moveHistory();         //移除部分历史记忆
signals:
    void sendIs();
    void receiveIs();
private slots:

    void handle_user_information();

    void handle_bot_information();

    void add_bot_information(const QString& str);

    void handle_bot_sound(const QString& str);

    void play_sound(const QString& str);

    void pushbutton_send_clicked();

private:
    Ui::PushAndReceiveWidget *ui;
};

#endif // PUSHANDRECEIVEWIDGET_H
