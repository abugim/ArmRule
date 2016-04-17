#include "armrulelib.h"


ArmRuleLib::ArmRuleLib()
{
    ufrn_header();
    serial_retorno = abrir_porta();
}
void ArmRuleLib::pegar(){
    enviar_comando("#4P1500T5000", serial_retorno);
}
void ArmRuleLib::soltar(){
    enviar_comando("#4P2400T5000", serial_retorno);
}
void ArmRuleLib::move(double x, double y, double z, double phi){
    calcularCinematicaInversa(x, y, z, phi);
}
void ArmRuleLib::repouso(){
    enviar_comando("#0P500T5000#1P500T5000#2P500T5000#3P500T5000#4P500T5000", serial_retorno);
}

void ArmRuleLib::calcularCinematicaInversa(double posX, double posY, double posZ, double orientacao){

    double lTotalXY = qSqrt(qPow(posY,2) + qPow(posX,2));
    double sinThetaBase = posY/lTotalXY;
    double cosThetaBase = posX/lTotalXY;

    double thetaBase = atan2(sinThetaBase, cosThetaBase);

    double x4 =  (cos(qDegreesToRadians(orientacao)))*L4;
    double z4 =  (sin(qDegreesToRadians(orientacao)))*L4;

    double x41 = lTotalXY - x4;
    double z41 = posZ - L1 - z4;

    double cosThetaCotovelo = (qPow(x41, 2) + qPow(z41, 2) - qPow(L2, 2) - qPow(L3,2))/(2*L2*L3);
    double sinThetaCotovelo = qSqrt(1 - qPow(cosThetaCotovelo,2));

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

    QString comando = ("#0P"+posBase+"T5000#1P"+posOmbro+"T5000#2P"+posCotovelo+"T5000#3P"+posPunho+"T5000#4P2400T5000");

    enviar_comando(strdup(comando.toStdString().c_str())
                   , serial_retorno);
}


int ArmRuleLib::calcular_posicao_base(float teta)
{
    int pos = -teta*10 + 1550;
    return trava(0, pos);
}

int ArmRuleLib::calcular_posicao_ombro(float teta)
{
    int pos = 673.33 + 8.4*teta;
    return pos;//trava(1, pos);
}

int ArmRuleLib::calcular_posicao_cotovelo(float teta)
{
    int pos = 931 - 7.778*teta;
    return pos;//trava(2, pos);
}

int ArmRuleLib::calcular_posicao_punho(float teta)
{
    int pos = 1441.667 + 10.278*teta;
    return trava(3, pos);
}
