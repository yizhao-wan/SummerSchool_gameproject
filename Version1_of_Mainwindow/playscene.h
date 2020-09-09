#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

signals:
    void playSceneBack();
};

#endif // PLAYSCENE_H
