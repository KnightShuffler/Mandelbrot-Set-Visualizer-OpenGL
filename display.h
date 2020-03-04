#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

#include <SDL2/SDL.h>

class Display {
public:
	Display (int width, int height, const std::string& title);
	virtual ~Display ();

	// Update the display
	void update ();
private:
	SDL_Window* m_window = nullptr;			// Pointer to SDL Window object
	SDL_GLContext m_glContext = nullptr;	// Pointer to GLContext object
};

#endif