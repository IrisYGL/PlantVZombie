#include "zombie.h"
#include "mainpage.h"

Zombie::Zombie(const QString & path, const QPoint pos, QWidget * parent, zombieType type, mainpage * page)
    : QLabel(parent)
{
    m_page = page;
    m_path = path;
    m_type = type;
    movie = new QMovie(path);
    resize(QPixmap(path).size());
    setMovie(movie);
    movie->setParent(this);
    movie->start();
    move(pos);
    show();
    walkingTime = new QTimer(this);
    connect(walkingTime, SIGNAL(timeout()),this,SLOT(walking()));
    walkingTime->start(60);
    speed = 1;
    meetPlant = false;
    lifevalue = 120;
    m_dead = false;
    connect(this, SIGNAL(stepInHouse()), m_page->parentWidget(), SLOT(returnStartPage()));
}

Zombie::~Zombie()
{
}

OrdinaryZombie::OrdinaryZombie(const QPoint pos, QWidget * parent, mainpage * page)
    : Zombie(":/new/PlantsAndCombie/Images/Zombies/OrdinaryZombie/Zombie.gif", pos, parent, OrdinaryZombie0, page)
{
//lifevalue = 220;
}

OrdinaryZombie::~OrdinaryZombie()
{
}

BucketHeadZombie::BucketHeadZombie(const QPoint pos, QWidget * parent, mainpage * page)
    : Zombie(":/new/PlantsAndCombie/Images/Zombies/BucketheadZombie/BucketheadZombie.gif", pos, parent, BucketHeadZombie0, page)
{
    dropflag = 0;
}

BucketHeadZombie::~BucketHeadZombie()
{
}

ConeHeadZombie::ConeHeadZombie(const QPoint pos, QWidget * parent, mainpage * page)
    : Zombie(":/new/PlantsAndCombie/Images/Zombies/ConeheadZombie/ConeheadZombie.gif", pos, parent, ConeHeadZombie0, page)
{
    dropflag = 0;
}

ConeHeadZombie::~ConeHeadZombie()
{
}

FlagZombie::FlagZombie(const QPoint pos,  QWidget * parent, mainpage * page)
    : Zombie(":/new/PlantsAndCombie/Images/Zombies/FlagZombie/FlagZombie.gif", pos, parent, FlagZombie0, page)
{

}

FlagZombie::~FlagZombie()
{
}

PoleVaultingZombie::PoleVaultingZombie(const QPoint pos,  QWidget * parent, mainpage * page)
    : Zombie(":/new/PlantsAndCombie/Images/Zombies/PoleVaultingZombie/PoleVaultingZombie.gif", pos, parent, PoleVaultingZombie0, page)
{
flag = 0;
speed = 2;
}

PoleVaultingZombie::~PoleVaultingZombie()
{
}

void Zombie::startMove()
{
    meetPlant = 0;
    if(m_type == OrdinaryZombie0)
        m_path = ":/new/PlantsAndCombie/Images/Zombies/OrdinaryZombie/Zombie.gif";
    else if(m_type == BucketHeadZombie0 && dropflag == 0)
        m_path = ":/new/PlantsAndCombie/Images/Zombies/BucketheadZombie/BucketheadZombie.gif";
    else if(m_type == ConeHeadZombie0 && dropflag == 0)
        m_path = ":/new/PlantsAndCombie/Images/Zombies/ConeheadZombie/ConeheadZombie.gif";
    else if(m_type == BucketHeadZombie0 && dropflag == 1)
        m_path = ":/new/PlantsAndCombie/Images/Zombies/OrdinaryZombie/Zombie.gif";
    else if(m_type == ConeHeadZombie0 && dropflag == 1)
        m_path = ":/new/PlantsAndCombie/Images/Zombies/OrdinaryZombie/Zombie.gif";
    else if(m_type == FlagZombie0)
        m_path = ":/new/PlantsAndCombie/Images/Zombies/FlagZombie/FlagZombie.gif";
    else if(m_type == PoleVaultingZombie0)
        m_path = ":/new/PlantsAndCombie/Images/Zombies/PoleVaultingZombie/PoleVaultingZombieWalk.gif";
    else
        return;
    movie = new QMovie(m_path);
    resize(QPixmap(m_path).size());
    setMovie(movie);
    movie->setParent(this);
    movie->start();
}

