#ifndef _SRWELLD_DLL_H
#define _SRWELLD_DLL_H
/*
SRwelld Module
Author： s.z.
Time: 2016/12/13
version 2.0: 2017.3.31
用于对图像的放大、缩小，五种插值方法可选
//8-bit image在intel-i3(TM) 2.9Ghz, 2G 内存，winxp系统测试，720*512BYTE linear-resize时间<1ms
24bit image在intel-i3(TM) 2.9Ghz, 2G 内存，winxp系统测试，720*440BYTE linear-resize至2.1倍，约3.5ms //2017.3.31
*/
#ifdef SRWELLD_EXPORTS
#define SRWELLD_API __declspec(dllexport)
#else
#define SRWELLD_API __declspec(dllimport)
#endif


/*
	used to set initial coefficient and memory alloc before srResize function
	pSrc: 源图像指针
	pBmpInfo	:源图像信息
	pDst:	目标图像指针
	pBmpInfoDst	:目标BitmapInfo
	scale:	放大倍数 >0 && <10 
	success :return 0;
*/
EXTERN_C SRWELLD_API  int __stdcall srCreateResizeCoef(BYTE* pSrc, BITMAPINFO* pBmpInfo,BYTE** pDst, BITMAPINFO ** pBmpInfoDst, double scale);

/*
*	method :can only be set as 0 or 1 or 2 or 3 or 4
		INTER_NN =0 - 最近邻插值,
		INTER_LINEAR =1 - 双线性插值 (缺省使用)
		INTER_CUBIC =2 - 立方插值.
		INTER_AREA =3 - 使用象素关系重采样。当图像缩小时候，该方法可以避免波纹出现。当图像放大时，类似于 INTER_NN 方法..
		INTER_LANCZOS4 =4 
	success :return 0;
*/
EXTERN_C SRWELLD_API  int __stdcall srResize(int method);

/*
	when you finish using resize function, MUST use this function to release the buffer
	success :return 0;
*/
EXTERN_C SRWELLD_API  int __stdcall srReleaseResizeCoef();

/*
	output dll information
*/
EXTERN_C SRWELLD_API  int __stdcall srAbout();

#endif