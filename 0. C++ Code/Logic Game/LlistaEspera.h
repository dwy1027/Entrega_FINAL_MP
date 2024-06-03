#include "Desplas.h"

class LlistaEspera
{
public:
	LlistaEspera() { m_primer = nullptr; }
	~LlistaEspera();
	LlistaEspera(const LlistaEspera& list);
	LlistaEspera& operator=(const LlistaEspera& list);
	Desplas* insereix(const TipusTecla& ins);
	
	//GETTERS
	int getNElements() const;
	TipusTecla getPrimer() const { return m_primer->getValor(); }

	bool lliure() const { return m_primer == nullptr; }
	void elimina();	
 private:
	 Desplas* m_primer;
	 Desplas* m_final;
};
