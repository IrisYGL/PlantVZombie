#include "startpage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlantVZombie w;
    w.show();

    return a.exec();
}
