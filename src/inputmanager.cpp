#include "inputmanager.h"

InputManager::InputManager () {

}

InputManager::~InputManager () {

}

bool InputManager::isKeyDown (unsigned int key) {
    // Check if the key exists
    auto it = m_keyMap.find(key);
    if (it != m_keyMap.end())
        // Return the pressed status
        return it->second;
    
    // If not return false
    return false;
}