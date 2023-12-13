#include "RemoveComponent.h"
#include "PointComponent.h"

#define VERBOSE false

RemoveComponent::RemoveComponent(double lifeSpan, int updateOrder)
	: Component(updateOrder),  lifeSpan(lifeSpan)
{}



RemoveComponent::~RemoveComponent()
{
	if (VERBOSE) cout << "RemoveComponent destructor called " << endl;
	PointComponent::setScore(50);
	
}

void RemoveComponent::update(const float & deltaTime)
{
	age += deltaTime;

	if (age > lifeSpan) {
		age = -1000;
		if (VERBOSE) cout << "Removing Game Object " << endl;
		
			

		this->owningGameObject->removeAndDelete();
	}

}
