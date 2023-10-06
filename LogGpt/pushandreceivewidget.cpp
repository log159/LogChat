#include "pushandreceivewidget.h"
#include "ui_pushandreceivewidget.h"

PushAndReceiveWidget::PushAndReceiveWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PushAndReceiveWidget)
{
    ui->setupUi(this);
    this->init();
    this->initConnect();
}

PushAndReceiveWidget::~PushAndReceiveWidget()
{
    delete ui;
}

void PushAndReceiveWidget::init()
{
    this->setFixedSize(_Width,_Height);

    m_ListWidget=new QListWidget(this);
    m_ListWidget->setFixedSize(840,520);
    m_ListWidget->move(0,0);
    m_ListWidget->setStyleSheet(
                "QScrollBar:vertical {width: 10px;background-color: #F5F5F5;margin: 0px 0px 0px 0px;border-radius: 5px;}"
                "QScrollBar::handle:vertical {background-color: #CCCCCC;min-height: 20px;border-radius: 5px;}"
                "QScrollBar::handle:vertical:hover {background-color: #BBBBBB;border-radius: 5px;}"
                "QScrollBar::add-line:vertical {height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;}"
                "QScrollBar::sub-line:vertical {height: 0 px;subcontrol-position: top; subcontrol-origin: margin;}"
                "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background-color: #F5F5F5;border-radius: 5px;}"
                );
    m_ListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);         // 禁止编辑
    m_ListWidget->setSelectionMode(QAbstractItemView::NoSelection);           //禁止选中
    m_ListWidget->setFocusPolicy(Qt::NoFocus);                                //禁止获取焦点
    m_ListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   //平滑效果
    m_ListWidget->show();

    m_UserTextEdit=new UserTextEdit(this);
    m_UserTextEdit->setFixedSize(730,80);
    m_UserTextEdit->move(30,520);
    m_UserTextEdit->setPlaceholderText("来说点什么吧( Shift+Enter换行 Enter发送 )");
    m_UserTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_UserTextEdit->show();

    QFrame* frame=new QFrame(this);
    frame->setFixedSize(80,80);
    frame->move(760,520);
    frame->setStyleSheet("background-color:white;");


    m_PushButtonSend=new QPushButton(this);
    m_PushButtonSend->setFixedSize(55,55);
    m_PushButtonSend->move(775,535);
    m_PushButtonSend->setStyleSheet("background-color: transparent;");
    QPixmap sendbutton_img;
    sendbutton_img.load(":/res/PushImg.png");
    sendbutton_img = sendbutton_img.scaled(m_PushButtonSend->width(),m_PushButtonSend->height(), Qt::KeepAspectRatio);
    m_PushButtonSend->setIcon(QIcon(sendbutton_img));
    m_PushButtonSend->setIconSize(sendbutton_img.size()*0.7);
    m_PushButtonSend->setFixedSize(sendbutton_img.size()*0.7);
    m_PushButtonSend->setCursor(Qt::PointingHandCursor);
    m_PushButtonSend->show();


    addCharacterConfig();
    m_UserTextEdit->setFocus();
}

void PushAndReceiveWidget::initConnect()
{
    connect(m_PushButtonSend,&QPushButton::clicked,this,&PushAndReceiveWidget::pushbutton_send_clicked);
    connect(m_UserTextEdit,&UserTextEdit::returnSend,this,&PushAndReceiveWidget::pushbutton_send_clicked);
}


void PushAndReceiveWidget::addCharacterConfig()
{
    //启用扮演
    if(Config::get_ENABLE_ROLE())
    {
        m_OldUserTextList.push_back(Config::get_CHARACTER_CONFIG());
        m_OldRobotTextList.push_back("好的");

    }
    //不启用扮演
    else{

    }

}

void PushAndReceiveWidget::moveHistory()
{
    //启用扮演情况下移除
    if(Config::get_ENABLE_ROLE()){
        //如果历史记录过长则移除部分
        if(m_OldUserTextList.size()-1>Config::get_MAX_SPEAK()){
            m_OldUserTextList.removeAt(1);
            m_OldRobotTextList.removeAt(1);
        }
    }
    //不启用扮演情况下移除
    else{
        //如果历史记录过长则移除部分
        if(m_OldUserTextList.size()>Config::get_MAX_SPEAK()){
            m_OldUserTextList.removeAt(0);
            m_OldRobotTextList.removeAt(0);
        }
    }

}

