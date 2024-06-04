#include "Partida.h"
#include "GraphicManager.h"
#include <fstream>

void Partida::inicialitza(const string& fitxer1, const string& fitxer2, const string& fitxer3)
{
    if (m_mode == MODE_NORMAL)
        m_final = m_joc.creaFigura();
    else
    {
        m_joc.inicialitza(fitxer1);
        iniciFigura(fitxer2);
        iniciDesplas(fitxer3);
    }
	    
}

void Partida::iniciFigura(const string& nomFitxer)
{
    ifstream fitxer(nomFitxer);
    if (!fitxer.is_open()) 
        return; // No es pot obrir el fitxer, sortim de la funci?    I delete a { make the code fuction now

    DadesFigura figura;
    int tipus;

    while (fitxer >> tipus >> figura.fila >> figura.columna >> figura.gir) {
        figura.tipus = TipusFigura(tipus);
        m_figura.insereix(figura);
    }

    fitxer.close();
}

void Partida::iniciDesplas(const string& nomFitxer)
{
    ifstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open())
    {
        int tipus;
        fitxer >> tipus;
        while (!fitxer.eof())
        {
            m_desplas.insereix(TipusTecla(tipus));
            fitxer >> tipus;
        }
        fitxer.close();
    }
}


void Partida::canviNormal(float deltaTime)
{
    if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT)) {
        m_joc.mouFigura(1);
    }
    else if (Keyboard_GetKeyTrg(KEYBOARD_LEFT)) {
        m_joc.mouFigura(-1);
    }

    if (Keyboard_GetKeyTrg(KEYBOARD_UP)) {
        m_joc.giraFigura(GIR_HORARI);
    }
    else if (Keyboard_GetKeyTrg(KEYBOARD_DOWN)) {
        m_joc.giraFigura(GIR_ANTI_HORARI);
    }

    int nFilesEliminades;
    if (Keyboard_GetKeyTrg(KEYBOARD_SPACE)) {
        nFilesEliminades = m_joc.posarFigura();
        acturalitzar(nFilesEliminades);
        m_final = m_joc.creaFigura();
        m_temps = 0.0;
    }
    else {
        m_temps += deltaTime;
        if (m_temps > m_velocitat) {
            nFilesEliminades = m_joc.baixaFigura();
            if (nFilesEliminades != -1) {
                m_final = m_joc.creaFigura();
                acturalitzar(nFilesEliminades);
            }
            m_temps = 0.0;
        }
    }
}

void Partida::canviTest(float deltaTime)
{
    m_temps += deltaTime;
    if (m_temps > m_velocitat)
    {
        m_temps = 0.0;
        TipusTecla op;
        if (m_desplas.lliure())
        {
            m_final = true;
        }
        else
        {
            op = m_desplas.getPrimer();
            m_desplas.elimina();
            int eliminFil;
            switch (op)
            {
            case DRETA:
                m_joc.mouFigura(1);
                break;
            case ESQUERRA:
                m_joc.mouFigura(-1);
                break;
            case GIR_HORARI_1:
                m_joc.giraFigura(GIR_HORARI);
                break;
            case GIR_ANTI_HORARI_1:
                m_joc.giraFigura(GIR_ANTI_HORARI);
                break;
            case BAIXA_FINAL:
                eliminFil = m_joc.posarFigura();
                acturalitzar(eliminFil);
                if (!m_figura.lliure())
                {
                    DadesFigura figura = m_figura.getPrimer();
                    m_figura.elimina();
                    m_joc.creaFigura(figura);
                }
                else
                    m_final = true;
                break;
            case BAIXA:
                eliminFil = m_joc.baixaFigura();
                if (eliminFil != -1)
                {
                    acturalitzar(eliminFil);
                    if (!m_figura.lliure())
                    {
                        DadesFigura figura = m_figura.getPrimer();
                        m_figura.elimina();
                        m_joc.creaFigura(figura);
                    }
                    else
                        m_final = true;
                }
            }
        }
                    
    }
}

void Partida::actualitza(float deltaTime)
{
    if (!m_final)
    {
        if (m_mode == MODE_NORMAL)
            canviNormal(deltaTime);
        else
            canviTest(deltaTime);
    }

	GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
	m_joc.representa();
    string punts = "Puntuacio: " + to_string(m_punts);
    string Nivell = "Nivell: " + to_string(m_nivell);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_PUNTUACIO, POS_Y_PUNTUACIO, 0.8, punts);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_NIVELL, POS_Y_NIVELL, 0.8, Nivell);
    if (m_final)
    {
        string gmaeOver = "GAME OVER";
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_FINAL_JOC, POS_Y_FINAL_JOC, 1.8, gmaeOver);

    }
}

void Partida::acturalitzar(int filesEliminades)
{
    if (filesEliminades == 0)
        m_punts += PUNTS_FIGURA;
    else
    {
        m_punts += PUNTS_FILA;
        switch (filesEliminades)
        {
        case 2:
            m_punts += DOBLE_FILA;
            break;
        case 3:
            m_punts += TRIPLE_FILA;
            break;
        case 4:
            m_punts += QUADRUPLE_FILA;
            break;
        }
    }
    if (m_punts > (m_nivell * CANVI_NIVELL))
    {
        m_nivell += 1;
        m_velocitat *= CANVI_VELOCITAT;
    }
}
