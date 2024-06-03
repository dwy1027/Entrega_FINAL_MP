#ifndef FIGURA_H
#define FIGURA_H

#include "InfoJoc.h"


const int MAX_ALCADA = 4;
const int MAX_AMPLADA = 4;



class Figura
{
public:
    Figura() : m_tipus(NO_FIGURA), m_color(NO_COLOR), m_amplada(MAX_AMPLADA), m_altura(MAX_ALCADA), m_fila(0), m_columna(0), m_girar(0) { reiniciaFigura(); }
    void inicialitza(TipusFigura tipus, int fila, int columna);
    void gira(DireccioGir direccio);
    void mou(int dirX);
    void baixa();
    void puja();
    void representa();

    //GETTERS
    int getFila() const{ return m_fila; }
    int getColumna() const { return m_columna; }

    ColorFigura getColor() const { return m_color; }
    void getMascara(int mascara[MAX_ALCADA][MAX_AMPLADA]) const;
  
    int getAltura() const { return m_altura; }
    int getAmplada() const { return m_amplada; }
    TipusFigura getTipus() const { return m_tipus; }

private:
    //Caracteristiques Figures
    TipusFigura m_tipus;
    ColorFigura m_color;
    //Parametres figura
    int m_mascara[MAX_ALCADA][MAX_AMPLADA];
    int m_fila;
    int m_columna;
    //MAxims dels parametres
    int m_amplada;
    int m_altura;
    //funcio rotacio
    int m_girar;

    
    //Metodes
    void reiniciaFigura();//Ens assegurem que es la figura que volem reinicant-ho a zero

    void transposaMascara();//Trasposa mascara
    void inverteixMascaraHorizontal(); //Trasposem matriu horizontalment
    void inverteixMascaraVertical();//Trasposem matriu Verticalment

    void representacioEnBinari(TipusFigura tipus);//Inicialitzem la seva forma
   
};


#endif
