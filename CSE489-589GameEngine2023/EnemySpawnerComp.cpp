#include "EnemySpawnerComp.h"
#include "RemoveComponent.h"
#include "RigidBodyComponent.h"
#include "SoundSourceComponent.h"
#include "PointComponent.h"
float elapsedTime;
EnemySpawnerComp::EnemySpawnerComp(GLuint shaderProgram, string pathAndFileName)
	: pathAndFileName(pathAndFileName), shaderProgram(shaderProgram)
{

}

EnemySpawnerComp::~EnemySpawnerComp()
{
}

void EnemySpawnerComp::initialize()
{
	std::shared_ptr<class GameObject> playerObj = std::make_shared<GameObject>();
}

void EnemySpawnerComp::update(const float& deltaTime)
{
	elapsedTime += deltaTime;
	if (elapsedTime > 3.0f) {
		elapsedTime = 0.0f;
		int randomval = std::rand();
		cout << "spawned" << elapsedTime << endl;
		
		std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();

		owningGameObject->addChildGameObject(gameObject);
		int adjust = randomval % 200 - 100;
		gameObject->setPosition(owningGameObject->getPosition(LOCAL) + vec3((float) adjust, 0.0f,0.0f), WORLD);

		gameObject->addComponent(std::make_shared<RemoveComponent>(20.0));

		// Create empty game object to rotate the model to face -Z i.e. "forward"
		// Only necessary with some models
		std::shared_ptr<GameObject> emptyGameObject = std::make_shared<GameObject>();

		gameObject->addChildGameObject(emptyGameObject);
		emptyGameObject->setRotation(glm::rotate(PI, UNIT_Y_V3), LOCAL);
		emptyGameObject->setRotation(emptyGameObject->getRotation() * glm::rotate(-PI_OVER_2, UNIT_X_V3), LOCAL);

		std::shared_ptr<ModelMeshComponent> model = std::make_shared<ModelMeshComponent>(this->pathAndFileName, this->shaderProgram);
		emptyGameObject->addComponent(model);
		//emptyGameObject->setScale(vec3(.0125f, .0125f, .0125f),LOCAL);
		std::shared_ptr<RigidBodyComponent> rgb = std::make_shared<RigidBodyComponent>(model, DYNAMIC);



		emptyGameObject->addComponent(rgb);
		rgb->setVelocity(owningGameObject->getFowardDirection(LOCAL) * 50.0f);
		rgb->setGravityOn(false);
		///emptyGameObject->addComponent(std::make_shared<PointComponent>());


		emptyGameObject->gameObjectName = "alien";

		
		if (randomval % 3 == 0) {
			std::shared_ptr<SoundSourceComponent> sfx =
				std::make_shared<SoundSourceComponent>("Sounds/Tommy.wav", 10.0f, .10f, 100.0f, 200);
			sfx->setLooping(true);
			sfx->play();
			sfx->setGain(10);
			gameObject->addComponent(sfx);
		}
		if (randomval % 3 == 1) {
			std::shared_ptr<SoundSourceComponent> sfx =
				std::make_shared<SoundSourceComponent>("Sounds/Fernando.wav", 10.0f, .10f, 100.0f, 200);
			sfx->setLooping(true);
			sfx->play();
			sfx->setGain(10);
			gameObject->addComponent(sfx);
		}
		else {
			std::shared_ptr<SoundSourceComponent> sfx =
				std::make_shared<SoundSourceComponent>("Sounds/Junior.wav", 10.0f, .10f, 100.0f, 200);
			sfx->setLooping(true);
			sfx->play();
			sfx->setGain(10);
			gameObject->addComponent(sfx);
		}
		
	}
}
