#include "card.h"
#include "sun.h"
#include <QTimer>

Card::Card(const plantType type,  const QString & path,  QWidget *parent, int m_sunvalue)
    : QLabel(parent), m_type(type)
{
    if(type == Shovel)
    {
        QPixmap pMap;
        pMap.load(":/Images/Card/Shovel0.png");
        setPixmap(pMap);
        resize(pMap.size());
        show();
        m_timer = nullptr;
    }
    else
    {
    QPixmap pMap;
    pMap.load(":/Images/Card/CardBackground_Smaller.png");
    setPixmap(pMap);
    resize(pMap.size());

    pMap.load(path);
    QLabel * m_plant = new QLabel(this);
    QSize pMapSize(pMap.width() * 36 / pMap.height(), 36);
    m_plant->setPixmap(pMap.scaled(pMapSize));
    m_plant->resize(pMapSize);
    m_plant->move((width() - pMapSize.width()) / 2, 12);

    QString s;
    s.sprintf("<font size = 2>%d", price(type));
    QLabel * m_sunCost = new QLabel(s, this);
    m_sunCost->setGeometry(0, 53, 40, 17);
    m_sunCost->setAlignment(Qt::AlignCenter);
    show();
    m_timer = nullptr;
    }
    select = true;
    useCheckCover = new QLabel(this);
    useCheckCover->resize(size());
    getSunvalue(m_sunvalue);

    coolingTime = 50;
}

Card::~Card()
{
}


void Card::mousePressEvent(QMouseEvent * event)
{
    if (event->button() != Qt::LeftButton)
        return;
    if (!select)
        return;
    emit clicked(this);
}

int Card::price(plantType m_type)
{
    if(m_type == Sunflower)
        return 50;
    if(m_type == PeaShooter)
        return 100;
    if(m_type == CherryBomb)
        return 150;
    if(m_type == Wallnut)
        return 50;
    if(m_type == Shovel)
        return 0;
}

 void Card::getSunvalue(int sunvalue)
 {
     if(m_type == PeaShooter)
      {
         if(sunvalue < 100)
            useCheckCover->setStyleSheet("background-color:rgba(0,0,0,0.5)");
         else
            useCheckCover->setStyleSheet("background-color:rgba(0,0,0,0)");
       }
     if(m_type == Sunflower )
      {
         if(sunvalue < 50)
            useCheckCover->setStyleSheet("background-color:rgba(0,0,0,0.5)");
         else
            useCheckCover->setStyleSheet("background-color:rgba(0,0,0,0)");
       }
     if(m_type == CherryBomb )
      {
         if(sunvalue < 150)
            useCheckCover->setStyleSheet("background-color:rgba(0,0,0,0.5)");
         else
            useCheckCover->setStyleSheet("background-color:rgba(0,0,0,0)");
       }
     if(m_type == Wallnut)
      {
         if(sunvalue < 50)
            useCheckCover->setStyleSheet("background-color:rgba(0,0,0,0.5)");
         else
            useCheckCover->setStyleSheet("background-color:rgba(0,0,0,0)");
       }
 }

 void Card::becooled()
 {
     QTimer * unusefulTime = new QTimer(this);
     unusefulTime->start(100);
     connect(unusefulTime, SIGNAL(timeout()), this, SLOT(coverSize()));
     coolingCover = new QLabel(this);
     coolingCover->setStyleSheet("background-color:rgba(0,0,0,0.7)");
     coolingCover->resize(size());
     coolingCover->show();
     select = false;
     currentCoolingTime = 0;
 }

 void Card::coverSize()
 {
     if (coolingCover->height() <= 0)
     {
         select = true;
         return;
     }
     ++currentCoolingTime;
     coolingCover->resize(width(), height() * (coolingTime - currentCoolingTime) / coolingTime);
 }
