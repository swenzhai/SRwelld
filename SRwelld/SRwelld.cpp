// SRwelld.cpp : 定义 DLL 应用程序的导出函数。
//
#define SRWELLD_EXPORTS
#include "stdafx.h"
#include "SRwelld.h"
#include "srRGB.hpp"
#include "srGrey.hpp"
#include <map>

SRWELLD_API int __stdcall srCreateResizeCoef(
	BYTE * pSrc, BITMAPINFO * pBmpInfo, BYTE ** pDst, BITMAPINFO ** pBmpInfoDst, double scale)
{
	
	return 0;
}

SRWELLD_API int __stdcall srResize(int method)
{
	
	return  0;
}

SRWELLD_API int __stdcall srReleaseResizeCoef()
{

	return  0;
}

SRWELLD_API int __stdcall srAbout()
{
	MessageBox(NULL, TEXT("Copy Right: Shenzhen Welld CO,.Ltd\n SR Module.\n Version 2.0"),TEXT("About"), MB_OK);
	return 0;
}




