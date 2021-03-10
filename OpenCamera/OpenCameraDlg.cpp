
// OpenCameraDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OpenCamera.h"
#include "OpenCameraDlg.h"
#include "afxdialogex.h"
#include "opencv2/opencv.hpp"
#include "CvvImage.h"

#include <opencv2/opencv.hpp>
#include <cstdio>
#include <cstdlib>

using namespace std;
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

	CvCapture* Capture;
	CvCapture* m_Video;
	IplImage* frame;
	IplImage* m_grabframe;
	CRect rect;
	CDC *pDC;
	HDC hDC;
	CWnd *pwnd;
	int ImgNum = 0;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COpenCameraDlg 对话框




COpenCameraDlg::COpenCameraDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COpenCameraDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COpenCameraDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &COpenCameraDlg::On_OpenCamera)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &COpenCameraDlg::OnCloseCamera)
	ON_BN_CLICKED(IDC_BUTTON1, &COpenCameraDlg::OnCaptureImage)
	ON_BN_CLICKED(IDCANCEL, &COpenCameraDlg::OnButtonExit)
END_MESSAGE_MAP()


// COpenCameraDlg 消息处理程序

BOOL COpenCameraDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void COpenCameraDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void COpenCameraDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR COpenCameraDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//打开摄像头
void COpenCameraDlg::On_OpenCamera()
{
	// TODO: 在此添加控件通知处理程序代码


	Capture = cvCreateCameraCapture(0); //打开摄像头，0是默认，1是外接设备
	if (Capture==0)
	{
		MessageBox(_T("无法连接摄像头！！！"));
		return;
	}

	SetTimer(1, 25, NULL); //定时器，定时时间和帧率一致（定时器id，帧率，返回动作）
						//SetTimer函数简单说就是一个定时器函数，可以创建一个定时器并指定间隔时长TLen和回调函数，回调函数默认就是OnTimer函数。
						//实现的效果是每隔TLen时间就产生一个消息调用一次OnTimer函数。
}

//设置定时器
void COpenCameraDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	frame = cvQueryFrame(Capture); //从摄像头或者文件中抓取并返回一帧
	pDC = GetDlgItem(IDC_PIC_STATIC)->GetDC();//GetDlgItem(IDC_PIC_STATIC)意思为获取视频框的句柄（句柄就是指针），获取显示控件的DC
	GetDlgItem(IDC_PIC_STATIC)->GetClientRect(&rect);
	hDC = pDC->GetSafeHdc();//获取显示控件的句柄
	
	// 【1】加载分类器
	// 加载Haar特征检测分类器
	// 将haarcascade_frontalface_alt2.xml拷至项目目录下，便于操作
	//const char *pstrCascadeFileName = "haarcascade_eye_tree_eyeglasses.xml";//检测人眼
	const char *pstrCascadeFileName = "haarcascade_eye_tree_eyeglasses.xml";
	CvHaarClassifierCascade *pHaarCascade = NULL;
	
	pHaarCascade = (CvHaarClassifierCascade *)cvLoad(pstrCascadeFileName);

	if(!pHaarCascade) {
		MessageBox(_T("分类器加载失败！！！"));
		return;
	}

	// 【2】载入图像预处理
	IplImage *pGrayImage = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
	cvCvtColor(frame, pGrayImage, CV_BGR2GRAY); // 转化成灰度图，提高检测速度
	cvResize( pGrayImage, pGrayImage, CV_INTER_LINEAR );//图像放缩，双线性差值 (缺省使用)
	cvEqualizeHist(pGrayImage, pGrayImage);   //直方图均衡化，增加对比度方便处理
	// 标记颜色		
	CvScalar FaceCirclecolors[] = 
	{
		{{0, 0, 255}},
		{{0, 128, 255}},
		{{0, 255, 255}},
		{{0, 255, 0}},
		{{255, 128, 0}},
		{{255, 255, 0}},
		{{255, 0, 0}},
		{{255, 0, 255}}
	};
	
	// 设置缓存区
	CvMemStorage *pcvMStorage = cvCreateMemStorage(0);
	cvClearMemStorage(pcvMStorage);// 创建内存存储器

	// 【3】识别
	double scale_factore = 1.1;
	CvSeq *pcvSeqFaces = cvHaarDetectObjects(pGrayImage, pHaarCascade, pcvMStorage,scale_factore,3,CV_HAAR_DO_CANNY_PRUNING,cvSize(40,40));
	
	// 【4】标记
	for(int i = 0; i <pcvSeqFaces->total; i++)
	{
		//矩形框
		//CvRect* r = (CvRect*)cvGetSeqElem(pcvSeqFaces, i); 
		//Point2f p1=Point2f(r->x,r->y);  //矩形左上角点位
		//Point2f p2=Point2f(r->x+r->height,r->y+r->width);  //矩形右下角点位
		//cvRectangle(frame,p1,p2,Scalar(255,0,0),2);   //矩形框标注人脸位置

		CvRect* r = (CvRect*)cvGetSeqElem(pcvSeqFaces, i);//从矩形框稠密数列中抽取每一个矩形框
		CvPoint center;//定义一个中点
		int radius;//定义一个半径
		center.x = cvRound((r->x + r->width * 0.5));//获取圆心的中心点x,y坐标
		center.y = cvRound((r->y + r->height * 0.5));
		radius = cvRound((r->width + r->height) * 0.25);//简化计算，本来应该是高的一半平方和宽的一半平方，求根号
		cvCircle(frame, center, radius, FaceCirclecolors[i % 8], 2);//画在图片上画圆圈，涂上颜色,使用不同颜色绘制各个face，共八种色
	}
	cvReleaseMemStorage(&pcvMStorage); // 释放缓存

	// 【5】显示
	CvvImage m_CvvImage;
	m_CvvImage.CopyOf(frame, 1); //复制该帧图像   

	m_CvvImage.DrawToHDC(hDC, &rect); //显示到设备的矩形框内

	CDialogEx::OnTimer(nIDEvent);
}



