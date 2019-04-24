#ifndef WIDGET_H
#define WIDGET_H
#include "game.h"
#include <QWidget>
#include <QKeyEvent>
#include "dialog.h"
#include <QLabel>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
     Game game;
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
   void SHOW();//打印到屏幕
public slots:
   void JiXu();//槽函数，继续游戏
   void TuiChu();//槽函数，退出游戏
private:
    void keyPressEvent(QKeyEvent *event);//获取输入并执行相应操作
    QLabel *lab;
    Ui::Widget *ui;
    Dialog *dialog;//定义一个对话框成员

};

#endif // WIDGET_H
