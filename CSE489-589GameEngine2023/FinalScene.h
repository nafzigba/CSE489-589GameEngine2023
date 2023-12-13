#pragma once

#include "GameEngine.h"
#include "GroundSpawnerComp.h"

class FinalScene : public Game
{
	void loadScene() override
	{
		// Set the window title
		glfwSetWindowTitle(renderWindow, "Scene 1");

		// Set the clear color
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		// Build and use the shader program
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "Shaders/vertexShader.glsl" },
			{ GL_FRAGMENT_SHADER, "Shaders/fragmentShader.glsl" },
			{ GL_NONE, NULL } // signals that there are no more shaders 
		};

		GLuint shaderProgram = BuildShaderProgram(shaders);

		SharedMaterials::setUniformBlockForShader(shaderProgram);
		SharedTransformations::setUniformBlockForShader(shaderProgram);
		SharedLighting::setUniformBlockForShader(shaderProgram);

		// ****** Directional light *********

		std::shared_ptr<class GameObject> directionaLightGO = std::make_shared<GameObject>();

		addChildGameObject(directionaLightGO);
		directionaLightGO->rotateTo(vec3(-1.0f, -1.0f, -1.0f), WORLD);

		std::shared_ptr<DirectionalLightComponent> dlc = std::make_shared<DirectionalLightComponent>(GLFW_KEY_D);
		dlc->setAmbientColor(vec4(0.3f, 0.3f, 0.3f, 1.0f));
		dlc->setDiffuseColor(vec4(.20f, .20f, .20f, 1.0f));
		dlc->setSpecularColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
		dlc->setEnable(true);
		directionaLightGO->addComponent(dlc);

		std::shared_ptr<class GameObject> playerObj = std::make_shared<GameObject>();
		addChildGameObject(playerObj);
		std::shared_ptr<ModelMeshComponent> playerMesh =
			std::make_shared<ModelMeshComponent>("Assets/is4/is4.obj", shaderProgram);
		playerObj->addComponent(playerMesh);
		playerObj->setPosition(vec3(0.0f, 0.0f, 0.0f));
		playerObj->rotateTo(vec3(0.0f, 0.0f, -100.0f));
		playerObj->setScale(vec3(5.0f, 5.0f, 5.0f));
		//playerObj->setRotation(glm::rotate(-180.0f, UNIT_Y_V3));
		//playerObj->addComponent(std::make_shared<WaypointComponent>());
		//playerObj->addComponent(std::make_shared<WASDMoveComponent>());
		//playerObj->addComponent(std::make_shared<ModSteerComp>(objs, vec3(1.0f, 1.0f, 1.0f) * 80.0f));
		playerObj->addComponent(std::make_shared < StrafeComp>(40.0f, 18));
		playerObj->addComponent(std::make_shared<ModelMakerComponent>(shaderProgram, "Assets/TankShell/Tankshell.obj"));

		std::shared_ptr<SpotLightComponent> dlc1 = std::make_shared<SpotLightComponent>(GLFW_KEY_E);
		dlc1->setAmbientColor(vec4(0.3f, 0.3f, 0.3f, 1.0f));
		dlc1->setDiffuseColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
		dlc1->setSpecularColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
		dlc1->setCutoffAngleInDegrees(60.0f);
		dlc1->setAttenuationFactors(.001f, .0001f, .00001f);
		dlc1->setEnable(true);
		playerObj->addComponent(dlc1);



		// **** camera
		std::shared_ptr<class GameObject> camObj = std::make_shared<GameObject>();
		addChildGameObject(camObj);
		camObj->setPosition(vec3(0.0f, 300.0f, -500.0f), WORLD);
		std::shared_ptr<CameraComponent> cam = std::make_shared<CameraComponent>(0, 30.0f, 1.0f, 2000.0f);
		//camObj->setRotation(vec3(0.0f, 0.0f, 10.0f), WORLD);
		cam->setViewPort(0, 0, 1.0f, 1.0f);
		cam->addCamera(cam);
		cam->setCameraClearColor(WHITE_RGBA);
		camObj->addComponent(cam);
		camObj->setRotation(glm::rotate(-PI_OVER_2*2, UNIT_Y_V3));
		camObj->setRotation(camObj->getRotation() * glm::rotate(-PI_OVER_2/4.0f, UNIT_X_V3));
		//camObj->setRotation(glm::rotate(-PI_OVER_2/100, UNIT_X_V3));
		//camObj->addComponent(std::make_shared<ArrowRotateComponent>());
		//camObj->rotateTo(vec3(0.0f,0.0f,0.0f));
		
		
		//cameraGameObject2->setRotation(glm::rotate(-PI_OVER_2, UNIT_X_V3));



		//Sound listener comp
		std::shared_ptr<SoundListenerComponent> ear =
			std::make_shared<SoundListenerComponent>(11);
		playerObj->addComponent(ear);

		std::shared_ptr<SoundSourceComponent> driveSfx =
			std::make_shared<SoundSourceComponent>("Sounds/Driving1.wav", 1.0f, 2.0f, 100.0f, 200);
		driveSfx->setLooping(true);
		driveSfx->play();
		driveSfx->setGain(.3);
		playerObj->addComponent(driveSfx);

		std::shared_ptr<SoundSourceComponent> drive2Sfx =
			std::make_shared<SoundSourceComponent>("Sounds/Driving2.wav", 1.0f, 2.0f, 100.0f, 200);
		drive2Sfx->setLooping(true);
		drive2Sfx->play();
		drive2Sfx->setGain(.3);
		playerObj->addComponent(drive2Sfx);

		/*
		std::shared_ptr<class GameObject> enemyObj = std::make_shared<GameObject>();
		addChildGameObject(enemyObj);
		std::shared_ptr<ModelMeshComponent> enemyMesh =
			std::make_shared<ModelMeshComponent>("Assets/grayAlien/GrayAlien.obj", shaderProgram);
		enemyObj->addComponent(enemyMesh);
		enemyObj->setPosition(vec3(2.0f, 2.0f, 4.0f));
		//enemyObj->setScale(vec3(0.01f, 0.01f, 0.01f),LOCAL);
		*/
		// Alien Spawner 
		
		std::shared_ptr<class GameObject> EspawnerObj = std::make_shared<GameObject>();
		addChildGameObject(EspawnerObj);
		EspawnerObj->setPosition(vec3(0.0f, 0.0f, 500.0f));
		EspawnerObj->rotateTo(vec3(0.0f, 0.0f, -1.0f));
		EspawnerObj->addComponent(std::make_shared<EnemySpawnerComp>(shaderProgram, "Assets/grayAlien/GrayAlien.obj"));
		
		std::shared_ptr<class GameObject> GspawnerObj = std::make_shared<GameObject>();
		addChildGameObject(GspawnerObj);
		GspawnerObj->setPosition(vec3(0.0f, 0.0f, 500.0f));
		GspawnerObj->rotateTo(vec3(0.0f, 0.0f, -1.0f));
		GspawnerObj->addComponent(std::make_shared<GroundSpawnerComp>(shaderProgram, "Textures/grassjpg.jpg"));

		std::shared_ptr<class GameObject> camGameParent = std::make_shared<GameObject>();
		addChildGameObject(camGameParent);
		camGameParent->setPosition(vec3(0.0f, 1050.0f, 0.0f));
		camGameParent->rotateTo(vec3(0.0f, 1.0f, 0.0f));

		std::shared_ptr<class GameObject> topCamObj = std::make_shared<GameObject>();
		playerObj->addChildGameObject(topCamObj);
		topCamObj->setPosition(vec3(0.0f, 20.0f, -10.0f), LOCAL);
		topCamObj->setRotation(glm::rotate(-PI_OVER_2 * 2, UNIT_Y_V3));

		//camObj->setRotation(glm::rotate(180.0f, UNIT_Y_V3));
		std::shared_ptr<CameraComponent> cam1 = std::make_shared<CameraComponent>(1, 60.0f, 1.0f, 3000.0f);
		//camObj->setRotation(vec3(0.0f, 0.0f, 10.0f), WORLD);
		cam1->setViewPort(0.75f, .750f, .250f, .250f);
		cam1->addCamera(cam1);
		cam1->setCameraClearColor(WHITE_RGBA);
		//camObj->rotateTo(vec3(0.0f, 0.0f, -1.0f));
		topCamObj->addComponent(cam1);

		std::vector<string> faces
		{
			"Assets/Cube Map/right.jpg",
			"Assets/Cube Map/left.jpg",
			"Assets/Cube Map/top.jpg",
			"Assets/Cube Map/bottom.jpg",
			"Assets/Cube Map/back.jpg",
			"Assets/Cube Map/front.jpg"
		};
		std::shared_ptr<SkyBoxComponent> skybox = std::make_shared<SkyBoxComponent>(faces);
		std::shared_ptr<SkyBoxComponent> skybox2 = std::make_shared<SkyBoxComponent>(faces);

		camObj->addComponent(skybox);
		cam->setSkyBox(skybox);
		topCamObj->addComponent(skybox2);
		cam1->setSkyBox(skybox2); 

	}
};
