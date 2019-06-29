#ifndef TEXTURE3D_H
#define TEXTURE3D_H

#include <string>
#include <GL/glew.h>
#include <GL/GL.h>
#include <iostream>
#include "RawDataProcessor.h"
#include "TranformationMgr.h"


class Texture3D
{
public:
	Texture3D(CRawDataProcessor* pRawDataProc_i, CTranformationMgr* pTransformationMgr_i);

	void Bind();

	virtual ~Texture3D();
protected:
private:
	Texture3D(const Texture3D& texture) {}
	void operator=(const Texture3D& texture) {}

	CRawDataProcessor* m_pRawDataProc;
	CTranformationMgr* m_pTransformMgr;
};

#endif
