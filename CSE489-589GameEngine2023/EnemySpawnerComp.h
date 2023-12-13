#pragma once
#include "Component.h"
#include "ModelMeshComponent.h"

class EnemySpawnerComp :
    public Component
{
public:
	EnemySpawnerComp(GLuint shaderProgram, string pathAndFileName = "Assets/alien/alien_11.obj");
	~EnemySpawnerComp();
	virtual void initialize() override;
	virtual void update(const float& deltaTime) override;

protected:
	std::shared_ptr<class GameObject> pausedObject;
	string pathAndFileName;
	GLuint shaderProgram = 0;
	float elapsedTime;
};
