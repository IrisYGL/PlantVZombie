    #include "startpage.h"
    #include "ui_plantvzombie.h"
    #include "QPainter"
    #include "QSize"
    #include "QMessageBox"
    #include "QMouseEvent"
    #include "mainpage.h"
    #include <qlabel.h>
#include <qmediaplaylist.h>


    PlantVZombie::PlantVZombie(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::PlantVZombie)
    {
        ui->setupUi(this);
        int width = this->geometry().width();
        int height = this->geometry().height();
        this->setFixedSize(width,height);
        QPixmap pm;
        pm.load(":/Images/Surface/LoadBar.png");
        ui->label->setGeometry(450-pm.width()/2,560-pm.height(),pm.width(),pm.height());
        ui->label->setPixmap(pm);
        connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
        m_isStart = false;
        QMediaPlaylist * list = new QMediaPlaylist(this);
        list->addMedia(QUrl("qrc:/Images/plantsgarden.mp3"));
        list->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        player = new QMediaPlayer(this);
        player->setPlaylist(list);
        player->setVolume(100);
        player->play();

    }

    PlantVZombie::~PlantVZombie()
    {
        delete ui;
    }

    void PlantVZombie::paintEvent(QPaintEvent*)
    {
        if(m_isStart)
            return;
        QPainter painter(this);
        QPixmap pix;
        pix.load(":/Images/Surface/Surface.jpg");
        painter.drawPixmap(0,0,width(),height(),pix);
    }

    void PlantVZombie::mousePressEvent(QMouseEvent *e)
    {
        int x = e->x();
        int y = e->y();
        if (x>284 && x<616 && y>499 && y<600)
        {
            emit clicked();
        }
    }

    void PlantVZombie::slotClicked()
    {
        time = new QTimer(this);
        connect(time,SIGNAL(timeout()),this,SLOT(moveUpdate()));
        QPixmap pm;
        pm.load(":/Images/Surface/backgroundlong.png");
        m_background = new QLabel(this);
        m_background->setPixmap(pm);
        m_background->move(0, 0);
        m_background->resize(pm.size());
        m_background->show();
        time->start(30);
    }

    void PlantVZombie::moveUpdate()
    {
        static int i = -10;
        if (m_background->x() <= -500)
        {
            if (time->interval() == 30)
            {
                time->setInterval(1000);
                i = -i;
                return;
            }
            else if (time->interval() != 30)
            {
                time->setInterval(30);
                m_background->move(m_background->x() + i, m_background->y());
                return;
            }
        }
        else if (m_background->x() == -130 && i > 0)
        {
            if (time->interval() == 30)
            {
             time->setInterval(1000);
             return;
            }
            else
            {
            delete time;
            time = nullptr;
            w = new mainpage(this);
            w->resize(size());
            w->move(0, 0);
               w->show();
               m_isStart = true;
            i = -i;
            return;
            }
        }
        m_background->move(m_background->x() + i, m_background->y());
    }

    void PlantVZombie::returnStartPage()
    {
        delete w;
        w = nullptr;
        m_isStart = false;
        delete m_background;
    }
