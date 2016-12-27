#ifndef BULLET_H
#define BULLET_H
#include <QLabel>
#include <QTimer>

class mainpage;

class Bullet : public QLabel
{
    Q_OBJECT
public:
    Bullet(QWidget * parent, QPoint, mainpage * page);
    virtual ~Bullet();

public slots:
    void bulletPlaceUpdate();

public:
    void deleteThis();

public:
    QTimer * shotTimer;
    mainpage * m_page;
};

#endif // BULLET_H
