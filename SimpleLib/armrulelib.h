#ifndef ARMRULELIB_H
#define ARMRULELIB_H
#define L1 7.3
#define L2 14.8
#define L3 18.5
#define L4 8.7
#include <string>
#include <math.h>
extern "C"{
    #include "ufrn_al5d.h"
}

    void init();
    void pegar();
    void soltar();
    void move(double x, double y, double z, double phi);
    void repouso();
    void calcularCinematicaInversa(double posX, double posY, double posZ, double phi);
    int serial_retorno;
    int calcular_posicao_base(float teta);
    int calcular_posicao_ombro(float teta);
    int calcular_posicao_cotovelo(float teta);
    int calcular_posicao_punho(float teta);
    double degreesToRadians(double graus);

#endif // ARMRULELIB_H
