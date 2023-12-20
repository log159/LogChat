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

    QString information_str="LogChat客户端 V-5.0\n"
                            "By LearningLog\n"
                            "-------------------\n"
                            "支持LLM大模型:\n"
                            "ChatGPT\n"
                            "讯飞星火\n\n"
                            "-------------------\n"
                            "支持vits模型:\n"
                            "vits\n"
                            "bert-vits2\n"
                            "w2v2-vits\n";
    QFont font;
    font.setPixelSize(25);
    ui->textEdit_about->setFont(font);
    ui->textEdit_about->setReadOnly(true);
    ui->textEdit_about->setText(information_str);

}
