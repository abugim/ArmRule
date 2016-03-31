#include "armrule.h"
#include <QDebug>
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
    //int pos = (teta / (2380 - 500)) + 500;
    int pos = -teta*10 + 1550;
    return trava(0, pos);
}

int ArmRule::calcular_posicao_ombro(float teta)
{
    //int pos = (teta / (2000 - 1200)) + 1200;
   // int pos = 1200+ 8.889*teta; era 600
   int pos = teta*(-50.0/9.0) + 2000;

    return trava(1, pos);
}

int ArmRule::calcular_posicao_cotovelo(float teta)
{
    //int pos = (teta / (2100 - 1100)) + 1100;
    int pos = 750- 10*teta;
    return trava(2, pos);
}

int ArmRule::calcular_posicao_punho(float teta)
{
    //int pos = (teta / (2500 - 500)) + 500;
    int pos = 1441.667+10.278*teta;
    return trava(3, pos);
}

int ArmRule::calcular_posicao_garra(float abertura)
{
    //int pos = (abertura / (2400 - 1500)) + 1500;
    int pos = abertura*(9) + 1500;
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
    ui->dialBase->setValue(ui->editBase->text().toInt());
    enviar_base();
}

void ArmRule::on_editOmbro_returnPressed()
{
    ui->dialOmbro->setValue(ui->editOmbro->text().toInt());
    enviar_ombro();
}

void ArmRule::on_editCotovelo_returnPressed()
{
    ui->dialCotovelo->setValue(ui->editCotovelo->text().toInt());
    enviar_cotovelo();
    qDebug() << "enter pressed cotovelo" << ui->editCotovelo->text();
}

void ArmRule::on_editPunho_returnPressed()
{
    ui->dialPunho->setValue(ui->editPunho->text().toInt());
    enviar_punho();
}

void ArmRule::on_editGarra_returnPressed()
{
    ui->dialGarra->setValue(ui->editGarra->text().toInt());
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
     qDebug() << comando;
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
    qDebug() << comando;
}

void ArmRule::on_buttonSalvar_clicked()
{
    // Calculo Cinematica
    double x, y;
    calcular_ponto(0, 0, 0, 0, x, y);

    QListWidgetItem *novo_ponto = new QListWidgetItem();
    novo_ponto->setText("(" + QString::number(x) + "; " + QString::number(y) + ")");

    ui->listaPontos->addItem(novo_ponto);
}

void ArmRule::calcular_ponto(double tetaBase, double tetaOmbro, double tetaCotovelo, double tetaPunho, double &x, double &y)
{
    double T10[4][4] = {{cos(tetaBase),-sin(tetaBase),0,0},{sin(tetaBase),cos(tetaBase),0, 0},{0, 0, 1, L1}, {0, 0, 0, 1}};
    double T21[4][4] = {{cos(tetaOmbro),-sin(tetaOmbro),0,0},{0,0,-1,0},{sin(tetaOmbro),cos(tetaOmbro), 0, 0}, {0, 0, 0, 1}};
    double T32[4][4] = {{cos(tetaCotovelo),-sin(tetaCotovelo),0,L2},{sin(tetaCotovelo),cos(tetaCotovelo),0,0}, {0, 0,1,0},{0,0,0,1}};
    double T43[4][4] = {{cos(tetaPunho),-sin(tetaPunho),0,L3},{sin(tetaPunho),cos(tetaPunho),0,0}, {0, 0,1,0},{0,0,0,1}};
    double T54[4][4] = {{1, 0, 0, L4}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0,0,0,1}};


    multiplicarMatrizes(T10, T21);
    multiplicarMatrizes(resultado,T32);
    multiplicarMatrizes(resultado, T43);
    multiplicarMatrizes(resultado, T54);


    double T50[4][4];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            T50[i][j] = resultado[i][j];
        }
    }


    x = T50[0][4];
    y = T50[1][4];
}

void ArmRule::on_buttonLimparLista_clicked()
{
    ui->listaPontos->clear();
}
void ArmRule::multiplicarMatrizes(double A[4][4], double B[4][4]){

    double C[4][4];

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            C[i][j] = 0;
        }
    }

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            resultado[i][j] = C[i][j];
        }
    }
}
