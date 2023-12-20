#include "changelive2dwidget.h"
#include "ui_changelive2dwidget.h"

ChangeLive2DWidget::ChangeLive2DWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeLive2DWidget)
{
    ui->setupUi(this);

    init();
}

ChangeLive2DWidget::~ChangeLive2DWidget()
{
    delete ui;
}

void ChangeLive2DWidget::init()
{
    this->setFixedSize(_Width,_Height);
}
