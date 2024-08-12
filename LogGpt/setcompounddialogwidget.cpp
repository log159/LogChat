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
    delete ui;
}

void SetCompoundDialogWidget::init()
{
    this->resize(_Width,_Height);
    this->setWindowTitle("语音合成");
    this->setWindowIcon(QIcon(":/res/u77.svg"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint | Qt::WindowStaysOnTopHint);

    QString path = ConfigConstWay::get_TRUE_WAY(ConfigConstWay::OUTPUT_COMPOUNDWAV_WAY);
    path.remove("/%1.wav");
    ui->lineEdit->setText(path);
    ui->lineEdit->setReadOnly(true);

    QButtonGroup *block=new QButtonGroup(this);

    block->addButton(ui->radioButton_1,0);
    block->addButton(ui->radioButton_2,1);
    block->addButton(ui->radioButton_3,2);
    block->addButton(ui->radioButton_4,3);

    static_cast<QRadioButton*>(block->buttons()[0])->setChecked(true);
}

void SetCompoundDialogWidget::initConnect()
{

    connect(ui->pushButton_start,&QPushButton::clicked,[=](){
        isReturn=false;
        m_Vits = VITSFactory::getNew(this);
        connect(m_Vits,SIGNAL(playerWay(QString)),this,SLOT(save_sound(QString)));
        m_Vits->start(ui->textEdit_txt->toPlainText());
    });
    connect(ui->pushButton_stop,&QPushButton::clicked,[=](){

    });
    connect(ui->pushButton_end,&QPushButton::clicked,[=](){

    });

    connect(ui->pushButton_play,&QPushButton::clicked,[=](){
        if(isReturn==false){return ;}
        qDebug()<<"音频开始播放";

        if(m_MySound!=nullptr){
            delete  m_MySound;
            m_MySound=nullptr;
        }
        m_MySound=new QSound(path);
        m_MySound->setParent(this);
        m_MySound->play();
    });
    connect(ui->pushButton_unplay,&QPushButton::clicked,[=](){

    });
    connect(ui->pushButton_replay,&QPushButton::clicked,[=](){

    });

    //打开音频输出文件夹
    connect(ui->pushButton_find,&QPushButton::clicked,[=](){
        QString directoryPath = ui->lineEdit->text();
        qDebug()<<"open file path"<<directoryPath;

        // 构建目录的URL
        QUrl directoryUrl = QUrl::fromLocalFile(directoryPath);

        // 打开资源管理器并指定目录
        if (QDesktopServices::openUrl(directoryUrl)) {
            qDebug() << "File explorer opened successfully.";
        } else {
            qDebug() << "Failed to open file explorer.";
        }
    });
    connect(ui->radioButton_1,&QRadioButton::toggled,[=](){});
    connect(ui->radioButton_2,&QRadioButton::toggled,[=](){});
    connect(ui->radioButton_3,&QRadioButton::toggled,[=](){});
    connect(ui->radioButton_4,&QRadioButton::toggled,[=](){});



}

void SetCompoundDialogWidget::save_sound(const QString &str)
{
    path=str;
    isReturn=true;
}
