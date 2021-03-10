
// OpenCameraDlg.h : ͷ�ļ�
//

#pragma once


// COpenCameraDlg �Ի���
class COpenCameraDlg : public CDialogEx
{
// ����
public:

	COpenCameraDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_OPENCAMERA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
