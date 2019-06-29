#include <iostream>
#include <SDL2/SDL.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "texture3D.h"
#include "transform.h"
#include "camera.h"
#include "RawDataProcessor.h"
#include "TranformationMgr.h"

static const int DISPLAY_WIDTH = 2400;
static const int DISPLAY_HEIGHT = 1800;
//GLfloat dOrthoSize2 = 1.0f;

int main(int argc, char** argv)
{
	/*
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(369);
	_CrtSetBreakAlloc(368);*/

	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	/*
	//Find the aspect ratio of the window.
	GLdouble AspectRatio = (GLdouble)(DISPLAY_WIDTH) / (GLdouble)(DISPLAY_HEIGHT);
	//glViewport( 0, 0, cx , cy );
	glViewport(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Set the orthographic projection.
	if (DISPLAY_WIDTH <= DISPLAY_HEIGHT)
	{
		glOrtho(-dOrthoSize2, dOrthoSize2, -(dOrthoSize2 / AspectRatio),
			dOrthoSize2 / AspectRatio, 2.0f * -dOrthoSize2, 2.0f * dOrthoSize2);
	}
	else
	{
		glOrtho(-dOrthoSize2 * AspectRatio, dOrthoSize2 * AspectRatio,
			-dOrthoSize2, dOrthoSize2, 2.0f * -dOrthoSize2, 2.0f * dOrthoSize2);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/
	
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
	/*
	Vertex vertices[] =
	{
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1)),

		Vertex(glm::vec3(-1, -1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(0, 0), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 0), glm::vec3(0, -1, 0)),

		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(1, 1), glm::vec3(0, 1, 0)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 0), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 1), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0)),

		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 0), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 1), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0)),
	};
	*/

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

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	//Mesh mesh("C:/Users/Nick/Documents/school work/capstone/redo/Bowl.obj");
	Shader shader("C:/Users/Nick/Documents/school work/capstone/redo/basicShader");
	Texture texture("C:/Users/Nick/Documents/school work/capstone/redo/wood_top2.jpg");
	//CRawDataProcessor* m_pRawDataProc = new CRawDataProcessor();
	//CTranformationMgr* m_pTransform = new CTranformationMgr();
	//CFileDialog objOpenFile(TRUE);
	/*if (IDOK != objOpenFile.DoModal())
	{
		exit(0);
	}*/
	/*objOpenFile.GetPathName()*/
	
	//Texture3D texture3d(m_pRawDataProc, m_pTransform);
	Transform transform;
	Camera camera(glm::vec3(0.0f, 0.0f, -9.0f), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);

	SDL_Event e;
	bool isRunning = true;
	float counter = 0.0f;
	while (isRunning)
	{
		while (SDL_PollEvent(&e))
		{
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
		mesh.Draw();

		display.SwapBuffers();
		SDL_Delay(1);
		counter += 0.001f;
	}

	return 0;
}