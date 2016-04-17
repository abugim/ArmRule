#ifndef ARMRULEFORBEGINNERS_H
#define ARMRULEFORBEGINNERS_H

#include <QMainWindow>
#include"include/armrulelib.h"
#include "include/armrulelib_global.h"
#define L1 7.3
#define L2 14.8
#define L3 18.5
#define L4 8.7

namespace Ui {
class ArmRuleForBeginners;
}

class ArmRuleForBeginners : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArmRuleForBeginners(QWidget *parent = 0);
    ArmRuleLib arm;
    ~ArmRuleForBeginners();

private slots:
    void on_btnMover_clicked();

    void on_btnPegar_clicked();

    void on_btnSoltar_clicked();

    void on_btnRespouso_clicked();

private:
    Ui::ArmRuleForBeginners *ui;
};

#endif // ARMRULEFORBEGINNERS_H
