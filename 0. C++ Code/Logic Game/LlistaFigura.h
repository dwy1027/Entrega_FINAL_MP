#include "Forma.h"

class LlistaFigura
{
public:
	LlistaFigura() { m_primer = nullptr; }
	~LlistaFigura();
	LlistaFigura(const LlistaFigura& list);
	LlistaFigura& operator=(const LlistaFigura& list);
	Forma* insereix(const DadesFigura& ins);
	
	//GETTERS
	int getNElements() const;
	DadesFigura getPrimer() const { return m_primer->getValor(); }

	bool lliure() const { return m_primer == nullptr; }
	void elimina();	

 private:
	 Forma* m_primer;
	 Forma* m_final;
};
