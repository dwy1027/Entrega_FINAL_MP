#include "Tauler.h"
#include "GraphicManager.h"
#include "InfoJoc.h"
#include <iostream>
using namespace std;

Tauler::Tauler()
{
    for (int i = 0; i < MAX_FILA; i++)
    {
        m_tauler[i][0] = NO_COLOR;
        m_tauler[i][1] = NO_COLOR;
        m_tauler[i][MAX_COL + 2] = NO_COLOR;
        m_tauler[i][MAX_COL + 3] = NO_COLOR;
        for (int j = 0; j < MAX_COL; j++)
            m_tauler[i][j + 2] = COLOR_NEGRE;
    }
    for (int j = 0; j < MAX_COL + 4; j++)
    {
        m_tauler[MAX_FILA][j] = NO_COLOR;
        m_tauler[MAX_FILA + 1][j] = NO_COLOR;
    }
    for (int i = 0; i < MAX_FILA; i++)
        m_lliures[i] = MAX_COL;
}

void Tauler::inicialitza(ColorFigura taulerInicial[MAX_FILA][MAX_COL])
{
    for (int i = 0; i < MAX_FILA; i++)
        m_lliures[i] = MAX_COL;
    for (int i = 0; i < MAX_FILA; i++)
        for (int j = 0; j < MAX_COL; j++)
        {
            m_tauler[i][j + 2] = taulerInicial[i][j];
            if (taulerInicial[i][j] != COLOR_NEGRE)
                m_lliures[i]--;
        }
}

bool Tauler::confrontacioFigures(const Figura& figura)
{
    bool colisionaFigura = false;
    int mascara[MAX_ALCADA][MAX_AMPLADA];
    figura.getMascara(mascara);

    for (int i = 0; i < figura.getAltura(); i++)
    {
        for (int j = 0; j < figura.getAmplada(); j++)
        {
            if (mascara[i][j] != 0 && m_tauler[figura.getFila() - 1 + i][figura.getColumna() + 1 + j] != 0)
            {
                colisionaFigura = true;
                break;
            }
        }
        if (colisionaFigura) break;
    }

    return colisionaFigura;

}

int Tauler::posicioFigura(const Figura& figura)
{
    int mascara[MAX_ALCADA][MAX_AMPLADA];
    int numFilesFetes = 0;

    ColorFigura color = figura.getColor();
    figura.getMascara(mascara);

    for (int i = 0; i < figura.getAltura(); i++)
    {
        for (int j = 0; j < figura.getAmplada(); j++)
        {
            if (mascara[i][j] > 0)
            {
                m_tauler[figura.getFila() - 1 + i][figura.getColumna() + 1 + j] = color;
                m_lliures[figura.getFila() - 1 + i]--;
                if (m_lliures[figura.getFila() - 1 + i] == 0)
                {
                    numFilesFetes++;
                    destruirFila(figura.getFila() - 1 + i);
                }
            }
        }
    }
    return numFilesFetes;
}


void Tauler::dibuixaFigura(const Figura& figura)
{
    int mascara[MAX_ALCADA][MAX_AMPLADA];

    ColorFigura color = figura.getColor();
    figura.getMascara(mascara);

    for (int i = 0; i < figura.getAltura(); i++)
    {
        for (int j = 0; j < figura.getAmplada(); j++)
        {
            if (mascara[i][j] > 0)
            {
                m_tauler[figura.getFila() - 1 + i][figura.getColumna() + 1 + j] = color;
            }
        }
    }
}

void Tauler::destruirFila(int fila)
{
    if (fila > 0)
    {
        for (int i = fila; i > 0; i--)
        {
            for (int j = 0; j < MAX_COL; j++)
            {
                m_tauler[i][j + 2] = m_tauler[i - 1][j + 2];
            }
            m_lliures[i] = m_lliures[i - 1];
        }
    }
    for (int i = 0; i < MAX_COL; i++)
        m_tauler[0][i + 2] = COLOR_NEGRE;
    m_lliures[0] = MAX_COL;
}

void Tauler::getValorsTauler(ColorFigura tauler[MAX_FILA][MAX_COL])
{
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
            tauler[i][j] = m_tauler[i][j + 2];
    }
}

void Tauler::representa()
{
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);

    for (int i = 0; i < MAX_FILA; i++)
        for (int j = 0; j < MAX_COL; j++)
        {
            if (m_tauler[i][j + 2] != COLOR_NEGRE)
                dibuixaQuadrat(m_tauler[i][j + 2], POS_X_TAULER + ((j + 1) * MIDA_QUADRAT),
                    POS_Y_TAULER + (i * MIDA_QUADRAT));
        }

}