#include "pushandreceivewidget.h"
#include "ui_pushandreceivewidget.h"

QString PushAndReceiveWidget::TempText ="";
bool PushAndReceiveWidget::CanSend     =true;
bool PushAndReceiveWidget::CanSound    =true;

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

    this->setFixedSize(ConfigWindow::getStaticWidth(),ConfigWindow::getStaticHeight());

    m_AudioTimer=new QTimer(this);
    m_AudioTimer->start(10);

    m_ListWidget=new QListWidget(this);

    m_ListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);         //禁止编辑
    m_ListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);       //禁用水平滑动条
    m_ListWidget->setSelectionMode(QAbstractItemView::NoSelection);           //禁止选中
    m_ListWidget->setFocusPolicy(Qt::NoFocus);                                //禁止获取焦点
    m_ListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   //平滑效果
    m_ListWidget->setAttribute(Qt::WA_TranslucentBackground);

    m_ListWidget->show();

    m_UserTextEdit=new UserTextEdit(this);
    m_UserTextEdit->setPlaceholderText("来说点什么吧( Shift+Enter换行 Enter发送 )");
    m_UserTextEdit->setFixedHeight(_TextEditMinHeight);

    m_UserTextEdit->show();
    m_Frame=new QFrame(this);
    m_Frame->setStyleSheet("background-color:white;");

    m_PushButtonListen=new QPushButton(this);
    m_PushButtonListen->setText("点击说话");
    m_PushButtonListen->setGeometry(m_UserTextEdit->geometry());
    m_PushButtonListen->setStyleSheet("background-color: transparent;");
    m_PushButtonListen->hide();


    m_PushButtonSend=new QPushButton(this);
    m_PushButtonSend->setFixedSize(50,50);
    m_PushButtonSend->setStyleSheet("background-color: transparent;");
    QPixmap sendbutton_img;
    sendbutton_img.load(":/res/PushImg.png");
    sendbutton_img = sendbutton_img.scaled(m_PushButtonSend->width(),m_PushButtonSend->height(), Qt::KeepAspectRatio);
    m_PushButtonSend->setIcon(QIcon(sendbutton_img));
    m_PushButtonSend->setIconSize(sendbutton_img.size()*0.7);
    m_PushButtonSend->setCursor(Qt::PointingHandCursor);
    m_PushButtonSend->show();

    m_PushButtonSet=new QPushButton(this);
    m_PushButtonSet->setFixedSize(50,50);
    m_PushButtonSet->setStyleSheet("background-color: transparent;");
    QPixmap setbutton_img;
    setbutton_img.load(":/res/SetImg.png");
    setbutton_img = setbutton_img.scaled(m_PushButtonSet->width(),m_PushButtonSet->height(), Qt::KeepAspectRatio);
    m_PushButtonSet->setIcon(QIcon(setbutton_img));
    m_PushButtonSet->setIconSize(setbutton_img.size()*0.7);
    m_PushButtonSet->setCursor(Qt::PointingHandCursor);
    m_PushButtonSet->show();


    m_PushButtonSpeak=new QPushButton(this);
    m_PushButtonSpeak->setFixedSize(50,50);
    m_PushButtonSpeak->setStyleSheet("background-color: transparent;");
    QPixmap speakbutton_img;
    speakbutton_img.load(":/res/SoundImg.png");
    speakbutton_img = speakbutton_img.scaled(m_PushButtonSpeak->width(),m_PushButtonSpeak->height(), Qt::KeepAspectRatio);
    m_PushButtonSpeak->setIcon(QIcon(speakbutton_img));
    m_PushButtonSpeak->setIconSize(speakbutton_img.size()*0.7);
    m_PushButtonSpeak->setCursor(Qt::PointingHandCursor);
    m_PushButtonSpeak->show();


    m_PushButtonWrite=new QPushButton(this);
    m_PushButtonWrite->setFixedSize(50,50);
    m_PushButtonWrite->setStyleSheet("background-color: transparent;");
    QPixmap writebutton_img;
    writebutton_img.load(":/res/KeyboardImg.png");
    writebutton_img = writebutton_img.scaled(m_PushButtonWrite->width(),m_PushButtonWrite->height(), Qt::KeepAspectRatio);
    m_PushButtonWrite->setIcon(QIcon(writebutton_img));
    m_PushButtonWrite->setIconSize(writebutton_img.size()*0.7);
    m_PushButtonWrite->setCursor(Qt::PointingHandCursor);
    m_PushButtonWrite->hide();

    m_Frame->setStyleSheet("background-color: transparent;");


    m_PushButtonStop=new QPushButton(this);
    m_PushButtonStop->setFixedSize(50,50);
    m_PushButtonStop->setStyleSheet("background-color: transparent;");
    QPixmap stopbutton_img;
    stopbutton_img.load(":/res/StopImg.svg");
    stopbutton_img = stopbutton_img.scaled(m_PushButtonStop->width(),m_PushButtonStop->height(), Qt::KeepAspectRatio);
    m_PushButtonStop->setIcon(QIcon(stopbutton_img));
    m_PushButtonStop->setIconSize(stopbutton_img.size()*0.7);
    m_PushButtonStop->setCursor(Qt::PointingHandCursor);
    m_PushButtonStop->hide();

    setAdapt();
    m_UserTextEdit->setFocus();

    QFile file(":/main.qss");
    if(file.open(QFile::ReadOnly)){
        QString styleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }
}

