#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

#include <SDL2/SDL.h>

class Display {
public:
	Display (int width, int height, const std::string& title);
	virtual ~Display ();

	// Clear the window with a color
	void clear (float r, float g, float b, float a);
	// Update the display
	void update ();
private:
	SDL_Window* m_window = nullptr;			// Pointer to SDL Window object
	SDL_GLContext m_glContext = nullptr;	// Pointer to GLContext object
};

#endif