#include <iostream>
#include <string>

#include "display.h"

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

int main (int argc, char** argv) {
	try {
		// Create the display object
		Display d (WINDOW_WIDTH, WINDOW_HEIGHT, "Mandelbrot Set");
		
		// Exit loop
		std::cout << "Enter any key to exit..." << std::endl;
		int exit;
		while (std::cin >> exit);

		return 0;
	}
	catch (std::string & ex) {
		std::cerr << ex << std::endl;
		exit (EXIT_FAILURE);
	}
	catch (...) {
		std::cerr << "Unexpected behavior, stopping execution" << std::endl;
		exit (EXIT_FAILURE);
	}
}
