#include "mainpage.h"
#include "QPainter"
#include "card.h"
#include "sun.h"
#include "plant.h"
#include "zombie.h"

mainpage::mainpage(QWidget *parent) :
    QWidget(parent)
{
    connect(this, SIGNAL(win()), parent, SLOT(returnStartPage()));
    m_selectPic = nullptr;
    m_card = nullptr;
    sunvalue = 300;
    Card * card1 = new Card(plantType::PeaShooter, ":/Images/Card/Peashooter_card.gif", this, sunvalue);
    connect(this,SIGNAL(sunvalueChanged(int)),card1,SLOT(getSunvalue(int)));
    connect(card1, SIGNAL(clicked(Card *)), this, SLOT(mb_selectPlant(Card *)));
    card1->move(322, 7);
    Card * card2 = new Card(plantType::Sunflower, ":/Images/Card/Sunflowers_card.gif", this, sunvalue);
     connect(this,SIGNAL(sunvalueChanged(int)),card2,SLOT(getSunvalue(int)));
    connect(card2, SIGNAL(clicked(Card *)), this, SLOT(mb_selectPlant(Card *)));
    card2->move(380, 7);
    Card * card3 = new Card(plantType::Wallnut, ":/Images/Card/WallNut_card.gif", this, sunvalue);
     connect(this,SIGNAL(sunvalueChanged(int)),card3,SLOT(getSunvalue(int)));
    connect(card3, SIGNAL(clicked(Card *)), this, SLOT(mb_selectPlant(Card *)));
    card3->move(438, 7);
    Card * card4 = new Card(plantType::CherryBomb, ":/Images/Card/CherryBomb_card.gif", this, sunvalue);
     connect(this,SIGNAL(sunvalueChanged(int)),card4,SLOT(getSunvalue(int)));
    connect(card4, SIGNAL(clicked(Card *)), this, SLOT(mb_selectPlant(Card *)));
    card4->move(496, 7);
    Card * card5 = new Card(plantType::Shovel, ":/Images/Card/Shovel.png", this, sunvalue);
    connect(card5, SIGNAL(clicked(Card *)), this, SLOT(mb_selectPlant(Card *)));
    card5->move(612, 22);

    QTimer * timeSunflow = new QTimer(this);
    srand((unsigned)time(NULL));
    connect(timeSunflow, SIGNAL(timeout()), this, SLOT(sunFlow()));
    timeSunflow->start(5000);
    m_sunvalueLabel = new QLabel(QString::number(sunvalue), this);
    m_sunvalueLabel->setGeometry(232, 60, 40, 17);
    m_sunvalueLabel->setAlignment(Qt::AlignCenter);
    m_sunvalueLabel->show();

   TimeZombieAccur = new QTimer(this);
    srand((unsigned)time(NULL));
    connect(TimeZombieAccur, SIGNAL(timeout()), this, SLOT(ZombieAccur()));
    TimeZombieAccur->start(10000);

    zombieNum = 0;
}

mainpage::~mainpage()
{
}

void mainpage::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Images/Surface/backgroud.png");
    painter.drawPixmap(0,0,width(),height(),pix);
    pix.load(":/Images/Card/ShovelBack.png");
    painter.drawPixmap(600,0,100,80,pix);
    pix.load(":/Images/Card/Cardbox.jpg");
    painter.drawPixmap(220,2,380,80,pix);
    pix.load(":/Images/Card/Add.jpg");
    painter.drawPixmap(220,0,380,2,pix);
}

void mainpage::mb_selectPlant(Card * card)
{
    m_selectPic = new QLabel(this);
    if (card->m_type == plantType::PeaShooter)
    {
        if(sunvalue >= 100)
        {
        m_card = card;
        QPixmap pMap(":/Images/Card/Peashooter_card.gif");
        m_selectPic->resize(pMap.size());
        m_selectPic->setPixmap(pMap);
        m_selectPic->show();
        m_selectPic->move(322, 12);
        }
    }
    if (card->m_type == plantType::Sunflower)
    {
        if(sunvalue >= 50)
        {
            m_card = card;
        QPixmap pMap(":/Images/Card/Sunflowers_card.gif");
        m_selectPic->resize(pMap.size());
        m_selectPic->setPixmap(pMap);
        m_selectPic->show();
        m_selectPic->move(380, 12);
        }
    }
    if (card->m_type == plantType::Wallnut)
    {
        if(sunvalue >= 50)
        {
            m_card = card;
        QPixmap pMap(":/Images/Card/WallNut_card.gif");
        m_selectPic->resize(pMap.size());
        m_selectPic->setPixmap(pMap);
        m_selectPic->show();
        m_selectPic->move(438, 12);
        }
    }
    if (card->m_type == plantType::CherryBomb)
    {
        if(sunvalue >= 150)
        {
            m_card = card;
        QPixmap pMap(":/Images/Card/CherryBomb_card.gif");
        m_selectPic->resize(pMap.size()*4/5);
        m_selectPic->setPixmap(pMap.scaled(pMap.size() * 4/5));
        m_selectPic->show();
        m_selectPic->move(486, 8);
        }
    }
    if (card->m_type == plantType::Shovel)
    {
        m_card = card;
        QPixmap pMap(":/Images/Card/Shovel.png");
        m_selectPic->resize(pMap.size());
        m_selectPic->setPixmap(pMap);
        m_selectPic->show();
        m_selectPic->move(630, 12);
    }
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(mb_update()));
    m_timer->start(30);
}

