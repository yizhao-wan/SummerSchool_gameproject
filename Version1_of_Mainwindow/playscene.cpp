#include "playscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include "mypushbutton.h"
#include "mainscene.h"

PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
{
    //设置窗口固定大小
    this->setFixedSize(1024, 768);
    //设置图标
    this->setWindowIcon(QPixmap(":/images/title_popcap.jpg"));
    //设置标题
    this->setWindowTitle("曹一凡年级第一");

    //创建菜单栏
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
    //创建按钮菜单项
    QAction * quitAction = startMenu->addAction("退出");
    //点击退出 退出游戏
    connect(quitAction, &QAction::triggered, [=]() {
        this->close();
    });

    //创建暂停按钮,但是目前设置为返回上一个界面
    MyPushButton* pauseBtn = new MyPushButton(":/images/PAUSE.gif", ":/images/Pause_.jpg");
    pauseBtn->setParent(this);
    pauseBtn->move(this->width() * 0.8 - pauseBtn->width() * 0.5, this->height() * 0.4);

    connect(pauseBtn, &MyPushButton::clicked, [=](){
        pauseBtn->zoom1(); //向下跳跃
        pauseBtn->zoom2(); //向上跳跃
        QTimer::singleShot(200, this, [=]() {
            this->hide();
            emit this->playSceneBack();
        });
    });
}

void PlayScene::paintEvent(QPaintEvent *)
{
    //设置背景图片
    QPainter painter(this);
    QPixmap pix1, pix2, pix3;
    pix1.load(":/images/backdrops/backdrop11.jpg");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix1);

    //设置棋盘的边框
    pix3.load(":/images/puzzleframe.gif");
    painter.drawPixmap(14, 126, 544, 544, pix3);

    //设置半透明的棋盘
    pix2.load(":/images/sm_puzzleframe_.gif");
    QPixmap temp(pix2.size());
    temp.fill(Qt::transparent);
    QPainter p1(&temp);
    p1.setCompositionMode(QPainter::CompositionMode_Source);
    p1.drawPixmap(0, 0, pix2);
    p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p1.fillRect(temp.rect(), QColor(0, 0, 0, 150));
    p1.end();
    pix2 = temp;
    painter.drawPixmap(30, 140, 512, 512, pix2);
}
