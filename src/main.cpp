#include <iostream>
#include <string>

#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "inputmanager.h"

#define WINDOW_WIDTH  1024
#define WINDOW_HEIGHT 576

inline bool isMoving (InputManager& im);

int main (int argc, char** argv) {
	try {
		// Create the display object
		Display display (WINDOW_WIDTH, WINDOW_HEIGHT, "Mandelbrot Set");

		// Create input manager
		InputManager inputManager;

		// Flag to close the program
		bool closed = false;

		// Vertices of the screen (normalized device coordinates)
		Vertex vertices[] = {	Vertex (glm::vec2 (-1.f,-1.f)),
								Vertex (glm::vec2 (-1.f, 1.f)),
								Vertex (glm::vec2 ( 1.f, 1.f)),
								Vertex (glm::vec2 ( 1.f, -1.f)),
							};

		// Mesh of the vertices (quad)
		Mesh mesh (vertices, sizeof (vertices) / sizeof (vertices[0]));

		// Shader program linked to the mandelbrot shaders
		Shader mandelbrotShader ("./res/mandelbrot-shader");

		// Uniforms
		float r = (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT;
		float s = 2.f;
		glm::vec2 center(0.f, 0.f);

		displayInfo (center, s);

		// Main loop
		while (!closed) {
			// Output
			if (isMoving (inputManager)) {
				displayInfo (center, s);
			}


			// Clear the display with black color
			display.clear (0.f, 0.f, 0.f, 1.0f);

			// Use the mandelbrot shaders
			mandelbrotShader.bind ();
			
			// Set the uniforms in the shader program
			mandelbrotShader.setFloat ("r", r);
			mandelbrotShader.setFloat ("s", s);
			mandelbrotShader.setFloat ("center", center);

			// Draw the quad to the buffer
			mesh.draw ();
			// Swap the buffer to the display
			display.update ();

			/// Receive input
			SDL_Event e;

			// Poll for events
			while (SDL_PollEvent (&e)) {
				switch (e.type) {
				// Close Window
				case SDL_QUIT:
					closed = true;
					break;
				case SDL_KEYDOWN:
					inputManager.pressKey(e.key.keysym.sym);
					break;
				case SDL_KEYUP:	
					inputManager.releaseKey(e.key.keysym.sym);
					break;
				default:
					break;
				}
			}

			// Handle input
			if (inputManager.isKeyDown(KEYS::UP)) {
				center.y += s*0.1f;
			}
			if (inputManager.isKeyDown(KEYS::DOWN)) {
				center.y -= s*0.1f;
			}
			if (inputManager.isKeyDown(KEYS::LEFT)) {
				center.x -= s*0.1f;
			}
			if (inputManager.isKeyDown(KEYS::RIGHT)) {
				center.x += s*0.1f;
			}
			if (inputManager.isKeyDown(KEYS::QUIT)) {
				closed = true;
			}
			if (inputManager.isKeyDown(KEYS::ZOOM_IN)) {
				s *= 0.9f;
			}
			if (inputManager.isKeyDown(KEYS::ZOOM_OUT)) {
				s *= 1.1f;
			}
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

bool isMoving (InputManager& im) {
	return (im.isKeyDown(KEYS::UP) || 
			im.isKeyDown(KEYS::DOWN) || 
			im.isKeyDown(KEYS::LEFT) || 
			im.isKeyDown(KEYS::RIGHT) || 
			im.isKeyDown(KEYS::ZOOM_IN) || 
			im.isKeyDown(KEYS::ZOOM_OUT)
	);
}