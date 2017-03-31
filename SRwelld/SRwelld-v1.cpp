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
	volatile int widthStep = (4-1 - (pBmpInfo->bmiHeader.biWidth*pBmpInfo->bmiHeader.biPlanes-1) % 4) 
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

//format change from 1-plane to 3-plane

uchar* FillGrayRow8(uchar* data, uchar* indices, int len, uchar* palette)
{
	int i;
	for (i = 0; i < len; i++)
	{
		data[i] = palette[indices[i]];
	}
	return data + len;
}

#define  SCALE  14
#define  cR  (int)(0.299*(1 << SCALE) + 0.5)
#define  cG  (int)(0.587*(1 << SCALE) + 0.5)
#define  cB  ((1 << SCALE) - cR - cG)
#define  descale(x,n)  (((x) + (1 << ((n)-1))) >> (n))

void icvCvt_BGR2Gray_8u_C3C1R(const uchar* rgb, int rgb_step,
	uchar* gray, int gray_step,
	CvSize size, int _swap_rb)
{
	int i;
	int swap_rb = _swap_rb ? 2 : 0;
	for (; size.height--; gray += gray_step)
	{
		for (i = 0; i < size.width; i++, rgb += 3)
		{
			int t = descale(rgb[swap_rb] * cB + rgb[1] * cG + rgb[swap_rb ^ 2] * cR, SCALE);
			gray[i] = (uchar)t;
		}

		rgb += rgb_step - size.width * 3;
	}
}
struct PaletteEntry
{
	unsigned char b, g, r, a;
};
void CvtPaletteToGray(const PaletteEntry* palette, uchar* grayPalette, int entries)
{
	int i;
	for (i = 0; i < entries; i++)
	{
		icvCvt_BGR2Gray_8u_C3C1R((uchar*)(palette + i), 0, grayPalette + i, 0, cvSize(1, 1),0);
	}
}


