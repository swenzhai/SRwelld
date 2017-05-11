#ifndef _SR_BASE_H
#define _SR_BASE_H

#include"stdafx.h"
#include "include\imgproc_c.h"
#pragma comment(lib,"lib\\zlib.lib")
#pragma comment(lib,"lib\\IlmImf.lib")
#pragma comment(lib,"lib\\libtiff.lib")
#pragma comment(lib,"lib\\libjasper.lib")
#pragma comment(lib,"lib\\opencv_core2413.lib")
#pragma comment(lib,"lib\\opencv_imgproc2413.lib")

class srBase {
public:
	virtual int srCreateResizeCoef(BYTE * pSrc, BITMAPINFO * pBmpInfo, BYTE ** pDst, BITMAPINFO ** pBmpInfoDst, double scale) =0 ;
	virtual int srResize(int method) = 0;
	virtual int srReleaseResizeCoef() = 0;
	
protected:
	IplImage *src = 0;
	IplImage *dst = 0;
};

#endif