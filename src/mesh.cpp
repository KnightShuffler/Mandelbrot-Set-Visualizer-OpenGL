#include "mesh.h"

Mesh::Mesh (Vertex* vertices, unsigned int numVertices) {
	//
	m_drawCount = numVertices;

	// Allocate data on the GPU for one vertex array object
	glGenVertexArrays (1, &m_vertexArrayObject);

	// Bind the following instructions for this vertex array object
	glBindVertexArray (m_vertexArrayObject);

	// Generate the GPU data buffers
	glGenBuffers (NUM_BUFFERS, m_vertexArrayBuffers);

	// Copy the vertices array to the GPU
	glBindBuffer (GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData (GL_ARRAY_BUFFER, numVertices * sizeof (vertices[0]), vertices, GL_STATIC_DRAW);

	// Enable the position attribute to be read
	glEnableVertexAttribArray (0);
	// Tell the GPU how to read the data:
	//		Attribute index
	//		Size of attribute vector (1-4)
	//		Data type of attribute vector
	//		Should the GPU Normalize integer data?
	//		Size of the vertex in bytes, tells the GPU how far to jump to get to the next attribute, can use 0 if tightly packed
	//		Offset pointer: number of bytes to skip in reading the vertex data
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, sizeof (vertices[0]), (void*)0);
	//glDisableVertexAttribArray (0);

	// Stop binding instructions to this vertex array object
	glBindVertexArray (0);
}

Mesh::~Mesh () {
	// Free data on the GPU for the vertex array object
	glDeleteVertexArrays (1, &m_vertexArrayObject);
}

void Mesh::draw () {
	// Bind the GPU to draw this vertex array
	glBindVertexArray (m_vertexArrayObject);

	// Draw it as a quad
	glDrawArrays (GL_QUADS, 0, m_drawCount);

	// Unbind the vertex array
	glBindVertexArray (0);
}