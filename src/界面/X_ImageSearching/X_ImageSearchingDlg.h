
// X_ImageSearchingDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CX_ImageSearchingDlg �Ի���
class CX_ImageSearchingDlg : public CDialogEx
{
// ����
public:
	CX_ImageSearchingDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_X_IMAGESEARCHING_DIALOG };

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
	CListCtrl x_listControl;
	CStatic x_picture;
//	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCm();
};

extern void ListFill(CListCtrl& c);//��ʼ���б�ؼ���������ͼƬ���뵽�б�ؼ���extern void outputTheResult();//������ҽ��
