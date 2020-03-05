#include <iostream>
#include <string>

#include "display.h"
#include "mesh.h"
#include "shader.h"

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

int main (int argc, char** argv) {
	try {
		// Create the display object
		Display display (WINDOW_WIDTH, WINDOW_HEIGHT, "Mandelbrot Set");

		Vertex vertices[] = {	Vertex (glm::vec3 (-1.f,-1.f, 0.f)),
								Vertex (glm::vec3 (-1.f, 1.f, 0.f)),
								Vertex (glm::vec3 ( 1.f, 1.f, 0.f)),	};

		Mesh mesh (vertices, sizeof (vertices) / sizeof (vertices[0]));

		Shader s ("./res/test-shader");

		// Window update loop
		while (!display.isClosed ()) {
			display.clear (0.15f, 0.3f, 0.0f, 1.0f);

			s.bind ();
			mesh.draw ();
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
