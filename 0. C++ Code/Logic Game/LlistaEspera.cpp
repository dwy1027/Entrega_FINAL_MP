#include "LlistaEspera.h"

LlistaEspera::~LlistaEspera()
{
	while (m_primer != nullptr)
		elimina();
}

LlistaEspera::LlistaEspera(const LlistaEspera& list)
{
	m_primer = nullptr;
	m_final = nullptr;
	Desplas* aux = list.m_primer;
	Desplas* aux_nova = m_primer;
	while (aux != nullptr)
	{
		aux_nova = insereix(aux->getValor());
		aux = aux->getNext();
	}

}

LlistaEspera& LlistaEspera::operator=(const LlistaEspera& list)
{
	if (this != &list)
	{
		elimina();
		Desplas* current = list.m_primer;
		while (current != nullptr)
		{
			insereix(current->getValor());
			current = current->getNext();
		}
	}
	return *this;
}

Desplas* LlistaEspera::insereix(const TipusTecla& valor)
{
	Desplas* aux = new Desplas;
	if (aux != nullptr)
	{
		aux->setValor(valor);
		aux->setNext(nullptr);
		if (m_primer == nullptr)
		{
			m_primer = aux;
		}
		else
		{
			m_final->setNext(aux);
		}
		m_final = aux;
	}

	return aux;
}

void LlistaEspera::elimina()
{
	Desplas* aux;
	if (m_primer == m_final)
	{
		delete m_primer;
		m_primer = nullptr;
		m_final = nullptr;
	}
	else
	{
		aux = m_primer->getNext();
		delete m_primer;
		m_primer = aux;
	}
}

int LlistaEspera::getNElements() const
{
	int nElements = 0;
	Desplas*aux = m_primer;
	while (aux != NULL)
	{
		nElements++;
		aux = aux->getNext();
	}
	
	return nElements;
}

