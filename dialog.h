#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

/*
定义一个对话框，游戏输了或者赢了，弹出
*/
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
signals:
    void jixu();//发送继续游戏信号
    void tuichu();//发送退出游戏信号
private slots:
    void on_pushButton_2_released();
    void on_pushButton_released();
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
