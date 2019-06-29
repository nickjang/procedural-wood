#include "RawDataProcessor.h"
#include <GL\glew.h>
#include <iostream>
#include <stdlib.h>
#include <string>

CRawDataProcessor::CRawDataProcessor(void) : 
m_uImageWidth(0)
,m_uImageHeight(0)
,m_uImageCount(0)
,m_nTexId(0)
{
}


CRawDataProcessor::~CRawDataProcessor(void)
{
    // If not initialized, then this will be zero. So no checking is needed.
    if( 0 != m_nTexId )
    {
        glDeleteTextures( 1, (GLuint*)&m_nTexId );
    }
}

size_t CRawDataProcessor::read_file(const char* filename, char* text, size_t len)
{
	size_t rc = -1;
	FILE* fp = fopen(filename, "r");
	if (fp)
	{
		rc = fread(text, sizeof(char), len, fp);
		text[rc - 1] = '\0'; /* force null termination */
		fclose(fp);
	}
	else
	{
		fprintf(stderr, "Error could not open %s: %s\n",
			filename, strerror(errno));
	}
	return rc;
}

bool CRawDataProcessor::ReadFile(LPCTSTR lpFileName_i, int nWidth_i, int nHeight_i, int nSlices_i )
{


	CFile Medfile;
	if (!Medfile.Open(lpFileName_i, CFile::modeRead))
	{
		return false;
	}


    // File has only image data. The dimension of the data should be known.
    m_uImageCount = nSlices_i;
    m_uImageWidth = nWidth_i;
    m_uImageHeight = nHeight_i;



    
    

	// Holds the texture IDs.
	int* m_puTextureIDs = new int[m_uImageCount];

	// Holds the luminance buffer
	//char* chBuffer;
	int* chBuffer;
	// Holds the RGBA buffer
	int* pRGBABuffer;
	glGenTextures(m_uImageCount, (GLuint*)m_puTextureIDs);

	for (int nIndx = 0; nIndx < m_uImageCount; ++nIndx)
	{
		// Read the frame
		//chBuffer = new char[m_uImageWidth * m_uImageHeight];
		//pRGBABuffer = new char[m_uImageWidth * m_uImageHeight * 4];
		//Medfile.Read(chBuffer, m_uImageWidth * m_uImageHeight);
		chBuffer = new int[256 * 256];
		pRGBABuffer = new int[256 * 256 *4];
		for (int i = 0; i < 256 * 256; i++) {
			chBuffer[i] = 220;
		}

		// Set the properties of the texture.
		glBindTexture(GL_TEXTURE_2D, m_puTextureIDs[nIndx]);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Convert the data to RGBA data.
		// Here we are simply putting the same value to R, G, B and A channels.
		// Usually for raw data, the alpha value will
		// be constructed by a threshold value given by the user 
		//std::cout << m_uImageCount << std::endl;
		
		for (int nIndx = 0; nIndx < m_uImageWidth * m_uImageHeight; ++nIndx)
		{
			//std::cout << (int)chBuffer[nIndx] << std::endl;
			pRGBABuffer[nIndx * 4] = chBuffer[nIndx];
			pRGBABuffer[nIndx * 4 + 1] = chBuffer[nIndx];
			pRGBABuffer[nIndx * 4 + 2] = chBuffer[nIndx];
			pRGBABuffer[nIndx * 4 + 3] = 255;
			if (chBuffer[nIndx] < 20)
			{
				pRGBABuffer[nIndx * 4 + 3] = 0;
			}
		}
		//std::cout << "ok" << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_uImageWidth, m_uImageHeight, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)pRGBABuffer);
		glBindTexture(GL_TEXTURE_2D, 0);
		delete[] chBuffer;
		delete[] pRGBABuffer;
	}
	return true;
}