#include "texture.h"
#include "stb_image.h"
#include <iostream>

Texture::Texture(const std::string& fileName)
{
	int width, height, numComponents;
    unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);
	int nwidth, nheight;
	nwidth = (int)(width * 0.75);
	nheight = (int)(height * 0.75);
	int size = width * height * 4 * 50;
	unsigned char* data3d = new unsigned char[size];
	if (data == NULL) {
		std::cerr << "Unable to load texture: " << fileName << std::endl;
		return;
	}

	m_puTextureIDs = new GLuint[50];
	glGenTextures(1, m_puTextureIDs);

	//faster way is to use subranges i.e. data[0:14][3:17] and add it to data3d 
	//all at once for each slice instead of pixel by pixel
	for (int nIndx = 0; nIndx < size; nIndx++)
	{
		data3d[nIndx] = data[nIndx % (width * height * 4)];
	}

	glBindTexture(GL_TEXTURE_3D, *m_puTextureIDs);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, nwidth, nheight, 50, 0, GL_RGBA, GL_UNSIGNED_BYTE, data3d);

	stbi_image_free(data);
	stbi_image_free(data3d);

	//glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_GREATER, 0.5f);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Texture::~Texture()
{
	glDeleteTextures(1, m_puTextureIDs);
}

void Texture::Bind()
{
	glEnable(GL_TEXTURE_3D);
	glBindTexture(GL_TEXTURE_3D, *m_puTextureIDs);
}