void Zombie :: walking()
{
    reachHouse();

    if(!meetPlant)
    {
        move(x() - speed, y());
    }
    stop(m_page);
    //CherryBombDie();
}

void Zombie :: stop(mainpage * page)
{
    int step;
    if (m_type == PoleVaultingZombie0)
    {
        step = 220;
    }
    else if (m_type == ConeHeadZombie0)
    {
        step = 110;
    }
    else if (m_type == FlagZombie0)
    {
        step = 105;
    }
    else
    {
        step = 80;
    }
    int i = (x() - 130 + step) / 80;
    if (i < 0 || i > 8)
        return;
    if(page->grass[m_zombieRow][i] == 1)
    {
        if (!meetPlant)
             eatting();
       meetPlant = true;
       page->plantlist[m_zombieRow][i]->eatted(3);
    }
}

void Zombie :: eatting()
{
    if(m_type == OrdinaryZombie0)
        m_path = ":/new/PlantsAndCombie/Images/Zombies/OrdinaryZombie/ZombieAttack.gif";
    else if(m_type == BucketHeadZombie0 && dropflag == 0)
        m_path = ":/new/PlantsAndCombie/Images/Zombies/BucketheadZombie/BucketheadZombieAttack.gif";
    else if(m_type == ConeHeadZombie0 && dropflag == 0)
        m_path = ":/new/PlantsAndCombie/Images/Zombies/ConeheadZombie/ConeheadZombieAttack.gif";
    else if(m_type == BucketHeadZombie0 && dropflag == 1)
        m_path = ":/new/PlantsAndCombie/Images/Zombies/OrdinaryZombie/ZombieAttack.gif";
    else if(m_type == ConeHeadZombie0 && dropflag == 1)
        m_path = ":/new/PlantsAndCombie/Images/Zombies/OrdinaryZombie/ZombieAttack.gif";
    else if(m_type == FlagZombie0)
        m_path = ":/new/PlantsAndCombie/Images/Zombies/FlagZombie/FlagZombieAttack.gif";
    else if(m_type == PoleVaultingZombie0)
        m_path = ":/new/PlantsAndCombie/Images/Zombies/PoleVaultingZombie/PoleVaultingZombieAttack.gif";
    else
        return;
    movie = new QMovie(m_path);
    resize(QPixmap(m_path).size());
    setMovie(movie);
    movie->setParent(this);
    movie->start();
}

void PoleVaultingZombie::walking()
{
    if (flag)
    {
        Zombie::walking();
        return;
    }

    if (!meetPlant)
    {
        move(x() - speed, y());
         stop(m_page);
    }
    else if (flag == 0)
    {
        jump();
    }
    reachHouse();
}

void PoleVaultingZombie::jump()
{
    if (flag == 0)
    {
            m_path = ":/new/PlantsAndCombie/Images/Zombies/PoleVaultingZombie/PoleVaultingZombieJump1.gif";
            movie = new QMovie(m_path);
            resize(QPixmap(m_path).size());
            setMovie(movie);
            movie->setParent(this);
            movie->start();
            walkingTime->stop();
            QTimer::singleShot(1000, this, SLOT(jump()));
            flag = 1;
    }
    else if (flag == 1)
    {
        m_path = ":/new/PlantsAndCombie/Images/Zombies/PoleVaultingZombie/PoleVaultingZombieJump2.gif";
        movie = new QMovie(m_path);
        resize(QPixmap(m_path).size());
        setMovie(movie);
        movie->setParent(this);
        movie->start();
        flag = 2;
        move(x() - 140, y());
         QTimer::singleShot(1000, this, SLOT(jump()));
    }
    else
    {
        m_path = ":/new/PlantsAndCombie/Images/Zombies/PoleVaultingZombie/PoleVaultingZombieWalk.gif";
        movie = new QMovie(m_path);
        resize(QPixmap(m_path).size());
        setMovie(movie);
        movie->setParent(this);
        movie->start();
        walkingTime->start();
        meetPlant = 0;
    }
    speed = 1;
}

