#ifndef ZOMBIE_H
#define ZOMBIE_H
#include<QTimer>
#include<QLabel>
#include <QMovie>

class mainpage;

enum zombieType {OrdinaryZombie0, BucketHeadZombie0, ConeHeadZombie0,  FlagZombie0, PoleVaultingZombie0};

class Zombie:public QLabel
{
    Q_OBJECT

public:
    Zombie(const QString & path, const QPoint pos, QWidget * parent, zombieType type, mainpage * page);
    virtual ~Zombie();

public slots:
    void stop(mainpage * page);
    void eatting();
    virtual void walking();
    void startMove();
    void CherryBombDie();
    int canbeBombeb(mainpage * page);
    void dead();
    void reachHouse();

signals:
    void stepInHouse();

public:
    QMovie * movie;
    int m_zombieRow;
    QTimer * walkingTime;
    int lifevalue;
    bool meetPlant;
    zombieType m_type;
    QString  m_path;
    mainpage * m_page;
    int speed;
    int dropflag;
    bool m_dead;
private:
    QLabel * m_selectPic;
};


class OrdinaryZombie : public Zombie
{
    Q_OBJECT

public:
    OrdinaryZombie(const QPoint pos, QWidget * parent, mainpage * page);
    virtual ~OrdinaryZombie();

public:
    int zombieLifevalue;
};


class BucketHeadZombie : public Zombie
{
    Q_OBJECT

public:
    BucketHeadZombie(const QPoint pos,  QWidget * parent, mainpage * page);
    virtual ~BucketHeadZombie();

public:
    int zombieLifevalue = 800;
    void BucketDroped();
    virtual void walking();
};


class ConeHeadZombie : public Zombie
{
    Q_OBJECT

public:
    ConeHeadZombie(const QPoint pos, QWidget * parent, mainpage * page);
    virtual ~ConeHeadZombie();

public:
    int zombieLifevalue = 600;
    virtual void walking();
    void hatDroped();
};


class FlagZombie : public Zombie
{
    Q_OBJECT

public:
    FlagZombie(const QPoint pos,  QWidget * parent, mainpage * page);
    virtual ~FlagZombie();

public:
    int zombieLifevalue = 400;

};


class PoleVaultingZombie : public Zombie
{
    Q_OBJECT

public:
    PoleVaultingZombie(const QPoint pos, QWidget * parent, mainpage * page);
    virtual ~PoleVaultingZombie();

public slots:
     virtual void walking();
    void jump();

public:
    int zombieLifevalue = 400;

    int flag;
};

#endif // ZOMBIE_H