void PushAndReceiveWidget::clearHistory()
{
    m_OldUserTextList.clear();
    m_OldRobotTextList.clear();
    if(Config::get_ENABLE_ROLE()){
        addCharacterConfig();
    }
    m_ListWidget->clear();
    m_InformationComing=false;

}

void PushAndReceiveWidget::handle_user_information()
{

    QString textUser=m_UserTextEdit->toPlainText();
    // listWidget添加user列表项
    QListWidgetItem *item = new QListWidgetItem();
    ListItemsWidget * widget=new UserItemsWidget;
    int lineCount=m_UserTextEdit->toPlainText().size()/15+1;

    widget->initItem(textUser,ItemEnum::User,lineCount);
    m_ListWidget->addItem(item);
    item->setSizeHint(QSize(widget->width(),widget->height()+20));
    m_ListWidget->setItemWidget(item,widget);
    m_ListWidget->scrollToBottom();
}

void PushAndReceiveWidget::handle_bot_information()
{

    // 创建QProcess对象
    QProcess * process=new QProcess;

    QObject::connect(process,&QProcess::readyReadStandardOutput, [=]() {
        this->m_InformationComing=false;
        QByteArray data = process->readAllStandardOutput();
        QString receivedData = QString::fromUtf8(data);
        qDebug()<<"内容成功接收!";
        emit receiveIs();
        qDebug() << "接收内容为:" << receivedData;
        //----------接收内容添加进缓存-----------
        m_OldRobotTextList.push_back(receivedData);

        //启用百度翻译 和 语音
        if(Config::get_ENABLE_SOUND() && Config::get_ENABLE_BAIDUFANYI())
        {
            BaiduApi* baiduApi=new BaiduApi(this);
            //百度翻译处理
            ReplyFinishedData replyFinishedData=&BaiduApi::replyFinishedData;
            connect(baiduApi,replyFinishedData,[=](QString handleData){
                qDebug()<<"百度翻译处理后："<<handleData;
                //启用翻译后的语言显示
                if(Config::get_ENABLE_LATERLANGUAGE()){
                    add_bot_information(handleData);//listWidget添加bot列表项
                }
                //不启用翻译后的语言显示（语言与user保持一致）
                else {
                    add_bot_information(receivedData);//listWidget添加bot列表项
                }
                handle_bot_sound(handleData);//音频处理和播放
            });
            if(baiduApi!=nullptr){
                baiduApi->functionData(receivedData);
            }
        }
        //启用百度翻译 不启用语音
        else if(Config::get_ENABLE_BAIDUFANYI() && !Config::get_ENABLE_SOUND()){
            BaiduApi* baiduApi=new BaiduApi(this);
            //百度翻译处理
            ReplyFinishedData replyFinishedData=&BaiduApi::replyFinishedData;
            connect(baiduApi,replyFinishedData,[=](QString handleData){
                qDebug()<<"百度翻译处理后："<<handleData;
                //启用翻译后的语言显示
                if(Config::get_ENABLE_LATERLANGUAGE()){
                    add_bot_information(handleData);//listWidget添加bot列表项
                }
                //不启用翻译后的语言显示（语言与user保持一致）
                else {
                    add_bot_information(receivedData);//listWidget添加bot列表项
                }
            });
            if(baiduApi!=nullptr){
                baiduApi->functionData(receivedData);
            }
        }
        //启用语音 不启用百度翻译
        else if(Config::get_ENABLE_SOUND() && !Config::get_ENABLE_BAIDUFANYI()){
           handle_bot_sound(receivedData);
           add_bot_information(receivedData);//listWidget添加bot列表项
        }
        //不启用语音 不启用百度翻译
        else {
            add_bot_information(receivedData);//listWidget添加bot列表项
        }

    });

    FinishedFunc finished = &QProcess::finished;
    connect(process,finished,[=](){
        process->deleteLater();
        delete process;
        qDebug()<<"------------LLM 请求资源释放-----------";
        //如果没有接收信息就释放资源则报错
        if(m_InformationComing==true){
            QMessageBox::warning(this,"Fail","出现错误，接收信息失败！");
        }
    });

    qDebug()<<"-------------------------新的请求------------------------";
    QStringList arguments;
    arguments << Config::get_PY_CHAT_SCRIPT_WAY();
    qDebug()<<"------------发送请求-----------";
    emit sendIs();
    process->start(Config::get_PY_INTERPRETER_WAY(), arguments);
    QString response = m_UserTextEdit->toPlainText();
    m_UserTextEdit->clear();
    m_UserTextEdit->setFocus();
    response.replace("\n", "");
    qDebug()<<"发送内容为："<<response;

    //如果历史记录过长则移除部分
    moveHistory();

    //----------------发送内容添加进缓存------------------
    m_OldUserTextList.push_back(response);

    QString response_havehistory;
    QVector<QString>   oldVector;

    //历史记录拼接
//    qDebug()<<"------------------------------历史记录-----------------------------";
    for(int i=0;i<m_OldUserTextList.size();++i){
        QString item_str=m_OldUserTextList[i];
        oldVector.push_back("["+item_str+"],");
        if(i==m_OldRobotTextList.size()){
            oldVector.back().push_back("[]");
            break;
        }
        else {
            oldVector.back().push_back("["+m_OldRobotTextList[i]+"]");
        }

    }
    for(int i=0;i<oldVector.size();++i){
        if(i!=oldVector.size()-1){
            response_havehistory+=QString("["+oldVector[i]+"],");
        }
        else {
            response_havehistory+=QString("["+oldVector[i]+"]");
        }
    }
    response_havehistory.push_front("[");
    response_havehistory.push_back("]");

    qDebug()<<"发送内容为————>"<<response_havehistory;

    QByteArray responseData = response_havehistory.toUtf8();
    process->write(responseData);
    process->closeWriteChannel();
}

