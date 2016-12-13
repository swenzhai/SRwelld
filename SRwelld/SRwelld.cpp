// SRwelld.cpp : 定义 DLL 应用程序的导出函数。
//
#define SRWELL_EXPORTS
#include "stdafx.h"
#include "SRwelld.h"

#include "include\imgproc_c.h"
#pragma comment(lib,"lib\\zlib.lib")
#pragma comment(lib,"lib\\IlmImf.lib")
#pragma comment(lib,"lib\\libtiff.lib")
#pragma comment(lib,"lib\\libjasper.lib")
#pragma comment(lib,"lib\\opencv_core2413.lib")
#pragma comment(lib,"lib\\opencv_imgproc2413.lib")

IplImage *src = 0;
IplImage *dst = 0;

SRWELLD_API int __stdcall srCreateResizeCoef(BYTE * pSrc, BITMAPINFO * pBmpInfo, BYTE ** pDst, double scale)
{
	if (!pSrc || !pBmpInfo || !pDst)
		return -1;
	if (scale < 0 || scale >10)
		return -2;
	if (pBmpInfo->bmiHeader.biWidth <= 0 || pBmpInfo->bmiHeader.biHeight <= 0 || pBmpInfo->bmiHeader.biBitCount <= 0 || pBmpInfo->bmiHeader.biPlanes <= 0)
		return -3;
	if (src || dst)
		return -4;

	CvSize dst_cvsize;
	src = cvCreateImageHeader(cvSize(pBmpInfo->bmiHeader.biWidth, pBmpInfo->bmiHeader.biHeight),
		pBmpInfo->bmiHeader.biBitCount, pBmpInfo->bmiHeader.biPlanes);
	
	//widthStep 4字节对齐
	int widthStep = (4 - (pBmpInfo->bmiHeader.biWidth*pBmpInfo->bmiHeader.biPlanes-1) % 4) 
		+ pBmpInfo->bmiHeader.biWidth*pBmpInfo->bmiHeader.biPlanes;
	cvSetData(src, pSrc, widthStep);

	dst_cvsize.width = (int)(src->width*scale);
	dst_cvsize.height = (int)(src->height*scale);
	dst = cvCreateImage(dst_cvsize, src->depth, src->nChannels);
	*pDst = (BYTE*)dst->imageDataOrigin;

	return 0;
}

SRWELLD_API int __stdcall srResize(int method)
{
	if (method < 0 || method>4)
		return -1;
	if (!src || !dst)
		return -2;
	cvResize(src, dst, method);
	return  0;
}

SRWELLD_API int __stdcall srReleaseResizeCoef()
{
	//release buffer
	if (!src || !dst)
		return -1;
	cvReleaseImageHeader(&src);
	cvReleaseImage(&dst);
	src = dst = 0;
	return  0;
}

SRWELLD_API int __stdcall srAbout()
{
	MessageBox(NULL, TEXT("Copy Right: Shenzhen Welld CO,.Ltd\n SR Module.\n Version 1.0"),TEXT("About"), MB_OK);
	return 0;
}
