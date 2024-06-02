#ifndef GALDIALOG_H
#define GALDIALOG_H

#define PADDING 2
enum Direction { UP=0, DOWN=1, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };

#include <QWidget>
#include <QLineEdit>
namespace Ui {
class GalDialog;
}

class GalDialog : public QWidget
{
    Q_OBJECT

public:
    explicit GalDialog(QWidget *parent = nullptr);
    ~GalDialog();

private slots:
    void on_lineEdit_returnPressed();

    void on_pushButton_clicked();

private:
    Ui::GalDialog *ui;
public slots:
    void receive_data_from_widget(QString data);   //接收Widget传递过来的数据的槽
signals:
    void send_data_from_gal_to_main(QString);   //用来传递发送信息的信号

public:
    void region(const QPoint &currentGlobalPoint);  //鼠标的位置,改变光标
protected:
    //鼠标按下移动及释放事件
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QPoint m_movePoint;  //鼠标的位置
    bool isLeftPressDown;  // 判断左键是否按下
    Direction dir;        // 窗口大小改变时，记录改变方向


};

#endif // GALDIALOG_H
