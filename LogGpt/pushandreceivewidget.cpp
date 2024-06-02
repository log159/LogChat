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
    this->setFixedSize(ConfigWindow::getStaticWidth(),ConfigWindow::getStaticHeight());


    m_VitsApi=new VitsApi(this);

    m_ListWidget=new QListWidget(this);
    m_ListWidget->setStyleSheet(
                "QScrollBar:vertical {width: 10px;background-color: #F5F5F5;margin: 0px 0px 0px 0px;border-radius: 5px;}"
                "QScrollBar::handle:vertical {background-color: #CCCCCC;min-height: 20px;border-radius: 5px;}"
                "QScrollBar::handle:vertical:hover {background-color: #BBBBBB;border-radius: 5px;}"
                "QScrollBar::add-line:vertical {height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;}"
                "QScrollBar::sub-line:vertical {height: 0 px;subcontrol-position: top; subcontrol-origin: margin;}"
                "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background-color: #F5F5F5;border-radius: 5px;}"
                );

    m_ListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);         //禁止编辑
    m_ListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);       //禁用水平滑动条
    m_ListWidget->setSelectionMode(QAbstractItemView::NoSelection);           //禁止选中
    m_ListWidget->setFocusPolicy(Qt::NoFocus);                                //禁止获取焦点
    m_ListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   //平滑效果


    m_ListWidget->show();

    m_UserTextEdit=new UserTextEdit(this);
    m_UserTextEdit->setPlaceholderText("来说点什么吧( Shift+Enter换行 Enter发送 )");
    m_UserTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_UserTextEdit->setFixedHeight(_TextEditMinHeight);
    m_UserTextEdit->setStyleSheet("QTextEdit {"
                                  "border: 2px solid #AAAAAA; " /* 设置边框颜色为浅绿色 */
                                  "border-radius: 10px; "       /* 设置圆角半径为10像素 */
                                  "background-color: #FFFFFF; " /* 设置背景颜色为淡蓝色 */
                                  "padding: 5px; "              /* 设置内边距为5像素 */
                                  "}"
                                  "QTextEdit:focus {"
                                  "outline: none; "             /* 移除焦点时的边框 */
                                  "}"
                                  );
    QFont font;
    font.setFamily("黑体");
    font.setPointSize(10);
    m_UserTextEdit->setFont(font);
    m_UserTextEdit->show();
    m_Frame=new QFrame(this);
    m_Frame->setStyleSheet("background-color:white;");

    m_PushButtonListen=new QPushButton(this);
    m_PushButtonListen->setText("点击说话(敬请期待)");
    m_PushButtonListen->setStyleSheet("QPushButton {"
                                  "border: 2px solid #AAAAAA; " /* 设置边框颜色为浅绿色 */
                                  "border-radius: 10px; "       /* 设置圆角半径为10像素 */
                                  "background-color: #FFFFFF; " /* 设置背景颜色为淡蓝色 */
                                  "padding: 5px; "              /* 设置内边距为5像素 */
                                  "}"
                                  "QTextEdit:focus {"
                                  "outline: none; "             /* 移除焦点时的边框 */
                                  "}"
                                  );
    m_PushButtonListen->setGeometry(m_UserTextEdit->geometry());
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

    setAdapt();
    addCharacterConfig();
    m_UserTextEdit->setFocus();
}

void PushAndReceiveWidget::initConnect()
{
    connect(m_UserTextEdit,SIGNAL(textChanged()),this,SLOT(slot_text_change()));
    connect(m_VitsApi,SIGNAL(playerWay(QString)),this,SLOT(play_sound(QString)));
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
}

void PushAndReceiveWidget::updateListWidget()
{
    for(int i=0;i<m_ListWidget->count();++i){
        QListWidgetItem* listWidgetItem=m_ListWidget->item(i);
        QSize size=(static_cast<ListItemsWidget*>(m_ListWidget->itemWidget(listWidgetItem)))->size();
        listWidgetItem->setSizeHint(QSize(size.width(),size.height()+20));
    }
}


