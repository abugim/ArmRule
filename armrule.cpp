#include "armrule.h"
#include "ui_armrule.h"
extern "C" {
#include "include/ufrn_al5d.h"
}
#include <QString>
#include <QListWidgetItem>

ArmRule::ArmRule(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArmRule)
{
    ui->setupUi(this);

    ui->editBase->setText(QString::number(ui->dialBase->value()));
    ui->editOmbro->setText(QString::number(ui->dialOmbro->value()));
    ui->editCotovelo->setText(QString::number(ui->dialCotovelo->value()));
    ui->editPunho->setText(QString::number(ui->dialPunho->value()));
    ui->editGarra->setText(QString::number(ui->dialGarra->value()));

    ufrn_header();
    serial_retorno = abrir_porta();
}

ArmRule::~ArmRule()
{
    delete ui;
}

void ArmRule::clean()
{
//    memset(comando, 0, BUFSIZE);
//    memset(membro_srt, 0, BUFSIZE);
//    memset(pw_str, 0, BUFSIZE);
//    memset(time_str, 0, BUFSIZE);
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

int ArmRule::calcular_posicao_base(float teta)
{
    int pos = (teta / (2380 - 500)) + 500;
    return trava(0, pos);
}

int ArmRule::calcular_posicao_ombro(float teta)
{
    int pos = (teta / (2000 - 1200)) + 1200;
    return trava(1, pos);
}

int ArmRule::calcular_posicao_cotovelo(float teta)
{
    int pos = (teta / (2100 - 1100)) + 1100;
    return trava(2, pos);
}

int ArmRule::calcular_posicao_punho(float teta)
{
    int pos = (teta / (2500 - 500)) + 500;
    return trava(3, pos);
}

int ArmRule::calcular_posicao_garra(float abertura)
{
    int pos = (abertura / (2400 - 1500)) + 1500;
    return trava(4, pos);
}

void ArmRule::on_dialBase_sliderReleased()
{
    enviar_base();
}

void ArmRule::on_dialOmbro_sliderReleased()
{
    enviar_ombro();
}

void ArmRule::on_dialCotovelo_sliderReleased()
{
    enviar_cotovelo();
}

void ArmRule::on_dialPunho_sliderReleased()
{
    enviar_punho();
}

void ArmRule::on_dialGarra_sliderReleased()
{
    enviar_garra();
}

void ArmRule::on_editBase_returnPressed()
{
    enviar_base();
}

void ArmRule::on_editOmbro_returnPressed()
{
    enviar_ombro();
}

void ArmRule::on_editCotovelo_returnPressed()
{
    enviar_cotovelo();
}

void ArmRule::on_editPunho_returnPressed()
{
    enviar_punho();
}

void ArmRule::on_editGarra_returnPressed()
{
    enviar_garra();
}

void ArmRule::enviar_base()
{
    QString comando;
    comando = "#0P" + QString::number(calcular_posicao_base(ui->dialBase->value())) + "S100";
    enviar_comando(strdup(comando.toStdString().c_str()), serial_retorno);
}

void ArmRule::enviar_ombro()
{
    QString comando;
    comando = "#1P" + QString::number(calcular_posicao_ombro(ui->dialOmbro->value())) + "S100";
    enviar_comando(strdup(comando.toStdString().c_str()), serial_retorno);
}

void ArmRule::enviar_cotovelo()
{
    QString comando;
    comando = "#2P" + QString::number(calcular_posicao_cotovelo(ui->dialCotovelo->value())) + "S100";
    enviar_comando(strdup(comando.toStdString().c_str()), serial_retorno);
}

void ArmRule::enviar_punho()
{
    QString comando;
    comando = "#3P" + QString::number(calcular_posicao_punho(ui->dialPunho->value())) + "S100";
    enviar_comando(strdup(comando.toStdString().c_str()), serial_retorno);
}

void ArmRule::enviar_garra()
{
    QString comando;
    comando = "#4P" + QString::number(calcular_posicao_garra(ui->dialGarra->value())) + "S100";
    enviar_comando(strdup(comando.toStdString().c_str()), serial_retorno);
}

void ArmRule::on_buttonSalvar_clicked()
{
    // Calculo Cinematica
    float x, y;
    calcular_ponto(0, 0, 0, 0, x, y);

    QListWidgetItem *novo_ponto = new QListWidgetItem();
    novo_ponto->setText("(" + QString::number(x) + "; " + QString::number(y) + ")");

    ui->listaPontos->addItem(novo_ponto);
}

void ArmRule::calcular_ponto(float tetaBase, float tetaOmbro, float tetaCotovelo, float tetaPunho, float &x, float &y)
{
    x = 2.7;
    y = 3.14;
}

void ArmRule::on_buttonLimparLista_clicked()
{
    ui->listaPontos->clear();
}
