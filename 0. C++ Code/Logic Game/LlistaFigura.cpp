#include "LlistaFigura.h"

LlistaFigura::~LlistaFigura()
{
	while (m_primer != nullptr)
		elimina();
}

LlistaFigura::LlistaFigura(const LlistaFigura& list)
{
	m_primer = nullptr;
	m_final = nullptr;

	// Copia los elementos de la lista original
	for (Forma* auxiliar = list.m_primer; auxiliar != nullptr; auxiliar = auxiliar->getNext())
	{
		insereix(auxiliar->getValor());
	}

}

LlistaFigura& LlistaFigura::operator=(const LlistaFigura& list)
{
	if (this != &list)
	{
		// Limpia la lista actual
		while (m_primer != nullptr)
		{
			elimina();
		}

		// Copia los elementos de la lista original
		for (Forma* auxiliar = list.m_primer; auxiliar != nullptr; auxiliar = auxiliar->getNext())
		{
			insereix(auxiliar->getValor());
		}
	}
	return *this;
}

Forma*LlistaFigura::insereix(const DadesFigura& valor)
{
	Forma* auxiliar = new Forma;
	if (auxiliar != nullptr)
	{
		auxiliar->setValor(valor);
		auxiliar->setNext(nullptr);
		if (m_primer == nullptr)
		{
			m_primer = auxiliar;
		}
		else
		{
			m_final->setNext(auxiliar);
		}
		m_final = auxiliar;
	}

	return auxiliar;
}

void LlistaFigura::elimina()
{
	Forma* auxiliar;
	if (m_primer == m_final)
	{
		delete m_primer;
		m_primer = nullptr;
		m_final = nullptr;
	}
	else
	{
		auxiliar = m_primer->getNext();
		delete m_primer;
		m_primer = auxiliar;
	}
}

int LlistaFigura::getNElements() const
{
	int nElements = 0;
	Forma* auxiliar = m_primer;
	while (auxiliar != NULL)
	{
		nElements++;
		auxiliar = auxiliar->getNext();
	}
	
	return nElements;
}

