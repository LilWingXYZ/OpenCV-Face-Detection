
// OpenCameraDlg.h : 头文件
//

#pragma once


// COpenCameraDlg 对话框
class COpenCameraDlg : public CDialogEx
{
// 构造
public:

	COpenCameraDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_OPENCAMERA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void On_OpenCamera();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnCloseCamera();
	afx_msg void OnCaptureImage();
	afx_msg void OnButtonExit();
	afx_msg void OnStnClickedPic1Static();
};
