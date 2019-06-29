#pragma once
#include "StdAfx.h"

class CRawDataProcessor
{
public:
    CRawDataProcessor(void);
    virtual ~CRawDataProcessor(void);
    // Call this only after the open gl is initialized.
	size_t read_file(const char* filename, char* text, size_t len);
    bool ReadFile(LPCTSTR lpFileName_i, int nWidth_i, int nHeight_i, int nSlices_i );
    int GetTexture3D()
    {
        return m_nTexId;
    }
    const int GetWidth()
    {
        return m_uImageWidth;
    }
    const int GetHeight()
    {
        return m_uImageHeight;
    }
    const int GetDepth()
    {
        return m_uImageCount;
    }

private:

    int m_uImageCount;
    int m_uImageWidth;
    int m_uImageHeight;
    int m_nTexId;
};

