#include "GroundMoveComp.h"

GroundMoveComp::GroundMoveComp(float speed, int updateOrder)
	:Component(updateOrder), speed(speed) {
}

void GroundMoveComp::update(const float& deltaTime) {
	vec3 pos = owningGameObject->getPosition();
	pos -= UNIT_Z_V3 * deltaTime * speed;
	this->owningGameObject->setPosition(pos);

}