void PushAndReceiveWidget::addCharacterConfig()
{
    //启用扮演
    if(Config::get_ENABLE_ROLE())
    {
        m_OldUserTextList.push_back(Config::get_CHARACTER_CONFIG());
        m_OldRobotTextList.push_back("OK");
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
        if(m_OldUserTextList.size()-1>(Config::get_ENABLE_RESERVE()?Config::get_RESERVE_LONG():0)){
            m_OldUserTextList.removeAt(1);
            m_OldRobotTextList.removeAt(1);
        }
    }
    //不启用扮演情况下移除
    else{
        //如果历史记录过长则移除部分
         if(m_OldUserTextList.size()>(Config::get_ENABLE_RESERVE()?Config::get_RESERVE_LONG():0)){
             m_OldUserTextList.removeAt(0);
             m_OldRobotTextList.removeAt(0);
         }
    }
}

const QString PushAndReceiveWidget::getSpeakXFXH()
{
    QString content="";
    if(Config::get_ENABLE_ROLE()){
        content = Config::get_CHARACTER_CONFIG()+"\n 我的问题：";
    }
    content+=m_OldUserTextList.back();
    return content;
// json 字符串格式
//    const QPair<QString,QString>user_pair=QPair<QString,QString>(QString("{\"role\":\"user\",\"content\":\""),QString("\"}"));
//    const QPair<QString,QString>bot_pair=QPair<QString,QString>(QString("{\"role\":\"assistant\",\"content\":\""),QString("\"}"));
//    QString response_havehistory;
//    QVector<QString>   old_vector;
//    for(int i=0;i<m_OldUserTextList.size();++i){
//        QString item_str=m_OldUserTextList[i];
//        old_vector.push_back(user_pair.first+item_str+user_pair.second);
//        if(i==m_OldRobotTextList.size()){
//            break;
//        }
//        else {
//            old_vector.push_back(bot_pair.first+m_OldRobotTextList[i]+bot_pair.second);
//        }

//    }
//    for(int i=0;i<old_vector.size();++i){
//        response_havehistory+=old_vector.at(i);
//        if(i==old_vector.size()-1){
//            break;
//        }
//        response_havehistory+=",";
//    }
//    response_havehistory.push_front("[");
//    response_havehistory.push_back("]");
    //    return response_havehistory;
}

void PushAndReceiveWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    QBrush brush;
    brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);
    painter.drawRect(0,0,this->width(),this->height());

}

const QString PushAndReceiveWidget::getSpeakChatGPT()
{
    QString response_havehistory;
    QVector<QString>   old_vector;
    for(int i=0;i<m_OldUserTextList.size();++i){
        QString item_str=m_OldUserTextList[i];
        old_vector.push_back("["+item_str+"],");
        if(i==m_OldRobotTextList.size()){
            old_vector.back().push_back("[]");
            break;
        }
        else {
            old_vector.back().push_back("["+m_OldRobotTextList[i]+"]");
        }

    }
    for(int i=0;i<old_vector.size();++i){
        if(i!=old_vector.size()-1){
            response_havehistory+=QString("["+old_vector[i]+"],");
        }
        else {
            response_havehistory+=QString("["+old_vector[i]+"]");
        }
    }
    response_havehistory.push_front("[");
    response_havehistory.push_back("]");
    return response_havehistory;
}

void PushAndReceiveWidget::clearHistory()
{
    //历史记录清除
    qDebug()<<"聊天记录清除";
    m_OldUserTextList.clear();
    m_OldRobotTextList.clear();
    if(Config::get_ENABLE_ROLE()){
        addCharacterConfig();
    }
    m_InformationComing=false;

}

void PushAndReceiveWidget::clearUi()
{

    m_ListWidget->clear();

}



