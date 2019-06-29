#include "mesh.h"
#include "util.h"
#include "debugTimer.h"
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <glm/gtx/string_cast.hpp>

Mesh::Mesh(const std::string& fileName)
{
	InitMesh(OBJModel(fileName).ToIndexedModel());
}

void Mesh::InitMesh(const IndexedModel& model)
{
	m_numIndices = model.indices.size();

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.positions[0]) * model.positions.size(), &model.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.texCoords[0]) * model.texCoords.size(), &model.texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.indices[0]) * model.indices.size(), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}
	/*
	for (float fIndx = -1.0f; fIndx <= 1.0f; fIndx += 0.003f)
	{
		model.texCoords.push_back(glm::vec3(0.0f, 0.0f, ((float)fIndx + 1.0f) / 2.0f));
		model.texCoords.push_back(glm::vec3(0.0f, 1.0f, ((float)fIndx + 1.0f) / 2.0f));
		model.texCoords.push_back(glm::vec3(1.0f, 0.0f, ((float)fIndx + 1.0f) / 2.0f));
		model.texCoords.push_back(glm::vec3(1.0f, 1.0f, ((float)fIndx + 1.0f) / 2.0f));
		
	}
	*/
	for (unsigned int i = 0; i < numIndices; i++)
		model.indices.push_back(indices[i]);

	InitMesh(model);
}

Mesh::~Mesh()
{
	glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);

	//glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
	glDrawElementsBaseVertex(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0, 0);

	glBindVertexArray(0);
}
