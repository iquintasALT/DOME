#pragma once
#include "player_health_component.h"

struct WoundComparator
{
	bool operator()(const PlayerHealthComponent* a, const PlayerHealthComponent* b) const
	{
		return a->renderPriority > b->renderPriority;
	}
};