#include "DomeEvents.h"

#include <Event.h>

class Heal : public Event
{
public:

	Heal(Treatment t, bool exito) : Event(HEAL)
	{
		std::cout << "PLAYER USED " + std::to_string(t);

		if (exito)
			std::cout << " DE FORMA EXITOSA\n";
		else
			std::cout << " DE FORMA ERRONEA\n"; 

		add("TreatmentUse", t);
		add("TreatmentUse", exito);
	}
};