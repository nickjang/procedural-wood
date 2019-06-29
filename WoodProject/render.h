#ifndef RENDER_H
#define RENDER_H

#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

struct Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	INDEX_VB
};

class Render
{
public:
	Render(const std::string& filename);

	void Draw();

	virtual ~Render();
protected:
private:
	Render(const Render& other) {}
	void operator=(const Render& other) {}

	enum
	{
		POSITION_VB,

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
	const aiScene* objScene;


};

#endif // RENDER_H