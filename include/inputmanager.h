#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include<SDL2/SDL.h>

#include<unordered_map>

// Define the keys to use in the program
enum KEYS {
    UP = (unsigned int) SDLK_w,
    DOWN = (unsigned int) SDLK_s,
    LEFT = (unsigned int) SDLK_a,
    RIGHT = (unsigned int) SDLK_d,

    ZOOM_IN = (unsigned int) SDLK_UP,
    ZOOM_OUT = (unsigned int) SDLK_DOWN,

    TURBO = (unsigned int) SDLK_SPACE,

    QUIT = (unsigned int) SDLK_ESCAPE,
};

class InputManager {
public:
    InputManager();
    virtual ~InputManager ();

    // Press the passed key
    void pressKey (unsigned int key) {
        m_keyMap[key] = true;
    }
    // Release the passed key
    void releaseKey (unsigned int key) {
        m_keyMap[key] = false;
    }

    // Check if a key is currently pressed
    bool isKeyDown (unsigned int key) ;

private:
    // Hash map of bools, key ids are the keys
    std::unordered_map<unsigned int, bool> m_keyMap;
};

#endif