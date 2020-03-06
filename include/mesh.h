#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class Vertex {
public:
	Vertex (const glm::vec2& pos) {
		this->pos = pos;
	}
public:
	glm::vec2 pos;
};

class Mesh {
public:
	Mesh (Vertex* vertices, unsigned int numVertices);
	virtual ~Mesh ();

	// Draw the mesh onto the buffer
	void draw ();
private:
	// Enumerator for each buffer
	enum {
		POSITION_VB=0u,
		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject = 0u;					// GPU pointer to vertex array object
	GLuint m_vertexArrayBuffers[NUM_BUFFERS] = { 0u };	// GPU pointers to the vertex array buffers
	unsigned int m_drawCount = 0u;						// 
};

#endif