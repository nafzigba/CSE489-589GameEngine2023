#include "GroundSpawnerComp.h"
#include "RemoveComponent.h"
#include "RigidBodyComponent.h"
#include "Texture.h"
#include "BoxMeshComponent.h"
#include "GroundMoveComp.h"
float GelapsedTime;
GroundSpawnerComp::GroundSpawnerComp(GLuint shaderProgram, string pathAndFileName)
	: pathAndFileName(pathAndFileName), shaderProgram(shaderProgram)
{

}

GroundSpawnerComp::~GroundSpawnerComp()
{
}

void GroundSpawnerComp::initialize()
{
	pO = std::make_shared<GameObject>();

	this->owningGameObject->addChildGameObject(pO);
	pO->setPosition(vec3(0.0f, 0.0f, 0.0f),WORLD);
	// Create a blue material for the box
	Material boxMaterial;
	boxMaterial.setDiffuseTexture(Texture::GetTexture(this->pathAndFileName)->getTextureObject());
	boxMaterial.setAmbientAndDiffuseMat(BLUE_RGBA);

	// Create the sphere mesh
	std::shared_ptr<BoxMeshComponent> boxMesh = std::make_shared<BoxMeshComponent>(this->shaderProgram, boxMaterial, 1000.0f, 2.0f, 500.0f);
	pO->addComponent(boxMesh);
	pO->addComponent(std::make_shared<GroundMoveComp>(10.0f, 19));
	pO->setState(ACTIVE);

	std::shared_ptr<class GameObject> boxObject1 = std::make_shared<GameObject>();

	owningGameObject->addChildGameObject(boxObject1);
	boxObject1->setPosition(vec3(0.0f, 0.0f, 500.0f), WORLD);

	// Create a blue material for the box

	// Create the sphere mesh
	std::shared_ptr<BoxMeshComponent> boxMesh1 = std::make_shared<BoxMeshComponent>(this->shaderProgram, boxMaterial, 1000.0f, 2.0f, 500.0f);
	boxObject1->addComponent(boxMesh1);
	boxObject1->addComponent(std::make_shared<GroundMoveComp>(10.0f, 19));
	boxObject1->setState(ACTIVE);

	std::shared_ptr<class GameObject> boxObject2 = std::make_shared<GameObject>();

	owningGameObject->addChildGameObject(boxObject2);
	boxObject2->setPosition(vec3(0.0f, 0.0f, 1000.0f), WORLD);

	// Create a blue material for the box

	// Create the sphere mesh
	std::shared_ptr<BoxMeshComponent> boxMesh2 = std::make_shared<BoxMeshComponent>(this->shaderProgram, boxMaterial, 1000.0f, 2.0f, 500.0f);
	boxObject2->addComponent(boxMesh2);
	boxObject2->addComponent(std::make_shared<GroundMoveComp>(10.0f, 19));
	boxObject2->setState(ACTIVE);


}

void GroundSpawnerComp::update(const float& deltaTime)
{

	GelapsedTime += deltaTime;
	if (GelapsedTime > 100.0f) {
		GelapsedTime = 0.0f;
		std::shared_ptr<class GameObject> boxObject = std::make_shared<GameObject>();

		owningGameObject->addChildGameObject(boxObject);
		boxObject->setPosition(vec3(0.0f, 0.0f, 0.0f), LOCAL);

		// Create a blue material for the box
		Material boxMaterial;
		boxMaterial.setDiffuseTexture(Texture::GetTexture(this->pathAndFileName)->getTextureObject());
		boxMaterial.setAmbientAndDiffuseMat(BLUE_RGBA);

		// Create the sphere mesh
		std::shared_ptr<BoxMeshComponent> boxMesh = std::make_shared<BoxMeshComponent>(this->shaderProgram, boxMaterial, 1000.0f, 2.0f, 500.0f);
		boxObject->addComponent(boxMesh);
		boxObject->addComponent(std::make_shared<GroundMoveComp>(10.0f, 19));
		boxObject->setState(ACTIVE);
	}

}
