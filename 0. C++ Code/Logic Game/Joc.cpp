#include "Joc.h"
#include <fstream>
using namespace std;

bool Joc::creaFigura()
{
	TipusFigura tipus = static_cast<TipusFigura>(rand() % N_TIPUS_FIGURES + 1);
	int colMaxima = N_COL_TAULER - (tipus == FIGURA_I ? 3 : (tipus == FIGURA_O ? 1 : 2));
	int columna = rand() % colMaxima + 1;
	int nGir = rand() % 4;

	m_figuraActual.inicialitza(tipus, 1, columna);
	for (int i = 0; i < nGir; i++)
		m_figuraActual.gira(GIR_HORARI);

	return m_tauler.confrontacioFigures(m_figuraActual);
}

void Joc::creaFigura(DadesFigura figura)
{
	m_figuraActual.inicialitza(figura.tipus, figura.fila, figura.columna);
	for (int i = 0; i < figura.gir; i++)
		m_figuraActual.gira(GIR_HORARI);
}

void Joc::inicialitza(const string& nomFitxer)
{
	ifstream fitxer(nomFitxer);
	if (!fitxer.is_open())
	{
		return;
	}

	// Llegir les dades de la figura actual
	int tipus, fila, columna, gir;
	fitxer >> tipus >> fila >> columna >> gir;
	m_figuraActual.inicialitza(TipusFigura(tipus), fila, columna);
	for (int i = 0; i < gir; ++i)
		m_figuraActual.gira(GIR_HORARI);

	// Llegim les dades del tauler inicial
	ColorFigura taulerInicial[MAX_FILA][MAX_COL];
	for (int i = 0; i < MAX_FILA; ++i)
	{
		for (int j = 0; j < MAX_COL; ++j)
		{
			int color;
			fitxer >> color;
			taulerInicial[i][j] = ColorFigura(color);
		}
	}
	m_tauler.inicialitza(taulerInicial);

	fitxer.close();
}

bool Joc::giraFigura(DireccioGir direccio)
{
	m_figuraActual.gira(direccio);
	bool colisiona = m_tauler.confrontacioFigures(m_figuraActual);
	if (colisiona)
	{
		if (direccio == GIR_HORARI)
			direccio = GIR_ANTI_HORARI;
		else
			direccio = GIR_HORARI;
		m_figuraActual.gira(direccio);
	}
	return !colisiona;
}

bool Joc::mouFigura(int dirX)
{
	m_figuraActual.mou(dirX);
	bool colisiona = m_tauler.confrontacioFigures(m_figuraActual);
	if (colisiona)
		m_figuraActual.mou(-dirX);
	return !colisiona;
}

int Joc::baixaFigura()
{
	int nFiles = -1;
	m_figuraActual.baixa();
	if (m_tauler.confrontacioFigures(m_figuraActual))
	{
		nFiles = 0;
		m_figuraActual.puja();
		nFiles = m_tauler.posicioFigura(m_figuraActual);
	}
	return nFiles;
}

int Joc::posarFigura()
{
	int nFiles;
	do 
	{
		nFiles = baixaFigura();
	} while (nFiles == -1);
	return nFiles;
}

void Joc::escriuTauler(const string& nomFitxer)
{
	ofstream fitxerSortida(nomFitxer);
	if (!fitxerSortida.is_open()) {
		return; // No es pot obrir el fitxer de sortida, sortim de la funció
	}

	if (m_figuraActual.getTipus() != NO_FIGURA) {
		m_tauler.dibuixaFigura(m_figuraActual);
	}

	ColorFigura tauler[MAX_FILA][MAX_COL];
	m_tauler.getValorsTauler(tauler);

	for (int i = 0; i < MAX_FILA; ++i) {
		for (int j = 0; j < MAX_COL; ++j) {
			fitxerSortida << static_cast<int>(tauler[i][j]) << " ";
		}
		fitxerSortida << endl;
	}

	fitxerSortida.close();
}

void Joc::representa()
{
	m_tauler.representa();
	m_figuraActual.representa();
}