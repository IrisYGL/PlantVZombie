#ifndef PLANT_H
#define PLANT_H
#include "card.h"
#include "sun.h"
#include "bullet.h"
#include <QMovie>

class mainpage;

class Plant : public QLabel
{
    Q_OBJECT
public:
    Plant(QWidget *parent, int x, int y, QString path, mainpage * page);
    virtual ~Plant();

public slots:
    void eatted(int attackvalue);
    void bombAttak();


signals:
    void beEaten();

public:
    QString m_path;
    int attack;
    int lifevalue;
    int row;
    int line;
    QMovie * movie;
    mainpage * m_page;
};

class Sunflowers : public Plant
{
    Q_OBJECT
public:
    Sunflowers(QWidget *parent, int x, int y, mainpage * page);
    virtual ~Sunflowers();
public slots:
    void emitSun();
    void collected();
public:
    bool collectFlag;

};

class CherryBombs : public Plant
{
    Q_OBJECT
public:
    CherryBombs(QWidget *parent, int x, int y, mainpage * page);
    virtual ~CherryBombs();
public slots:
    void plantdead();

};

class PeaShooters : public Plant
{
     Q_OBJECT
public:
    PeaShooters(QWidget *parent, int x, int y, mainpage * page);
    virtual ~PeaShooters();

public slots:
    void emitBullet();
};

class Wallnuts : public Plant
{
    Q_OBJECT
public:
    Wallnuts(QWidget *parent, int x, int y, mainpage * page);
    virtual ~Wallnuts();
public slots:
    void cracked();
};

class Shovels : public Plant
{
    Q_OBJECT
public:
    Shovels(QWidget *parent, int x, int y);
    virtual ~Shovels();
};

#endif // PLANT_H
