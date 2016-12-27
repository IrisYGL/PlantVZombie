#include "plant.h"
#include "bullet.h"
#include "sun.h"
#include "card.h"
#include "mainpage.h"
#include "zombie.h"
#include <QTimer>

Plant::Plant(QWidget *parent,int x, int y, QString path, mainpage * page)
    : QLabel(parent)
{
   m_path = path;
   m_page = page;
   movie = new QMovie(path);
   resize(QPixmap(path).size());
   setMovie(movie);
   movie->setParent(this);
   movie->start();
   move(x, y);
   show();
   lifevalue = 200;
}

Plant::~Plant()
{
}

Sunflowers::Sunflowers(QWidget *parent, int x, int y, mainpage * page)
    :Plant(parent, x, y, ":/new/PlantsAndCombie/Images/Plants/SunFlower/SunFlower.gif", page)
{
  QTimer * emitSun1 = new QTimer(this);
  connect(emitSun1, SIGNAL(timeout()), this, SLOT(emitSun()));
  emitSun1->start(10000);
  collectFlag = 1;
}

Sunflowers::~Sunflowers()
{

}

Wallnuts::Wallnuts(QWidget *parent, int x, int y, mainpage * page)
    :Plant(parent, x, y,":/new/PlantsAndCombie/Images/Plants/WallNut/WallNut.gif", page)
{
    lifevalue = 500;
    connect(this, SIGNAL(beEaten()), this, SLOT(cracked()));
}

Wallnuts::~Wallnuts()
{

}

PeaShooters::PeaShooters(QWidget *parent, int x, int y, mainpage * page)
    :Plant(parent, x, y, ":/new/PlantsAndCombie/Images/Plants/Peashooter/Peashooter.gif", page)
{
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(emitBullet()));
    timer->start(1400);
}

PeaShooters::~PeaShooters()
{

}

CherryBombs::CherryBombs(QWidget *parent, int x, int y, mainpage * page)
 :Plant(parent, x, y, ":/Images/Card/CherryBomb_card.gif", page)
{
    delete movie;
    QPixmap m(":/Images/Card/CherryBomb_card.gif");
    m = m.scaled(m.size() *3/4);
    resize(m.size());
    setPixmap(m);
    QTimer::singleShot(1000, this, SLOT(bombAttak()));
}

CherryBombs::~CherryBombs()
{

}

Shovels::Shovels(QWidget *parent, int x, int y)
    :Plant(parent, x, y, ":/Images/Card/Shovel.png", nullptr)
{
}

Shovels::~Shovels()
{

}

void Sunflowers::emitSun()
{
    if(collectFlag == 1)
    {
        sun * m_sun2 = new sun(parentWidget(), pos() - QPoint(12, -18), true);
         connect(m_sun2,SIGNAL(sunAdd(int)), this, SLOT(collected()));
        collectFlag = 0;
        connect(m_sun2, SIGNAL(sunAdd(int)), parentWidget(), SLOT(sunvalueShow(int)));
    }
}

void Sunflowers::collected()
{
    collectFlag = 1;
}

void PeaShooters::emitBullet()
{
    QVector<Zombie *> list = m_page->zombieList[(y() - 80) / 100];
    for (const auto & i : list)
    {
        if (i->x() + i->width() > x() + width())
        {
            Bullet * bullet = new Bullet(parentWidget(), pos() + QPoint(30, 3), m_page);
            return;
        }

    }

}

void Wallnuts::cracked()
{
    if(abs(lifevalue - 400) < 3)
    {
        m_path = ":/new/PlantsAndCombie/Images/Plants/WallNut/Wallnut_cracked1.gif";
    }
    else if(abs(lifevalue - 200) < 3)
    {
        m_path = ":/new/PlantsAndCombie/Images/Plants/WallNut/Wallnut_cracked2.gif";
    }
    else
        return;
    delete movie;
    movie = new QMovie(m_path);
    resize(QPixmap(m_path).size());
    setMovie(movie);
    movie->setParent(this);
    movie->start();
}

void Plant::eatted(int attackvalue)
{
    lifevalue -= attackvalue;
    emit beEaten();
    if (lifevalue <= 0)
    {
        m_page->plantlist[(y() - 80) / 100][(x() - 130) / 80] = nullptr;
        m_page->grass[(y() - 80) / 100][(x() - 130) / 80] = 0;
        for (const auto & j : m_page->zombieList[(y() - 80) / 100])
        {
            int step;
            if (j->m_type == PoleVaultingZombie0)
            {
                step = 220;
            }
            else if (j->m_type == ConeHeadZombie0)
            {
                step = 110;
            }
            else if (j->m_type == FlagZombie0)
            {
                step = 105;
            }
            else
            {
                step = 80;
            }
            int i = (j->x() - 130 + step) / 80;
            if (i < 0 || i > 8)
                continue;
            if (i == (x() - 130) / 80)
            {
                j->startMove();
            }
        }
        delete this;
        return;
    }
}

void Plant::bombAttak()
{
    movie = new QMovie(":/new/PlantsAndCombie/Images/Plants/CherryBomb/CherryBomb.gif");
    resize(QPixmap(":/new/PlantsAndCombie/Images/Plants/CherryBomb/CherryBomb.gif").size());
    setMovie(movie);
    movie->setParent(this);
    movie->start();
    show();
    QTimer::singleShot(700, this, SLOT(plantdead()));
}

void CherryBombs::plantdead()
{
    int row = (y() - 80) / 100;
    int col = (x() - 130) / 80;

    int min = row - 1;
    if (min < 0)
        min = 0;
    int max = row + 1;
    if (max > 4)
        max = 4;
    for (int i = min; i <= max; ++i)
    {
        QVector<Zombie *> & list = m_page->zombieList[i];
        for (int j = 0; j < list.size(); ++j)
        {
            int step;
            if (list[j]->m_type == PoleVaultingZombie0)
            {
                step = 190;
            }
            else if (list[j]->m_type == ConeHeadZombie0)
            {
                step = 110;
            }
            else if (list[j]->m_type == FlagZombie0)
            {
                step = 105;
            }
            else
            {
                step = 80;
            }
            int c = (list[j]->x() - 130 + step) / 80;
            if (abs(col - c) <= 1)
            {
                list[j]->CherryBombDie();
            }
        }
    }

    m_page->plantlist[(y() - 80) / 100][(x() - 130) / 80] = nullptr;
    m_page->grass[(y() - 80) / 100][(x() - 130) / 80] = 0;
    delete this;
}
