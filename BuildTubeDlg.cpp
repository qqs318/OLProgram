// BuildTubeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EliteSoftWare.h"
#include "BuildTubeDlg.h"
#include "afxdialogex.h"

// CBuildTubeDlg 对话框
IMPLEMENT_DYNAMIC(CBuildTubeDlg, CDialogEx)

CBuildTubeDlg::CBuildTubeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBuildTubeDlg::IDD, pParent)
	, m_dTubeDia(1000)
	, m_dTubeThick(30)
	, m_dTubeLength(4000)
	, m_dHoleDia(400)
	, m_dHoleXOffset(500)
	, m_dHoleZOffset(0)
	, m_dHoleThroughAng(90)
	, m_dHoleRotAng(0)
	, m_nHoleID(0)
{
	m_pHCombParam = NULL;
	m_bBulidTube = TRUE;
}

CBuildTubeDlg::~CBuildTubeDlg()
{
}

void CBuildTubeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TUBEDIA, m_dTubeDia);
	DDV_MinMaxDouble(pDX, m_dTubeDia, 0.0000001, 1000000);
	DDX_Text(pDX, IDC_EDIT_TUBETHICK, m_dTubeThick);
	DDV_MinMaxDouble(pDX, m_dTubeThick, 0.0000001, 10000000);
	DDX_Text(pDX, IDC_EDIT_TUBELENGTH, m_dTubeLength);
	DDV_MinMaxDouble(pDX, m_dTubeLength, 0.0000001, 10000000);
	DDX_Control(pDX, IDC_LIST_HPARAM, CHParamListCtrl);
	DDX_Text(pDX, IDC_EDIT_HOLEDIA, m_dHoleDia);
	DDV_MinMaxDouble(pDX, m_dHoleDia, 0.0000001, 100000000);
	DDX_Text(pDX, IDC_EDIT_HOLEXOFFSET, m_dHoleXOffset);
	DDV_MinMaxDouble(pDX, m_dHoleXOffset, -100000000, 100000000);
	DDX_Text(pDX, IDC_EDIT_HOLEZOFFSET, m_dHoleZOffset);
	DDV_MinMaxDouble(pDX, m_dHoleZOffset, -100000000, 100000000);
	DDX_Text(pDX, IDC_EDIT_HOLETHROUGHANG, m_dHoleThroughAng);
	DDV_MinMaxDouble(pDX, m_dHoleThroughAng, 0.0000001, 179.9999999);
	DDX_Text(pDX, IDC_EDIT_HOLEROTANG, m_dHoleRotAng);
	DDV_MinMaxDouble(pDX, m_dHoleRotAng, 0, 360);
}

