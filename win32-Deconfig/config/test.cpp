#include "highgui.h"
int main( int argc,char** argv ) 
{ 
//IplImage* img = cvLoadImage( argv[0] ); 
IplImage* img = cvLoadImage("E:\\1.jpg" ); //文件路径双//

cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE ); 
//cvNamedWindow(“Example1”, 0 ); 
cvShowImage("Example1", img ); 
cvWaitKey(0); 
cvReleaseImage( &img );//这些函数显示释放资源总是有好处的。 
cvDestroyWindow("Example1"); 
} 
