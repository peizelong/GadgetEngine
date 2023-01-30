#include <iostream>
#include "engine/engine.h"


int main() {

	GE::Engine engine;

	engine.initEngine();
	engine.run();
	engine.destroy();



	return 0;
}