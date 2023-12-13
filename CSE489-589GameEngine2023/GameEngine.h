#pragma once

// Shader program building
#include "BuildShaderProgram.h"
#include "Texture.h"

// Shared Uniform Blocks
#include "SharedMaterials.h"
#include "SharedTransformations.h"

// Component container
#include "GameObject.h"

// Custom GameObjects
#include "Game.h"

// Camera
#include "CameraComponent.h"
#include "SkyBoxComponent.h"

// GameObject Management
#include "ModelMakerComponent.h"
#include "EnemySpawnerComp.h"

// Lights
#include "DirectionalLightComponent.h"
#include "SpotLightComponent.h"
#include "PositionalLightComponent.h"

// Meshes
#include "SphereMeshComponent.h"
#include "CylinderMeshComponent.h"
#include "ModelMeshComponent.h"
#include "BoxMeshComponent.h"

// Movement and Control
#include "MoveComponent.h"
#include "WaypointComponent.h"
#include "SteeringComponent.h"
#include "RemoveComponent.h"
#include "CollisionComponent.h"
#include "SpinComponent.h"
#include "ArrowRotateComponent.h"
#include "StrafeComp.h"

// Physics
#include "RigidBodyComponent.h"

// Sound
#include "SoundEngine.h"
#include "SoundListenerComponent.h"
#include "SoundSourceComponent.h"

