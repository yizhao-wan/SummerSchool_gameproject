#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include "mypushbutton.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置窗口大小
    this->setFixedSize(1024, 768);
    //设置标题图片
    this->setWindowIcon(QPixmap(":/images/title_popcap.jpg"));
    //设置标题
    this->setWindowTitle("万书记带你上天入地");
    //退出按钮
    connect(ui->actionQuit, &QAction::triggered, [=]() {
        this->close();
    });

    //初始化主菜单的按钮
    MyPushButton* startBtn = new MyPushButton(":/images/Play.gif", ":/images/Play_.jpg");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.2 - startBtn->width() * 0.5, this->height() * 0.2);

    MyPushButton* quitBtn = new MyPushButton(":/images/Quit.gif", ":/images/Quit_.jpg");
    quitBtn->setParent(this);
    quitBtn->move(this->width() * 0.2 - startBtn->width() * 0.5, this->height() * 0.55);

    MyPushButton* optionsBtn = new MyPushButton(":/images/Options.gif", ":/images/Options_.jpg");
    optionsBtn->setParent(this);
    optionsBtn->move(this->width() * 0.2 - startBtn->width() * 0.5, this->height() * 0.4);

    //实例化开始游戏的场景和选择的场景
    play = new PlayScene;
    chooseScene = new ChooseLevelScene;

    connect(startBtn, &MyPushButton::clicked, [=]() {
        startBtn->zoom1(); //向下跳跃
        startBtn->zoom2(); //向上跳跃
        QTimer::singleShot(200, this, [=]() {
            this->hide();
            play->show();
        });
    });

    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, [=]() {
        this->show();
    });

    connect(play, &PlayScene::playSceneBack, [=]() {
        this->show();
    });

    connect(quitBtn, &MyPushButton::clicked, [=]() {
        quitBtn->zoom1(); //向下跳跃
        quitBtn->zoom2(); //向上跳跃
        QTimer::singleShot(200, this, [=]() {
            this->close();
        });
    });

    connect(optionsBtn, &MyPushButton::clicked, [=]() {
        optionsBtn->zoom1(); //向下跳跃
        optionsBtn->zoom2(); //向上跳跃
        QTimer::singleShot(200, this, [=]() {
            qDebug() << "点到options按钮了";
        });
    });
}

void MainScene::paintEvent(QPaintEvent *)
{
    //创建画家，指定绘图设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/images/backdrops/backdrop16.jpg");
    //绘制背景图
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}

MainScene::~MainScene()
{
    delete ui;
}