void PushAndReceiveWidget::initConnect()
{
    connect(m_AudioTimer,&QTimer::timeout,[&](){
        //这个循环是将合成的音频加入List
        if(true==CanSend && !m_RankTextList.isEmpty()){
            CanSend=false;
            VITSBase* vits = VITSFactory::getNew(this);
            connect(vits,&VITSBase::playerWay,[=](QString path){
                CanSend=true;
                m_RankAudioList.push_back(path);
                qDebug()<<"音频输出:--------->"<<path;
                vits->deleteLater();
            });
            connect(vits,&VITSBase::quit,[=](){
                qDebug()<<"vits 端返回失败，释放资源";
                vits->deleteLater();
            });
            vits->start(m_RankTextList.front());
            m_RankTextList.pop_front();
        }
        //音频列表顺序播放 用LogChat端播放
        if(SetLive2DDialogWidget::live2DIsOpen==false){
            if(true==CanSound && !m_RankAudioList.isEmpty()){
                qDebug()<<"Chat端播放音频: "<<m_RankAudioList.front();
                CanSound=false;
                AudioPlayer* sound=new AudioPlayer(QUrl(m_RankAudioList.front()),this);
                connect(sound,&AudioPlayer::endof,[=](){
                    CanSound=true;
                });
                m_RankAudioList.pop_front();
            }
        }
        //音频列表顺序发送到 L2d用Unity端播放
        else{
            while(!m_RankAudioList.isEmpty()) {
                emit sendAudio(m_RankAudioList.front());
                m_RankAudioList.pop_front();
            }
        }
    });

    connect(m_UserTextEdit,SIGNAL(textChanged()),this,SLOT(slot_text_change()));
    connect(m_PushButtonSend,&QPushButton::clicked,this,&PushAndReceiveWidget::pushbutton_send_clicked);
    connect(m_UserTextEdit,&UserTextEdit::returnSend,this,&PushAndReceiveWidget::pushbutton_send_clicked);

    connect(m_PushButtonSet,&QPushButton::clicked,[=](){
        emit setPass();
    });
    connect(m_PushButtonWrite,&QPushButton::clicked,[=](){
        qDebug()<<"切换为语音输入";
        m_PushButtonWrite->hide();
        m_PushButtonSpeak->show();

        m_UserTextEdit->show();
        m_PushButtonListen->hide();


    });
    connect(m_PushButtonSpeak,&QPushButton::clicked,[=](){
        qDebug()<<"切换为键盘输入";
        m_PushButtonSpeak->hide();
        m_PushButtonWrite->show();

        m_UserTextEdit->hide();
        m_PushButtonListen->show();
    });
    connect(m_PushButtonListen,&QPushButton::pressed,[=](){
        qDebug()<<"开始录音";
        m_PushButtonListen->setText("监听中...");
        /*
         * 此处可以使用ffplay -f s16le -ar 16000 -ac 1 -1 record_temp.pcm 进行播放测试
         * 参数就是qaudiocapture.cpp里设置的
        */
    #ifndef DEBUG
        m_audio.startRecord("./record_temp.pcm"); //暂存位置
    #endif
    });
    connect(m_PushButtonListen,&QPushButton::released,[=](){
        //停止录音
        qDebug()<<"结束录音";
        m_PushButtonListen->setText("监听完毕!");
    #ifndef DEBUG
        m_audio.stopRecord();
        //Config部分重构，这样获取到appid,key,secret,如果没有设定则为空字符串
        ::IKS iks=Config::get_IKS(::EnIks::STT_BDYUN);

        //提交录音
        QString str = m_speechrgn.speechIdentify(iks.key,iks.secret,"./record_temp.pcm");
        m_UserTextEdit->setText(str); //获取返回内容
        emit pushbutton_send_clicked();
    #endif
#ifdef DEBUG
        //Config部分重构，这样获取到appid,key,secret,如果没有设定则为空字符串
        ::IKS iks=Config::get_IKS(::EnIks::STT_BDYUN);

        //提交录音
        QString str = m_speechrgn.speechIdentify(iks.key,iks.secret,"./record_temp_debug.pcm");
        m_UserTextEdit->setText(str); //获取返回内容

        emit pushbutton_send_clicked();
#endif

    });
}

