#ifndef PUSHANDRECEIVEWIDGET_H
#define PUSHANDRECEIVEWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QIcon>
#include <QPixmap>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDir>
#include <QSound>
#include <QVector>
#include <QListWidget>
#include <QPushButton>
#include <QFrame>
#include <QMessageBox>
#include <QPair>
#include <QTextDocument>
#include <QPainter>
#include <QScrollBar>

#include "listitemswidget.h"
#include "botitemswidget.h"
#include "useritemswidget.h"
#include "config.h"
#include "baiduapi.h"
#include "usertextedit.h"
#include "configwindow.h"
#include "configwindow.h"
#include "llmbase.h"
#include "llmfactory.h"
#include "chatgptapi.h"
#include "xfxhapi.h"
#include "netlive2d.h"
#include "vitsapi.h"
#include "setlive2ddialogwidget.h"

namespace Ui {
class PushAndReceiveWidget;
}

class PushAndReceiveWidget : public QWidget
{
    Q_OBJECT

    typedef void (BaiduApi::*ReplyFinishedData)(QString);
private:
    const int _TextEditMinHeight               =50;
    const int _TextEditMaxHeight               =200;
private:

    QList<QString>    m_OldUserTextList;
    QList<QString>    m_OldRobotTextList;
    bool              m_InformationComing      =false;
    QListWidget*      m_ListWidget             =nullptr;
    UserTextEdit*     m_UserTextEdit           =nullptr;
    QPushButton*      m_PushButtonListen       =nullptr;
    QPushButton*      m_PushButtonSend         =nullptr;
    QPushButton*      m_PushButtonSet          =nullptr;
    QPushButton*      m_PushButtonSpeak        =nullptr;
    QPushButton*      m_PushButtonWrite        =nullptr;
    QFrame*           m_Frame                  =nullptr;
    VitsApi*          m_VitsApi                =nullptr;

public:


    explicit PushAndReceiveWidget(QWidget *parent = nullptr);
    ~PushAndReceiveWidget();

    void setAdapt();            //调整大小
    void clearHistory();        //清除历史
    void clearUi();
private:

    void init();
    void initConnect();
    void updateListWidget();
    void addCharacterConfig();          //角色设定配置
    void moveHistory();                 //移除部分历史记忆
    const QString getSpeakChatGPT();    //历史记忆拼接 适用于Python脚本
    const QString getSpeakXFXH();       //历史记忆拼接 适用于讯飞星火SDK

    void paintEvent(QPaintEvent* e);

signals:
    void sendIs();
    void receiveIs();
    void setPass();
    void sendAudio(QString);

private slots:

    void add_user_information(const QString& str);
    void handle_bot_information();
    void handle_receive(const QString&str);
    void add_bot_information(const QString& str);
    void handle_bot_sound(const QString& str);
    void play_sound(const QString& str);
    void pushbutton_send_clicked();
    void slot_text_change();

public slots:
    void slot_receive_data_from_widget_to_llm(const QString& str);
signals:
    void signals_send_data_from_llm_to_main(QString);   //用来传递发送信息的信号
private:
    Ui::PushAndReceiveWidget *ui;
};

#endif // PUSHANDRECEIVEWIDGET_H