void PushAndReceiveWidget::add_bot_information(const QString &str)
{
    QString receivedData=str;
    QListWidgetItem *item = new QListWidgetItem();
    ListItemsWidget * widget=new BotItemsWidget;
    int lineCount=receivedData.size()/35+1;
    widget->initItem(receivedData,ItemEnum::Bot,lineCount);
    m_ListWidget->addItem(item);
    item->setSizeHint(QSize(widget->width(),widget->height()+20));
    m_ListWidget->setItemWidget(item,widget);
    m_ListWidget->scrollToBottom(); //将滚动条设置为最底部
}

void PushAndReceiveWidget::handle_bot_sound(const QString &str)
{

    QString url = Config::get_URL_ADDRESS().arg(str);
    qDebug()<<"向 vits-api 端发送请求"<<url;
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
                QString currentDir = Config::get_OUTPUT_WAV_WAY();
                QFile outputFile(currentDir);
                if (outputFile.open(QIODevice::WriteOnly)) {
                    outputFile.write(reply->readAll());
                    outputFile.close();
                    //播放音频
                    this->play_sound(currentDir);

                } else {
                    qDebug() << "Failed to open output file";
                }
            } else {
                qDebug() << "HTTP error:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            }
        } else {
            qDebug() << "Network error:" << reply->error();
        }
        reply->deleteLater();
        qDebug()<<"------------VITS 请求资源释放-----------";
    });



}

void PushAndReceiveWidget::play_sound(const QString &str)
{
    qDebug()<<"音频开始播放";
    qDebug()<<"音频路径："<<str;
    QSound * startGameSound=new QSound(str);
    startGameSound->setParent(this);
    startGameSound->play();

}


void PushAndReceiveWidget::pushbutton_send_clicked()
{
    if(this->m_InformationComing){return;}
    if(this->m_UserTextEdit->toPlainText()==""){return;}
    m_InformationComing=true;
    handle_user_information();
    handle_bot_information();
}
