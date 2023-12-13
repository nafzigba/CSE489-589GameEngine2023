#include "ModelMakerComponent.h"
#include "RemoveComponent.h"
#include "RigidBodyComponent.h"
#include "SoundSourceComponent.h"

#define VERBOSE true

ModelMakerComponent::ModelMakerComponent(GLuint shaderProgram, string pathAndFileName)
	: pathAndFileName(pathAndFileName), shaderProgram(shaderProgram)
{

}

ModelMakerComponent::~ModelMakerComponent()
{
}

void ModelMakerComponent::initialize()

{
	// Add a "paused" game object with an a mesh attached (will not be rendered)
	// to avoid delays in loading at run time.

	pausedObject = std::make_shared<GameObject>();
	pausedObject->setState(PAUSED);
	this->owningGameObject->addChildGameObject(pausedObject);

	std::shared_ptr<ModelMeshComponent> baseMesh = std::make_shared<ModelMeshComponent>(this->pathAndFileName, this->shaderProgram);
	pausedObject->addComponent(baseMesh);
}



void ModelMakerComponent::processInput()
{
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_J) && j_key_up == true) {

		std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();

		owningGameObject->addChildGameObject(gameObject);

		gameObject->setPosition(owningGameObject->getPosition(LOCAL), WORLD);
		
		gameObject->addComponent(std::make_shared<RemoveComponent>(10.0));
		
		// Create empty game object to rotate the model to face -Z i.e. "forward"
		// Only necessary with some models
		std::shared_ptr<GameObject> emptyGameObject = std::make_shared<GameObject>();

		gameObject->addChildGameObject(emptyGameObject);
		emptyGameObject->setRotation(glm::rotate(PI, UNIT_Y_V3), LOCAL);
		emptyGameObject->setRotation(emptyGameObject->getRotation() * glm::rotate(-PI_OVER_2, UNIT_X_V3), LOCAL);

		std::shared_ptr<ModelMeshComponent> model = std::make_shared<ModelMeshComponent>(this->pathAndFileName, this->shaderProgram);
		emptyGameObject->addComponent(model);
		emptyGameObject->setScale(vec3(2.5f, 2.5f, 2.5f));
		std::shared_ptr<RigidBodyComponent> rgb = std::make_shared<RigidBodyComponent>(model, DYNAMIC,100.0f);

		emptyGameObject->addComponent(rgb);
		rgb->setVelocity(owningGameObject->getFowardDirection(LOCAL) * -250.0f);
		rgb->setGravityOn(false);

		emptyGameObject->gameObjectName = "projectile";

		int randomval = std::rand();
		if (randomval % 2 == 0) {
			std::shared_ptr<SoundSourceComponent> sfx =
				std::make_shared<SoundSourceComponent>("Sounds/Shooting1.wav", 1.0f, 2.0f, 100.0f, 200);
			sfx->setLooping(false);
			sfx->play();
			sfx->setGain(2);
			gameObject->addComponent(sfx);
		}
		else {
			std::shared_ptr<SoundSourceComponent> sfx =
				std::make_shared<SoundSourceComponent>("Sounds/Shooting3.wav", 1.0f, 2.0f, 100.0f, 200);
			sfx->setLooping(false);
			sfx->play();
			sfx->setGain(2);
			gameObject->addComponent(sfx);
		}

		j_key_up = false;
	}
	if (!glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_J)) {

		j_key_up = true;
	}

}