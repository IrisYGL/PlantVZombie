#include "sun.h"
#include "plant.h"
#include<QMovie>
#include<qmath.h>
#include<QTimer>

sun::sun(QWidget * parent, const QPoint & pos, bool sunflower)
    : QWidget(parent), m_sunflower(sunflower)
{
    m_pic = new QLabel(this);
    QMovie * pMovie = new QMovie(":/new/PlantsAndCombie/Images/Sun/Sun.gif");
    pMovie->setParent(this);
    m_pic->setMovie(pMovie);
    m_pic->resize(QPixmap(":/new/PlantsAndCombie/Images/Sun/Sun.gif").size());
    resize(m_pic->size());
    pMovie->start();
    move(pos);
    show();
    timer = new QTimer(this);
    if (!sunflower)
    {
        srand((unsigned)time(NULL));
        placeSetdown = rand() % 500 + 60;
        connect(timer, SIGNAL(timeout()), this, SLOT(mb_moveUpdate()));
    }
    else
    {

    }
    timer->start(30);
}

sun::~sun()
{
}

void sun::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
    {
        delete timer;
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(mb_collect()));
        timer->start(30);
    }
}

void sun::mb_collect()
{
    if (x() == 210 && y() == 0)
    {
        timer->stop();
        emit sunAdd(25);
        delete this;
        return;
    }
   move(210 + (x() - 210) * 9/10, y() * 9/10);
}

void sun::mb_moveUpdate()
{
    if (y() > placeSetdown)
    {
        delete timer;
        timer = nullptr;
        return;
    }
    move(x(), y() + 3);
}
