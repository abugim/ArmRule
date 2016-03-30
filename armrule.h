#ifndef ARMRULE_H
#define ARMRULE_H

#include <QMainWindow>

namespace Ui {
class ArmRule;
}

class ArmRule : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArmRule(QWidget *parent = 0);
    ~ArmRule();

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

private:
    Ui::ArmRule *ui;
    float tetaBase;
    float tetaOmbro;
    float tetaCotovelo;
    float tetaPunho;
    float aberturaGarra;
};

#endif // ARMRULE_H
