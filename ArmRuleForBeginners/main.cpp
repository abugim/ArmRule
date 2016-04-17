#include "armruleforbeginners.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ArmRuleForBeginners w;
    w.show();

    return a.exec();
}
