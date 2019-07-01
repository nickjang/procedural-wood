#include "texture.h"
#include "stb_image.h"
#include <iostream>

Texture::Texture(const std::string& fileName)
{
	int width, height, numComponents;
	unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);
	int nwidth, nheight, depth;
	nheight = (int)(height * 0.75);
	nwidth = (int)(width * 0.75);
	depth = std::fmin(nwidth, nheight);
	//nheight = height;
	//nwidth = width;
	int size = nwidth * nheight * 4 * depth;
	unsigned char* data3d = new unsigned char[size];
	if (data == NULL)
		std::cerr << "Unable to load texture: " << fileName << std::endl;

	m_puTextureIDs = new GLuint[depth];
	glGenTextures(1, m_puTextureIDs);

	//faster way is to use subranges i.e. data[0:14][3:17] and add it to data3d 
	//all at once for each slice instead of pixel by pixel
	int imgIndx = -1;
	int xoffset;
	int yoffset;
	int skip = 0;
	double rdm = 0.0;
	for (int nIndx = 0; nIndx < width * height * 4 * depth; nIndx++)
	{
		if (floor(nIndx / (width * height * 4)) > imgIndx)
			rdm = (rand() % 7) / 140.0;
		imgIndx = floor(nIndx / (width * height * 4));
		
		
		//variation in xy movement of image by sin functin and add random (<=.05%) offset for fibers
		//xoffset = floor(abs(sin(rdm + 1.75 + ((double)imgIndx / depth))) * ((double)width - (double)nwidth)) * 4.0;
		xoffset = floor(abs(sin(1.75 + ((double)imgIndx / depth))) * ((double)width - (double)nwidth)) * 4.0;
		//xoffset = 0;
		//yoffset = floor(abs(sin(sin((imgIndx + rdm) /(depth/5.0))/(depth/10.0) + 1.75 + ((double)imgIndx/((depth*2.0)+rdm*2.0)))) * ((double)height - (double)nheight));
		//yoffset = floor(abs(sin(sin((imgIndx) /(depth/5.0))/(depth/10.0) + 1.75 + ((double)imgIndx/((depth*2.0))))) * ((double)height - (double)nheight));
		//xoffset = (width - nwidth) * 4;
		yoffset = (height - nheight);
		//just add to nIndx instead of continuing?
		if ((nIndx % (width * height * 4)) < yoffset * width * 4 && (nIndx % (width * height * 4)) < (height - nheight) * width * 4){
			skip++;
			continue;
		}
		if ((nIndx % (width * height * 4)) % (width * 4) < xoffset && (nIndx % (width * height * 4)) % (width * 4) < (width - nwidth) * 4) {
			skip++;
			continue;
		}
		if ((floor(((nIndx - skip) % (nwidth * nheight * 4)) / (nwidth * 4)) + yoffset) > (int)floor((nIndx % (width * height * 4)) / (width * 4))) {
			skip++;
			continue;
		}
		
		if ((floor((nIndx - skip) / (nwidth * nheight * 4)) > imgIndx) && (nIndx - skip) % (nwidth * nheight * 4) == 0 && nIndx % (width * height * 4) != 0) {
			skip++;
			continue;
		}

		if (floor((nIndx - skip) / (nwidth * nheight * 4)) != imgIndx) {
			std::cout << imgIndx << std::endl;
			std::cout << floor((nIndx - skip) / (nwidth * nheight * 4)) << std::endl;
			std::cerr << "Image indexing issue creating new texture." << std::endl;
		}
	
		/*
		if (floor((pxcount % (nwidth * nheight * 4)) / (nwidth * 4)) + yoffset > floor((nIndx % (width * height)) / width))
			continue;
			*/



		/*
		if (floor((pxcount % (nwidth * nheight * 4)) % (nwidth * 4) / 4.0) + xoffset > (nIndx % (width * height)) % width)
			continue;
		*/
		
		if ((floor(((nIndx - skip) % (nwidth * nheight * 4)) / (nwidth * 4)) + yoffset) != (int)floor((nIndx % (width * height * 4)) / (width * 4))) {
			std::cout << "indx = ";
			std::cout << nIndx << std::endl;
			std::cout << nwidth * nheight * 4 << std::endl;
			std::cout << yoffset << std::endl;
			std::cout << xoffset << std::endl;
			std::cout << (floor(((nIndx - skip) % (nwidth * nheight * 4))/(nwidth * 4)) + yoffset) << std::endl;
			std::cout << floor((nIndx % (width * height * 4)) / (width * 4)) << std::endl;
			std::cerr << "Row indexing issue creating new texture." << std::endl;
		}
		
		// (xoffset * (height - yoffset) + yoffset * width * 4) * (imgIndx + 1);

		data3d[nIndx - skip] = data[nIndx % (width * height * 4)];
	}

	glBindTexture(GL_TEXTURE_3D, *m_puTextureIDs);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, nwidth, nheight, depth, 0, GL_RGBA, GL_UNSIGNED_BYTE, data3d);

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