void PushAndReceiveWidget::updateListWidget()
{
    for(int i=0;i<m_ListWidget->count();++i){
        QListWidgetItem* listWidgetItem=m_ListWidget->item(i);
        QSize size=(static_cast<ListItemsWidget*>(m_ListWidget->itemWidget(listWidgetItem)))->size();
        listWidgetItem->setSizeHint(QSize(size.width(),size.height()+20));
    }
}

void PushAndReceiveWidget::moveHistory()
{
    bool er=(Config::get_USER(::EnUser::ENABLE_RESERVE).toInt()!=0);
    long rl=Config::get_USER(::EnUser::RESERVE_LONG).toInt();

    while(m_OldUserTextList.size()>(er?rl:0)){
        m_OldUserTextList.pop_front();
    }
    while (m_OldRobotTextList.size()>(er?rl:0)) {
        m_OldRobotTextList.pop_front();
    }

}

const QString PushAndReceiveWidget::getLLMSpeak()
{
    int id=Config::get_USER(::EnUser::LLM_MODEL_ID).toInt();
    if(id==0)return getSpeakChatGPT();
    else if(id==1)return getSpeakXFXH();
    else if(id==2)return getSpeakDeepSeek();
    else return "";
}

const QString PushAndReceiveWidget::getSpeakXFXH()
{
    /*讯飞星火bug无法实现完美上下文对话（输出混乱,返回json不完整并且伴随自问自答胡言乱语）*/
    if(Config::get_USER(::EnUser::ENABLE_ROLE).toInt()!=0){
        QString data="";
        data=Config::get_CHARACTERCONFIG();
        data+=("我的问题:"+m_OldUserTextList.back());
        return data;
    }
    else{
        return m_OldUserTextList.back();
    }
}

const QString PushAndReceiveWidget::getSpeakDeepSeek()
{
    QList<QString>    userTextList=m_OldUserTextList;
    QList<QString>    robotTextList=m_OldRobotTextList;
    QString data="";
    while(!userTextList.empty()||!robotTextList.empty()){
        if(!userTextList.empty()){
            data+=QString("user:"+userTextList.front()+"|MARK|");
            userTextList.pop_front();
        }
        if(!robotTextList.empty()){
            data+=QString("assistant:"+robotTextList.front()+"|MARK|");
            robotTextList.pop_front();
        }
    }
    if(Config::get_USER(::EnUser::ENABLE_ROLE).toInt()!=0){
        data.push_front(QString("user:%1|MARK|assistant:%2|MARK|").arg(Config::get_CHARACTERCONFIG()).arg("好的"));
    }
    return data;
}

