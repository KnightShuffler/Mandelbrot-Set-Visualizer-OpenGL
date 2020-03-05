#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <GL/glew.h>

class Shader {
public:
	Shader (const std::string& fileName);
	virtual ~Shader ();

	// Make the GPU use this shader program
	void bind ();
private:
	enum { 
		VERTEX_SHADER = 0u, 
		FRAGMENT_SHADER, 
		NUM_SHADERS 
	};

	GLuint m_program = 0;				// Pointer to the shader program in GPU memory
	GLuint m_shaders[NUM_SHADERS] = { 0 };	// Pointers to each shader of the program in GPU memory
};

#endif // !SHADER_H