void ConeHeadZombie::walking()
{
    Zombie::walking();
    hatDroped();
}

void ConeHeadZombie::hatDroped()
{
    if(abs(lifevalue - 60) > 10)
        return;
    if(!meetPlant)
    {
         m_path = ":/new/PlantsAndCombie/Images/Zombies/OrdinaryZombie/Zombie.gif";
    }
    else
    {
        m_path = ":/new/PlantsAndCombie/Images/Zombies/OrdinaryZombie/ZombieAttack.gif";
    }
    movie = new QMovie(m_path);
    resize(QPixmap(m_path).size());
    setMovie(movie);
    movie->setParent(this);
    movie->start();
    dropflag = 1;
}

void BucketHeadZombie::walking()
{
    Zombie::walking();
    BucketDroped();
}

void BucketHeadZombie::BucketDroped()
{
    if(abs(lifevalue - 60) > 10)
        return;
    if(!meetPlant)
    {
         m_path = ":/new/PlantsAndCombie/Images/Zombies/OrdinaryZombie/Zombie.gif";
    }
    else
    {
         m_path = ":/new/PlantsAndCombie/Images/Zombies/OrdinaryZombie/ZombieAttack.gif";
    }
    movie = new QMovie(m_path);
    resize(QPixmap(m_path).size());
    setMovie(movie);
    movie->setParent(this);
    movie->start();
    dropflag = 1;
}

int Zombie::canbeBombeb(mainpage * page)
{
}

void Zombie::CherryBombDie()
{
        m_path = ":/new/PlantsAndCombie/Images/Zombies/Zombie_BoomDie.gif";
        movie = new QMovie(m_path);
        resize(QPixmap(m_path).size());
        setMovie(movie);
        movie->setParent(this);
        movie->start();
        walkingTime->stop();
        QTimer::singleShot(1000, this, SLOT(dead()));
        m_dead = true;
}

void Zombie::dead()
{
    if (!m_dead)
    {
        if (m_type == PoleVaultingZombie0)
            m_path = ":/new/PlantsAndCombie/Images/Zombies/PoleVaultingZombie/PoleVaultingZombieDie.gif";
        else
            m_path = ":/new/PlantsAndCombie/Images/Zombies/OrdinaryZombie/ZombieDie.gif";
        movie = new QMovie(m_path);
        resize(QPixmap(m_path).size());
        setMovie(movie);
        movie->setParent(this);
        movie->start();
        walkingTime->stop();
        QTimer::singleShot(1000, this, SLOT(dead()));
        m_dead = true;
    }
    else
    {
    QVector<Zombie *> & list = m_page->zombieList[m_zombieRow];
    for (int i = 0; i < list.size(); ++i)
    {
        if (list[i]->pos() == pos())
        {
            list.erase(list.begin() + i);
            delete this;
            return;
        }
    }
    }
}

void Zombie::reachHouse()
{

    if(m_type != PoleVaultingZombie0)
    {
        if(x()+width() <= 40)
        {
             m_selectPic = new QLabel(parentWidget());
        QPixmap pMap(":/Images/Surface/ZombiesWon.png");
        m_selectPic->resize(pMap.size());
        m_selectPic->setPixmap(pMap);
        m_selectPic->move((parentWidget()->width() - pMap.width()) / 2,
                          (parentWidget()->height() - pMap.height()) / 2);
        m_selectPic->show();
        QTimer::singleShot(2000, this, SIGNAL(stepInHouse()));
        delete walkingTime;
        }
    }
    else
    {
        if(x()+width()/2<= 40)
        {
             m_selectPic = new QLabel(parentWidget());
            QPixmap pMap(":/Images/Surface/ZombiesWon.png");
            m_selectPic->resize(pMap.size());
            m_selectPic->setPixmap(pMap);
            m_selectPic->move((parentWidget()->width() - pMap.width()) / 2,
                              (parentWidget()->height() - pMap.height()) / 2);
            m_selectPic->show();
            QTimer::singleShot(2000, this, SIGNAL(stepInHouse()));
            delete walkingTime;
        }
    }
}
