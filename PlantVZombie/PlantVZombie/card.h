#ifndef CARD_H
#define CARD_H
#include <QLabel>
#include <qevent.h>

enum plantType {PeaShooter, Sunflower, Wallnut,  CherryBomb, Shovel};
class Card : public QLabel
{
    Q_OBJECT

public:
    Card(const plantType type, const QString & path, QWidget *parent, int m_value);
    virtual ~Card();

public:
    int price (plantType m_type);

public:
    virtual void mousePressEvent(QMouseEvent *event);

signals:
    void clicked(Card *);

public slots:
    void getSunvalue(int sunvalue);
    void becooled();
    void coverSize();

private:
    QLabel * m_plant;
    QLabel * m_sunCost;
    QTimer * m_timer;
    QLabel * useCheckCover;
    QLabel * coolingCover;

public:
    plantType m_type;
    int coolingTime;
    int currentCoolingTime;
    bool select;
};


#endif // CARD_H
