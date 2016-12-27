#ifndef SUN_H
#define SUN_H
#include<QMouseEvent>
#include<QLabel>

class sun : public QWidget
{
    Q_OBJECT

public:
    sun(QWidget * parent, const QPoint &, bool sunflower = true);
    virtual ~sun();

public:
    void mousePressEvent(QMouseEvent *event);

public slots:
    void mb_collect();
    void mb_moveUpdate();

signals:
   void sunAdd(int);

private:
    QLabel * m_pic;
    QTimer * timer;
    int placeSetdown;

public:
    const bool m_sunflower;
};

#endif // SUN_H
