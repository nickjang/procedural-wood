#include "texture3D.h"
#include "RawDataProcessor.h"
#include "TranformationMgr.h"

GLfloat dOrthoSize = 1.0f;

#define MAP_3DTEXT( TexIndex ) \
            glTexCoord3f(0.0f, 0.0f, ((float)TexIndex+1.0f)/2.0f);  \
        glVertex3f(-dOrthoSize,-dOrthoSize,TexIndex);\
        glTexCoord3f(1.0f, 0.0f, ((float)TexIndex+1.0f)/2.0f);  \
        glVertex3f(dOrthoSize,-dOrthoSize,TexIndex);\
        glTexCoord3f(1.0f, 1.0f, ((float)TexIndex+1.0f)/2.0f);  \
        glVertex3f(dOrthoSize,dOrthoSize,TexIndex);\
        glTexCoord3f(0.0f, 1.0f, ((float)TexIndex+1.0f)/2.0f);  \
        glVertex3f(-dOrthoSize,dOrthoSize,TexIndex);

Texture3D::Texture3D(CRawDataProcessor* pRawDataProc_i, CTranformationMgr* pTransformationMgr_i)
{
	m_pRawDataProc = pRawDataProc_i;
	m_pTransformMgr = pTransformationMgr_i;
	LPCTSTR lpFileName_i = "C:/Users/Nick/Downloads/head256x256x109";
	m_pRawDataProc->ReadFile(lpFileName_i, 256, 256, 109);
}

Texture3D::~Texture3D()
{
}

void Texture3D::Bind()
{
	glEnable( GL_ALPHA_TEST );
    glAlphaFunc( GL_GREATER, 0.5f );
	/*
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	*/
    // A scaling applied to normalize the axis 
    // (Usually the number of slices will be less so if this is not - 
    // normalized then the z axis will look bulky)
    // Flipping of the y axis is done by giving a negative value in y axis.
    // This can be achieved either by changing the y co ordinates in -
    // texture mapping or by negative scaling of y axis
   /* glScaled( (float)m_pRawDataProc->GetWidth()/(float)m_pRawDataProc->GetWidth(), 
        -1.0f*(float)m_pRawDataProc->GetWidth()/(float)(float)m_pRawDataProc->GetHeight(), 
        (float)m_pRawDataProc->GetWidth()/(float)m_pRawDataProc->GetDepth());*/

    

    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D,  m_pRawDataProc->GetTexture3D());

	/*
    for ( float fIndx = -1.0f; fIndx <= 1.0f; fIndx+=0.01f )
    {
        glBegin(GL_QUADS);
            MAP_3DTEXT( fIndx );
        glEnd();
     }
	 */
}
