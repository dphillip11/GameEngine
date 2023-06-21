#include "PCH/pch.h"
#include "Tests/Tests.h"
#include "Registries/ComponentRegistry.h"
#include "Registries/ForceRegistry.h"
#include "Entity/Entity.h"
#include "Components/Components.h"
#include "Geometry/Vector3.h"
#include "Managers/ParticleManager.h"
#include "Physics/ContactManager.h"
#include "Physics/CollisionDetection.h" 

#define Log(x) {std::cout<<x<<std::endl; return false;}
namespace TestSuite {

	std::vector<Test*> Test::tests;

	void RunTests()
	{
		Test::RunTests();
	}


}

