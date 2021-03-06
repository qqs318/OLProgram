//////////////////////////////////////////////////////////////////////////
//
// 创建管件和贯穿孔的对话框
//
// 2016.10.28 by qqs
//
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#define ID_CURCTL_NULL -100;
// CBuildTubeDlg 对话框

class CBuildTubeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBuildTubeDlg)

public:
	CBuildTubeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBuildTubeDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_BUILDTUBE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 管件参数
	//////////////////////////////////////////////////////////////////////////
	double m_dTubeDia;   // 管件直径
	double m_dTubeThick; // 管件厚度
	double m_dTubeLength;// 管件长度
	//////////////////////////////////////////////////////////////////////////

	// 孔参数
	//////////////////////////////////////////////////////////////////////////
	double m_dHoleDia;        // 孔直径
	double m_dHoleXOffset;    // 孔X向偏移距离
	double m_dHoleZOffset;    // 孔Z向偏移距离
	double m_dHoleThroughAng; // 孔贯穿角度
	double m_dHoleRotAng;     // 孔旋转角度
	//////////////////////////////////////////////////////////////////////////

	// 其他参数
	//////////////////////////////////////////////////////////////////////////
	CListCtrl  CHParamListCtrl; // 孔list控件
	CHCombParam* m_pHCombParam; // 当前文档孔参数集合
	int  m_nHoleID;             // 孔ID
	BOOL m_bBulidTube;          // 标记管件是否已经创建
	int m_nCurCtrID;  // 当前激活的控件ID
	BOOL m_bEditMode; // 是否为编辑参数状态
	//////////////////////////////////////////////////////////////////////////
	CMenu m_cMenu ; // 右键菜单

public:
	// 接口函数
	//////////////////////////////////////////////////////////////////////////
	BOOL CheckParam(BOOL bEditMode = FALSE, CHoleParam* pHParam = NULL);// 用于检验参数合理性
	void SetHParamList(CHCombParam* pHCombList); 
	void CorrectParams(); //对路径参数组进行参数调整
	virtual BOOL OnInitDialog();	
	//////////////////////////////////////////////////////////////////////////
public:
	// 消息函数
	//////////////////////////////////////////////////////////////////////////
	afx_msg void OnBnClickedButtonHoleadd();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnDelete();
	afx_msg void OnEdit();
	//////////////////////////////////////////////////////////////////////////
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnSetfocusEditTubedia();
	afx_msg void OnEnKillfocusEditTubedia();
//	CStatic m_cTDia;
	afx_msg void OnEnSetfocusEditTubethick();
	afx_msg void OnEnKillfocusEditTubethick();
	afx_msg void OnEnSetfocusEditTubelength();
	afx_msg void OnEnKillfocusEditTubelength();
	afx_msg void OnEnSetfocusEditHoledia();
	afx_msg void OnEnKillfocusEditHoledia();
	afx_msg void OnEnSetfocusEditHolexoffset();
	afx_msg void OnEnKillfocusEditHolexoffset();
	afx_msg void OnEnSetfocusEditHolezoffset();
	afx_msg void OnEnKillfocusEditHolezoffset();
	afx_msg void OnEnSetfocusEditHolethroughang();
	afx_msg void OnEnKillfocusEditHolethroughang();
	afx_msg void OnEnSetfocusEditHolerotang();
	afx_msg void OnEnKillfocusEditHolerotang();
	afx_msg void OnNMRClickListHParam(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListHparam(NMHDR *pNMHDR, LRESULT *pResult);
};