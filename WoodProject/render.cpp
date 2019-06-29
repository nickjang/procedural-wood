#include "render.h"

Render::Render(const std::string& filename)
{
	objScene = aiImportFile(filename.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	m_drawCount = objScene->mMeshes[0]->mNumVertices;

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, objScene->mMeshes[0]->mNumVertices * sizeof(objScene->mMeshes[0]->mVertices[0]), objScene->mMeshes[0]->mVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);

}

Render::~Render()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Render::Draw()
{
	glBindVertexArray(m_vertexArrayObject);

	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

	glBindVertexArray(0);
}
