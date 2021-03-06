﻿//////////////////////////////////////////////////////////////////////////
//
//  路径输出设置对话框
//
//  2016.10.28 by qqs
//
//////////////////////////////////////////////////////////////////////////

// ExportDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "EliteSoftWare.h"
#include "ExportDlg.h"
#include "afxdialogex.h"


// CExportDlg 对话框

IMPLEMENT_DYNAMIC(CExportDlg, CDialogEx)

CExportDlg::CExportDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExportDlg::IDD, pParent)
	, m_nExportOrder(0)
	, m_dFixAng(90)
{
}

CExportDlg::~CExportDlg()
{
}

void CExportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FIXANG, m_dFixAng);
	DDV_MinMaxDouble(pDX, m_dFixAng, 0, 360);
}


BEGIN_MESSAGE_MAP(CExportDlg, CDialogEx)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_RADIO_XDIR, &CExportDlg::OnBnClickedRadioXdir)
	ON_BN_CLICKED(IDC_RADIO_ROTANGDIR, &CExportDlg::OnBnClickedRadioRotangdir)
	ON_BN_CLICKED(IDC_RADIO_CUSTOM, &CExportDlg::OnBnClickedRadioCustom)
END_MESSAGE_MAP()


// CExportDlg 消息处理程序


int CExportDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}


void CExportDlg::OnBnClickedRadioXdir()
{
	((CButton *)GetDlgItem(IDC_RADIO_XDIR))->SetCheck(TRUE);
	m_nExportOrder = EXPORT_XORDER;
}


void CExportDlg::OnBnClickedRadioRotangdir()
{
	((CButton *)GetDlgItem(IDC_RADIO_ROTANGDIR))->SetCheck(TRUE);
	m_nExportOrder = EXPORT_ANGORDER;
}


void CExportDlg::OnBnClickedRadioCustom()
{
	((CButton *)GetDlgItem(IDC_RADIO_CUSTOM))->SetCheck(TRUE);
	m_nExportOrder = EXPORT_CUSTOMORDER;
}


BOOL CExportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	if (EXPORT_XORDER == m_nExportOrder)
	{
		((CButton *)GetDlgItem(IDC_RADIO_XDIR))->SetCheck(TRUE);
	}
	if (EXPORT_ANGORDER == m_nExportOrder)
	{
		((CButton *)GetDlgItem(IDC_RADIO_ROTANGDIR))->SetCheck(TRUE);
	}
	if (EXPORT_CUSTOMORDER == m_nExportOrder)
	{
		((CButton *)GetDlgItem(IDC_RADIO_CUSTOM))->SetCheck(TRUE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}
