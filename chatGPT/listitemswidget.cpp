#include "listitemswidget.h"
#include "ui_listitemswidget.h"

ListItemsWidget::ListItemsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListItemsWidget)
{
    ui->setupUi(this);

    initWidget();
}

ListItemsWidget::~ListItemsWidget()
{
    delete ui;
}
void ListItemsWidget::initWidget()
{
    this->setFixedSize(415,40);
    this->_Font.setPixelSize(20);

    _Icon_lab=new QLabel(this);
    _Title_edit=new QTextEdit(this);
    _Title_edit->setFixedSize(int(this->width()*0.88),int(this->height()*0.9));
    _Title_edit->move(int((this->width()-_Title_edit->width())*0.5),int((this->height()-_Title_edit->height())*0.5));
//    _Title_edit->setStyleSheet("border:2px solid red;");//设置边框
    _Title_edit->setFont(this->_Font);
    _Title_edit->show();
    _Title_edit->setReadOnly(true);
    //文本框样式
    _Title_edit->setObjectName("_Title_edit");
    _Title_edit->setStyleSheet("QTextEdit#_Title_edit {"
                               "color: #FFFFFF; "
                               "background-color: #388E3C; "
                               "border: 2px solid #388E3C; "
                               "border-radius: 5px; "
                               "}"
                               " QTextEdit#_Title_edit:hover {"
                               "background-color: "
                               "#2E7D32;}"
                               "QScrollBar:vertical {"
                               "width: 10px; "
                               "background-color: #F5F5F5; "
                               "margin: 0px 0px 0px 0px;"
                               "border-radius: 5px;"
                               "} "
                               "QScrollBar::handle:vertical {"
                               "background-color: #CCCCCC; "
                               "min-height: 20px;"
                                "border-radius: 5px;"
                               "} "
                               "QScrollBar::handle:vertical:hover {"
                               "background-color: #BBBBBB;"
                               "border-radius: 5px;"
                               "} "
                               "QScrollBar::add-line:vertical {"
                               "height: 0px; "
                               "subcontrol-position: bottom; "
                               "subcontrol-origin: margin;"
                               "} "
                               "QScrollBar::sub-line:vertical "
                               "{height: 0 px; "
                               "subcontrol-position: top; "
                               "subcontrol-origin: margin;"
                               "} "
                               "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
                               "background-color: #F5F5F5;"
                               "border-radius: 5px;"
                               "}");
    _Icon_lab=new QLabel(this);
    _Icon_lab->setFixedSize(_IconWidth,_IconHeight);
    _Icon_lab->hide();

}

void ListItemsWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
//    QPainter painter(this);
//    painter.drawRect(0,0,this->width()-1,this->height()-1);

}


void ListItemsWidget::initItem(const QString &strTitle,const ItemEnum& ItEn,int line)
{
    this->setItemTitle(strTitle);
    this->setItemHeight(strTitle);
    int linePx=this->height()*line;
    if(linePx>300){linePx=300;}
    this->setFixedSize(this->width(),linePx);
    this->_Title_edit->setFixedSize(this->_Title_edit->width(),linePx-5);
    if(ItEn==ItemEnum::User){_Title_edit->move(10,_Title_edit->y());}
    else if(ItEn==ItemEnum::Bot){_Title_edit->move(this->width()-10-_Title_edit->width(),_Title_edit->y());}
    else {}
}

void ListItemsWidget::setItemTitle(const QString &strTitle){
    this->_Title_edit->setText(strTitle);
}

void ListItemsWidget::setItemHeight(const QString &strTitle){
    this->_Title_edit->setFixedSize(this->_Title_edit->width(),strTitle.size()*10);

    _Title_edit->setFixedSize(_Title_edit->width(),int(this->height()*0.9));
}
