#include "aboutsoftwaredialogwidget.h"
#include "ui_aboutsoftwaredialogwidget.h"

AboutSoftwareDialogWidget::AboutSoftwareDialogWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutSoftwareDialogWidget)
{
    ui->setupUi(this);
    init();
}

AboutSoftwareDialogWidget::~AboutSoftwareDialogWidget()
{
    delete ui;
}

void AboutSoftwareDialogWidget::init()
{
    this->resize(_Width,_Height);
    this->setWindowTitle("关于");
    this->setWindowIcon(QIcon(":/res/u77.svg"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QString information_str="#LogChat Version-7.3\n"
                            "- 一个开源免费的Chat客户端！\n"
                            "- GitHub:https://github.com/log159/LogChat\n"
                            "#版本记录"
                            "#before--------------------------\n"
                            "- 支持ChatGPT、讯飞星火大语言模型\n"
                            "- 支持vits、bert-vits2、w2v2-vits\n"
                            "#6.0-----------------------------\n"
                            "- 支持基本Live2D\n"
                            "#7.0-----------------------------\n"
                            "- 支持Live2D基本自定义\n"
                            "#7.1\n"
                            "- Live2d窗口显示不适配问题\n"
                            "- Live2d窗口遮挡Web界面问题\n"
                            "#7.2\n"
                            "- 发送消息框光标问题\n"
                            "- UI优化，感谢GitHub@Zao-chen\n"
                            "- 使得设置信息可以保存\n"
                            "- 百度翻译处理不完全问题\n"
                            "#7.3\n"
                            "- 添加了Galgame样式对话框\n"
                            "- 右键点击l2d可出现对话框\n"
                            "- 解决了Live2d设置滑动条两端非整数显示问题\n"
                            "- 解决了消息界面大小突变时文本框的显示问题\n"
                            "#End 有Bug欢迎反馈！\n";
    QFont font;
    font.setPixelSize(20);
    ui->textEdit_about->setFont(font);
    ui->textEdit_about->setReadOnly(true);
    ui->textEdit_about->setText(information_str);

    ui->textEdit_about->setStyleSheet(
                "QScrollBar:vertical {width: 10px;background-color: #F5F5F5;margin: 0px 0px 0px 0px;border-radius: 5px;}"
                "QScrollBar::handle:vertical {background-color: #CCCCCC;min-height: 20px;border-radius: 5px;}"
                "QScrollBar::handle:vertical:hover {background-color: #BBBBBB;border-radius: 5px;}"
                "QScrollBar::add-line:vertical {height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;}"
                "QScrollBar::sub-line:vertical {height: 0 px;subcontrol-position: top; subcontrol-origin: margin;}"
                "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background-color: #F5F5F5;border-radius: 5px;}"
                );


    /*读取qss文件*/
    QFile file(":/main.qss");
    if(file.open(QFile::ReadOnly)){
        QString styleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }

}