const QString PushAndReceiveWidget::getSpeakChatGPT()
{

    QList<QString>    userTextList=m_OldUserTextList;
    QList<QString>    robotTextList=m_OldRobotTextList;
    QString data="";
    while(!userTextList.empty()||!robotTextList.empty()){
        if(!userTextList.empty()){
            data+=QString("user:"+userTextList.front()+"|MARK|");
            userTextList.pop_front();
        }
        if(!robotTextList.empty()){
            data+=QString("assistant:"+robotTextList.front()+"|MARK|");
            robotTextList.pop_front();
        }
    }
    if(Config::get_USER(::EnUser::ENABLE_ROLE).toInt()!=0){
        data.push_front(QString("user:%1|MARK|assistant:%2|MARK|").arg(Config::get_CHARACTERCONFIG()).arg("好的"));
    }
    return data;
}

void PushAndReceiveWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    QBrush brush;
    brush.setColor(QColor(255, 255, 255, 0));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0,0,this->width(),this->height());

}


void PushAndReceiveWidget::clearHistory()
{
    //历史记录清除
    qDebug()<<"聊天记录清除";
    m_OldUserTextList.clear();
    m_OldRobotTextList.clear();
    //历史存档清除
    m_HistoryTextList.clear();

    m_InformationComing=false;

}

void PushAndReceiveWidget::clearUi()
{
    m_ListWidget->clear();
}

void PushAndReceiveWidget::handle_bot_information()
{
    emit sendIs();//设置按钮不得点击
    m_PushButtonStop->show();

    LLMBase* llm=LLMFactory::getNew(this);
    QObject::connect(llm,&LLMBase::read, [=](QString str) {
        m_PushButtonStop->hide();
        this->m_InformationComing=false;
        emit receiveIs();//按钮可点击
        this->handle_receive(str);//处理接收到的内容
        llm->deleteLater();
    });
    connect(llm,&LLMBase::quit,[=](){
        //如果没有接收信息就释放资源则报错
        if(m_InformationComing==true){
            add_bot_information("资源释放，接收信息失败！");
            m_PushButtonStop->hide();
            m_InformationComing=false;
            if(!m_OldUserTextList.isEmpty())
                m_OldUserTextList.pop_back();
            emit receiveIs();//按钮可点击
            llm->deleteLater();
        }
    });
    connect(llm,&LLMBase::stopQuit,[=](){
        llm->deleteLater();
    });
    QObject::disconnect(m_PushButtonStop, nullptr, nullptr, nullptr);
    connect(m_PushButtonStop,&QPushButton::clicked,[=](){

        add_bot_information("资源释放，接收信息失败！");
        m_PushButtonStop->hide();
        m_InformationComing=false;
        if(!m_OldUserTextList.isEmpty())
            m_OldUserTextList.pop_back();
        emit receiveIs();//按钮可点击
        llm->stop();

    });

    //向LLM端发送内容
    llm->start(getLLMSpeak());
}

