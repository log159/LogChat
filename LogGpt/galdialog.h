#ifndef GALDIALOG_H
#define GALDIALOG_H

#define PADDING 2

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
    void slots_receive_data_from_widget_to_gal(QString data); //接收Widget传递过来的数据
signals:
    void signal_send_data_from_gal_to_main(QString); //发送信息到Widget

protected:
    //鼠标按下移动及释放事件
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QPoint m_movePoint; //鼠标的位置
    bool isLeftPressDown; // 判断左键是否按下
};

#endif // GALDIALOG_H
