#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"

const int MAX_FILA = 21;
const int MAX_COL = 11;

class Tauler
{
public:
    Tauler();
    void inicialitza(ColorFigura taulerInicial[MAX_FILA][MAX_COL]);
    bool confrontacioFigures(const Figura& figura);
    int posicioFigura(const Figura& figura);
    void dibuixaFigura(const Figura& figura);
    void getValorsTauler(ColorFigura tauler[MAX_FILA][MAX_COL]);
    void representa();
private:
    ColorFigura m_tauler[MAX_FILA + 2][MAX_COL + 4];
    int m_lliures[MAX_FILA];

    void destruirFila(int fila);
};
#endif