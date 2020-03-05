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

	glEnableVertexAttribArray (0);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glDisableVertexAttribArray (0);

	// Stop binding instructions to this vertex array object
	glBindVertexArray (0);
}

Mesh::~Mesh () {
	// Free data on the GPU for the vertex array object
	glDeleteVertexArrays (1, &m_vertexArrayObject);
}

void Mesh::draw () {
	glBindVertexArray (m_vertexArrayObject);

	glDrawArrays (GL_TRIANGLES, 0, m_drawCount);

	glBindVertexArray (0);
}