# SRwelld
super resolution of 8-bit (0-255) bitmap

## release
- [x] change the Bitmap from 8-bit to 24-bit(RGB), then resize the Image
## note

	1. OpenCV的resize功能：有理数倍的横向和纵向都可放大，且进行了如：
		多线程并行处理优化、SSE||AVX指令集优化；
  2. OpenCV的LoadImage功能：
  根据图片格式进行选择处理，用ImageDecoder父类以及BmpDecoder子类来实现格式转换，
  可将8-bit带palette的图像转换成24-bit不带palette的图像，进行同一处理；
  抽取其中的代码用来实现我的format-change

