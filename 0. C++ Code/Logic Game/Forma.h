#include <stdlib.h>
#include "InfoJoc.h"


class Forma
{
public:
    Forma() { m_seguent = nullptr;};
	~Forma() {};
    Forma(const DadesFigura& valor) { m_dada = valor; m_seguent = nullptr;}
   
    //GETTERS
    Forma* getNext() { return m_seguent; }
    DadesFigura getValor() { return m_dada; }
    //SETTERS
    void setNext(Forma* next) { m_seguent = next; }
    void setValor(const DadesFigura& valor) { m_dada = valor; }

private:
    DadesFigura m_dada;
    Forma* m_seguent;
};