void mainpage::mb_update()
{
    QPoint p = mapFromGlobal(cursor().pos());
    if (m_selectPic != nullptr)
    {
     m_selectPic->move(p.x() - m_selectPic->width()/2, p.y() - m_selectPic->height() / 2);
    }
}

void mainpage::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
     putPlant(event->pos());
    }
    else if (event->button() == Qt::RightButton)
    {
      m_card = nullptr;
    }
}

void mainpage::putPlant(QPoint pos)
{
   if (m_card != nullptr)
   {
    int x = (pos.x()-130)/80*80+130;
    int y = (pos.y()-80)/100*100+80;
    if (m_card->m_type == Shovel && grass[(pos.y()-80)/100][(pos.x()-130)/80] == 1)
    {
        delete plantlist[(pos.y()-80)/100][(pos.x()-130)/80];
        delete m_selectPic;
        m_selectPic = nullptr;
        m_card = nullptr;
        grass[(pos.y()-80)/100][(pos.x()-130)/80] = 0;
        return;
    }
    if (grass[(pos.y()-80)/100][(pos.x()-130)/80] == 1)
        return;
    Plant * unit;
    if (m_card->m_type == PeaShooter && grass[(pos.y()-80)/100][(pos.x()-130)/80] == 0)
    {
        unit = new PeaShooters(this, x, y, this);
        grass[(pos.y()-80)/100][(pos.x()-130)/80] = 1;
        plantlist[(pos.y()-80)/100][(pos.x()-130)/76] = unit;
        sunvalueShow(-100);
        m_card->becooled();
    }
    if (m_card->m_type == Wallnut && grass[(pos.y()-80)/100][(pos.x()-130)/80] == 0)
    {
        unit = new Wallnuts(this, x, y, this);
        grass[(pos.y()-80)/100][(pos.x()-130)/80] = 1;
        plantlist[(pos.y()-80)/100][(pos.x()-130)/80] = unit;
        sunvalueShow(-50);
        m_card->becooled();
    }
    if (m_card->m_type == CherryBomb && grass[(pos.y()-80)/100][(pos.x()-130)/80] == 0)
    {
        unit = new CherryBombs(this, x, y, this);
        grass[(pos.y()-80)/100][(pos.x()-130)/80] = 1;
        //isCherryBomb[(pos.y()-80)/100][(pos.x()-130)/80] = 1;
        plantlist[(pos.y()-80)/100][(pos.x()-130)/80] = unit;
        sunvalueShow(-150);
        m_card->becooled();
    }
    if (m_card->m_type == Sunflower && grass[(pos.y()-80)/100][(pos.x()-130)/80] == 0)
    {
        unit = new Sunflowers(this, x, y, this);
        grass[(pos.y()-80)/100][(pos.x()-130)/80] = 1;
        plantlist[(pos.y()-80)/100][(pos.x()-130)/80] = unit;
        sunvalueShow(-50);
        m_card->becooled();
    }
    if (m_card->m_type == Shovel && grass[(pos.y()-80)/100][(pos.x()-130)/80] == 0)
    {
        return;
    }
    }
    delete m_selectPic;
    m_selectPic = nullptr;
    m_card = nullptr;
}

void mainpage::sunvalueShow(int value)
{
    sunvalue += value;
    m_sunvalueLabel->setText(QString::number(sunvalue));
    emit sunvalueChanged(sunvalue);
}

void mainpage::sunFlow()
{
    placeSunshow = rand() % 800 + 60;
    sun * m_sun1 = new sun(this, QPoint(placeSunshow, -50), false);
    connect(m_sun1, SIGNAL(sunAdd(int)), this, SLOT(sunvalueShow(int)));
}

void mainpage::ZombieAccur()
{
    rowZombieShow = rand() % 5;
    zombieTypeNum = rand() % 5;
    ++zombieNum;
    if (zombieNum > 20)
    {
        for (int i = 0; i < 5; ++i)
        {
         if (!zombieList[i].empty())
             return;
        }
       delete TimeZombieAccur;
       QLabel * pic = new QLabel(this);
       QPixmap pMap(":/Images/Surface/trophy.png");
       pic->resize(pMap.size());
       pic->setPixmap(pMap);
       pic->move((parentWidget()->width() - pMap.width()) / 2,
                         (parentWidget()->height() - pMap.height()) / 2);
       pic->show();
       QTimer::singleShot(2000, this, SIGNAL(win()));
        return;
    }
    Zombie * zombie;
    if(zombieTypeNum == 0)
    {
        zombie = new OrdinaryZombie(QPoint(900, rowZombieShow*100+16), this, this);
        zombie->m_zombieRow = rowZombieShow;
    }
    if(zombieTypeNum == 1)
    {
        zombie = new BucketHeadZombie(QPoint(900, rowZombieShow*100+16), this, this);
        zombie->m_zombieRow = rowZombieShow;
    }
    if(zombieTypeNum == 2)
    {
        zombie = new ConeHeadZombie(QPoint(900, rowZombieShow*100+16), this, this);
        zombie->m_zombieRow = rowZombieShow;
    }
    if(zombieTypeNum == 3)
    {
        zombie = new FlagZombie(QPoint(900, rowZombieShow*100+16), this, this);
        zombie->m_zombieRow = rowZombieShow;
    }
    if(zombieTypeNum == 4)
    {
        zombie = new PoleVaultingZombie(QPoint(900, rowZombieShow*100-38), this, this);
        zombie->m_zombieRow = rowZombieShow;
    }
    zombieList[rowZombieShow].push_back(zombie);
}

