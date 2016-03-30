#include "armrule.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ArmRule w;
    w.show();

    return a.exec();
}
