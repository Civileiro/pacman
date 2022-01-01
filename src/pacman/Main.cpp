
#include <iostream>
#include <pacman/Pacman.hpp>

int main() {
	try {

		Pacman pac {};
		pac.engineInit();

	} catch (std::runtime_error e) {
		std::cout << e.what();
	}

	return 0;
}
