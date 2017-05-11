#ifndef _SR_GREY_H
#define _SR_GREY_H


#include"srBase.hpp"
class srGrey :public srBase {
public:
	virtual int srCreateResizeCoef(BYTE * pSrc, BITMAPINFO * pBmpInfo, BYTE ** pDst, BITMAPINFO ** pBmpInfoDst, double scale);
	virtual int srResize(int method);
	virtual int srReleaseResizeCoef();
private:
	
};
int srGrey::srCreateResizeCoef(BYTE * pSrc, BITMAPINFO * pBmpInfo, BYTE ** pDst, BITMAPINFO ** pBmpInfoDst, double scale) {
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

	//widthStep 4×Ö½Ú¶ÔÆë
	int widthStep = (pBmpInfo->bmiHeader.biWidth  * 4 + 3) / 4;
	cvSetData(src, pSrc, widthStep);

	dst_cvsize.width = (int)(src->width*scale);
	dst_cvsize.height = (int)(src->height*scale);
	dst = cvCreateImage(dst_cvsize, src->depth, src->nChannels);
	*pDst = (BYTE*)dst->imageDataOrigin;

	return 0;
}
int srGrey::srResize(int method) {
	if (method < 0 || method>4)
		return -1;
	if (!src || !dst)
		return -2;
	cvResize(src, dst, method);
	return  0;
}
int srGrey::srReleaseResizeCoef() {
	//release buffer
	if (!src || !dst)
		return -1;
	cvReleaseImageHeader(&src);
	cvReleaseImage(&dst);
	src = dst = 0;
	return  0;
}

#endif // !_SR_GREY_H