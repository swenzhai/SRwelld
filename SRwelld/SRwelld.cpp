// SRwelld.cpp : 定义 DLL 应用程序的导出函数。
//
#define SRWELLD_EXPORTS
#include "stdafx.h"
#include "SRwelld.h"
#include "srRGB.hpp"
#include "srGrey.hpp"


SRWELLD_API int __stdcall srCreateResizeCoef(
	BYTE * pSrc, BITMAPINFO * pBmpInfo, BYTE ** pDst, BITMAPINFO ** pBmpInfoDst, double scale,
	int rgb_or_grey,int *hSR)
{
	srBase* a;
	HRESULT h;
	if (rgb_or_grey == SR_IS_RGB) {
		a = new srRGB;
	}
	else if (rgb_or_grey == SR_IS_GREY) {
		a = new srGrey;
	}
	else return -1;
	try {
		*hSR = (int)a;
		h = a->srCreateResizeCoef(pSrc, pBmpInfo, pDst, pBmpInfoDst, scale);
	}
	catch (...) {

	}
	

	return h;
	
}

SRWELLD_API int __stdcall srResize(int *hSR,int method)
{
	if (hSR == NULL || *hSR == NULL) return -1;
	HRESULT h;
	try {
		srBase* a = (srBase*)*hSR;
		h = a->srResize(method);
	}
	catch (...) {

	}
	return  h;
}

SRWELLD_API int __stdcall srReleaseResizeCoef(int *hSR)
{
	if (hSR == NULL || *hSR == NULL) return -1;
	HRESULT h;
	try {
		srBase* a = (srBase*)*hSR;
		h = a->srReleaseResizeCoef();
		delete a;
		*hSR = NULL;
	}
	catch (...) {

	}
	return  h;
}

SRWELLD_API int __stdcall srAbout()
{
	MessageBox(NULL, TEXT("Copy Right: Shenzhen Welld CO,.Ltd\n SR Module.\n Version 3.0"),TEXT("About"), MB_OK);
	return 0;
}




