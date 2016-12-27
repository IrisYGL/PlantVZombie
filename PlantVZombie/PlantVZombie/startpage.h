#ifndef PLANTVZOMBIE_H
#define PLANTVZOMBIE_H

#include <QMainWindow>
#include "mainpage.h"
#include <QMediaPlayer>

namespace Ui {
class PlantVZombie;
}

class PlantVZombie : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlantVZombie(QWidget *parent = 0);
    ~PlantVZombie();
    int flag;

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *e);

private slots:
    void slotClicked();
    void moveUpdate();
    void returnStartPage();

signals:
    void clicked();

private:
    Ui::PlantVZombie *ui;
    mainpage * w;
    QTimer * time;
    QLabel * m_background;
    bool m_isStart;
    QMediaPlayer * player;
};

#endif // PLANTVZOMBIE_H
