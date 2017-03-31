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

//format change from 1-plane to 3-plane
struct PaletteEntry
{
	unsigned char b, g, r, a;
};
#define WRITE_PIX( ptr, clr )       \
    (((uchar*)(ptr))[0] = (clr).b,  \
     ((uchar*)(ptr))[1] = (clr).g,  \
     ((uchar*)(ptr))[2] = (clr).r)
inline uchar* FillColorRow8(uchar* data, uchar* indices, int len, PaletteEntry* palette)
{
	uchar* end = data + len * 3;
	while ((data += 3) < end)
	{
		*((PaletteEntry*)(data - 3)) = palette[*indices++];
	}
	PaletteEntry clr = palette[indices[0]];
	WRITE_PIX(data - 3, clr);
	return data;
}

static IplImage *src = 0;
static IplImage *dst = 0;
static BITMAPINFO BmpInfoDst;
static PaletteEntry* color_palette;
static uchar  gray_palette[256];
static uchar* src_data;
static uchar* resizeSrc = NULL;//in heap
static int nWidth, nHeight;
SRWELLD_API int __stdcall srCreateResizeCoef(BYTE * pSrc, BITMAPINFO * pBmpInfo, BYTE ** pDst, BITMAPINFO ** pBmpInfoDst, double scale)
{
	//error detect
	if (!pSrc || !pBmpInfo || !pDst || !pBmpInfoDst)
		return -1;
	if (scale < 0 || scale >10)
		return -2;
	if (pBmpInfo->bmiHeader.biWidth <= 0 || pBmpInfo->bmiHeader.biHeight <= 0 || pBmpInfo->bmiHeader.biBitCount <= 0 || pBmpInfo->bmiHeader.biPlanes <= 0)
		return -3;
	if (src || dst)
		return -4;
	//image format chang from 1-channel to 3-channel && coefficient prepare
	color_palette = (PaletteEntry*)&pBmpInfo->bmiColors[0].rgbBlue;
	//new bmpinfo
	nWidth = pBmpInfo->bmiHeader.biWidth;
	nHeight = pBmpInfo->bmiHeader.biHeight;
	BmpInfoDst.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	BmpInfoDst.bmiHeader.biWidth = nWidth*scale;
	BmpInfoDst.bmiHeader.biHeight = nHeight*scale;
	BmpInfoDst.bmiHeader.biPlanes = 1;
	BmpInfoDst.bmiHeader.biBitCount = 24;
	BmpInfoDst.bmiHeader.biCompression = BI_RGB;
	BmpInfoDst.bmiHeader.biSizeImage = 0;// (DWORD)nHeight* scale * (DWORD)nWidth * scale * 3;
	BmpInfoDst.bmiHeader.biXPelsPerMeter = 0;
	BmpInfoDst.bmiHeader.biYPelsPerMeter = 0;
	BmpInfoDst.bmiHeader.biClrUsed = 0;
	BmpInfoDst.bmiHeader.biClrImportant = 0;
	*pBmpInfoDst = &BmpInfoDst;

	//src prepare
	src = cvCreateImageHeader(cvSize(pBmpInfo->bmiHeader.biWidth, pBmpInfo->bmiHeader.biHeight),
		IPL_DEPTH_8U, 3);
	volatile int widthStep = (pBmpInfo->bmiHeader.biWidth * 3 * 4 +3) / 4;//widthStep 4字节对齐
	src_data = pSrc;
	resizeSrc = (uchar*)malloc((nWidth+3)*nHeight * 3);//guarantee memory enough
	cvSetData(src, resizeSrc, widthStep);

	//dst prepare
	CvSize dst_cvsize;
	dst_cvsize.width = (int)(src->width*scale);
	dst_cvsize.height = (int)(src->height*scale);
	dst = cvCreateImage(dst_cvsize, IPL_DEPTH_8U, 3);
	*pDst = (BYTE*)dst->imageDataOrigin;
	return 0;
}

SRWELLD_API int __stdcall srResize(int method)
{
	//error detect
	if (method < 0 || method>4)
		return -1;
	if (!src || !dst)
		return -2;
	//format change process
	uchar *src_t = src_data;
	uchar *resizeSrc_t = resizeSrc;
	int step = nWidth * 3;
	int  src_pitch = ((nWidth*8 + 7) / 8 + 3) & -4;
	for (int y = 0; y < nHeight; y++, resizeSrc_t += step, src_t += src_pitch)
	{
		FillColorRow8(resizeSrc_t, src_t, nWidth, color_palette);
	}
	//resize
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
	free(resizeSrc);
	resizeSrc = NULL;
	return  0;
}

SRWELLD_API int __stdcall srAbout()
{
	MessageBox(NULL, TEXT("Copy Right: Shenzhen Welld CO,.Ltd\n SR Module.\n Version 2.0"),TEXT("About"), MB_OK);
	return 0;
}