BOOL CBuildTubeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 在此添加额外的初始化代码
	CHParamListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_SINGLESEL & ~LVS_EX_CHECKBOXES);

	CHParamListCtrl.InsertColumn(0, _T("序号"),LVCFMT_LEFT,38,-1);
	CHParamListCtrl.InsertColumn(1, _T("割孔直径"),LVCFMT_LEFT,60,-1);
	CHParamListCtrl.InsertColumn(2, _T("X向距离"),LVCFMT_LEFT,55,-1);
	CHParamListCtrl.InsertColumn(3, _T("轴心距离"),LVCFMT_LEFT,60,-1);
	CHParamListCtrl.InsertColumn(4, _T("贯穿角度"),LVCFMT_LEFT,60,-1);
	CHParamListCtrl.InsertColumn(5, _T("旋转角度"),LVCFMT_LEFT,60,-1);
	CHParamListCtrl.DeleteAllItems();
	if (!m_bBulidTube)
	{
		GetDlgItem(IDC_EDIT_TUBEDIA)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TUBETHICK)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TUBELENGTH)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BEGIN_MESSAGE_MAP(CBuildTubeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_HOLEADD, &CBuildTubeDlg::OnBnClickedButtonHoleadd)
	ON_BN_CLICKED(IDOK, &CBuildTubeDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CBuildTubeDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

// 检查输入的孔参数的合理性
BOOL CBuildTubeDlg::CheckParam()
{
	// 1.最大值与最小值合理性判断
	/* 此处不满足条件的提示对话框由系统自动弹出*/
	if ((m_dTubeDia<0.0000001||m_dTubeDia>100000000) ||
		(m_dTubeThick<0.0000001||m_dTubeThick>100000000) ||
		(m_dTubeLength<0.0000001||m_dTubeLength>100000000) ||
		(m_dHoleDia<0.0000001||m_dHoleDia>100000000) ||
		(m_dHoleXOffset<-100000000||m_dHoleXOffset>100000000) ||
		(m_dHoleZOffset<-100000000||m_dHoleZOffset>100000000) ||
		(m_dHoleThroughAng<0.0000001||m_dHoleThroughAng>179.9999999) ||
		(m_dHoleRotAng<0||m_dHoleRotAng>360))
	{
		return FALSE;
	}
	// 2.X向负向偏移必须大于孔半径判断
	if (m_dHoleXOffset<(-m_dTubeDia*0.5))
	{
		AfxMessageBox(_T("X向负向偏移必须大于孔半径。"));
		return FALSE;
	}
	// 3.X向偏移不能大于或等于管长度+孔半径判断
	if (m_dHoleXOffset>((m_dTubeLength+m_dTubeDia*0.5)-0.0000001))
	{
		AfxMessageBox(_T("X向偏移不能大于或等于管长度与孔半径之和。"));
		return FALSE;
	}
	// 4.Z向偏移绝对值不能大于或等于管半径加孔半径判断
	if (abs(m_dHoleZOffset)>((m_dTubeDia*0.5+m_dTubeDia*0.5)-0.0000001))
	{
		AfxMessageBox(_T("轴心距离不能大于或等于管半径与孔半径之和。"));
		return FALSE;
	}
	// 5.孔直径必须小于管直径判断
	if (m_dTubeDia<(m_dHoleDia+0.0000001))
	{
		AfxMessageBox(_T("孔直径必须小于管直径。"));
		return FALSE;
	}
	// 6.X向偏移值不能等于孔半径
	if (abs(m_dHoleXOffset-(m_dHoleDia*0.5))<0.0000001)
	{
		AfxMessageBox(_T("X向偏移值不能等于孔半径。"));
		return FALSE;
	}
	return TRUE;
}

// CBuildTubeDlg 消息处理程序
void CBuildTubeDlg::OnBnClickedButtonHoleadd()
{
	UpdateData(TRUE);
	if (!CheckParam())
		return;
	// TODO: 在此添加控件通知处理程序代码
	CHoleParam* pHParam = new CHoleParam();
	pHParam->m_dCenterDis = m_dHoleZOffset;
	pHParam->m_dThroughAng = m_dHoleThroughAng;
	pHParam->m_dHoleR = m_dHoleDia*0.5;
	pHParam->m_dOffsetX = m_dHoleXOffset;
	pHParam->m_dExRotAng = m_dHoleRotAng;
	CHParamListCtrl.InsertItem(m_nHoleID,_T(""),0);

	CString str;
	str.Format( _T("%d"), m_nHoleID+1 ) ;
	CHParamListCtrl.SetItemText( m_nHoleID, 0, str ) ;
	str.Format( _T("%f"), m_dHoleDia ) ;
	TrimZeroForCSring(str);
	CHParamListCtrl.SetItemText( m_nHoleID, 1,str) ;
	str.Format( _T("%f"), m_dHoleXOffset ) ;
	TrimZeroForCSring(str);
	CHParamListCtrl.SetItemText( m_nHoleID, 2,str) ;
	str.Format( _T("%f"), m_dHoleZOffset ) ;
	TrimZeroForCSring(str);
	CHParamListCtrl.SetItemText( m_nHoleID, 3,str) ;
	str.Format( _T("%f"), m_dHoleThroughAng ) ;
	TrimZeroForCSring(str);
	CHParamListCtrl.SetItemText( m_nHoleID, 4,str) ;
	str.Format( _T("%f"), m_dHoleRotAng ) ;
	TrimZeroForCSring(str);
	CHParamListCtrl.SetItemText( m_nHoleID, 5,str) ;

	CHParamListCtrl.SetItemData(m_nHoleID,(DWORD_PTR)pHParam);
	m_nHoleID++;
	UpdateData(FALSE);
}

void CBuildTubeDlg::SetHParamList(CHCombParam* pHCombList)
{
	m_pHCombParam = pHCombList;
}

// 不论什么情况，只需对X进行修正就可以，因为就算斜向贯穿管，X的最大和最小值的平均值，也是X偏向距离
// 修正参数用于后期路径与路径参数匹配
void CBuildTubeDlg::CorrectParams()
{
	POSITION pos = m_pHCombParam->m_LHParamList.GetHeadPosition();
	while(pos)
	{
		CHoleParam* pHParam = m_pHCombParam->m_LHParamList.GetNext(pos);
		if (NULL == pHParam)
			continue;
		POSITION tmpPos = m_pHCombParam->m_LHParamList.GetHeadPosition();;
		int nXSameCount = 1;
		while(tmpPos)
		{
			CHoleParam* pTmpParam = m_pHCombParam->m_LHParamList.GetNext(tmpPos);
			if (NULL == pTmpParam || pTmpParam == pHParam)
				continue;
			// 当X值相同时，进行修正
			if (abs(pHParam->m_dOffsetX-pTmpParam->m_dOffsetX)<0.000001)
			{
				pTmpParam->m_dOffsetX += nXSameCount*CVALUE;
				pTmpParam->m_bChanged = TRUE;
				pTmpParam->m_dChangedVal = nXSameCount*CVALUE;
				nXSameCount++;
			}
		}
	}
}

void CBuildTubeDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int nAddOrder = 0;
	if (NULL == m_pHCombParam)
	{
		AfxMessageBox(_T("当前文档孔参数集合为空。"));
		return;
	}
	else
	{
		int nCount = CHParamListCtrl.GetItemCount();
		for (int i = 0; i < nCount; i++)
		{
			CHoleParam* tmp = ( CHoleParam*)CHParamListCtrl.GetItemData(i);
			if(NULL == tmp)
				continue;
			m_pHCombParam->m_LHParamList.AddTail(tmp);
			tmp->SetParentComb(m_pHCombParam);
			tmp->m_nAddOrder = nAddOrder;
			tmp->m_nExOrder = nAddOrder;
			nAddOrder++;
			tmp->m_dHoleR /= 1000.;
			tmp->m_dOffsetX /= 1000.;
			tmp->m_dCenterDis /= 1000.;
			tmp->m_dThroughAng = tmp->m_dThroughAng*PI/180.;
			tmp->m_dOrgRotAng = tmp->m_dExRotAng;
			double ang = tmp->m_dExRotAng;
			ang = 180.-ang;
			if (ang<0.)
			{
				ang += 360.;
			}

			tmp->m_dExRotAng = ang*PI/180.;
		}
		CorrectParams();
	}

	CDialogEx::OnOK();
}


void CBuildTubeDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	int nCount = CHParamListCtrl.GetItemCount();
	for (int i = 0; i < nCount; i++)
	{
		CHoleParam* tmp = ( CHoleParam*)CHParamListCtrl.GetItemData(i);
		if(NULL == tmp)
			continue;
		delete tmp;
		tmp = NULL;
	}
	CHParamListCtrl.RemoveAllGroups();
	CDialogEx::OnCancel();
}
