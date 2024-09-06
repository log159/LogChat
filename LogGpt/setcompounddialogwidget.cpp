#include "setcompounddialogwidget.h"
#include "ui_setcompounddialogwidget.h"

SetCompoundDialogWidget::SetCompoundDialogWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetCompoundDialogWidget)
{
    ui->setupUi(this);

    init();

    initConnect();
}

SetCompoundDialogWidget::~SetCompoundDialogWidget()
{
    qDebug()<<"SetCompoundDialogWidget 析构";
    delete ui;
}

void SetCompoundDialogWidget::init()
{
    this->resize(_Width,_Height);
    this->setWindowTitle("语音合成");
    this->setWindowIcon(QIcon(":/res/u77.svg"));
    this->setWindowFlags((windowFlags() & ~Qt::WindowContextHelpButtonHint) | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
    QString path = ConfigConstWay::get_TRUE_WAY(ConfigConstWay::OUTPUT_SAVEWAV_WAY);
    path.chop(QString("/%1.wav").size());
    ui->lineEdit_vioceway->setText(path);
    ui->lineEdit_vioceway->setReadOnly(true);

    QButtonGroup *block=new QButtonGroup(this);

    block->addButton(ui->radioButton_1,0);
    block->addButton(ui->radioButton_2,1);
    block->addButton(ui->radioButton_3,2);
    block->addButton(ui->radioButton_4,3);
    m_ListenTimer=new QTimer(this);


    int pos = Config::get_USER(::EnUser::AUDIOSYNTHESIS).toInt();

    static_cast<QRadioButton*>(block->buttons()[pos])->setChecked(true);
    ui->lineEdit_str->setText(Config::get_USER(::EnUser::AUDIOBREAKSTR));

    QFile file(":/main.qss");
    if(file.open(QFile::ReadOnly)){
        QString styleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }

}

void SetCompoundDialogWidget::initConnect()
{
    connect(m_ListenTimer,&QTimer::timeout,[=](){
        static bool canSend=true;
        if(true==canSend && !m_RankTextList.isEmpty()){
            m_ListenTimer->stop();
            VITSBase* vits = VITSFactory::getNew(this);
            canSend=false;
            connect(vits,&VITSBase::playerWay,[=](QString path){
                canSend=true;
                saveSound(path);
                if(true==m_CanPause){
                    m_ListenTimer->stop();
                }
                else {
                    m_ListenTimer->start(10);
                }
                qDebug()<<path;
                vits->deleteLater();
            });
            vits->start(m_RankTextList.front());
            m_RankTextList.pop_front();
        }

    });

    connect(ui->pushButton_start,&QPushButton::clicked,[=](){
        m_ListenTimer->start(10);
        handleText();
    });
    connect(ui->pushButton_stop,&QPushButton::clicked,[=](){
        if(!m_CanPause){
            m_ListenTimer->stop();
            ui->pushButton_stop->setText("继续");
        }
        else {
            m_ListenTimer->start(10);
            ui->pushButton_stop->setText("暂停");
        }
        m_CanPause=!m_CanPause;
    });
    connect(ui->pushButton_end,&QPushButton::clicked,[=](){
        m_CanPause=false;
        m_RankTextList.clear();
        ui->pushButton_stop->setText("暂停");
    });

    connect(ui->pushButton_play,&QPushButton::clicked,[=](){
        QListWidgetItem* selectedItem = ui->listWidget_voiceway->currentItem();
        if (!selectedItem) {
            return;
        }
        QString text = selectedItem->text();
        m_MySound.reset(new QSound(text));

        qDebug()<<"音频开始播放";
        m_MySound->play();
    });
    connect(ui->pushButton_unplay,&QPushButton::clicked,[=](){
        m_MySound.reset(nullptr);
    });

    connect(ui->pushButton_voicefind,&QPushButton::clicked,[=](){
        QString directoryPath = ui->lineEdit_vioceway->text();
        qDebug()<<"open file path"<<directoryPath;

        QUrl directoryUrl = QUrl::fromLocalFile(directoryPath);
        if (QDesktopServices::openUrl(directoryUrl)) {
            qDebug() << "File explorer opened successfully.";
        } else {
            qDebug() << "Failed to open file explorer.";
        }
    });
    connect(ui->radioButton_1,&QRadioButton::toggled,[=](){
        Config::set_USER(::EnUser::AUDIOSYNTHESIS,QString::number(0));
    });
    connect(ui->radioButton_2,&QRadioButton::toggled,[=](){
        Config::set_USER(::EnUser::AUDIOSYNTHESIS,QString::number(1));
    });
    connect(ui->radioButton_3,&QRadioButton::toggled,[=](){
        Config::set_USER(::EnUser::AUDIOSYNTHESIS,QString::number(2));
    });
    connect(ui->radioButton_4,&QRadioButton::toggled,[=](){
        Config::set_USER(::EnUser::AUDIOSYNTHESIS,QString::number(3));
    });

    connect(ui->lineEdit_str, &QLineEdit::textChanged,[=](){
        Config::set_USER(::EnUser::AUDIOBREAKSTR,ui->lineEdit_str->text());
    });

}

void SetCompoundDialogWidget::handleText()
{
    int pos = Config::get_USER(::EnUser::AUDIOSYNTHESIS).toInt();
    QString text = ui->textEdit_txt->toPlainText();
    qDebug()<<"QString List:";
    if(pos==0){
        m_RankTextList.push_back(text);
        qDebug()<<text;
    }
    else if(pos==1){
        QStringList strlist = text.split('\n');
        for(const QString& val:strlist){
            if(val.isEmpty())continue;
            m_RankTextList.push_back(val);
            qDebug()<<val;
        }
    }
    else if(pos==2){

        QRegExp regex(QString("[%1%2]").arg(QRegularExpression::escape(RegExpChar::CHINESE_CHAR)).arg(QRegularExpression::escape(RegExpChar::ENGLISH_CHAR)));
        // 使用正则表达式分割字符串
        QStringList strlist = text.split(regex);
        for(const QString& val:strlist){
            if(val.isEmpty())continue;
            m_RankTextList.push_back(val);
            qDebug()<<val;
        }

    }
    else if(pos==3){
        QString userstr = ui->lineEdit_str->text();
        QStringList strlist = text.split(userstr);
        for(const QString& val:strlist){
            if(val.isEmpty())continue;
            m_RankTextList.push_back(val);
            qDebug()<<val;
        }
    }
}

void SetCompoundDialogWidget::saveSound(const QString &path)
{
    if(path.size()<QString(".wav").size()){
        return;
    }
    int pos=path.lastIndexOf('/');
    if(pos==-1){
        return;
    }
    QString fileName=path.mid(pos+1);
    fileName.chop(QString(".wav").size());
    QString sourceFile = path;
    QString destFile = ConfigConstWay::get_TRUE_WAY(ConfigConstWay::OUTPUT_SAVEWAV_WAY).arg(fileName);
    bool success = QFile::copy(sourceFile, destFile);
    if (!success) {
        qDebug() << "拷贝文件失败：" << sourceFile << " 到 " << destFile;
    }
    ui->listWidget_voiceway->addItem(QString(destFile));

}

QList<QString> SetCompoundDialogWidget::getHandleText(const QString &str)
{
    QString text=str;
    text.remove(QRegExp(QString("[%1]").arg(RegExpChar::SPECIAL_CHAR)));
    int pos = Config::get_USER(::EnUser::AUDIOSYNTHESIS).toInt();
    qDebug()<<"QString List:";
    QList<QString> list;
    if(pos==0){
        list.push_back(text);
        qDebug()<<text;
    }
    else if(pos==1){
        QStringList strlist = text.split('\n');
        for(const QString& val:strlist){
            if(val.isEmpty())continue;
            list.push_back(val);
            qDebug()<<val;
        }
    }
    else if(pos==2){

        QRegExp regex(QString("[%1%2]").arg(QRegularExpression::escape(RegExpChar::CHINESE_CHAR)).arg(QRegularExpression::escape(RegExpChar::ENGLISH_CHAR)));
        // 使用正则表达式分割字符串
        QStringList strlist = text.split(regex);
        for(const QString& val:strlist){
            if(val.isEmpty())continue;
            list.push_back(val);
            qDebug()<<val;
        }

    }
    else if(pos==3){
        QString userstr = Config::get_USER(::EnUser::AUDIOBREAKSTR);
        QStringList strlist = text.split(userstr);
        for(const QString& val:strlist){
            if(val.isEmpty())continue;
            list.push_back(val);
            qDebug()<<val;
        }
    }
    return list;
}
