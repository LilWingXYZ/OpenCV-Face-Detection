#include "highgui.h"
int main( int argc,char** argv ) 
{ 
//IplImage* img = cvLoadImage( argv[0] ); 
IplImage* img = cvLoadImage("E:\\1.jpg" ); //�ļ�·��˫//

cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE ); 
//cvNamedWindow(��Example1��, 0 ); 
cvShowImage("Example1", img ); 
cvWaitKey(0); 
cvReleaseImage( &img );//��Щ������ʾ�ͷ���Դ�����кô��ġ� 
cvDestroyWindow("Example1"); 
} 
