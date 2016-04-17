#ifndef ARMRULE_H
#define ARMRULE_H
#define L1 6.73
#define L2 14.6
#define L3 18.73
#define L4 8.57

#include <QMainWindow>
#include <QDebug>

namespace Ui {
class ArmRule;
}

class ArmRule : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArmRule(QWidget *parent = 0);
    ~ArmRule();


    double resultado[4][4];

private slots:
    void on_dialBase_sliderReleased();

    void on_dialOmbro_sliderReleased();

    void on_dialCotovelo_sliderReleased();

    void on_dialPunho_sliderReleased();

    void on_dialGarra_sliderReleased();

    void on_dialBase_valueChanged(int value);

    void on_dialOmbro_valueChanged(int value);

    void on_dialCotovelo_valueChanged(int value);

    void on_dialPunho_valueChanged(int value);

    void on_dialGarra_valueChanged(int value);

    void on_editBase_returnPressed();

    void on_editOmbro_returnPressed();

    void on_editCotovelo_returnPressed();

    void on_editPunho_returnPressed();

    void on_editGarra_returnPressed();

    void on_buttonSalvar_clicked();

    void on_buttonLimparLista_clicked();

    void on_btnInversa_clicked();

private:
    Ui::ArmRule *ui;

    int serial_retorno;

    int calcular_posicao_base(float teta);
    int calcular_posicao_ombro(float teta);
    int calcular_posicao_cotovelo(float teta);
    int calcular_posicao_punho(float teta);
    int calcular_posicao_garra(float abertura);

    void calcular_ponto(double tetaBase, double tetaOmbro, double  tetaCotovelo, double tetaPunho, double &x, double &y);
    void calcularCinematicaInversa(double posX,double posY,double posZ, double orientacao);
    void multiplicarMatrizes(double A[4][4], double B[4][4]);
    void enviar_base();
    void enviar_ombro();
    void enviar_cotovelo();
    void enviar_punho();
    void enviar_garra();

    void clean();
};

#endif // ARMRULE_H
