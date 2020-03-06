#include "shader.h"

#include <iostream>
#include <fstream>

// Loads the shader file into a single std::string object and returns it
static std::string loadShader (const std::string& fileName);

// Create shader from the text
static GLuint createShader (const std::string& text, GLenum shaderType);

// Checks for errors in the shaders and throws an exception if one is found
static void checkShaderError (GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

Shader::Shader (const std::string& fileName) {
	// Allocate memory for the shader program
	m_program = glCreateProgram ();
	
	// Read the shader files
	m_shaders[VERTEX_SHADER]   = createShader (loadShader (fileName + ".vert"), GL_VERTEX_SHADER);
	m_shaders[FRAGMENT_SHADER] = createShader (loadShader (fileName + ".frag"), GL_FRAGMENT_SHADER);

	// Add shaders to the program
	for (unsigned int i = VERTEX_SHADER; i < NUM_SHADERS; i++)
		glAttachShader (m_program, m_shaders[i]);

	// Bind the fragment shader attribute outColor to the program
	//		Program GPU pointer
	//		Index of buffer to write to, 0 for color
	//		Name of attribute
	glBindFragDataLocation (m_program, 0, "outColor");

	// Bind the attribute 'position' to the program
	glBindAttribLocation (m_program, 0, "position");
	
	// Link the program
	glLinkProgram (m_program);
	checkShaderError (m_program, GL_LINK_STATUS, true, "Error: Shader program linking failed");

	// Validate the program
	glValidateProgram (m_program);
	checkShaderError (m_program, GL_VALIDATE_STATUS, true, "Error: Shader program is invalid");
}

Shader::~Shader () {
	// Detatch shaders from the program and delete them from the GPU memory
	for (unsigned int i = VERTEX_SHADER; i < NUM_SHADERS; i++) {
		glDetachShader (m_program, m_shaders[i]);
		glDeleteShader (m_shaders[i]);
	}

	// Deletet the program from the GPU memory
	glDeleteProgram (m_program);
}

void Shader::bind () {
	// Use this shader program
	glUseProgram (m_program);
}

static std::string loadShader (const std::string& fileName) {
	std::ifstream file;
	file.open (fileName);

	std::string output;
	std::string line;

	if (file.is_open ()) {
		while (file.good ()) {
			getline (file, line);
			output.append (line + "\n");
		}
	}
	else {
		throw std::string ("Unable to load shader: ") + fileName;
	}

	file.close ();
	return output;
}

static GLuint createShader (const std::string& text, GLenum shaderType) {
	GLuint shader = glCreateShader (shaderType);

	// Check  if the shader was created
	if (shader == 0)
		throw std::string ("Error: Shader creation failed");

	// OpenGL being a C library, needs the text as a character array
	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringsLengths[1];
	
	// Load the shader
	shaderSourceStrings[0] = text.c_str ();
	shaderSourceStringsLengths[0] = (text.length());
	glShaderSource (shader, 1, shaderSourceStrings, shaderSourceStringsLengths);

	// Compile the shader
	glCompileShader (shader);

	// Check for compilation errors
	checkShaderError (shader, GL_COMPILE_STATUS, false, "Error: Shader failed to compile");

	return shader;
}

static void checkShaderError (GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
	// Error flag
	GLint success = 0;
	// Error message
	GLchar error[1024] = { 0 };

	// Check if there was an error
	if (isProgram)
		glGetProgramiv (shader, flag, &success);
	else
		glGetShaderiv (shader, flag, &success);

	// If there was an error, get the error log and throw it as an exception
	if (success == GL_FALSE) {
		if (isProgram)
			glGetProgramInfoLog (shader, sizeof (error), NULL, error);
		else
			glGetShaderInfoLog (shader, sizeof (error), NULL, error);

		throw errorMessage + ": '" + std::string (error) + "'";
	}
}

