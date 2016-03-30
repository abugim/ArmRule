#include "armrule.h"
#include "ui_armrule.h"

#include <QString>
#include <QListWidgetItem>

ArmRule::ArmRule(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArmRule)
{
    ui->setupUi(this);
    tetaBase = 0;
    tetaOmbro = 0;
    tetaCotovelo = 0;
    tetaPunho = 0;
    aberturaGarra = 0;

    ui->editBase->setText(QString::number(ui->dialBase->value()));
    ui->editOmbro->setText(QString::number(ui->dialOmbro->value()));
    ui->editCotovelo->setText(QString::number(ui->dialCotovelo->value()));
    ui->editPunho->setText(QString::number(ui->dialPunho->value()));
    ui->editGarra->setText(QString::number(ui->dialGarra->value()));
}

ArmRule::~ArmRule()
{
    delete ui;
}

void ArmRule::on_dialBase_sliderReleased()
{
    // Enviar
}

void ArmRule::on_dialOmbro_sliderReleased()
{
    // Enviar
}

void ArmRule::on_dialCotovelo_sliderReleased()
{
    // Enviar
}

void ArmRule::on_dialPunho_sliderReleased()
{
    // Enviar
}

void ArmRule::on_dialGarra_sliderReleased()
{
    // Enviar
}

void ArmRule::on_dialBase_valueChanged(int value)
{
    ui->editBase->setText(QString::number(value));
}

void ArmRule::on_dialOmbro_valueChanged(int value)
{
    ui->editOmbro->setText(QString::number(value));
}

void ArmRule::on_dialCotovelo_valueChanged(int value)
{
    ui->editCotovelo->setText(QString::number(value));
}

void ArmRule::on_dialPunho_valueChanged(int value)
{
    ui->editPunho->setText(QString::number(value));
}

void ArmRule::on_dialGarra_valueChanged(int value)
{
    ui->editGarra->setText(QString::number(value));
}

void ArmRule::on_editBase_returnPressed()
{
    // Enviar
}

void ArmRule::on_editOmbro_returnPressed()
{
    // Enviar
}

void ArmRule::on_editCotovelo_returnPressed()
{
    // Enviar
}

void ArmRule::on_editPunho_returnPressed()
{
    // Enviar
}

void ArmRule::on_editGarra_returnPressed()
{
    // Enviar
}

void calcular_ponto(float tetaBase, float tetaOmbro, float tetaCotovelo, float tetaPunho, float &x, float &y)
{
    x = 2.7;
    y = 3.14;
}

void ArmRule::on_buttonSalvar_clicked()
{
    // Calculo Cinematica
    float x, y;
    calcular_ponto(tetaBase, tetaOmbro, tetaCotovelo, tetaPunho, x, y);

    QListWidgetItem *novo_ponto = new QListWidgetItem();
    novo_ponto->setText("(" + QString::number(x) + "; " + QString::number(y) + ")");

    ui->listaPontos->addItem(novo_ponto);
}

void ArmRule::on_buttonLimparLista_clicked()
{
    ui->listaPontos->clear();
}
