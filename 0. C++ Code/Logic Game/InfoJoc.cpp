#include "InfoJoc.h"
#include "GraphicManager.h"

void dibuixaQuadrat(ColorFigura color, int x, int y)
{
	IMAGE_NAME cuadrat;

	switch (color)
	{
	case COLOR_GROC:
		cuadrat = GRAFIC_QUADRAT_GROC;
		break;
	case COLOR_BLAUCEL:
		cuadrat = GRAFIC_QUADRAT_BLAUCEL;
		break;
	case COLOR_MAGENTA:
		cuadrat = GRAFIC_QUADRAT_MAGENTA;
		break;
	case COLOR_TARONJA:
		cuadrat = GRAFIC_QUADRAT_TARONJA;
		break;
	case COLOR_BLAUFOSC:
		cuadrat = GRAFIC_QUADRAT_BLAUFOSC;
		break;
	case COLOR_VERMELL:
		cuadrat = GRAFIC_QUADRAT_VERMELL;
		break;
	case COLOR_VERD:
		cuadrat = GRAFIC_QUADRAT_VERD;
		break;
	}

	GraphicManager::getInstance()->drawSprite(cuadrat, x, y, false);
}



