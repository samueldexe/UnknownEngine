
#include <iostream>

#include "UnknownEngine/Engine.h"
#include "UnknownEngine/InputSystem.h"
#include "UnknownEngine/ComponentManager.h"
#include "UnknownEngine/EntityManager.h"
#include "UnknownEngine/SystemManager.h" 

int main() {
	
	UnknownEngine::Engine engine; 

	engine.Run(); 

	int Player = engine.getEntityManager().CreateEntity(); 

	return 0;  
}
