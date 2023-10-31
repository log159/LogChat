#include "listitemswidget.h"
#include "ui_listitemswidget.h"

ListItemsWidget::ListItemsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListItemsWidget)
{
    ui->setupUi(this);

    init();
}

ListItemsWidget::~ListItemsWidget()
{
    delete ui;
}
void ListItemsWidget::init()
{
    this->setFixedSize(ConfigWindow::getStaticWidth()-10,_Height);
    this->m_Font.setPixelSize(20);

    m_IconLab=new QLabel(this);
    m_TitleEdit=new QTextEdit(this);
    m_TitleEdit->setFixedSize(int(this->width()*0.85),this->height()-10);
    m_TitleEdit->move(int((this->width()-m_TitleEdit->width())*0.5),int((this->height()-m_TitleEdit->height())*0.5));
    m_TitleEdit->setFont(this->m_Font);
    m_TitleEdit->show();
    m_TitleEdit->setReadOnly(true);
    //文本框样式
    m_TitleEdit->setObjectName("m_TitleEdit");
    m_TitleEdit->setStyleSheet(
                                "QTextEdit#m_TitleEdit {color: #FFFFFF; background-color: #388E3C; border: 2px solid #388E3C; border-radius: 5px; }"
                                "QTextEdit#m_TitleEdit:hover {background-color: #2E7D32;}"
                                "QScrollBar:vertical {width: 10px; background-color: #F5F5F5; margin: 0px 0px 0px 0px;border-radius: 5px;} "
                                "QScrollBar::handle:vertical {background-color: #CCCCCC; min-height: 20px;border-radius: 5px;} "
                                "QScrollBar::handle:vertical:hover {background-color: #BBBBBB;border-radius: 5px;} "
                                "QScrollBar::add-line:vertical {height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;} "
                                "QScrollBar::sub-line:vertical {height: 0 px; subcontrol-position: top; subcontrol-origin: margin;} "
                                "QScrollBar::add-page:vertical, "
                                "QScrollBar::sub-page:vertical {background-color: #F5F5F5;border-radius: 5px;}"
                                );

    m_IconLab=new QLabel(this);
    m_IconLab->setFixedSize(_IconWidth,_IconHeight);
    m_IconLab->hide();

}



void ListItemsWidget::initItem(const QString &strTitle,const ItemEnum& ItEn,int line)
{
    m_ItemEnum=ItEn;
    this->setItemTitle(strTitle);
    this->setItemHeight(strTitle);
    int linePx=this->height()*line;
    if(linePx>300){linePx=300;}
    this->setFixedSize(this->width(),linePx);
    this->m_TitleEdit->setFixedSize(int(this->width()*0.85),linePx-5);

    if(ItEn==ItemEnum::User){m_TitleEdit->move(10,m_TitleEdit->y());}
    else if(ItEn==ItemEnum::Bot){m_TitleEdit->move(this->width()-10-m_TitleEdit->width(),m_TitleEdit->y());}
    else {}
}

void ListItemsWidget::setAdapt()
{
    this->setFixedSize(ConfigWindow::getStaticWidth()-10,this->height());
    this->m_TitleEdit->setFixedSize(int(this->width()*0.85),this->m_TitleEdit->height());

    if(ItemEnum::User==m_ItemEnum){
        this->m_IconLab->move(this->width()-m_IconLab->width()-3,3);
        this->m_TitleEdit->move(10,m_TitleEdit->y());
    }
    else if(ItemEnum::Bot==m_ItemEnum){
        this->m_IconLab->move(3,3);
        this->m_TitleEdit->move(this->width()-10-m_TitleEdit->width(),m_TitleEdit->y());
    }
    else {

    }
}

void ListItemsWidget::setItemTitle(const QString &strTitle){
    this->m_TitleEdit->setText(strTitle);
}

void ListItemsWidget::setItemHeight(const QString &strTitle){
    this->m_TitleEdit->setFixedSize(this->m_TitleEdit->width(),strTitle.size()*10);

    m_TitleEdit->setFixedSize(m_TitleEdit->width(),int(this->height()*0.9));
}