//关闭摄像头
void COpenCameraDlg::OnCloseCamera()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!Capture)
	{
		MessageBox(_T("没有打开摄像头！！！"));
		return;
	}
	KillTimer(1);//释放计时器
	cvReleaseCapture(&Capture);

}

//截取图像
void COpenCameraDlg::OnCaptureImage()
{
	// TODO: 在此添加控件通知处理程序代码
	m_grabframe = frame;

	if (!Capture)
	{
		MessageBox(_T("摄像头已关闭，无法捕捉图像！！！"));
		return;
	}
	
	CString ImagePath=TEXT("E:\\OpencvImage\\");
 
	if (!PathIsDirectory(ImagePath))
 
	{
		CreateDirectory(ImagePath, 0);//不存在则创建
		MessageBox(_T("标定图片文件夹已创建！！！"));
		return;
	}
	char ImagesName[100];
 
	ImgNum = ImgNum + 1;
 
	sprintf_s(ImagesName, "%s%.2d%s", "E:\\OpencvImage\\", ImgNum, ".jpg");
	
	IplImage * m_snap = cvCreateImage(cvGetSize(m_grabframe), m_grabframe->depth, m_grabframe->nChannels);//(大小，深度，通道数)
	cvCopy(m_grabframe, m_snap, NULL);
	cvSaveImage(ImagesName, m_snap); //把图像写入指定文件夹的文件中去
 
	//完成图像的显示过程
	pDC = GetDlgItem(IDC_PIC1_STATIC)->GetDC();//GetDlgItem(IDC_PIC1_STATIC)意思为获取图片框的句柄（句柄就是指针），获取显示控件的DC
 
	GetDlgItem(IDC_PIC1_STATIC)->GetClientRect(&rect);
 
	hDC = pDC->GetSafeHdc();//获取显示控件的句柄
 
	CvvImage m_CvvImage;
	m_CvvImage.CopyOf(m_snap, 1); //复制该帧图像   
	m_CvvImage.DrawToHDC(hDC, &rect); //显示到显示图片的矩形框内

}

//退出程序
void COpenCameraDlg::OnButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(IDCANCEL);
}
	


