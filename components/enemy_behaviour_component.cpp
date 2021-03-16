#include "enemy_behaviour_component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"

void EnemyBehaviourComponent::init()
{
	entityTr = entity_->getComponent<Transform>();
}