void PushAndReceiveWidget::handle_bot_information()
{
    emit sendIs();//设置按钮不得点击
    LLMBase* LLM=nullptr;
    if(Config::get_LLM_MODEL_ID()==0){LLM=LLMFactory::getChatGPTApi(this);}
    else {LLM=LLMFactory::getXfxhApi(this);}
    QObject::connect(LLM,&LLMBase::read, [=](QString str) {
        this->m_InformationComing=false;
        emit receiveIs();//按钮可点击
        this->handle_receive(str);//处理接收到的内容
    });
    connect(LLM,&LLMBase::quit,[=](){
        //如果没有接收信息就释放资源则报错
        if(m_InformationComing==true){
            QMessageBox::warning(this,"Error occurred","出现错误，接收信息失败！");
            m_InformationComing=false;
            m_OldUserTextList.pop_back();
            emit receiveIs();//按钮可点击
        }
    });
    //向LLM端发送内容
    if(Config::get_LLM_MODEL_ID()==0){
        LLM->start(getSpeakChatGPT());
    }
    else {
        //讯飞星火bug无法实现完美上下文对话
        LLM->start(getSpeakXFXH());
    }
}

void PushAndReceiveWidget::handle_receive(const QString &str)
{
    QString receivedData=str;

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
    textUser.replace("\n", "");
    m_OldUserTextList.push_back(textUser);

}
void PushAndReceiveWidget::add_bot_information(const QString &str)
{
    QString receivedData=str;
    QListWidgetItem *item = new QListWidgetItem();
    ListItemsWidget * widget=new BotItemsWidget;

    emit send_data_from_llm_to_main(str);
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
    QString url = Config::get_URL_ADDRESS_ALL().arg(str);
    m_VitsApi->start(url);
}

void PushAndReceiveWidget::play_sound(const QString &str)
{
    qDebug()<<"音频开始播放";
    qDebug()<<"音频路径："<<str;
    if(SetLive2DDialogWidget::live2DIsOpen==false){
        QSound * startGameSound=new QSound(str);
        startGameSound->setParent(this);
        startGameSound->play();
    }
    else {
        emit sendAudio(str);
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

    m_UserTextEdit->move(int(this->width()*0.15),this->height()-m_UserTextEdit->height());
////    m_UserTextEdit->moveCursor(QTextCursor::End);

//    if (!m_UserTextEdit->isCursorVisible()) {
////    m_UserTextEdit->ensureCursorVisible();
//        qDebug()<<"光标不可见";
//    }
//    else{
//        qDebug()<<"光标可见";
//    }
}


void PushAndReceiveWidget::setAdapt()
{

    this->setFixedSize(ConfigWindow::getStaticWidth(),ConfigWindow::getStaticHeight());

    for(int i=0;i<m_ListWidget->count();++i){
        QListWidgetItem* listWidgetItem=m_ListWidget->item(i);
        (static_cast<ListItemsWidget*>(m_ListWidget->itemWidget(listWidgetItem)))->setAdapt();
    }
    updateListWidget();

    m_ListWidget->move(-1,-1);
    m_ListWidget->setFixedSize(this->width()+2,this->height()-_TextEditMinHeight);
    m_UserTextEdit->setFixedWidth(int(this->width()*0.8)-10);
    m_UserTextEdit->move(int(this->width()*0.15)-10,this->height()-m_UserTextEdit->height());
    m_PushButtonListen->setGeometry(m_UserTextEdit->geometry());
    m_Frame->move(m_UserTextEdit->width()+m_UserTextEdit->x()+10,m_ListWidget->height());
    m_Frame->setFixedSize(this->width()-m_Frame->x(),this->height()-m_Frame->y());
    m_PushButtonSet->move(0,m_Frame->y()+int((m_Frame->height()-m_PushButtonSend->height())*0.5));
    m_PushButtonSpeak->move(m_PushButtonSet->width()+1,m_Frame->y()+int((m_Frame->height()-m_PushButtonSend->height())*0.5));
    m_PushButtonWrite->move(m_PushButtonSet->width()+1,m_Frame->y()+int((m_Frame->height()-m_PushButtonSend->height())*0.5));
    m_PushButtonSend->move(m_Frame->x()+int((m_Frame->width()-m_PushButtonSend->width())*0.5),m_Frame->y()+int((m_Frame->height()-m_PushButtonSend->height())*0.5));




}



void PushAndReceiveWidget::send_data_from_main_to_llm(const QString &str)
{
    qDebug()<<"发送来自gal视窗的信息"<<str;
    m_UserTextEdit->setText(str);
    pushbutton_send_clicked();
}
