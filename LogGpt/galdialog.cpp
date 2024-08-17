#include "galdialog.h"
#include "ui_galdialog.h"

#include <QDebug>
#include <QMouseEvent>


GalDialog::GalDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GalDialog)
{
    ui->setupUi(this);
    /*无边框设置*/
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setWindowOpacity(0.8);
    /*内容初始化*/
    ui->pushButton->hide();
    ui->label_name->setText("你");
}

GalDialog::~GalDialog()
{
    delete ui;
}

/*信息交互相关*/
//发送消息
void GalDialog::keyPressEvent(QKeyEvent* event)
{
    keys.append(event->key());
}
void GalDialog::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return)
    {
        if (!keys.contains(Qt::Key_Shift)) //过滤换行
        {
            //去除换行
            QTextCursor cursor=ui->textEdit->textCursor();//得到当前text的光标
            if(cursor.hasSelection()) cursor.clearSelection();
            cursor.deletePreviousChar();//删除前一个字符
            //等待回复
            ui->label_name->setText(Config::get_USER(::EnUser::CHARACTERGENDER).toInt()==0?"他":"她");
            //发起请求
            QString str = ui->textEdit->toPlainText();
            ui->textEdit->setText("...");
            ui->textEdit->setEnabled(false);
            emit signal_send_data_from_gal_to_widget(str); //获取lineEdit的输入并且传递到主界面
        }
    }
    keys.removeAll(event->key());
}
//接受信息
void GalDialog::slots_receive_data_from_widget_to_gal(QString data)
{
    qDebug()<<"Gal接受到来自Widget信息————>"<<data; //获取传递过来的数据
    ui->textEdit->setEnabled(true);
    ui->pushButton->show();
    ui->textEdit->setText(data);
}
//继续输入
void GalDialog::on_pushButton_clicked()
{
    ui->pushButton->hide();
    ui->textEdit->clear();
    ui->label_name->setText("你");
}
/*菜单相关*/
//关闭
void GalDialog::on_pushButton_close_clicked()
{
    this->destroy();
}
//历史记录
void GalDialog::on_pushButton_history_clicked()
{
    emit signal_show_widget_from_gal(); //显示widget
}
//播放
void GalDialog::on_pushButton_play_clicked()
{
    emit signal_play_voice_from_gal_to_widget(); //播放语言
}
/*语音输入相关*/
//长按录制
void GalDialog::on_pushButton_record_pressed()
{
    qDebug()<<"开始录音";
    /*
     * 此处可以使用ffplay -f s16le -ar 16000 -ac 1 -1 record_temp.pcm 进行播放测试
     * 参数就是qaudiocapture.cpp里设置的
    */
#ifndef DEBUG
//    m_audio.startRecord("./record_temp.pcm"); //暂存位置
#endif
}
//松开提交
void GalDialog::on_pushButton_record_released()
{
    //停止录音
    qDebug()<<"结束录音";
#ifndef DEBUG
//    m_audio.stopRecord();
    //Config部分重构，这样获取到appid,key,secret,如果没有设定则为空字符串
    ::IKS iks=Config::get_IKS(::EnIks::STT_BDYUN);

    //提交录音
    QString str = m_speechrgn.speechIdentify(iks.key,iks.secret,"./record_temp.pcm");
    ui->textEdit->setText(str); //获取返回内容

#endif
#ifdef DEBUG
    //Config部分重构，这样获取到appid,key,secret,如果没有设定则为空字符串
    ::IKS iks=Config::get_IKS(::EnIks::STT_BDYUN);

    //提交录音
    QString str = m_speechrgn.speechIdentify(iks.key,iks.secret,"./record_temp_debug.pcm");
    ui->textEdit->setText(str); //获取返回内容
#endif


}



/*无边框相关*/
//三个鼠标事件的重写
//鼠标按下事件
void GalDialog::mousePressEvent(QMouseEvent *event)
{
    switch(event->button())
    {
    case Qt::LeftButton:
        isLeftPressDown = true;
        this->mouseGrabber(); //返回当前抓取鼠标输入的窗口
        m_movePoint = event->globalPos() - this->frameGeometry().topLeft();
        //globalPos()鼠标位置，topLeft()窗口左上角的位置
        break;
    case Qt::RightButton:
//        this->destroy();
        //交给上级销毁
        emit signal_delete();
        break;
    default:
        GalDialog::mousePressEvent(event);
    }
}
//鼠标移动事件
void GalDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(isLeftPressDown)  //没有按下左键时
    {
        move(event->globalPos() - m_movePoint); //移动窗口
        event->accept();
    }
}
//鼠标释放事件
void GalDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isLeftPressDown = false;
        this->releaseMouse(); //释放鼠标抓取
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}










