#include <iostream>
#include <string>

#include "display.h"
#include "mesh.h"
#include "shader.h"

#define WINDOW_WIDTH  1024
#define WINDOW_HEIGHT 576

int main (int argc, char** argv) {
	try {
		// Create the display object
		Display display (WINDOW_WIDTH, WINDOW_HEIGHT, "Mandelbrot Set");

		Vertex vertices[] = {	Vertex (glm::vec2 (-1.f,-1.f)),
								Vertex (glm::vec2 (-1.f, 1.f)),
								Vertex (glm::vec2 ( 1.f, 1.f)),
								Vertex (glm::vec2 ( 1.f, -1.f)),
							};

		Mesh mesh (vertices, sizeof (vertices) / sizeof (vertices[0]));

		Shader mandelbrotShader ("./res/mandelbrot-shader");

		// Window update loop
		while (!display.isClosed ()) {
			display.clear (0.f, 0.f, 0.f, 1.0f);

			mandelbrotShader.bind ();
			
			mandelbrotShader.setFloat ("r", (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT);
			mandelbrotShader.setFloat ("s", 0.01f);
			mandelbrotShader.setFloat ("center", -0.761574f, -0.0847596f);

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
