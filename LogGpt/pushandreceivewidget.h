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
#include <QVector>
#include <QListWidget>
#include <QPushButton>
#include <QFrame>
#include <QMessageBox>
#include <QPair>
#include <QTextDocument>
#include <QPainter>
#include <QScrollBar>
#include <QSharedPointer>
#include <QList>
#include <QTimer>

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
#include "vitsfactory.h"
#include "setlive2ddialogwidget.h"
#include "qaudiocapture.h"
#include "speechrecognition.h"
#include "audioplayer.h"
#include "setcompounddialogwidget.h"

//#define DEBUG

namespace Ui {
class PushAndReceiveWidget;
}

class PushAndReceiveWidget : public QWidget
{
    Q_OBJECT

    typedef void (BaiduApi::*ReplyFinishedData)(QString);
private:
    static QString  TempText;
    static bool     CanSend;
    static bool     CanSound;

private:
    const int _TextEditMinHeight               =50;
    const int _TextEditMaxHeight               =500;
    const QString _UserMark                    ="User";
    const QString _BotMark                     ="Bot";
private:

    QAudioCapture       m_audio;
    speechRecognition   m_speechrgn;
    QList<QPair<QString,QString>>    m_HistoryTextList;
    QList<QString>    m_OldUserTextList;
    QList<QString>    m_OldRobotTextList;
    QList<QString>    m_RankTextList;
    QList<QString>    m_RankAudioList;
    bool              m_InformationComing      =false;
    QTimer*           m_AudioTimer             =nullptr;
    QListWidget*      m_ListWidget             =nullptr;
    UserTextEdit*     m_UserTextEdit           =nullptr;
    QPushButton*      m_PushButtonListen       =nullptr;
    QPushButton*      m_PushButtonSend         =nullptr;
    QPushButton*      m_PushButtonSet          =nullptr;
    QPushButton*      m_PushButtonSpeak        =nullptr;
    QPushButton*      m_PushButtonWrite        =nullptr;
    QPushButton*      m_PushButtonStop         =nullptr;
    QFrame*           m_Frame                  =nullptr;

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
    void moveHistory();                 //移除部分历史记忆

    const QString getLLMSpeak();        //历史记忆拼接
    const QString getSpeakChatGPT();    //历史记忆拼接 适用于Python脚本
    const QString getSpeakXFXH();       //历史记忆拼接 适用于讯飞星火SDK
    const QString getSpeakDeepSeek();   //历史记忆拼接 适用于DeepSeek脚本

    void paintEvent(QPaintEvent* event);

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
    void play_sound(const QString& path);
    void pushbutton_send_clicked();
    void slot_text_change();

public slots:
    void slot_receive_data_from_widget_to_llm(const QString& str); //收到主界面发送的信息
    void slot_play_voice_from_widget_to_llm(); //收到主界面发送的播放语言请求
signals:
    void signals_send_data_from_llm_to_main(QString); //返回给主界面
private:
    Ui::PushAndReceiveWidget *ui;
};

#endif // PUSHANDRECEIVEWIDGET_H
