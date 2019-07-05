#include <iostream>
#include <SDL2/SDL.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "texture3D.h"
#include "transform.h"
#include "camera.h"

static const int DISPLAY_WIDTH = 2400;
static const int DISPLAY_HEIGHT = 1800;


int main(int argc, char** argv)
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	
	Vertex vertices[] =
	{
		Vertex(glm::vec3(-1, -1, -1), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec3(0, 1, 0), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(1, 1, -1), glm::vec3(1, 1, 0), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(1, -1, -1), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1)),

		Vertex(glm::vec3(-1, -1, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, -1, 1), glm::vec3(1, 0, 1), glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec3(0, 0, 0), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec3(0, 0, 1), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec3(1, 0, 1), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(1, -1, -1), glm::vec3(1, 0, 0), glm::vec3(0, -1, 0)),

		Vertex(glm::vec3(-1, 1, -1), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec3(1, 1, 0), glm::vec3(0, 1, 0)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec3(0, 0, 1), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec3(0, 1, 1), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec3(0, 1, 0), glm::vec3(-1, 0, 0)),

		Vertex(glm::vec3(1, -1, -1), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec3(1, 0, 1), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec3(1, 1, 0), glm::vec3(1, 0, 0)),
	};

	unsigned int indices[] = { 0, 1, 2,
							  0, 2, 3,

							  6, 5, 4,
							  7, 6, 4,

							  10, 9, 8,
							  11, 10, 8,

							  12, 13, 14,
							  12, 14, 15,

							  16, 17, 18,
							  16, 18, 19,

							  22, 21, 20,
							  23, 22, 20
	};

	//CFileDialog objOpenFile(TRUE);
	/*if (IDOK != objOpenFile.DoModal())
	{
		exit(0);
	}*/
	/*objOpenFile.GetPathName()*/
	Mesh* bowl = new Mesh("./redo/Bowl.obj");
	Mesh* spoon = new Mesh("./redo/Spoon.obj");
	Mesh* box = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Mesh* sphere = new Mesh("./redo/sphere.obj");
	Mesh** meshes = new Mesh*[4];
	meshes[0] = bowl; meshes[1] = spoon; meshes[2] = box; meshes[3] = sphere;
	Mesh *mesh = box;
	Shader shader("./redo/basicShader");
	Texture texture("./redo/wood_top.jpg");

	Transform transform;
	Camera camera(glm::vec3(0.0f, 0.0f, -7.0f), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);

	SDL_Event e;
	bool isRunning = true;
	float counter = 0.0f;

	while (isRunning)
	{
		while (SDL_PollEvent(&e))
		{
			int mnum = display.handleEvent(e);
			if (mnum)
				mesh = meshes[display.handleEvent(e) - 1];
			if (e.type == SDL_QUIT)
				isRunning = false;
		}

		display.Clear(0.0f, 0.0f, 0.0f, 1.0f);

		float sinCounter = sinf(counter);
		float absSinCounter = abs(sinCounter);

		//transform.GetPos()->x = sinCounter;
		transform.GetRot()->y = counter;
		transform.GetRot()->z = -counter;
		
		//transform.GetScale()->x = absSinCounter;
		//transform.GetScale()->y = absSinCounter;

		shader.Bind();
		texture.Bind();
		shader.Update(transform, camera);
		mesh->Draw();

		display.SwapBuffers();
		SDL_Delay(1);
		counter += 0.001f;
	}



	return 0;
}