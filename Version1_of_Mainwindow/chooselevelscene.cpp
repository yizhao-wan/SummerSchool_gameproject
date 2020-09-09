#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
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

}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/backdrops/backdrop10.jpg");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}
