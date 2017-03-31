#ifndef _SRWELLD_DLL_H
#define _SRWELLD_DLL_H
/*
SRwelld Module
Author�� s.z.
Time: 2016/12/13
version 2.0: 2017.3.31
���ڶ�ͼ��ķŴ���С�����ֲ�ֵ������ѡ
//8-bit image��intel-i3(TM) 2.9Ghz, 2G �ڴ棬winxpϵͳ���ԣ�720*512BYTE linear-resizeʱ��<1ms
24bit image��intel-i3(TM) 2.9Ghz, 2G �ڴ棬winxpϵͳ���ԣ�720*440BYTE linear-resize��2.1����Լ3.5ms //2017.3.31
*/
#ifdef SRWELLD_EXPORTS
#define SRWELLD_API __declspec(dllexport)
#else
#define SRWELLD_API __declspec(dllimport)
#endif


/*
	used to set initial coefficient and memory alloc before srResize function
	pSrc: Դͼ��ָ��
	pBmpInfo	:Դͼ����Ϣ
	pDst:	Ŀ��ͼ��ָ��
	pBmpInfoDst	:Ŀ��BitmapInfo
	scale:	�Ŵ��� >0 && <10 
	success :return 0;
*/
EXTERN_C SRWELLD_API  int __stdcall srCreateResizeCoef(BYTE* pSrc, BITMAPINFO* pBmpInfo,BYTE** pDst, BITMAPINFO ** pBmpInfoDst, double scale);

/*
*	method :can only be set as 0 or 1 or 2 or 3 or 4
		INTER_NN =0 - ����ڲ�ֵ,
		INTER_LINEAR =1 - ˫���Բ�ֵ (ȱʡʹ��)
		INTER_CUBIC =2 - ������ֵ.
		INTER_AREA =3 - ʹ�����ع�ϵ�ز�������ͼ����Сʱ�򣬸÷������Ա��Ⲩ�Ƴ��֡���ͼ��Ŵ�ʱ�������� INTER_NN ����..
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