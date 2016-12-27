#include "bullet.h"
#include "zombie.h"
#include "mainpage.h"

Bullet::Bullet(QWidget * parent, QPoint place, mainpage * page):QLabel(parent),m_page(page)
{
    QPixmap pMap;
    pMap.load(":/new/PlantsAndCombie/Images/Plants/Peashooter/Peashooter_bullet.gif");
    setPixmap(pMap);
    resize(pMap.size());
    show();
    move(place);
    shotTimer = new QTimer(this);
    connect(shotTimer, SIGNAL(timeout()), this, SLOT(bulletPlaceUpdate()));
    shotTimer->start(30);
}

void Bullet::bulletPlaceUpdate()
{
    int r = (y() - 80) / 100;
    QVector<Zombie *> & list = m_page->zombieList[r];
    for (int i = 0; i < list.size(); ++i)
    {
        int step = 0;
        if (abs(x() - (list[i]->x() + step)) < 11)
        {
             list[i]->lifevalue -= 16;
             if (list[i]->lifevalue <= 0)
             {
                list[i]->dead();
             }
             deleteThis();
             return;
        }
    }
    if(x() >= 900)
    {
        deleteThis();
        return;
    }
    move(x()+8,y());
}

Bullet::~Bullet()
{

}

void Bullet::deleteThis()
{
    shotTimer->stop();
    delete this;
}
