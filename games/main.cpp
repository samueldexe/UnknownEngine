
#include <iostream>

#include "UnknownEngine/Engine.h"
#include "UnknownEngine/InputSystem.h"
#include "UnknownEngine/ComponentManager.h"
#include "UnknownEngine/EntityManager.h"
#include "UnknownEngine/SystemManager.h" 

#include "UnknownEngine/ecs/MeshComponent.h"  

int main() {
	
	UnknownEngine::Engine engine; 

	engine.Initialize();

	int Player = engine.getEntityManager().CreateEntity(); 

	auto meshComponent = std::make_shared<UnknownEngine::MeshComponent>("tree.obj", engine.getContext()); 
	engine.getComponentManager().RegisterComponent(Player, meshComponent); 

	engine.Start();  

	return 0;  
}
