#include "armrule.h"
#include <QDebug>
#include <QtMath>
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

    enviar_comando(strdup("#0P1550T5000#1P1422T5000#2P1644T5000#3P1442T5000#4P2400T5000"), serial_retorno);
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
    int pos = -teta*10 + 1550;
    return trava(0, pos);
}

int ArmRule::calcular_posicao_ombro(float teta)
{
//    int pos = 673.33 + 8.4*teta;
    int pos = 500 + teta/0.09;
    qDebug()<<pos;
    return pos;//trava(1, pos);
}

int ArmRule::calcular_posicao_cotovelo(float teta)
{
    int pos = 931 - 7.778*teta;
    qDebug() << "Pos" <<pos;
    return pos;//trava(2, pos);
}

int ArmRule::calcular_posicao_punho(float teta)
{
    int pos = 1441.667 + 10.278*teta;
    return trava(3, pos);
}

int ArmRule::calcular_posicao_garra(float abertura)
{
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
    calcular_ponto(ui->dialBase->value(), ui->dialOmbro->value(), ui->dialCotovelo->value(), ui->dialPunho->value(), x, y);

    QListWidgetItem *novo_ponto = new QListWidgetItem();
    novo_ponto->setText("(" + QString::number(x) + "; " + QString::number(y) + ")");

    ui->listaPontos->addItem(novo_ponto);
}

void ArmRule::calcular_ponto(double tetaBase, double tetaOmbro, double tetaCotovelo, double tetaPunho, double &x, double &y)
{
    double phi = tetaOmbro + tetaCotovelo + tetaPunho;
    tetaBase = qDegreesToRadians(tetaBase);
    tetaOmbro = qDegreesToRadians(tetaOmbro);
    tetaCotovelo = qDegreesToRadians(tetaCotovelo);
    tetaPunho = qDegreesToRadians(tetaPunho);

    double T10[4][4] = {{cos(tetaBase),(-1)*sin(tetaBase),0,0},{sin(tetaBase),cos(tetaBase),0, 0},{0, 0, 1, L1}, {0, 0, 0, 1}};
    double T21[4][4] = {{cos(tetaOmbro),(-1)*sin(tetaOmbro),0,0},{0,0,-1,0},{sin(tetaOmbro),cos(tetaOmbro), 0, 0}, {0, 0, 0, 1}};
    double T32[4][4] = {{cos(tetaCotovelo),(-1)*sin(tetaCotovelo),0,L2},{sin(tetaCotovelo),cos(tetaCotovelo),0,0}, {0, 0,1,0},{0,0,0,1}};
    double T43[4][4] = {{cos(tetaPunho),(-1)*sin(tetaPunho),0,L3},{sin(tetaPunho),cos(tetaPunho),0,0}, {0, 0,1,0},{0,0,0,1}};
    double T54[4][4] = {{1, 0, 0, L4}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0,0,0,1}};

    multiplicarMatrizes(T10, T21);
    multiplicarMatrizes(resultado,T32);
    multiplicarMatrizes(resultado, T43);
    multiplicarMatrizes(resultado, T54);

    // x = resultado[0][3];
    // y = resultado[1][3];

    x = qCos(tetaBase)*(L2*qCos(tetaOmbro) + L3*qCos(tetaOmbro + tetaCotovelo) + L4*qCos(tetaOmbro + tetaCotovelo + tetaPunho));
    y = qSin(tetaBase)*(L2*qCos(tetaOmbro) + L3*qCos(tetaOmbro + tetaCotovelo) + L4*qCos(tetaOmbro + tetaCotovelo + tetaPunho));
    double z = L1 + L2*qSin(tetaOmbro) + L3*qSin(tetaOmbro + tetaCotovelo) + L4*qSin(tetaOmbro + tetaCotovelo + tetaPunho);

    qDebug() << x << y << z << phi;
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


void ArmRule::on_btnInversa_clicked()
{
    double posX = ui->edtX->text().toDouble();
    double posY = ui->edtY->text().toDouble();
    double posZ = ui->edtZ->text().toDouble();
    double orientacao = ui->edtPhi->text().toDouble();

    calcularCinematicaInversa(posX, posY, posZ, orientacao);
}


void ArmRule::calcularCinematicaInversa(double posX, double posY, double posZ, double orientacao)
{
    orientacao = qDegreesToRadians(orientacao);
    double lTotalXY = qSqrt(qPow(posY,2) + qPow(posX,2));
    double sinThetaBase = posY/lTotalXY;
    double cosThetaBase = posX/lTotalXY;

    double thetaBase = atan2(sinThetaBase, cosThetaBase);

    double x4 =  (cos(orientacao))*L4;
    double z4 =  (sin(orientacao))*L4;

    double x41 = lTotalXY - x4;
    double z41 = posZ - L1 - z4;

    double cosThetaCotovelo = (qPow(x41, 2) + qPow(z41, 2) - qPow(L2, 2) - qPow(L3,2))/(2*L2*L3);
    double sinThetaCotovelo = (-1)*qSqrt(1 - qPow(cosThetaCotovelo,2));

    double thetaCotovelo = atan2(sinThetaCotovelo, cosThetaCotovelo);

    double lXZ41 = qSqrt(qPow(x41, 2)+ qPow(z41,2));

    double sinAlpha = (posZ - L1 - z4)/lXZ41;
    double cosAlpha = (lTotalXY - x4)/lXZ41;

    double sinBeta = (L3*sin(thetaCotovelo))/lXZ41;
    double cosBeta = (L2 + L3*cos(thetaCotovelo))/lXZ41;

    double alpha = atan2(sinAlpha, cosAlpha);
    double beta = atan2(sinBeta, cosBeta);

    double thetaOmbro = alpha - beta;

    double thetaPunho = orientacao - thetaOmbro - thetaCotovelo;

    QString posBase = QString::number(calcular_posicao_base(thetaBase));
    QString posOmbro = QString::number(calcular_posicao_ombro(thetaOmbro));
    QString posCotovelo = QString::number(calcular_posicao_cotovelo(thetaCotovelo));
    QString posPunho = QString::number(calcular_posicao_punho(thetaPunho));

    ui->edtInvBase->setText(QString::number(qRadiansToDegrees(thetaBase), 'f', 3));
    ui->edtInvOmbro->setText(QString::number(qRadiansToDegrees(thetaOmbro), 'f', 3));
    ui->edtInvCotovelo->setText(QString::number(qRadiansToDegrees(thetaCotovelo), 'f', 3));
    ui->edtInvPunho->setText(QString::number(qRadiansToDegrees(thetaPunho), 'f', 3));

    QString comando = ("#0P"+posBase+"T5000#1P"+posOmbro+"T5000#2P"+posCotovelo+"T5000#3P"+posPunho+"T5000#4P2400T5000");


    // 27.1834 0 23.0493 2
    enviar_comando(strdup(comando.toStdString().c_str())
                   , serial_retorno);


}
