#include "StrafeComp.h"

StrafeComp::StrafeComp(float speed, int updateOrder)
	:Component(updateOrder), speed(speed) {
}

void StrafeComp::update(const float& deltaTime) {
	vec3 pos = owningGameObject->getPosition();
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT)) {
		pos -= UNIT_X_V3 * deltaTime * speed;
	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT)) {
		pos += UNIT_X_V3 * deltaTime * speed;
	}
	this->owningGameObject->setPosition(pos);
	gameElapsedTime += deltaTime;

	if (gameElapsedTime > 30) {
		owningGameObject->getOwningGame()->notRunning();
	}
}
