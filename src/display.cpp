#include "display.h"

#include<GL/glew.h>

Display::Display (int width, int height, const std::string& title)
{
	// Initialize SDL
	SDL_Init (SDL_INIT_EVERYTHING);

	// OpenGL attrributes
	SDL_GL_SetAttribute (SDL_GL_RED_SIZE,     8);	// min  8 bits for RED
	SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE,   8);	// min  8 bits for GREEN
	SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE,    8);	// min  8 bits for BLUE
	SDL_GL_SetAttribute (SDL_GL_ALPHA_SIZE,   8);	// min  8 bits for ALPHA
	SDL_GL_SetAttribute (SDL_GL_BUFFER_SIZE, 32);	// min 32 bits for RGBA pixels
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);	// Use a double buffer

	// Create window
	m_window = SDL_CreateWindow (title.c_str (), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	// Create and link glContext to the window
	m_glContext = SDL_GL_CreateContext (m_window);

	// Initialize GLEW, giving us access to OpenGL functionality in the window
	GLenum status = glewInit ();

	// Throw an exception if failed to initialize
	if (status != GLEW_OK) {
		throw std::string("Glew failed to initialize!");
	}

	// Enable blending
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Display::~Display ()
{
	SDL_GL_DeleteContext (m_glContext);
	SDL_DestroyWindow (m_window);
	SDL_Quit ();
}

void Display::clear (float r, float g, float b, float a) {
	glClearColor (r, g, b, a);
	glClear (GL_COLOR_BUFFER_BIT);
}

void Display::update () {
	// Swap the buffers
	SDL_GL_SwapWindow (m_window);
}