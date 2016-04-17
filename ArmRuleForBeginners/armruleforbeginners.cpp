#include "armruleforbeginners.h"
#include "ui_armruleforbeginners.h"



ArmRuleForBeginners::ArmRuleForBeginners(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArmRuleForBeginners)
{
    arm  = ArmRuleLib();
    ui->setupUi(this);
}

ArmRuleForBeginners::~ArmRuleForBeginners()
{
    delete ui;
}

void ArmRuleForBeginners::on_btnMover_clicked()
{
    double x = ui->edtX->text().toDouble();
    double y = ui->edtY->text().toDouble();
    double z = ui->edtZ->text().toDouble();
    double phi = ui->edtPhi->text().toDouble();

    arm.move(x, y, z, phi);
}

void ArmRuleForBeginners::on_btnPegar_clicked()
{
    arm.pegar();
}

void ArmRuleForBeginners::on_btnSoltar_clicked()
{
    arm.soltar();
}

void ArmRuleForBeginners::on_btnRespouso_clicked()
{
    arm.repouso();
}
