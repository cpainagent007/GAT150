#pragma once

// Audio
#include "Audio/AudioSystem.h"
#include "Audio/AudioClip.h"

// Core
#include "Core/Factory.h"
#include "Core/File.h"
#include "Core/Json.h"
#include "Core/Logger.h"
#include "Core/Random.h"
#include "Core/Serializable.h"
#include "Core/Singleton.h"
#include "Core/StringHelper.h"
#include "Core/Time.h"

// Framework
#include "Framework/Actor.h"
#include "Framework/Component.h"
#include "Framework/Game.h"
#include "Framework/Object.h"
#include "Framework/Scene.h"

// Input
#include "Input/InputSystem.h"

// Math
#include "Math/Math.h"
#include "Math/Rect.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

// Event
#include "Event/Event.h"
#include "Event/EventManager.h"
#include "Event/Observer.h"

// Physics
#include "Physics/Collidable.h"
#include "Physics/Physics.h"
#include "Physics/PhysicsBody.h"

// Components
#include "Components/Animator.h"
#include "Components/AudioSource.h"
#include "Components/RendererComponent.h"
#include "Components/RigidBody.h"
#include "Components/SpriteRenderer.h"
#include "Components/ColliderComponent.h"
#include "Components/MeshRenderer.h"
#include "Components/CircleCollider2D.h"

// Renderer
#include "Renderer/Font.h"
#include "Renderer/Mesh.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/Texture.h"
#include "Renderer/TextureAnimation.h"

// Resources
#include "Resources/Resource.h"
#include "Resources/ResourceManager.h"

// ThirdParty
#include <fmod.hpp>
#include <fmod_errors.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <box2d/box2d.h>

// STD
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <list>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <variant>