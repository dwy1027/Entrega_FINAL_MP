#include <stdlib.h>
#include "InfoJoc.h"

class Desplas
{
public:
    Desplas() { m_seguent = nullptr;};
	~Desplas() {};
    Desplas(const TipusTecla& valor) { m_dada = valor; m_seguent = nullptr;}
    Desplas* getNext() { return m_seguent; }
    void setNext(Desplas* next) { m_seguent = next; }
    TipusTecla getValor() { return m_dada; }
    void setValor(const TipusTecla& valor) { m_dada = valor; }
private:
    TipusTecla m_dada;
    Desplas* m_seguent;
};

