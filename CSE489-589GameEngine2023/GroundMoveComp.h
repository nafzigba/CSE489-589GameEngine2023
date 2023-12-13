#pragma once
#include "Component.h"
class GroundMoveComp : public Component
{
public:
    GroundMoveComp(float speed = 30.0f, int updateOrder = 150);
    virtual void update(const float& deltaTime) override;
protected:
    float speed;
};

