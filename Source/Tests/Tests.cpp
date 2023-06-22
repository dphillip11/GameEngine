#include "PCH/pch.h"
//#include "Tests/Tests.h"
//#include "Registries/ComponentRegistry.h"
//#include "Registries/ForceRegistry.h"
//#include "Entity/Entity.h"
//#include "Components/Components.h"
//#include "Geometry/Vector3.h"
//#include "Managers/ParticleManager.h"
//#include "Physics/ContactManager.h"
//#include "Physics/CollisionDetection.h" 
//
//#define Log(x) {std::cout<<x<<std::endl; return false;}
//namespace TestSuite {
//
//	std::vector<Test*> Test::tests;
//
//	void RunTests()
//	{
//		Test::RunTests();
//	}
//
//	bool Test_Component_Registry()
//	{
//		// Create an instance of the ComponentRegistry
//		ComponentRegistry registry;
//
//		// Create some entities
//		Entity entity1;
//		Entity entity2;
//		Entity entity3;
//
//		// Register components to an entity
//		auto component1 = registry.RegisterComponent<Component>(entity1);
//		auto component2 = registry.RegisterComponent<Component>(entity1);
//		auto component3 = registry.RegisterComponent<Particle>(entity1);
//		auto component4 = registry.RegisterComponent<PhysicsMaterial>(entity1);
//
//		//retrieve components associated with entity
//		if (entity1.GetComponents<Component>().size() != 2)
//			Log("Error1");
//		auto components = entity1.GetComponents<Component>();
//		if (entity1.GetComponents<Particle>().size() != 1)
//			Log("Error2");
//		if (entity1.GetComponents<PhysicsMaterial>().size() != 1)
//			Log("Error3");
//
//		struct newComponent : Component {};
//
//		//correctly detect nullvector
//		if (entity1.GetComponents<newComponent>().size() != 0)
//			Log("Error4");
//
//		//register adhoc components
//		auto component5 = registry.RegisterComponent<newComponent>(entity1);
//
//		//retrieve adhoc components
//		if (entity1.GetComponents<newComponent>().size() != 1)
//			Log("Error5");
//
//		//pointers work
//		FP newInverseMass = 3;
//		entity1.GetComponents<Particle>()[0]->inverse_mass = newInverseMass;
//		if (component3->inverse_mass != newInverseMass)
//			Log("Error6");
//
//		//correctly associate entities
//		auto component6 = registry.RegisterComponent<Component>(entity2);
//
//		if (entity1.GetComponents<Component>().size() != 2)
//			Log("Error7");
//		if (entity2.GetComponents<Component>().size() != 1)
//			Log("Error8");
//		if (registry.GetComponents<Component>().size() != 3)
//			Log("Error9");
//
//		//get entity components via registry
//		if (registry.GetComponents<Component>(entity2).size() != 1)
//			Log("Error10");
//
//		//check removing entity deactivates components
//		Component* component7;
//		if (true)
//		{
//			Entity tempEntity;
//			component7 = registry.RegisterComponent<Component>(tempEntity);
//			if (!component7->Active)
//				Log("Error11");
//		}
//		//tempEntity auto destructed, components should be marked inactive
//		if (component7->Active)
//			Log("Error12");
//
//		//test that cull removes inactive components
//		auto currentSize = registry.GetComponents<Component>().size();
//		registry.CullInactive<Component>();
//		auto newSize = registry.GetComponents<Component>().size();
//		if (currentSize != newSize + 1)
//			Log("Error13");
//
//		//all tests passed
//		return true;
//	}
//
//	auto new_test1 = Test("Component Registry", Test_Component_Registry);
//
//	bool Test_Type_Counter()
//	{
//
//		// Get the type IDs for different types
//		int typeID1 = GetTypeID<int>();
//		int typeID2 = GetTypeID<float>();
//		int typeID3 = GetTypeID<std::string>();
//		int typeID4 = GetTypeID<bool>();
//
//		// Test that the type IDs are unique
//		if (typeID1 == typeID2 || typeID1 == typeID3 || typeID1 == typeID4 ||
//			typeID2 == typeID3 || typeID2 == typeID4 || typeID3 == typeID4) {
//			Log("Error14");
//		}
//
//		// Get the type ID for a component
//		int componentTypeID1 = GetTypeID(42);
//		int componentTypeID2 = GetTypeID(3.14f);
//		int componentTypeID3 = GetTypeID(std::string("Test"));
//		int componentTypeID4 = GetTypeID(true);
//
//		// Test that the component type IDs are unique
//		if (componentTypeID1 == componentTypeID2 || componentTypeID1 == componentTypeID3 ||
//			componentTypeID1 == componentTypeID4 || componentTypeID2 == componentTypeID3 ||
//			componentTypeID2 == componentTypeID4 || componentTypeID3 == componentTypeID4) {
//			Log("Error15");
//		}
//
//		// Test that the component type IDs are consistent
//		if (componentTypeID1 != typeID1 || componentTypeID2 != typeID2 ||
//			componentTypeID3 != typeID3 || componentTypeID4 != typeID4)
//			Log("Error16");
//
//		// All tests passed
//		return true;
//	}
//
//	auto new_test2 = Test("Type Counter", Test_Type_Counter);
//
//	bool Test_Vector3()
//	{
//		// Test default constructor
//		Vector3 v1;
//		if (v1.x != 0 || v1.y != 0 || v1.z != 0)
//		{
//			std::cout << "Default constructor test failed." << std::endl;
//			return false;
//		}
//
//		// Test parameterized constructor
//		Vector3 v2(1.0, 2.0, 3.0);
//		if (v2.x != 1.0 || v2.y != 2.0 || v2.z != 3.0)
//		{
//			std::cout << "Parameterized constructor test failed." << std::endl;
//			return false;
//		}
//
//		// Test operator overloads
//		Vector3 v3 = v1 + v2;
//		if (v3.x != 1.0 || v3.y != 2.0 || v3.z != 3.0)
//		{
//			std::cout << "Operator+ test failed." << std::endl;
//			return false;
//		}
//
//		v1 += v2;
//		if (v1.x != 1.0 || v1.y != 2.0 || v1.z != 3.0)
//		{
//			std::cout << "Operator+= test failed." << std::endl;
//			return false;
//		}
//
//		Vector3 v4 = v2 - v1;
//		if (v4.x != 0.0 || v4.y != 0.0 || v4.z != 0.0)
//		{
//			std::cout << "Operator- test failed." << std::endl;
//			return false;
//		}
//
//		v2 -= v1;
//		if (v2.x != 0.0 || v2.y != 0.0 || v2.z != 0.0)
//		{
//			std::cout << "Operator-= test failed." << std::endl;
//			return false;
//		}
//
//		Vector3 v5 = v1 * 2.0;
//		if (v5.x != 2.0 || v5.y != 4.0 || v5.z != 6.0)
//		{
//			std::cout << "Operator* test failed." << std::endl;
//			return false;
//		}
//
//		v1 *= 2.0;
//		if (v1.x != 2.0 || v1.y != 4.0 || v1.z != 6.0)
//		{
//			std::cout << "Operator*= test failed." << std::endl;
//			return false;
//		}
//
//		Vector3 v6 = v5 / 2.0;
//		if (v6.x != 1.0 || v6.y != 2.0 || v6.z != 3.0)
//		{
//			std::cout << "Operator/ test failed." << std::endl;
//			return false;
//		}
//
//		v5 /= 2.0;
//		if (v5.x != 1.0 || v5.y != 2.0 || v5.z != 3.0)
//		{
//			std::cout << "Operator/= test failed." << std::endl;
//			return false;
//		}
//
//		// Test Length and LengthSquared
//		FP lengthSquared = v1.LengthSquared();
//		if (lengthSquared != 56.0)
//		{
//			std::cout << "LengthSquared test failed." << std::endl;
//			return false;
//		}
//		// Test Dot function
//		FP dotProduct = v1.Dot(v2);
//		if (dotProduct != 0.0)
//		{
//			std::cout << "Dot function test failed." << std::endl;
//			return false;
//		}
//
//		// Test Cross function
//		Vector3 crossProduct = v1.Cross(v2);
//		Vector3 expectedCrossProduct(0.0, 0.0, 0.0);
//		if (crossProduct.x != expectedCrossProduct.x || crossProduct.y != expectedCrossProduct.y || crossProduct.z != expectedCrossProduct.z)
//		{
//			std::cout << "Cross function test failed." << std::endl;
//			return false;
//		}
//
//		v2 = Vector3(2, 2, 1);
//		// Test Normalize function
//		Vector3 normalizedVector = v2.Normalise();
//		FP expectedLength = 1.0;
//		if (normalizedVector.Length() != expectedLength)
//		{
//			std::cout << "Normalize function test failed." << std::endl;
//			return false;
//		}
//
//		v2 = Vector3(0);
//		// Test Normalize function
//		normalizedVector = v2.Normalise();
//		expectedLength = 0;
//		if (normalizedVector.Length() != 0)
//		{
//			std::cout << "Normalize function test failed." << std::endl;
//			return false;
//		}
//
//		v2 = 3;
//		if (int(v2.Length()) != 5)
//			return false;
//
//		return true;
//	}
//
//
//
//	bool Test_Particle_Manager() {
//
//		ComponentRegistry registry;
//		registry.CullInactive<Particle>();
//		// Create ParticleManager instance
//		ParticleManager particleManager(registry.GetContainer<Particle>().m_components);
//
//		//components require an entity to attach themselves to
//		Entity E;
//		// Create test particle
//		auto particle = registry.RegisterComponent<Particle>(E);
//
//		particle->position = Vector3(1, 1, 1);
//		particle->velocity = Vector3(2, 2, 2);
//		particle->acceleration = Vector3(3, 3, 3);
//
//		// Update the particles in the ParticleManager
//		particleManager.UpdateAllParticles(0.5);
//
//		// Check if the particle's position and velocity have been updated correctly
//		if (particle->position != Vector3(2.75, 2.75, 2.75) ||
//			particle->velocity != Vector3(3.5, 3.5, 3.5) ||
//			particle->acceleration != Vector3(0, 0, 0))
//		{
//			std::cout << "Particle manager functions failed the test.\n";
//			return false;
//		}
//		return true;
//	}
//
//	auto new_test4 = Test("Physics_Manager", Test_Particle_Manager);
//
//	bool Test_Force_Registry() {
//		// Create particles
//		Particle particle1;
//		Particle particle2;
//
//		GravityForce gravity(Vector3(0, -10, 0));
//
//		// Create force registry
//		ForceRegistry registry;
//
//		// Register force generators for particles
//		registry.AddForceGenerator(&gravity, &particle1);
//
//		// Apply forces for a certain time step
//		double dt = 1;
//		registry.UpdateForces(dt);
//
//		if (particle1.acceleration.y != -10)
//			Log("failed application of gravityForce");
//
//		// Remove force generators for particles
//		registry.RemoveForceGenerator(&gravity, &particle1);
//
//		// Clear the force registry
//		registry.Clear();
//
//		// Create some particles
//		Particle particle3;
//		Particle particle4;
//		Particle particle5;
//		particle5.inverse_mass = (1.0 / 5);
//
//		// Create force generators
//		GravityForce gravityForce(Vector3(0, -9.8f, 0)); // Apply gravity along the y-axis
//		ConstantForce constantForce(Vector3(10, 0, 0)); // Apply a constant force along the x-axis
//
//		// Create a force registry
//		ForceRegistry forceRegistry;
//
//		// Register force generators for particles
//		forceRegistry.AddForceGenerator(&gravityForce, &particle3);
//		forceRegistry.AddForceGenerator(&constantForce, &particle4);
//		forceRegistry.AddForceGenerator(&constantForce, &particle5);
//
//		// Apply forces to particles
//		forceRegistry.UpdateForces(0.1f); // Assuming a time step of 0.1 seconds
//
//		// Check the resulting particle accelerations
//		bool testPassed = true;
//		if (particle3.acceleration != Vector3(0, -9.8f, 0))
//		{
//			std::cout << "Particle 3 acceleration not correct!" << std::endl;
//			return false;
//		}
//		if (particle4.acceleration != Vector3(10, 0, 0))
//		{
//			std::cout << "Particle 4 acceleration not correct!" << std::endl;
//			return false;
//		}
//		if (particle5.acceleration != Vector3(2, 0, 0))
//		{
//			std::cout << "Particle 5 acceleration not correct!" << std::endl;
//			return false;
//		}
//
//		return true;
//	}
//
//	auto new_test5 = Test("Force_Registry", Test_Force_Registry);
//
//	bool Test_Buoyant_Force()
//	{
//		Particle particle;
//		particle.position = { 0, -1, 0 };
//		particle.inverse_mass = 1;
//
//		BuoyantForce buoyantForce(0, 1);
//
//		// Apply the buoyant force to the particle
//		buoyantForce.ApplyForce(&particle, 1.0);
//
//		// particle is fully submerged
//		Vector3 expectedAcceleration;
//		expectedAcceleration.y = (4.0 / 3) * M_PI;
//		if (particle.acceleration != expectedAcceleration)
//		{
//			Log("particle acceleration incorrect")
//		}
//
//		// particle is half submerged
//		particle.position = { 0,0,0 };
//		particle.acceleration = 0;
//		buoyantForce.ApplyForce(&particle, 1.0);
//		if (particle.acceleration != expectedAcceleration * 0.5)
//		{
//			Log("particle acceleration incorrect")
//		}
//
//		// particle is out of water
//		particle.position = { 0,1,0 };
//		particle.acceleration = 0;
//		buoyantForce.ApplyForce(&particle, 1.0);
//		if (particle.acceleration != 0)
//		{
//			Log("particle acceleration incorrect")
//		}
//
//		// particle is underwater
//		particle.position = { 0,-5,0 };
//		particle.acceleration = 0;
//		buoyantForce.ApplyForce(&particle, 1.0);
//		if (particle.acceleration != expectedAcceleration)
//		{
//			Log("particle acceleration incorrect")
//		}
//
//		return true;
//	}
//	auto new_test6 = Test("Buoyant_Force", Test_Buoyant_Force);
//
//	bool Test_Contact_Manager()
//	{
//		// Create particles
//		Particle particleA;
//		Particle particleB;
//
//		// Set particle properties
//		particleA.position = Vector3(0, 0, 0);
//		particleA.inverse_mass = 1.0;  // Assuming non-zero inverse mass
//		particleB.position = Vector3(1, 0, 0);
//		particleB.inverse_mass = 1.0;  // Assuming non-zero inverse mass
//
//		// Create contact manager
//		ContactManager contactManager;
//
//		// Create a particle contact
//		ParticleContact contact;
//		contact.particleA = &particleA;
//		contact.particleB = &particleB;
//		contact.penetration = 0.5;
//		contact.collisionNormal = Vector3(1, 0, 0);
//		contact.collisionSpeed = 0.5;
//
//		// Register the contact
//		contactManager.RegisterContact(contact);
//
//		// Resolve the contacts
//		contactManager.ResolveContacts();
//
//		// Verify the position adjustment
//		Vector3 expectedPositionA(0.25, 0, 0);
//		Vector3 expectedPositionB(0.75, 0, 0);
//
//		if (particleA.position != expectedPositionA || particleB.position != expectedPositionB) {
//			Log("Test_Contact_Manager failed!")
//		}
//
//		return true;
//	}
//	auto new_test7 = Test("Contact_Manager", Test_Contact_Manager);
//
//	bool Test_Contact_Manager2()
//	{
//		// Create particles
//		Particle particleA;
//		Particle particleB;
//
//		// Set particle properties
//		//immovable particle
//		particleA.inverse_mass = 0;
//		particleA.material = new PhysicsMaterial();
//		particleA.material->restitution = 0.8;
//
//		particleB.inverse_mass = 1;
//		particleB.material = new PhysicsMaterial();
//		particleB.material->restitution = 0.6;
//
//		// Set initial velocities and collision normal
//		particleA.velocity = Vector3(1, 0, 0);
//		particleB.velocity = Vector3(-1, 0, 0);
//		Vector3 collisionNormal(-1, 0, 0);
//
//		// Create a contact
//		ParticleContact contact;
//		contact.particleA = &particleA;
//		contact.particleB = &particleB;
//		contact.collisionNormal = collisionNormal;
//		contact.penetration = 1;
//
//		// Create and initialize the ContactManager
//		ContactManager contactManager;
//		contactManager.RegisterContact(contact);
//
//		if (contact.collisionSpeed != 2)
//			Log("failed to calculate collision speed");
//
//		// Resolve the contacts
//		contactManager.ResolveContacts();
//
//		if (particleB.position != Vector3(1, 0, 0))
//		{
//			Log(particleB.position.x)
//		}
//		// Check if velocities have been adjusted
//		if (particleA.velocity != Vector3(1, 0, 0) || abs(particleB.velocity.x + 2.4) < 0.001)
//		{
//			Log("no velocity update")
//
//		}
//		// Clean up memory
//		delete particleA.material;
//		delete particleB.material;
//
//		// Return test result
//		return true;
//	}
//
//	auto new_test8 = Test("Test_Contact_Manager_2", Test_Contact_Manager2);
//
//	bool Test_CollisionDetection()
//	{
//
//		ComponentRegistry registry;
//		std::vector<Particle> particles;
//		// Create a collision detection object
//		CollisionDetection collisionDetection(particles);
//
//		// Create some particles
//		Particle particle1;
//		particle1.position = Vector3(0, 0, 0);
//		particle1.radius = 1;
//
//		Particle particle2;
//		particle2.position = Vector3(2, 0, 0);
//		particle2.radius = 1;
//
//		Particle particle3;
//		particle3.position = Vector3(5, 0, 0);
//		particle3.radius = 1;
//
//		particles.push_back(particle1);
//		particles.push_back(particle2);
//		particles.push_back(particle3);
//
//		// Check collisions
//		collisionDetection.CheckCollisions();
//
//		// Get the number of registered contacts
//		auto& contacts = collisionDetection.GetContacts();
//
//		// Validate the test
//		// In this example, particle1 and particle2 are colliding, while particle2 and particle3 are not colliding
//		// So, we expect to have one contact registered
//		if (contacts.size() != 1)
//		{
//			std::cout << "Collision test failed!" << std::endl;
//			return false;
//		}
//	}
//
//	auto new_test9 = Test("Test_CollisionDetection", Test_CollisionDetection);
//
//
//}
//
