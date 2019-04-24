#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
#include <QDebug>
#include <QString>
#include "game.h"
#include <QMessageBox>
#include <QLabel>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFocus();
    game.Restart();
    this->SHOW();
    /* 设置对话框 */
    dialog =new Dialog(this);
    dialog->setModal(true);//模态窗口模式
    dialog->setWindowTitle("2048");
    dialog->hide();
    lab=new QLabel(dialog);
    lab->move(70,20);
    /*连接信号和槽 */
    connect(dialog,SIGNAL(jixu()),this,SLOT(JiXu()));
    connect(dialog,SIGNAL(tuichu()),this,SLOT(TuiChu()));
}


Widget::~Widget()
{
    delete ui;
}


void Widget::SHOW()
{
    //通过改变不同位置的样式表来显示不同的数字
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            int x=i*4+j;
            QGraphicsView *p=nullptr;
            //选择指针指向位置（第几行第几列）
            switch (x) {
            case 0: p=ui->p1;break;
            case 1: p=ui->p2;break;
            case 2: p=ui->p3;break;
            case 3: p=ui->p4;break;
            case 4: p=ui->p5;break;
            case 5: p=ui->p6;break;
            case 6: p=ui->p7;break;
            case 7: p=ui->p8;break;
            case 8: p=ui->p9;break;
            case 9: p=ui->p10;break;
            case 10: p=ui->p11;break;
            case 11: p=ui->p12;break;
            case 12: p=ui->p13;break;
            case 13: p=ui->p14;break;
            case 14: p=ui->p15;break;
            case 15: p=ui->p16;break;
            default:break;
            }
            //选择显示的数据
            switch(game.BoardList[i][j])
            {
            case 0:p->setStyleSheet("border-image:url(:/img/0.png)");break;
            case 2:p->setStyleSheet("border-image:url(:/img/2.png)");break;
            case 4:p->setStyleSheet("border-image:url(:/img/4.png)");break;
            case 8:p->setStyleSheet("border-image:url(:/img/8.png)");break;
            case 16:p->setStyleSheet("border-image:url(:/img/16.png)");break;
            case 32:p->setStyleSheet("border-image:url(:/img/32.png)");break;
            case 64:p->setStyleSheet("border-image:url(:/img/64.png)");break;
            case 128:p->setStyleSheet("border-image:url(:/img/128.png)");break;
            case 256:p->setStyleSheet("border-image:url(:/img/256.png)");break;
            case 512:p->setStyleSheet("border-image:url(:/img/512.png)");break;
            case 1024:p->setStyleSheet("border-image:url(:/img/1024.png)");break;
            case 2048:p->setStyleSheet("border-image:url(:/img/2048.png)");break;
            default:break;
            }
        }
    }
}

void Widget::JiXu()
{
    game.Restart();
    this->SHOW();
    this->SHOW();
}
void Widget::TuiChu()
{
    this->close();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    //根据按键执行相应的函数
    if(event->key()==Qt::Key_Escape)
    {
        this->close();
    }
    if(event->key()==Qt::Key_R)
    {

        game.Restart();

    }
    if(event->key()==Qt::Key_Up)
    {
        game.Up();
    }
    if(event->key()==Qt::Key_Left)
    {
        game.Left();
    }
    if(event->key()==Qt::Key_Right)
    {
        game.Right();
    }
    if(event->key()==Qt::Key_Down)
    {
        game.Down();
    }
    if(game.LOSE())
    {

        lab->setText("你输了，是否继续？");
        dialog->show();
     }
    if(game.WIN())
    {
        lab->setText("你赢了，是否继续？");
        dialog->show();
    }
    this->SHOW();
}


