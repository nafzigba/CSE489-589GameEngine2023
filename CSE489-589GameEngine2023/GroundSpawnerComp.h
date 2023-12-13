
#include "Component.h"
#include "ModelMeshComponent.h"

class GroundSpawnerComp :
	public Component
{
public:
	GroundSpawnerComp(GLuint shaderProgram, string pathAndFileName = "Textures/grassjpg.jpg");
	~GroundSpawnerComp();
	virtual void initialize() override;
	virtual void update(const float& deltaTime) override;

protected:
	std::shared_ptr<class GameObject> pO;
	string pathAndFileName;
	GLuint shaderProgram = 0;
	float GelapsedTime;
};
