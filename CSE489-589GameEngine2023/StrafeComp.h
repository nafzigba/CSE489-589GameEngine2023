#pragma once
#include "Component.h"
class StrafeComp :  public Component
{
public:
    StrafeComp(float speed = 30.0f, int updateOrder = 150);
    virtual void update(const float& deltaTime) override;
protected:
    float speed;
    float gameElapsedTime;
};