void PushAndReceiveWidget::handle_receive(const QString &str)
{
    QString receivedData=str;

    //----------接收内容添加进缓存-----------
    m_OldRobotTextList.push_back(receivedData);
    m_HistoryTextList.push_back(QPair<QString,QString>(_BotMark,receivedData));

    //启用百度翻译 和 语音
    if(Config::get_USER(::EnUser::ENABLE_SOUND).toInt()!=0 && Config::get_USER(::EnUser::ENABLE_BAIDUFANYI).toInt()!=0)
    {
        BaiduApi* baiduApi=new BaiduApi(this);
        //百度翻译处理
        ReplyFinishedData replyFinishedData=&BaiduApi::replyFinishedData;
        connect(baiduApi,replyFinishedData,[=](QString handleData){
            qDebug()<<"百度翻译处理后："<<handleData;
            //启用翻译后的语言显示
            if(Config::get_USER(::EnUser::ENABLE_LATERLANGUAGE).toInt()!=0){
                add_bot_information(handleData);//listWidget添加bot列表项
            }
            //不启用翻译后的语言显示（语言与user保持一致）
            else {
                add_bot_information(receivedData);//listWidget添加bot列表项
            }
            handle_bot_sound(handleData);//音频处理和播放
            baiduApi->deleteLater();
        });
        if(baiduApi!=nullptr){
            baiduApi->functionData(receivedData);
        }
    }
    //启用百度翻译 不启用语音
    else if(Config::get_USER(::EnUser::ENABLE_BAIDUFANYI).toInt()!=0 && !(Config::get_USER(::EnUser::ENABLE_SOUND).toInt()!=0)){
        BaiduApi* baiduApi=new BaiduApi(this);
        //百度翻译处理
        ReplyFinishedData replyFinishedData=&BaiduApi::replyFinishedData;
        connect(baiduApi,replyFinishedData,[=](QString handleData){
            qDebug()<<"百度翻译处理后："<<handleData;
            //启用翻译后的语言显示
            if(Config::get_USER(::EnUser::ENABLE_LATERLANGUAGE).toInt()!=0){
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
    else if(Config::get_USER(::EnUser::ENABLE_SOUND).toInt()!=0 && !(Config::get_USER(::EnUser::ENABLE_BAIDUFANYI).toInt()!=0)){
       handle_bot_sound(receivedData);
       add_bot_information(receivedData);//listWidget添加bot列表项
    }
    //不启用语音 不启用百度翻译
    else {
        add_bot_information(receivedData);//listWidget添加bot列表项
    }

    moveHistory();
}
void PushAndReceiveWidget::add_user_information(const QString& str)
{

    QString textUser=str;
    // listWidget添加user列表项
    QListWidgetItem *item = new QListWidgetItem();
    ListItemsWidget * widget=new UserItemsWidget;

    widget->initItem(textUser,ItemEnum::User);
    m_ListWidget->addItem(item);
    item->setSizeHint(QSize(widget->width(),widget->height()));
    m_ListWidget->setItemWidget(item,widget);
    m_ListWidget->scrollToBottom();
    setAdapt();

    m_UserTextEdit->clear();
    m_UserTextEdit->setFocus();
    m_OldUserTextList.push_back(textUser);

}
void PushAndReceiveWidget::add_bot_information(const QString &str)
{
    QString receivedData=str;
    QListWidgetItem *item = new QListWidgetItem();
    ListItemsWidget * widget=new BotItemsWidget;

    emit signals_send_data_from_llm_to_main(str);
    qDebug()<<"尝试发送信息到Widget";

    widget->initItem(receivedData,ItemEnum::Bot);
    m_ListWidget->addItem(item);
    item->setSizeHint(QSize(widget->width(),widget->height()));
    m_ListWidget->setItemWidget(item,widget);
    m_ListWidget->scrollToBottom();
    setAdapt();

    QTimer::singleShot(100,this,[=](){
        QScrollBar* scrollBar = m_ListWidget->verticalScrollBar();
        scrollBar->setValue(scrollBar->maximum());

    });
}

void PushAndReceiveWidget::handle_bot_sound(const QString &str)
{
    m_RankTextList.clear();
    m_RankAudioList.clear();

    //发送表情和动画响应请求
    if(NetLive2D::getIsConnect()){
        m_RankAudioList.push_front("null");
        NetLive2D::getInstance()->sendHandle("MotAndExp:null;");
    }

    TempText = str;
    CanSend=true;
    QList<QString>list= SetCompoundDialogWidget::getHandleText(str);
    //合并掉小于四字符的文本串（为兼容gpt-sovits/*raise Exception('有效文字数太少，至少输入4个字符')*/）
    SetCompoundDialogWidget::mergeShortStrings(list);

    if(list.size()==1 && list[0].toStdString().length()<4){
        m_RankTextList.push_back("有效文字数太少,语音无法合成");
        return;
    }
    for(const QString & val:list)
        m_RankTextList.push_back(val);

}

void PushAndReceiveWidget::play_sound(const QString &path)
{
    qDebug()<<"音频开始播放";
    qDebug()<<"音频路径："<<path;
    if(SetLive2DDialogWidget::live2DIsOpen==false){
        new AudioPlayer(QUrl(path),this);
    }
    else {
        emit sendAudio(path);
    }

}


void PushAndReceiveWidget::pushbutton_send_clicked()
{
    if(this->m_InformationComing){return;}
    QString willSendStr=this->m_UserTextEdit->toPlainText();
    willSendStr.remove(QChar('\n'));
    willSendStr.remove(QChar('\r'));
    willSendStr.remove(QChar(' '));
    if(willSendStr==""){return;}

    m_InformationComing=true;
    add_user_information(m_UserTextEdit->toPlainText());
    handle_bot_information();

    m_HistoryTextList.push_back(QPair<QString,QString>(_UserMark,m_UserTextEdit->toPlainText()));

}

void PushAndReceiveWidget::slot_text_change()
{
    QTextDocument *document = m_UserTextEdit->document();
    m_UserTextEdit->setFixedHeight(int(document->size().height())+5);
    if(m_UserTextEdit->height()<=_TextEditMinHeight){
        m_UserTextEdit->setFixedHeight(_TextEditMinHeight);
    }
    if(m_UserTextEdit->height()>=_TextEditMaxHeight){
        m_UserTextEdit->setFixedHeight(_TextEditMaxHeight);
    }
    m_UserTextEdit->move(m_UserTextEdit->x(),this->height()-m_UserTextEdit->height());
}


void PushAndReceiveWidget::setAdapt()
{

    this->setFixedSize(ConfigWindow::getStaticWidth(),ConfigWindow::getStaticHeight());

    m_ListWidget->move(-1,-1);
    m_ListWidget->setFixedSize(this->width()+3,this->height()-_TextEditMinHeight);

    for(int i=0;i<m_ListWidget->count();++i){
        QListWidgetItem* listWidgetItem=m_ListWidget->item(i);
        (static_cast<ListItemsWidget*>(m_ListWidget->itemWidget(listWidgetItem)))->setAdapt();
    }
    updateListWidget();

    m_UserTextEdit->setFixedWidth(int(this->width()*0.7)-10);
    m_UserTextEdit->move(int(this->width()*0.24)-10,this->height()-m_UserTextEdit->height());
    m_PushButtonListen->setGeometry(m_UserTextEdit->geometry());
    m_Frame->move(m_UserTextEdit->width()+m_UserTextEdit->x()+10,m_ListWidget->height());
    m_Frame->setFixedSize(this->width()-m_Frame->x(),this->height()-m_Frame->y());
    m_PushButtonSet->move(0,m_Frame->y()+int((m_Frame->height()-m_PushButtonSend->height())*0.5));
    m_PushButtonSpeak->move(m_PushButtonSet->width()+1,m_Frame->y()+int((m_Frame->height()-m_PushButtonSend->height())*0.5));
    m_PushButtonWrite->move(m_PushButtonSet->width()+1,m_Frame->y()+int((m_Frame->height()-m_PushButtonSend->height())*0.5));
    m_PushButtonStop->move(m_PushButtonWrite->x()+m_PushButtonWrite->width()+1,m_Frame->y()+int((m_Frame->height()-m_PushButtonSend->height())*0.5));
    m_PushButtonSend->move(m_Frame->x()+int((m_Frame->width()-m_PushButtonSend->width())*0.5),m_Frame->y()+int((m_Frame->height()-m_PushButtonSend->height())*0.5));



}



void PushAndReceiveWidget::slot_receive_data_from_widget_to_llm(const QString &str)
{
    qDebug()<<"llm接受到来自Widget的信息————>"<<str;
    m_UserTextEdit->setText(str);
    pushbutton_send_clicked();
}

void PushAndReceiveWidget::slot_play_voice_from_widget_to_llm()
{
    qDebug()<<"llm接受到来自Widget的语言播放请求";
    VITSBase* vits=VITSFactory::getNew(this);
    connect(vits,SIGNAL(playerWay(QString)),this,SLOT(play_sound(QString)));
    connect(vits,&VITSBase::playerWay,this,[=](){vits->deleteLater();});
    vits->start(TempText);
}
