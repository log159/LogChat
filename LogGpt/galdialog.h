#ifndef GALDIALOG_H
#define GALDIALOG_H

#define PADDING 2

#include "qaudiocapture.h"
#include "speechrecognition.h"

#include <QWidget>
#include <QLineEdit>
#include <config.h>

#define DEBUG

namespace Ui {
class GalDialog;
}

class GalDialog : public QWidget
{
    Q_OBJECT

public:
    explicit GalDialog(QWidget *parent = nullptr);
    ~GalDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_history_clicked();

    void on_pushButton_play_clicked();

    void on_pushButton_record_pressed();

    void on_pushButton_record_released();

private:
    Ui::GalDialog *ui;
    QList<int> keys; //按键按键获取

public slots:
    void slots_receive_data_from_widget_to_gal(QString data); //接收Widget传递过来的数据
signals:
    void signal_send_data_from_gal_to_widget(QString); //发送信息到Widget
    void signal_show_widget_from_gal(); //发送显示请求到Widget
    void signal_play_voice_from_gal_to_widget(); //发送播放请求到Widget

protected:
    //鼠标按下移动及释放事件
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    //键盘事件
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    QPoint m_movePoint; //鼠标的位置
    bool isLeftPressDown; // 判断左键是否按下

    QAudioCapture m_audio;
    speechRecognition m_speechrgn;
};

#endif // GALDIALOG_H
