#include <iostream>
#include <string>

#include "display.h"

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

int main (int argc, char** argv) {
	try {
		// Create the display object
		Display display (WINDOW_WIDTH, WINDOW_HEIGHT, "Mandelbrot Set");

		// Window update loop
		while (!display.isClosed ()) {
			display.update ();
		}

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
