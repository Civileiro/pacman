
#include "core/Engine.hpp"

#include <iostream>


int main() {
	
	try {

		Engine app {};
		app.startEngine();

	} catch (std::runtime_error e) {
		std::cout << e.what();
	}

	return 0;
}
