#ifndef MAINPAGE_H
#define MAINPAGE_H
#include "card.h"
#include "plant.h"
#include "qtimer.h"
#include <qvector.h>
#include "zombie.h"
class mainpage : public QWidget
{
    Q_OBJECT

public:
    explicit mainpage(QWidget *parent = 0);
    ~mainpage();

public:
    int grass[5][9] = {0};
    int isCherryBomb[5][9] = {0};
    Plant* plantlist[5][9];
    QVector<Zombie *> zombieList[5];
    int placeSunshow;
    int rowZombieShow;
    int zombieTypeNum;

public slots:
    void mb_selectPlant(Card*);
    void mb_update();
    void putPlant(QPoint);
    void sunvalueShow(int);
    void sunFlow();
    void ZombieAccur();

signals:
    void sunvalueChanged(int sunvalue);
    void win();

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);

private:
    QLabel * m_selectPic;
    QTimer * m_timer;
    Card * m_card;
    int sunvalue;
    QLabel * m_sunvalueLabel;
    int zombieNum;
     QTimer * TimeZombieAccur ;
};

#endif // MAINPAGE_H
