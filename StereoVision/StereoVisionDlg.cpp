/********************************************************************
	创建 :	2012/10/28
	文件 :	.\StereoVision\StereoVision\StereoVisionDlg.cpp
	类名 :	StereoVisionDlg
	作者 :	邹宇华 chenyusiyuan AT 126 DOT com
	
	功能 :	立体视觉测试程序界面实现代码
*********************************************************************/

#include "stdafx.h"

/***
 *	检测内存泄漏
 */
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif
//////////////////////////////////////////////////////////////////////////

#include "StereoVision.h"
#include "StereoVisionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//	ON_WM_TIMER()
END_MESSAGE_MAP()


// CStereoVisionDlg dialog

CStereoVisionDlg::CStereoVisionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStereoVisionDlg::IDD, pParent)
	, m_lfCamID(0)
	, m_riCamID(0)
	, m_nCamCount(0)
	, m_nImageWidth(0)
	, m_nImageHeight(0)
	, m_nImageChannels(0)
	, m_ProcMethod(0)
	, m_ObjectWidth(0)
	, m_ObjectHeight(0)
	, m_ObjectDistance(0)
	, m_ObjectDisparity(0)
	, m_nCornerSize_X(0)
	, m_nCornerSize_Y(0)
	, m_nSquareSize(0)
	, m_nBoards(0)
	, m_pCheck(NULL)
	, m_nID_RAD(0)
	, m_nMinDisp(0)
	, m_nMaxDisp(0)
	, m_nSADWinSiz(0)
	, m_nTextThres(0)
	, m_nDisp12MaxDiff(-1)
	, m_nPreFiltCap(0)
	, m_nUniqRatio(0)
	, m_nSpeckRange(0)
    , m_nSpeckWinSiz(0)
    , m_nViewWidth(0)
    , m_nViewHeight(0)
    , m_nViewDepth(0)
	, m_nDelayTime(0)
	, m_bFullDP(FALSE)
	, m_bSaveFrame(FALSE)
    , m_dAlpha(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}



void CStereoVisionDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDV_MinMaxInt(pDX, m_nCornerSize_X, 0, 50);
    DDV_MinMaxInt(pDX, m_nCornerSize_Y, 0, 50);
    DDV_MinMaxInt(pDX, m_nBoards, 0, 100);
    DDV_MinMaxInt(pDX, m_nMinDisp, -64, 16);
    DDV_MinMaxInt(pDX, m_nMaxDisp, 0, 240);
    DDV_MinMaxInt(pDX, m_nSADWinSiz, 0, 21);
    DDV_MinMaxInt(pDX, m_nTextThres, 0, 50);
    DDV_MinMaxInt(pDX, m_nDisp12MaxDiff, -1, 16);
    DDV_MinMaxInt(pDX, m_nPreFiltCap, 0, 100);
    DDV_MinMaxInt(pDX, m_nUniqRatio, 0, 50);
    DDV_MinMaxInt(pDX, m_nSpeckRange, 0, 64);
    DDV_MinMaxInt(pDX, m_nSpeckWinSiz, 0, 200);
    DDV_MinMaxInt(pDX, m_nViewWidth, 60, 600);
    DDV_MinMaxInt(pDX, m_nViewHeight, 40, 400);
    DDV_MinMaxInt(pDX, m_nViewDepth, 60, 600);
    DDV_MinMaxInt(pDX, m_nDelayTime, 0, 99);
    DDX_Control(pDX, IDC_CBN1CamList_L, m_CBNCamList_L);
    DDX_Control(pDX, IDC_CBN1CamList_R, m_CBNCamList_R);
    DDX_Control(pDX, IDC_CBN2MethodList, m_CBNMethodList);
    DDX_Control(pDX, IDC_SPIN_minDisp, m_spinMinDisp);
    DDX_Control(pDX, IDC_SPIN_maxDisp, m_spinMaxDisp);
    DDX_Control(pDX, IDC_SPIN_SADWinSiz, m_spinSADWinSiz);
    DDX_Control(pDX, IDC_SPIN_textThres, m_spinTextThres);
    DDX_Control(pDX, IDC_SPIN_disp12MaxDiff, m_spinDisp12MaxDiff);
    DDX_Control(pDX, IDC_SPIN_preFiltCap, m_spinPreFiltCap);
    DDX_Control(pDX, IDC_SPIN_uniqRatio, m_spinUniqRatio);
    DDX_Control(pDX, IDC_SPIN_speckRange, m_spinSpeckRange);
    DDX_Control(pDX, IDC_SPIN_speckWinSiz, m_spinSpeckWinSiz);
    DDX_Control(pDX, IDC_CBN_Resolution, m_CBNResolution);
    DDX_Check(pDX, IDC_CHK_fullDP, m_bFullDP);
    DDX_Check(pDX, IDC_CHK_SaveAsVideo, m_bSaveFrame);
    DDX_Text(pDX, IDC_EDIT_DelayTime, m_nDelayTime);
    DDX_Text(pDX, IDC_EDIT_speckWinSiz, m_nSpeckWinSiz);
    DDX_Text(pDX, IDC_EDIT_speckRange, m_nSpeckRange);
    DDX_Text(pDX, IDC_EDIT_uniqRatio, m_nUniqRatio);
    DDX_Text(pDX, IDC_EDIT_preFiltCap, m_nPreFiltCap);
    DDX_Text(pDX, IDC_e5LfObjSpan, m_ObjectWidth);
    DDX_Text(pDX, IDC_e6ObjPRLX, m_ObjectHeight);
    DDX_Text(pDX, IDC_e7ObjDist, m_ObjectDistance);
    DDX_Text(pDX, IDC_e8ObjSize, m_ObjectDisparity);
    DDX_Text(pDX, IDC_BoardWidth, m_nCornerSize_X);
    DDX_Text(pDX, IDC_BoardHeight, m_nCornerSize_Y);
    DDX_Text(pDX, IDC_SquareSize, m_nSquareSize);
    DDX_Text(pDX, IDC_EDIT_minDisp, m_nMinDisp);
    DDX_Text(pDX, IDC_nBoards, m_nBoards);
    DDX_Text(pDX, IDC_EDIT_maxDisp, m_nMaxDisp);
    DDX_Text(pDX, IDC_EDIT_SADWinSiz, m_nSADWinSiz);
    DDX_Text(pDX, IDC_EDIT_textThres, m_nTextThres);
    DDX_Text(pDX, IDC_EDIT_disp12MaxDiff, m_nDisp12MaxDiff);
    DDX_Text(pDX, IDC_Edit_alpha_rectify, m_dAlpha);
    DDX_Text(pDX, IDC_EDIT_viewWidth, m_nViewWidth);
    DDX_Text(pDX, IDC_EDIT_viewHeight, m_nViewHeight);
    DDX_Text(pDX, IDC_EDIT_viewDepth, m_nViewDepth);
    DDX_Control(pDX, IDC_SPIN_viewWidth, m_spinViewWidth);
    DDX_Control(pDX, IDC_SPIN_viewHeight, m_spinViewHeight);
    DDX_Control(pDX, IDC_SPIN_viewDepth, m_spinViewDepth);
	DDV_MinMaxDouble(pDX, m_dAlpha, -1, 1);
}


BEGIN_MESSAGE_MAP(CStereoVisionDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BN1RunCam, &CStereoVisionDlg::OnBnClkRunCam)
	ON_BN_CLICKED(IDC_BN2StopCam, &CStereoVisionDlg::OnBnClkStopCam)
	ON_BN_CLICKED(IDC_RAD_BM, &CStereoVisionDlg::OnBnClkRad_BM)
	ON_BN_CLICKED(IDC_RAD_SGBM, &CStereoVisionDlg::OnBnClkRad_SGBM)
	ON_BN_CLICKED(IDC_BN_CompDisp, &CStereoVisionDlg::OnBnClk_DoCompDisp)
	ON_BN_CLICKED(IDC_BN_StopDispComp, &CStereoVisionDlg::OnBnClk_StopDispComp)
	ON_BN_CLICKED(IDC_BN2StereoCalib, &CStereoVisionDlg::OnBnClk_DoCameraCalib)
	ON_BN_CLICKED(IDC_BN_ExitCameraCalib, &CStereoVisionDlg::OnBnClk_ExitCameraCalib)
	ON_BN_CLICKED(IDC_BN_StereoDefParam, &CStereoVisionDlg::OnBnClkDefaultStereoParam)
    ON_BN_CLICKED(IDC_BN_DefaultCamCalibParam, &CStereoVisionDlg::OnBnClkDefaultCamCalibParam)
    ON_CBN_SELCHANGE(IDC_CBN1CamList_L, &CStereoVisionDlg::OnCbnSelchgCbn1CamlistL)
	ON_CBN_SELCHANGE(IDC_CBN1CamList_R, &CStereoVisionDlg::OnCbnSelchgCbn1CamlistR)
	ON_CBN_SELCHANGE(IDC_CBN2MethodList, &CStereoVisionDlg::OnCbnSelchgCbn2Methodlist)
	ON_CBN_SELCHANGE(IDC_CBN_Resolution, &CStereoVisionDlg::OnCbnSelchangeCbnResolution)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_maxDisp, &CStereoVisionDlg::OnDeltaposSpin_MaxDisp)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SADWinSiz, &CStereoVisionDlg::OnDeltaposSpin_SADWinSiz)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_speckRange, &CStereoVisionDlg::OnDeltaposSpin_SpeckRange)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_viewWidth, &CStereoVisionDlg::OnDeltaposSpin_ViewWidth)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_viewHeight, &CStereoVisionDlg::OnDeltaposSpin_ViewHeight)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_viewDepth, &CStereoVisionDlg::OnDeltaposSpin_ViewDepth)
    ON_WM_CLOSE()
    ON_BN_CLICKED(IDC_BTN_DefaultViewField, &CStereoVisionDlg::OnBnClkDefaultViewfield)
END_MESSAGE_MAP()


// CStereoVisionDlg message handlers

/*----------------------------
 * 功能 : 初始化对话框
 *----------------------------
 * 函数 : CStereoVisionDlg::OnInitDialog
 * 访问 : virtual protected 
 * 返回 : BOOL
 *
 */
BOOL CStereoVisionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//////////////////////////////////////////////////////////////////////////
	// TODO: Add extra initialization here
	
	// 获取程序工作路径
	m_workDir = F_InitWorkDir();
    m_stereoCalibrator.setWorkDir(CStringA(m_workDir).GetBuffer(0));

	// 默认图像处理方法为显示原始图像
	m_ProcMethod = SHOW_ORIGINAL_FRAME;

	// 获取摄像头数目
	m_nCamCount = CCameraDS::CameraCount();
	if( m_nCamCount < 1 )
	{
		AfxMessageBox(_T("请插入至少1个摄像头！"));
		//return -1;
	}

	// 在组合框CamList中添加摄像头名称的字符串
	char camera_name[1024];
	char istr[1024];
	CString camstr;
	for(int i=0; i < m_nCamCount; i++)
	{  
		int retval = CCameraDS::CameraName(i, camera_name, sizeof(camera_name) );

		sprintf_s(istr, "#%d ", i);
		strcat_s( istr, camera_name );  
		camstr = istr;
		if(retval >0)
        {
            m_CBNCamList_L.AddString(camstr);
			m_CBNCamList_R.AddString(camstr);
        }
		else
			AfxMessageBox(_T("不能获取摄像头的名称"));
	}
	camstr.ReleaseBuffer();
    if (m_nCamCount <= 1)
        m_CBNCamList_R.EnableWindow(FALSE);

	// 在组合框MethodList中添加各种帧处理方法的字符串
	m_CBNMethodList.AddString(_T("显示原始画面"));
	m_CBNMethodList.AddString(_T("Canny边缘检测"));
	m_CBNMethodList.AddString(_T("直方图均衡"));
	m_CBNMethodList.AddString(_T("色彩空间变换"));
	m_CBNMethodList.SetCurSel(0);

	// 使一系列按钮失效
	GetDlgItem( IDC_BN1RunCam )->EnableWindow( FALSE );			// 启动摄像头失效
	GetDlgItem( IDC_BN2StopCam )->EnableWindow( FALSE );		// 停止摄像头失效
	GetDlgItem(IDC_BN_StopDispComp)->EnableWindow(FALSE);		// 停止视差计算失效
	GetDlgItem(IDC_EDIT_disp12MaxDiff)->EnableWindow(FALSE);	// 左右视差图检验失效
	
	// 初始化双目匹配区域控件设置
	CheckRadioButton(IDC_RAD_BOUGUET, IDC_RAD_HARTLEY, IDC_RAD_BOUGUET);				// 默认使用BOUGUET方法双目校正
	CheckRadioButton(IDC_RAD_BM, IDC_RAD_SGBM, IDC_RAD_BM);								// 默认使用 BM 算法计算视差
	CheckRadioButton(IDC_RAD_DispFromCam, IDC_RAD_DispFromImg, IDC_RAD_DispFromCam);	// 默认从摄像机获取图像
    CheckRadioButton(IDC_RAD_ToHSV, IDC_RAD_ToXYZ, IDC_RAD_ToHSV);						// 默认图像格式转换为 HSV 格式
    CheckRadioButton(IDC_RAD_ColorDisp, IDC_RAD_SideView, IDC_RAD_ColorDisp);			// 默认显示彩色视差图
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_StereoRectify);								// 默认执行双目校正
	m_pCheck->SetCheck(1);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_ProjTo3D);			// 默认执行双目测距
	m_pCheck->SetCheck(1);
	m_pCheck = NULL;

    m_nViewWidth = 200;
    m_nViewHeight = 200;
    m_nViewDepth = 200;
	m_nMaxDisp = 0;
	m_nSADWinSiz =0;
	m_nPreFiltCap =0;
	m_nSpeckRange = 0;
	m_nDelayTime = 5;
	m_spinMinDisp.SetRange(-64, 16);
	m_spinMaxDisp.SetRange(0, 240);
	m_spinSADWinSiz.SetRange(0, 21);
	m_spinTextThres.SetRange(0, 50);
	m_spinDisp12MaxDiff.SetRange(-1, 36);
	m_spinPreFiltCap.SetRange(0, 100);
	m_spinUniqRatio.SetRange(0, 50);
	m_spinSpeckRange.SetRange(0, 64);
    m_spinSpeckWinSiz.SetRange(0, 200);
    m_spinViewWidth.SetRange(60, 600);
    m_spinViewHeight.SetRange(40, 400);
    m_spinViewDepth.SetRange(60, 600);

	UpdateData( FALSE );

	// 初始化图像显示控件的图像
	CRect rect;
	GetDlgItem(IDC_PicLfCam) ->GetClientRect( &rect );
	m_lfImage = Mat::zeros(rect.Height(), rect.Width(), CV_8UC3);
	GetDlgItem(IDC_PicRiCam) ->GetClientRect( &rect );
	m_riImage = Mat::zeros(rect.Height(), rect.Width(), CV_8UC3);
	GetDlgItem(IDC_PicSynImg) ->GetClientRect( &rect );
	m_disparity = Mat::zeros(rect.Height(), rect.Width(), CV_8UC3);

	return TRUE;  // return TRUE  unless you set the focus to a control
}


/*----------------------------
 * 功能 : OnSysCommand
 *----------------------------
 * 函数 : CStereoVisionDlg::OnSysCommand
 * 访问 : protected 
 * 返回 : void
 *
 * 参数 : UINT nID
 * 参数 : LPARAM lParam
 */
void CStereoVisionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.


/*----------------------------
 * 功能 : OnPaint
 *----------------------------
 * 函数 : CStereoVisionDlg::OnPaint
 * 访问 : protected 
 * 返回 : void
 *
 */
void CStereoVisionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();						// 重绘对话框
		CDialog::UpdateWindow();				// 更新windows窗口，如果无这步调用，图片显示还会出现问题
		if (!m_lfImage.empty())
		{
			F_ShowImage( m_lfImage, m_lfImage, IDC_PicLfCam );		// 重绘图片函数
			F_ShowImage( m_riImage, m_riImage, IDC_PicRiCam );		// 重绘图片函数
			F_ShowImage( m_disparity, m_disparity, IDC_PicSynImg );	// 重绘图片函数
		}
	}
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
/*----------------------------
 * 功能 : OnQueryDragIcon
 *----------------------------
 * 函数 : CStereoVisionDlg::OnQueryDragIcon
 * 访问 : protected 
 * 返回 : HCURSOR
 *
 */
HCURSOR CStereoVisionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/*----------------------------
 * 功能 : 选择左摄像头下拉菜单响应
 *----------------------------
 * 函数 : CStereoVisionDlg::OnCbnSelchgCbn1CamlistL
 * 访问 : private 
 * 返回 : void
 *
 */
void CStereoVisionDlg::OnCbnSelchgCbn1CamlistL()
{
	// TODO: Add your control notification handler code here

    // 确定左右摄像头对应的设备序号（对应下拉菜单选择项的序号）
    m_lfCamID = m_CBNCamList_L.GetCurSel();

	// 使启动摄像头按钮生效
	GetDlgItem( IDC_BN1RunCam )->EnableWindow( TRUE );
	
	return;
}

/*----------------------------
 * 功能 : 选择右摄像头下拉菜单响应
 *----------------------------
 * 函数 : CStereoVisionDlg::OnCbnSelchgCbn1CamlistR
 * 访问 : private 
 * 返回 : void
 *
 */
void CStereoVisionDlg::OnCbnSelchgCbn1CamlistR()
{
	// TODO: Add your control notification handler code here

    // 确定左右摄像头对应的设备序号（对应下拉菜单选择项的序号）
    m_riCamID = m_CBNCamList_R.GetCurSel();

	// 使启动摄像头按钮生效
	GetDlgItem( IDC_BN1RunCam )->EnableWindow( TRUE );
	
	return;
}


/*----------------------------
 * 功能 : 选择摄像头分辨率
 *----------------------------
 * 函数 : CStereoVisionDlg::OnCbnSelchangeCbnResolution
 * 访问 : private 
 * 返回 : void
 *
 */
void CStereoVisionDlg::OnCbnSelchangeCbnResolution()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_CBNResolution.GetCurSel();
	switch (index)
	{
	case 0:
		m_nImageWidth = 640;
		m_nImageHeight = 480;
		break;
	case 1:
		m_nImageWidth = 352;
		m_nImageHeight = 288;
		break;
	case 2:
		m_nImageWidth = 320;
		m_nImageHeight = 240;
		break;
	default:
		m_nImageWidth = 352;
		m_nImageHeight = 288;
	}

	m_nImageChannels = 3;
}


/*----------------------------
 * 功能 : 启动摄像头
 *----------------------------
 * 函数 : CStereoVisionDlg::OnBnClkRunCam
 * 访问 : private 
 * 返回 : void
 *
 */
void CStereoVisionDlg::OnBnClkRunCam()
{
	// TODO: Add your control notification handler code here
	if (m_nImageWidth * m_nImageHeight * m_nImageChannels == 0)
	{
		AfxMessageBox(_T("请选择摄像头画面的分辨率！"));
		return;
	}
	if (m_nCamCount > 0)
	{
		//打开第一个摄像头
		//if( ! lfCam.OpenCamera(m_riCamID, false, m_nImageWidth, m_nImageHeight) ) //不弹出属性选择窗口，用代码制定图像宽和高
		if ( !lfCam.open(m_lfCamID) )
		{
			AfxMessageBox(_T("打开左摄像头失败."));
			return;
		}
		lfCam.set(CV_CAP_PROP_FRAME_WIDTH,  m_nImageWidth);
		lfCam.set(CV_CAP_PROP_FRAME_HEIGHT, m_nImageHeight);
	}
	if (m_nCamCount > 1)
	{
		if (m_lfCamID == m_riCamID)
		{
			AfxMessageBox(_T("左右摄像头的设备序号不能相同！"));
			return;
		}
		//打开第二个摄像头
		//if( ! riCam.OpenCamera(m_lfCamID, false, m_nImageWidth, m_nImageHeight) ) 
		if ( !riCam.open(m_riCamID) )
		{
			AfxMessageBox(_T("打开右摄像头失败."));
			return;
		}
		riCam.set(CV_CAP_PROP_FRAME_WIDTH,  m_nImageWidth);
		riCam.set(CV_CAP_PROP_FRAME_HEIGHT, m_nImageHeight);

		GetDlgItem( IDC_BN_CompDisp )->EnableWindow( TRUE );
	}
	
	// 使部分按钮生效
	GetDlgItem( IDC_BN2StopCam )->EnableWindow( TRUE );
	GetDlgItem( IDC_BN2StereoCalib)->EnableWindow( TRUE );
	// 使部分按钮失效
	GetDlgItem( IDC_BN1RunCam )->EnableWindow( FALSE );
    GetDlgItem( IDC_CBN1CamList_L )->EnableWindow( FALSE );
    GetDlgItem( IDC_CBN1CamList_R )->EnableWindow( FALSE );
	GetDlgItem( IDC_CBN_Resolution )->EnableWindow( FALSE );

	// 启动摄像头后显示实时画面
	DoShowOrigFrame();
	
	return;
}


/*----------------------------
 * 功能 : 定时器响应
 *		 主要用于 没有双目定标或双目匹配操作时 的其它显示和处理操作
 *----------------------------
 * 函数 : CStereoVisionDlg::OnTimer
 * 访问 : private 
 * 返回 : void
 *
 * 参数 : UINT_PTR nIDEvent
 */
void CStereoVisionDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (lfCam.isOpened())
	{
		Mat lfFrame;
		lfCam >> lfFrame;

		if (m_ProcMethod != SHOW_ORIGINAL_FRAME)
		{
			DoFrameProc(lfFrame, lfFrame);
		}

		F_ShowImage(lfFrame, m_lfImage, IDC_PicLfCam);
	}
	if (riCam.isOpened())
	{
		Mat riFrame;
		riCam >> riFrame;

		if (m_ProcMethod != SHOW_ORIGINAL_FRAME)
		{
			DoFrameProc(riFrame, riFrame);
		}

		F_ShowImage(riFrame, m_riImage, IDC_PicRiCam);
	}
	CDialog::OnTimer(nIDEvent);
}


/*----------------------------
 * 功能 : 关闭摄像头
 *----------------------------
 * 函数 : CStereoVisionDlg::OnBnClkStopCam
 * 访问 : private 
 * 返回 : void
 *
 */
void CStereoVisionDlg::OnBnClkStopCam()
{
	// TODO: Add your control notification handler code here
	if (lfCam.isOpened())
	{
		GetDlgItem( IDC_BN2StopCam )->EnableWindow( FALSE );
		KillTimer(1);

		// 对图像数据清零
		m_lfImage = Scalar(0);
		F_ShowImage( m_lfImage, m_lfImage, IDC_PicLfCam );
		lfCam.release();
		if (riCam.isOpened())
		{
			m_riImage = Scalar(0);
			F_ShowImage( m_riImage, m_riImage, IDC_PicRiCam );
			riCam.release();
		}

		// 使启动摄像头按钮和摄像头选择列表生效
		GetDlgItem( IDC_BN1RunCam )->EnableWindow( TRUE );
        GetDlgItem( IDC_CBN1CamList_L )->EnableWindow( TRUE );
        GetDlgItem( IDC_CBN1CamList_R )->EnableWindow( TRUE );
		GetDlgItem( IDC_CBN_Resolution )->EnableWindow( TRUE );
		GetDlgItem( IDC_BN2StereoCalib)->EnableWindow( FALSE );
		GetDlgItem( IDC_BN_CompDisp )->EnableWindow( FALSE );
	}
	return;
}


/*----------------------------
 * 功能 : 帧处理方法下拉菜单选择响应，
 *		 修改帧处理标志值
 *----------------------------
 * 函数 : CStereoVisionDlg::OnCbnSelchgCbn2Methodlist
 * 访问 : private 
 * 返回 : void
 *
 */
void CStereoVisionDlg::OnCbnSelchgCbn2Methodlist()
{
	// TODO: Add your control notification handler code here
	m_ProcMethod = m_CBNMethodList.GetCurSel();
}


/*----------------------------
 * 功能 : 弹出打开文件对话框，选择单个或多个文件
 *----------------------------
 * 函数 : CStereoVisionDlg::DoSelectFiles
 * 访问 : private 
 * 返回 : selectedFiles	选择的文件的路径序列
 *
 * 参数 : lpszDefExt			[in]	文件默认格式
 * 参数 : dwFlags			[in]	对话框选项
 * 参数 : lpszFilter			[in]	文件格式过滤条件
 * 参数 : lpstrTitle			[in]	对话框标题
 * 参数 : lpstrInitialDir	[in]	对话框的初始路径
 */
vector<CStringA> CStereoVisionDlg::DoSelectFiles(
	LPCTSTR	lpszDefExt,
	DWORD	dwFlags,
	LPCTSTR	lpszFilter,
	LPCWSTR	lpstrTitle,
	LPCWSTR	lpstrInitialDir )
{
	vector<CStringA> selectedFiles;
	POSITION filePosition;
	DWORD MAXFILE = 4000;  
	TCHAR* pc = new TCHAR[MAXFILE];  

	CFileDialog dlg( TRUE, lpszDefExt, NULL, dwFlags, lpszFilter, NULL );	
	
	dlg.m_ofn.nMaxFile = MAXFILE; 
	dlg.m_ofn.lpstrFile = pc;   
	dlg.m_ofn.lpstrFile[0] = NULL; 
	dlg.m_ofn.lpstrTitle = lpstrTitle;
	dlg.m_ofn.lpstrInitialDir = lpstrInitialDir;

	if( dlg.DoModal() == IDOK )
	{
		filePosition = dlg.GetStartPosition();
		while(filePosition != NULL)   
		{   
			CStringA path;
			path = dlg.GetNextPathName(filePosition);
			selectedFiles.push_back( path );  
		}  
	}

	delete []pc;
	return selectedFiles;
}


/*----------------------------
 * 功能 : 设置摄像头定标的默认参数
 *----------------------------
 * 函数 : CStereoVisionDlg::OnBnClkDefaultCamCalibParam
 * 访问 : private 
 * 返回 : void
 *
 */
void CStereoVisionDlg::OnBnClkDefaultCamCalibParam()
{
	// TODO: Add your control notification handler code here
	m_nCornerSize_X = 9;
	m_nCornerSize_Y = 6;
	m_nBoards = 20;
	m_nSquareSize = 26.0f;
    m_dAlpha = -1;
	UpdateData(FALSE);

	CheckRadioButton(IDC_RAD_CalibFromCam, IDC_RAD_CalibFromImg, IDC_RAD_CalibFromCam);
	CheckRadioButton(IDC_RAD_Load1CamCalibResult, IDC_RAD_StereoCalib, IDC_RAD_Calib1CamFirst);

	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_ShowCalibResult);
	m_pCheck->SetCheck(1);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK1FPP);
	m_pCheck->SetCheck(1);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK1FPP2);
	m_pCheck->SetCheck(1);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK2UIG);
	m_pCheck->SetCheck(0);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK2UIG2);
	m_pCheck->SetCheck(1);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK3FAR);
	m_pCheck->SetCheck(1);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK3FAR2);
	m_pCheck->SetCheck(1);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK4ZTD);
	m_pCheck->SetCheck(1);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK4SFL);
	m_pCheck->SetCheck(1);
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK5FI);
	m_pCheck->SetCheck(0);
	m_pCheck = NULL;

	return;
}


/*----------------------------
 * 功能 : 确认摄像机定标的相关选项
 *----------------------------
 * 函数 : CStereoVisionDlg::DoParseOptionsOfCameraCalib
 * 访问 : private 
 * 返回 : void
 *
 * 参数 : opt	[i/o]	摄像机定标选项
 */
bool CStereoVisionDlg::DoParseOptionsOfCameraCalib(OptionCameraCalib& opt)
{
	// 摄像头定标变量初始化
	opt.squareSize = 30.0f;
	opt.flagCameraCalib = CV_CALIB_FIX_K3;
	opt.flagStereoCalib = 0;
	opt.numberFrameSkip = 30;
	opt.doStereoCalib = true;

	UINT nCheckIDs[9] = { IDC_CHK1FPP, IDC_CHK2UIG, IDC_CHK3FAR, IDC_CHK4ZTD,
		IDC_CHK1FPP2, IDC_CHK2UIG2, IDC_CHK3FAR2, IDC_CHK4SFL, IDC_CHK5FI };
	int nFlagDefs1[4] = { CV_CALIB_FIX_PRINCIPAL_POINT, CV_CALIB_USE_INTRINSIC_GUESS,
		CV_CALIB_FIX_ASPECT_RATIO, CV_CALIB_ZERO_TANGENT_DIST };
	int nFlagDefs2[5] = { CV_CALIB_FIX_PRINCIPAL_POINT, CV_CALIB_USE_INTRINSIC_GUESS,
		CV_CALIB_FIX_ASPECT_RATIO, CV_CALIB_SAME_FOCAL_LENGTH, CV_CALIB_FIX_INTRINSIC };

	// 读入MFC界面的棋盘参数设定
	bool res = UpdateData(TRUE);
    if (!res)
        return false;

	opt.cornerSize.width = m_nCornerSize_X; 	// 棋盘角点数 (nx, ny)
	opt.cornerSize.height = m_nCornerSize_Y;
	opt.numberBoards = m_nBoards;				// 检测棋盘次数
	opt.squareSize = m_nSquareSize; 			// 棋盘方块大小

	// 确认棋盘角点坐标数据的获取方式
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_ReadCornerData);
	opt.loadConerDatas = m_pCheck->GetCheck() > 0;	

	// 确认左右视图的来源（摄像头 or 本地图片）
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_CalibFromCam, IDC_RAD_CalibFromImg);
	opt.readLocalImage = m_nID_RAD == IDC_RAD_CalibFromImg;
	if(opt.readLocalImage)		// 若从本地图片读入，则跳帧数减少为 5 帧
		opt.numberFrameSkip = 5;

	// 确认双目定标的次序
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_Load1CamCalibResult, IDC_RAD_StereoCalib);
	opt.calibOrder = m_nID_RAD == IDC_RAD_Load1CamCalibResult ? CALIB_LOAD_CAMERA_PARAMS : 
		m_nID_RAD == IDC_RAD_Calib1CamFirst ? CALIB_SINGLE_CAMERA_FIRST : 
		m_nID_RAD == IDC_RAD_StereoCalib ? CALIB_STEREO_CAMERAS_DIRECTLY : 	CALIB_SINGLE_CAMERA_FIRST;	
	if (m_nCamCount == 1)	//摄像头只有一个时，不能进行双目定标
	{
		opt.doStereoCalib = false;
		opt.calibOrder = CALIB_SINGLE_CAMERA_FIRST;
		m_pCheck = (CButton*)GetDlgItem(IDC_RAD_Calib1CamFirst);
		m_pCheck->SetCheck(1);
		GetDlgItem(IDC_RAD_StereoCalib)->EnableWindow(FALSE);
	}

	// 确认双目校正算法
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_BOUGUET, IDC_RAD_HARTLEY);
	opt.rectifyMethod = m_nID_RAD == IDC_RAD_BOUGUET ? StereoCalib::RECTIFY_BOUGUET : StereoCalib::RECTIFY_HARTLEY;

    // 确定双目校正缩放系数
    if (m_dAlpha < 0 || m_dAlpha > 1)
        m_dAlpha = -1;
    opt.alpha = m_dAlpha;

	// 读入定标参数的设置
	int i;
	for (i=0; i<4; i++)
	{
		m_pCheck = (CButton*)GetDlgItem(nCheckIDs[i]);
		if(m_pCheck->GetCheck())
			opt.flagCameraCalib |= nFlagDefs1[i];
	}
	for (i=4; i<9; i++)
	{
		m_pCheck = (CButton*)GetDlgItem(nCheckIDs[i]);
		if(m_pCheck->GetCheck())
			opt.flagStereoCalib |= nFlagDefs2[i-4];
	}

    res = UpdateData(FALSE);

    return res;
}


/*----------------------------
 * 功能 : 双目定标 按钮响应
 *----------------------------
 * 函数 : CStereoVisionDlg::OnBnClk_DoCameraCalib
 * 访问 : private 
 * 返回 : void
 *
 */
void CStereoVisionDlg::OnBnClk_DoCameraCalib()
{
	// TODO: Add your control notification handler code here

    //确认摄像机定标的相关选项
    OptionCameraCalib optCalib;
    if (!DoParseOptionsOfCameraCalib(optCalib))
        return;

	KillTimer(1);
	GetDlgItem(IDC_BN2StereoCalib)->EnableWindow(FALSE);
    GetDlgItem(IDC_CBN2MethodList)->EnableWindow(FALSE);
    GetDlgItem(IDC_BN_CompDisp)->EnableWindow(FALSE);

	// 棋盘检测参数初始化
	int nFoundBoard = 0, nFrame = 0;
	vector<CStringA> img0Files, img1Files;
	const char* img0_file = NULL, *img1_file = NULL;
	cv::Mat frame0, frame1, img0, img1;
	cv::Size imageSize;

	StereoCalib::CornerDatas cornerDatas;
	StereoCalib::StereoParams stereoParams;
	StereoCalib::RemapMatrixs remapMatrixs;

	try
    {
		////////////////////////////////////////////////////////////////////////
		// 读入或检测棋盘角点
		// *** 从本地文件读入角点坐标数据
        CStringA filePath(m_workDir);
        filePath.AppendFormat("CornerData.yml");
		const char* cornerFile = filePath.GetBuffer(0);
		if (optCalib.loadConerDatas)		
		{
			if ( m_stereoCalibrator.loadCornerData(cornerFile, cornerDatas) )
			{
				AfxMessageBox(_T("已读入角点坐标数据"));
			}
			else
			{
				LPCTSTR errMsg = _T("角点坐标数据读入失败！\n  --确认当前文件夹中包含 CornerData.yml 文件！ \n 或者\n  --执行棋盘角点检测。");
				throw errMsg;
			}
		} 
		// *** 从摄像头或本地图片检测棋盘角点
		else		
		{
			// 若选择从本地图片读入定标图像，首先弹出对话框选择图片文件
			if(optCalib.readLocalImage)
			{
				img0Files = DoSelectFiles(
					_T("*.bmp"), 
					OFN_ENABLESIZING   |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
					_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
					_T("选择左视图文件"),
					_T("Imgs\\Left"));

                if (optCalib.doStereoCalib)
                {
                    img1Files = DoSelectFiles(
                        _T("*.bmp"), 
                        OFN_ENABLESIZING   |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
                        _T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
                        _T("选择右视图文件"),
                        _T("Imgs\\Right"));
                }

				if( img0Files.empty() )	// 判断是否获得图片
				{
					LPCTSTR errMsg = _T("没有选择到有效的图像文件，请重新选择!");
					throw errMsg;
				}

				img0_file = img0Files[ 0 ];
				img0 = cvLoadImage(img0_file);
				imageSize = img0.size();

				if (false == img1Files.empty())
				{
					optCalib.numberBoards = MIN(optCalib.numberBoards, MIN(img0Files.size(), img1Files.size()));
				}
				else
				{
					optCalib.doStereoCalib = false;
					optCalib.numberBoards = MIN(optCalib.numberBoards, img0Files.size());
				}
			} 
			else
			{
				lfCam >> img0;
				imageSize = img0.size();
			}

			////////////////////////////////////////////////////////////////////////
			// 初始化角点数据集
			m_stereoCalibrator.initCornerData(optCalib.numberBoards, imageSize, optCalib.cornerSize, optCalib.squareSize, cornerDatas);
			
			// 启用退出摄像机定标按钮
			GetDlgItem(IDC_BN_ExitCameraCalib)->EnableWindow(TRUE);

			// 开始检测角点
			MSG msg;
			while(nFoundBoard < optCalib.numberBoards)
			{
				// MFC 窗口消息处理
				if(::PeekMessage(&msg, this->m_hWnd, 0, 0, PM_REMOVE)) 
				{ 
					if(msg.message == WM_QUIT) 
					{ 
						LPCTSTR errMsg = _T("手动退出双目标定!");
						throw errMsg; 
					}	

					//// 需要 #include "Strsafe.h"
					//TCHAR info[50];
					//StringCbPrintf( info, sizeof(info), _T("消息序号 = %d\n"), msg.message );
					//OutputDebugString(info);

					::TranslateMessage(&msg); 
					::DispatchMessage(&msg);
				}

				// 载入图像
				if(optCalib.readLocalImage)	// 从本地图片
				{
					img0_file = img0Files[ nFoundBoard ];
					frame0 = cvLoadImage(img0_file);
					if (optCalib.doStereoCalib)
					{
						img1_file = img1Files[ nFoundBoard ];
						frame1 = cvLoadImage(img1_file);
					}
				} 
				else	// 从摄像头
				{
					lfCam >> frame0;
					if (optCalib.doStereoCalib) 
						riCam >> frame1;
				}				
				if ( frame0.empty())	break;
				if (optCalib.doStereoCalib)
				{
					if ( frame1.empty())	break;
				}

				// 复制图像
				img0 = frame0.clone();
				if (optCalib.doStereoCalib) img1 = frame1.clone();

				// 检测角点
				if ( m_stereoCalibrator.detectCorners(img0, img1, cornerDatas, nFoundBoard) )
				{
					if (nFrame++ > optCalib.numberFrameSkip)
					{
						//保存视图
						if (optCalib.readLocalImage == false)
						{
							CStringA imgName( m_workDir );
							imgName.AppendFormat("Imgs\\left%03d.jpg",nFoundBoard);
							string imgname = imgName.GetBuffer(0);
							imwrite(imgname, frame0);

							if (optCalib.doStereoCalib) 
							{
								imgName = m_workDir;
								imgName.AppendFormat("Imgs\\right%03d.jpg",nFoundBoard);
								imgname = imgName.GetBuffer(0);
								imwrite(imgname, frame1);
							}
                            imgName.ReleaseBuffer();
						}

						nFoundBoard++; 
						nFrame = 0;
					}

					if (nFoundBoard > 0 && nFrame < 5)
					{
						//使图像反色，表明同时找到完整的棋盘角点
						bitwise_not(img0, img0);
						if (optCalib.doStereoCalib) bitwise_not(img1, img1);
					}
				} // --End "if ( m_stereoCalibrator.detectCorners )"

				// 显示检测到的角点
				F_ShowImage( img0, m_lfImage, IDC_PicLfCam );
				if (optCalib.doStereoCalib) F_ShowImage( img1, m_riImage, IDC_PicRiCam ); 
			} // --End "while(nFoundBoard < optCalib.numberBoards) "
			
			if (nFoundBoard < 4)
			{
				LPCTSTR errMsg = _T("检测成功的棋盘图像数小于4个，退出双目标定!");
				throw errMsg;
			}
			else if (nFoundBoard != optCalib.numberBoards)
			{
				optCalib.numberBoards = nFoundBoard;
				m_stereoCalibrator.resizeCornerData(optCalib.numberBoards, cornerDatas);
			}

			// 保存角点坐标数据
			m_stereoCalibrator.saveCornerData(cornerFile, cornerDatas);

			AfxMessageBox(_T("棋盘角点检测结束"));
		} // --End "if (optCalib.loadConerDatas)"
		// 已获取角点坐标数据

		// 禁用退出摄像机定标按钮
		GetDlgItem(IDC_BN_ExitCameraCalib)->EnableWindow(FALSE);

		////////////////////////////////////////////////////////////////////////
		// 是否读入已标定好的摄像头内参？
		if (optCalib.calibOrder == CALIB_LOAD_CAMERA_PARAMS)
		{		
            filePath = m_workDir;
            filePath.AppendFormat("cameraParams_left.yml");
			if (0 == m_stereoCalibrator.loadCameraParams(filePath.GetBuffer(0), stereoParams.cameraParams1))
			{
				LPCTSTR errMsg = _T("读入摄像头内参失败，找不到 cameraParams_left.yml 文件!");
				throw errMsg;
			}
			
			if (optCalib.doStereoCalib) 
			{
                filePath = m_workDir;
                filePath.AppendFormat("cameraParams_right.yml");
				if (0 == m_stereoCalibrator.loadCameraParams(filePath.GetBuffer(0), stereoParams.cameraParams2))
				{
					LPCTSTR errMsg = _T("读入摄像头内参失败，找不到 cameraParams_right.yml 文件!");
					throw errMsg;
				}
			}

			// 显示已读入已标定好的摄像头内参
			AfxMessageBox(_T("已读入标定好的摄像头内参"));
		}	

		// 进行摄像头标定
		if (optCalib.doStereoCalib)	// 双目标定和校正
		{
			stereoParams.cameraParams1.flags = optCalib.flagCameraCalib;
			stereoParams.cameraParams2.flags = optCalib.flagCameraCalib;
            stereoParams.flags = optCalib.flagStereoCalib;
            stereoParams.alpha = optCalib.alpha;

			bool needCalibSingleCamera = (CALIB_SINGLE_CAMERA_FIRST == optCalib.calibOrder);
			m_stereoCalibrator.calibrateStereoCamera(cornerDatas, stereoParams, needCalibSingleCamera);

			// 计算标定误差
			double avgErr = 0;
			m_stereoCalibrator.getStereoCalibrateError(cornerDatas, stereoParams, avgErr);
			char info[50];
			sprintf_s( info, "标定误差 = %7.4g", avgErr );
			CString ss;
			ss = info;
			AfxMessageBox(ss);

			// 执行双目校正
			m_stereoCalibrator.rectifyStereoCamera(cornerDatas, stereoParams, remapMatrixs, optCalib.rectifyMethod);

			AfxMessageBox(_T("已完成双目校正"));

            // 保存摄像头定标参数	
            filePath = m_workDir;
            filePath.AppendFormat("calib_paras.xml");
			m_stereoCalibrator.saveCalibrationDatas(filePath.GetBuffer(0), optCalib.rectifyMethod, cornerDatas, stereoParams, remapMatrixs);

            AfxMessageBox(_T("已保存定标参数"));

		} 
		else // 单目标定
		{
			StereoCalib::CameraParams cameraParams;
			cameraParams.flags = optCalib.flagCameraCalib;

			// 执行单目定标
            m_stereoCalibrator.calibrateSingleCamera(cornerDatas, cameraParams);

            // 保存定标参数
            filePath = m_workDir;
            filePath.AppendFormat("cameraParams.yml");
			m_stereoCalibrator.saveCameraParams(cameraParams, filePath.GetBuffer(0));

			// 计算标定误差
			double avgErr = 0;
			m_stereoCalibrator.getCameraCalibrateError(cornerDatas.objectPoints, cornerDatas.imagePoints1, cameraParams, avgErr);
			char info[50];
			sprintf_s( info, "已保存定标参数，标定误差 = %7.4g", avgErr );
			CString ss;
			ss = info;
			AfxMessageBox(ss);

			// 执行单目校正
			m_stereoCalibrator.rectifySingleCamera(cameraParams, remapMatrixs);

		}

		//////////////////////////////////////////////////////////////////////////
		// 显示标定效果
		{
			// 启用退出摄像机定标按钮
			GetDlgItem(IDC_BN_ExitCameraCalib)->EnableWindow(TRUE);

			MSG msg;
			while (true)
			{
				// MFC 窗口消息处理
				if(::PeekMessage(&msg, this->m_hWnd, 0, 0, PM_REMOVE)) 
				{ 
					if(msg.message == WM_QUIT) 
					{ 
						break; 
					}	
					::TranslateMessage(&msg); 
					::DispatchMessage(&msg);
				}

				// 载入图像
				lfCam >> frame0;
				if (optCalib.doStereoCalib) 
					riCam >> frame1;			
				if ( frame0.empty())	break;
				if (optCalib.doStereoCalib)
				{
					if ( frame1.empty())	break;
				}

				// 复制图像
				img0 = frame0.clone();
				if (optCalib.doStereoCalib) 
					img1 = frame1.clone();

				// 校正图像
				UpdateData(FALSE);
				m_pCheck = (CButton*)GetDlgItem(IDC_CHK_ShowCalibResult);
				bool showCalibrated = m_pCheck->GetCheck() > 0;
				if ( showCalibrated )
					m_stereoCalibrator.remapImage(img0, img1, img0, img1, remapMatrixs);
                
				// 显示校正效果
				if (optCalib.doStereoCalib) 
                {
                    // 画出等距的若干条横线，以比对 行对准 情况
                    for( int j = 0; j < img0.rows; j += 32 )		
                    {
                        line( img0, cvPoint(0,j),	cvPoint(img0.cols,j), CV_RGB(0,255,0)); 
                        line( img1, cvPoint(0,j),	cvPoint(img1.cols,j), CV_RGB(0,255,0)); 
                    }

                    F_ShowImage(img0, m_lfImage, IDC_PicLfCam);
					F_ShowImage(img1, m_riImage, IDC_PicRiCam);
                }
                else
                {
                    m_stereoCalibrator.showText(img0, "Distort");
                    F_ShowImage(img0, m_lfImage, IDC_PicLfCam);
                }
			}
		}

        filePath.ReleaseBuffer();
	}
	//////////////////////////////////////////////////////////////////////////
	// 错误信息处理
	catch (LPCTSTR errMsg)
	{
		AfxMessageBox(errMsg);
	}
	catch (cv::Exception& e)
	{
        char err[2048];
        sprintf_s(err, "发生错误: %s", e.what());
        CStringW errInfo(err);
        AfxMessageBox(errInfo);
	}
	catch (...)
	{
		AfxMessageBox(_T("发生未知错误！"));
	}

	// 禁用退出摄像机定标按钮
	GetDlgItem(IDC_BN_ExitCameraCalib)->EnableWindow(FALSE);

	//////////////////////////////////////////////////////////////////////////	
	if(lfCam.isOpened() || riCam.isOpened())
	{
		// 定标结束，恢复双目定标按钮
		GetDlgItem(IDC_BN2StereoCalib)->EnableWindow(TRUE);
        GetDlgItem(IDC_CBN2MethodList)->EnableWindow(TRUE);
        GetDlgItem(IDC_BN_CompDisp)->EnableWindow(TRUE);

		// 恢复正常显示
		DoShowOrigFrame();		
	}

	return;
}


/*----------------------------------
 * 功能 :	停止角点检测 按钮响应
 *----------------------------------
 * 函数 :	CStereoVisionDlg::OnBnClk_StopDetectCorners
 * 访问 :	private 
 * 返回 :	void
 *
 */
void CStereoVisionDlg::OnBnClk_ExitCameraCalib()
{
	// TODO: 在此添加控件通知处理程序代码
	// 发送退出消息
	::PostMessage(this->m_hWnd, WM_QUIT, 0, 0);
	// 禁用停止角点检测按钮
	GetDlgItem(IDC_BN_ExitCameraCalib)->EnableWindow(FALSE);
}


/*----------------------------
 * 功能 : 确认立体匹配的相关选项
 *----------------------------
 * 函数 : CStereoVisionDlg::DoParseOptionsOfStereoMatch
 * 访问 : private 
 * 返回 : void
 *
 * 参数 : opt	[i/o]	立体匹配选项
 */
bool CStereoVisionDlg::DoParseOptionsOfStereoMatch(OptionStereoMatch& opt)
{
    bool res = UpdateData(TRUE);
    if (!res)
        return false;

    if (m_nMaxDisp==0)
    {
        AfxMessageBox(_T("请先输入匹配算法参数"));
        return false;
    }

	// 确认计算视差的算法
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_BM, IDC_RAD_SGBM);
	opt.stereoMethod = m_nID_RAD == IDC_RAD_BM ? STEREO_BM :
		m_nID_RAD == IDC_RAD_SGBM ? STEREO_SGBM : STEREO_BM;
	// 确认左右视图的来源（摄像头 or 本地图片）
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_DispFromCam, IDC_RAD_DispFromImg);
	opt.readLocalImage = m_nID_RAD == IDC_RAD_DispFromImg;
	// 确认是否执行双目校正
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_StereoRectify);
	opt.useStereoRectify = m_pCheck->GetCheck() > 0;
	// 确认是否保存匹配结果
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_SaveAsVideo);
	opt.saveResults = m_pCheck->GetCheck() > 0;
	// 确认是否延时显示匹配效果
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_DelayProc);
	opt.delayEachFrame = m_pCheck->GetCheck() > 0;
	if (opt.readLocalImage)
	{
		opt.delayEachFrame = true;
		m_pCheck->SetCheck(1);
	}
	// 确认是否生成三维点云
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_ProjTo3D);
	opt.generatePointCloud = m_pCheck->GetCheck() > 0;

    return true;
}


/*----------------------------
 * 功能 : 更新 BM 求解器状态参数
 *----------------------------
 * 函数 : CStereoVisionDlg::DoUpdateStateBM
 * 访问 : private 
 * 返回 : void
 *
 */
void CStereoVisionDlg::DoUpdateStateBM()
{
	UpdateData(TRUE);
	m_stereoMatcher.m_BM.state->preFilterCap = m_nPreFiltCap;
	m_stereoMatcher.m_BM.state->SADWindowSize = m_nSADWinSiz;
	m_stereoMatcher.m_BM.state->minDisparity = m_nMinDisp;
	m_stereoMatcher.m_BM.state->numberOfDisparities = m_nMaxDisp;
	m_stereoMatcher.m_BM.state->textureThreshold = m_nTextThres;
	m_stereoMatcher.m_BM.state->uniquenessRatio = m_nUniqRatio;
	m_stereoMatcher.m_BM.state->speckleWindowSize = m_nSpeckWinSiz;
	m_stereoMatcher.m_BM.state->speckleRange = m_nSpeckRange;

}


/*----------------------------
 * 功能 : 更新 SGBM 求解器状态参数
 *----------------------------
 * 函数 : CStereoVisionDlg::DoUpdateStateSGBM
 * 访问 : private 
 * 返回 : void
 *
 * 参数 : imgChannels	[in]	图像通道数
 */
void CStereoVisionDlg::DoUpdateStateSGBM(int imgChannels)
{
	UpdateData(TRUE);
	m_stereoMatcher.m_SGBM.preFilterCap = m_nPreFiltCap;
	m_stereoMatcher.m_SGBM.SADWindowSize = m_nSADWinSiz;
	m_stereoMatcher.m_SGBM.P1 =  8 * imgChannels * m_nSADWinSiz * m_nSADWinSiz;
	m_stereoMatcher.m_SGBM.P2 = 32 * imgChannels * m_nSADWinSiz * m_nSADWinSiz;
	m_stereoMatcher.m_SGBM.minDisparity = m_nMinDisp;
	m_stereoMatcher.m_SGBM.numberOfDisparities = m_nMaxDisp;
	m_stereoMatcher.m_SGBM.uniquenessRatio = m_nUniqRatio;
	m_stereoMatcher.m_SGBM.speckleWindowSize = m_nSpeckWinSiz;
	m_stereoMatcher.m_SGBM.speckleRange = m_nSpeckRange;
	m_stereoMatcher.m_SGBM.fullDP = m_bFullDP;
}


/*----------------------------
 * 功能 : 计算视差 按钮响应
 *----------------------------
 * 函数 : CStereoVisionDlg::OnBnClk_DoCompDisp
 * 访问 : private 
 * 返回 : void
 *
 */
void CStereoVisionDlg::OnBnClk_DoCompDisp()
{
	// TODO: Add your control notification handler code here 

    //////////////////////////////////////////////////////////////////////////
    // 读入界面中的立体匹配选项设置
    OptionStereoMatch optMatch;
    if (!DoParseOptionsOfStereoMatch( optMatch )) 
        return;

	// 暂停显示摄像头画面的操作
	KillTimer(1);			

	GetDlgItem(IDC_BN_StopDispComp)->EnableWindow(TRUE);
	GetDlgItem(IDC_RAD_BM)->EnableWindow(FALSE);
	GetDlgItem(IDC_RAD_SGBM)->EnableWindow(FALSE);
	GetDlgItem(IDC_BN2StopCam)->EnableWindow(FALSE);
	GetDlgItem(IDC_BN_CompDisp)->EnableWindow(FALSE);
	GetDlgItem(IDC_BN2StereoCalib)->EnableWindow(FALSE);
    GetDlgItem(IDC_CBN2MethodList)->EnableWindow(FALSE);

	//////////////////////////////////////////////////////////////////////////
	// 参数初始化
	CStringA xmlPath;			// 定标结果数据文件
	vector<CStringA> imgFiles1; //左右视图文件路径序列
	vector<CStringA> imgFiles2;	
	int i = 0, j = 0;
	const char* img1_filename = NULL;
	const char* img2_filename = NULL;
	const char* xml_filename = NULL;

	cv::Mat img1, img2, img1p, img2p, disp, disp8u, pointCloud;
	LPCTSTR errMsg;

	try 
	{
		//////////////////////////////////////////////////////////////////////////
		// 选择/预载图像（摄像机 or 本地图片）
		if (optMatch.readLocalImage)
		{
			// 选择左视图
			imgFiles1 = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("选择左视图图像"),
				m_workDir
				);
			// 选择右视图
			imgFiles2 = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("选择右视图图像"),
				m_workDir
				);

			if( imgFiles1.empty() || imgFiles2.empty() )	
			{
				errMsg = _T("没有选中有效的图像文件!");
				throw errMsg;
			}

			img1_filename = imgFiles1[0];
			img2_filename = imgFiles2[0];
			img1 = imread(img1_filename);
			img2 = imread(img2_filename);
		} 
		else
		{
			lfCam >> img1;
			riCam >> img2;
		}

		//////////////////////////////////////////////////////////////////////////
		// 读取双目校正变换参数
		if( optMatch.useStereoRectify )
		{
			// 打开摄像头定标参数文件
			vector<CStringA> xmlFiles;
			xmlFiles = DoSelectFiles(
				_T("*.xml"), 
				OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
				_T("XML/YML file (*.xml; *.yml) |*.xml; *.yml | All Files (*.*) |*.*||"), 
				_T("选择摄像头定标参数文件"),
				m_workDir
				);
			if( xmlFiles.empty() )	
			{
				errMsg = _T("没有选中有效的摄像头定标参数文件!");			
				throw errMsg;
			}
			xmlPath = xmlFiles[0];			// 获取xml文件路径
			xml_filename = xmlPath;

			// 读入摄像头定标参数
			switch (m_stereoMatcher.init(img1.cols, img1.rows, xml_filename))
			{
			case 0:
			case -99:
				errMsg = _T("读取摄像头定标参数文件失败，请重新选择!");			
				throw errMsg;
			case -1:
				errMsg = _T("定标参数的图像尺寸与当前配置的图像尺寸不一致，请重新选择!");			
				throw errMsg;
			case -2:
				if (optMatch.generatePointCloud)
				{
					optMatch.generatePointCloud = false;
					errMsg = _T("定标文件对应的校正方法不是 BOUGUET 方法，无法生成三维点云!");			
					throw errMsg;
				}
				break;
			}

		}	
		else
			m_stereoMatcher.init(img1.cols, img1.rows, "");

		//////////////////////////////////////////////////////////////////////////
		// 开始计算图像视差
		m_stereoMatcher.m_BM.state->disp12MaxDiff = m_nDisp12MaxDiff;
		m_stereoMatcher.m_SGBM.disp12MaxDiff = m_nDisp12MaxDiff;

		int frameCount = 0;	//图像计数
		PointCloudAnalyzer pointCloudAnalyzer;
		clock_t tShowObjInfo = clock(), tStart, tPerFrame;
        CStringA strPerFrame;
		MSG msg;
		while(true)
		{
            tStart = clock();

			// MFC 窗口消息处理
			if(::PeekMessage(&msg, this->m_hWnd, 0, 0, PM_REMOVE)) 
			{ 
				if(msg.message == WM_QUIT) 
				{ 
					break; 
				}	
				::TranslateMessage(&msg); 
				::DispatchMessage(&msg);
			}

			// 载入图像
			if (optMatch.readLocalImage)
			{
				if (frameCount >= MIN(imgFiles1.size(), imgFiles2.size()))
					break;
				img1_filename = imgFiles1[frameCount];
				img2_filename = imgFiles2[frameCount];
				img1 = imread(img1_filename, 1);
				img2 = imread(img2_filename, 1);
				if(img1.empty() || img2.empty()) break;
				frameCount++;
			} 
			else
			{
				lfCam >> img1;
				riCam >> img2;
				if(img1.empty()) break;
			}

			// 预处理
			if (m_ProcMethod)
			{
				DoFrameProc(img1, img1);
				DoFrameProc(img2, img2);
			}

			// 执行双目匹配
			if (optMatch.stereoMethod == STEREO_BM)
			{
				DoUpdateStateBM();
				m_stereoMatcher.bmMatch(img1, img2, disp, img1p, img2p);
			} 
			else if (optMatch.stereoMethod == STEREO_SGBM)
			{
				DoUpdateStateSGBM(img1.channels());
				m_stereoMatcher.sgbmMatch(img1, img2, disp, img1p, img2p);
			}

			// 画出等距的若干条横线，以比对 行对准 情况
			for( j = 0; j < img1p.rows; j += 32 )		
			{
				line( img1p, cvPoint(0,j),	cvPoint(img1p.cols,j), CV_RGB(0,255,0)); 
				line( img2p, cvPoint(0,j),	cvPoint(img2p.cols,j), CV_RGB(0,255,0)); 
			}

			// 检测离摄像头最近的物体？
			if ( optMatch.generatePointCloud )
			{
				m_stereoMatcher.getPointClouds(disp, pointCloud);

				vector<PointCloudAnalyzer::ObjectInfo> objectInfos;
				pointCloudAnalyzer.detectNearObject(img1p, pointCloud, objectInfos);

				if (!objectInfos.empty() && (clock()-tShowObjInfo) > 500)
				{
					tShowObjInfo = clock();
					double fl = m_stereoMatcher.m_FL;
					m_ObjectDistance = objectInfos[0].distance; m_ObjectDistance = (int)(m_ObjectDistance * 10000) / 10000.;
					m_ObjectHeight = objectInfos[0].boundRect.height * objectInfos[0].distance / fl; m_ObjectHeight = (int)(m_ObjectHeight * 10000) / 10000.;
					m_ObjectWidth = objectInfos[0].boundRect.width * objectInfos[0].distance / fl; m_ObjectWidth = (int)(m_ObjectWidth * 10000) / 10000.;
					m_ObjectDisparity = disp.at<short>(objectInfos[0].nearest) / 16.;
                    UpdateData(FALSE);
				}
			}

            tPerFrame = clock() - tStart;
            strPerFrame.Format("（每帧 %d ms）", tPerFrame);

			// 切换视差图/视场图
            UpdateData(TRUE);
            m_stereoMatcher.setViewField(m_nViewWidth, m_nViewHeight, m_nViewDepth);
            m_nID_RAD = GetCheckedRadioButton(IDC_RAD_ColorDisp, IDC_RAD_SideView);
            switch ( m_nID_RAD )
            {
            case IDC_RAD_ColorDisp:
                m_stereoMatcher.getDisparityImage(disp, disp8u, true);
                GetDlgItem(IDC_STATIC_DispView)->SetWindowText(_T("彩色视差图") + CStringW(strPerFrame));
                break;
            case IDC_RAD_GrayDisp:
                m_stereoMatcher.getDisparityImage(disp, disp8u, false);
                GetDlgItem(IDC_STATIC_DispView)->SetWindowText(_T("灰度视差图") + CStringW(strPerFrame));
                break;
            case IDC_RAD_TopDownView:
                if ( optMatch.generatePointCloud )
                {
                    m_stereoMatcher.getTopDownView(pointCloud, disp8u, img1);
                    GetDlgItem(IDC_STATIC_DispView)->SetWindowText(_T("环境俯视图") + CStringW(strPerFrame));
                }
                else
                {
                    CheckRadioButton(IDC_RAD_ColorDisp, IDC_RAD_SideView, IDC_RAD_ColorDisp);			// 默认显示彩色视差图
                    m_stereoMatcher.getDisparityImage(disp, disp8u, true);
                }
                break;
            case IDC_RAD_SideView:
                if ( optMatch.generatePointCloud )
                {
                    m_stereoMatcher.getSideView(pointCloud, disp8u, img1);
                    GetDlgItem(IDC_STATIC_DispView)->SetWindowText(_T("环境侧视图") + CStringW(strPerFrame));
                }
                else
                {
                    CheckRadioButton(IDC_RAD_ColorDisp, IDC_RAD_SideView, IDC_RAD_ColorDisp);			// 默认显示彩色视差图
                    m_stereoMatcher.getDisparityImage(disp, disp8u, true);
                }
                break;
            default:
                m_stereoMatcher.getDisparityImage(disp, disp8u, true);
            }            
            UpdateData(FALSE);

			// 传送至MFC界面显示
			F_ShowImage( img1p, m_lfImage, IDC_PicLfCam );
			F_ShowImage( img2p, m_riImage, IDC_PicRiCam );
			F_ShowImage( disp8u, m_disparity, IDC_PicSynImg );	

			// 保存画面和视差图像
			if( optMatch.saveResults )
				F_Saveframe( img1, img2, disp);

			if( optMatch.delayEachFrame )
				Sleep(m_nDelayTime * 1000);
		}

		// 保存最后一帧景深图像的点云数据
		if ( optMatch.generatePointCloud )
		{
            CStringA filePath(m_workDir);
            filePath.AppendFormat("PointsClouds.txt");
			m_stereoMatcher.savePointClouds(pointCloud, filePath.GetBuffer(0));
            filePath.ReleaseBuffer();
		}

		// 对图像数据清零
		m_disparity = Scalar(0);
        F_ShowImage( m_disparity, m_disparity, IDC_PicSynImg );

		// 释放内存
		xmlPath.ReleaseBuffer();
	}
	catch (LPCTSTR ErrMsg)
	{
		AfxMessageBox(ErrMsg);
	}
	catch (cv::Exception& e)
    {
		char err[2048];
		sprintf_s(err, "发生错误: %s", e.what());
		CStringW errInfo(err);
		AfxMessageBox(errInfo);
	}
	catch (...)
	{
		AfxMessageBox(_T("发生未知错误！"));
	}

	GetDlgItem(IDC_RAD_BM)->EnableWindow(TRUE);
	GetDlgItem(IDC_RAD_SGBM)->EnableWindow(TRUE);
	GetDlgItem(IDC_BN2StopCam)->EnableWindow(TRUE);
	GetDlgItem(IDC_BN_CompDisp)->EnableWindow(TRUE);
	GetDlgItem(IDC_BN2StereoCalib)->EnableWindow(TRUE);
	GetDlgItem(IDC_CBN2MethodList)->EnableWindow(TRUE);
    GetDlgItem(IDC_BN_StopDispComp)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_DispView)->SetWindowText(_T("视差图"));

	// 返回显示实时画面
	DoShowOrigFrame();
	return;
}


/*----------------------------
 * 功能 : 停止计算视差，返回正常显示
 *----------------------------
 * 函数 : CStereoVisionDlg::OnBnClk_StopDispComp
 * 访问 : private 
 * 返回 : void
 *
 */
void CStereoVisionDlg::OnBnClk_StopDispComp()
{
	// TODO: Add your control notification handler code here

	// 发送退出消息
	::PostMessage(this->m_hWnd, WM_QUIT, 0, 0);
	GetDlgItem(IDC_BN_StopDispComp)->EnableWindow(FALSE);

	if (lfCam.isOpened() || riCam.isOpened())
	{
		// 启用部分按钮
		GetDlgItem(IDC_BN2StopCam)->EnableWindow(TRUE);
		GetDlgItem(IDC_BN2StereoCalib)->EnableWindow(TRUE);
		GetDlgItem(IDC_BN_CompDisp)->EnableWindow(TRUE);
		GetDlgItem(IDC_RAD_BM)->EnableWindow(TRUE);
		GetDlgItem(IDC_RAD_SGBM)->EnableWindow(TRUE);
	}

	return;
}


/*----------------------------
 * 功能 : 设置双目匹配算法的默认参数
 *----------------------------
 * 函数 : CStereoVisionDlg::OnBnClkDefaultStereoParam
 * 访问 : private 
 * 返回 : void
 *
 */
void CStereoVisionDlg::OnBnClkDefaultStereoParam()
{
	// TODO: Add your control notification handler code here
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_BM, IDC_RAD_GC);
	if (m_nID_RAD == IDC_RAD_BM)
	{
		m_nMinDisp = 0;	
		m_nMaxDisp = 64;
		m_nSADWinSiz = 19;
		m_nTextThres = 10;
		m_nDisp12MaxDiff = -1;
		m_nPreFiltCap = 31;
		m_nUniqRatio = 25;
		m_nSpeckRange = 32;
		m_nSpeckWinSiz = 100;
	} 
	else if(m_nID_RAD == IDC_RAD_SGBM)
	{
		m_nMinDisp = 0;	
		m_nMaxDisp = 64;
		m_nSADWinSiz = 7;
		m_nDisp12MaxDiff = -1;
		m_nPreFiltCap = 63;
		m_nUniqRatio = 25;
		m_nSpeckRange = 32;
		m_nSpeckWinSiz = 100;
		m_pCheck = (CButton*)GetDlgItem(IDC_CHK_fullDP);
		m_pCheck->SetCheck(0);
	}
	UpdateData(FALSE);
}


/*----------------------------
 * 功能 : 设置双目匹配算法的默认参数
 *----------------------------
 * 函数 : CStereoVisionDlg::OnBnClkDefaultViewfield
 * 访问 : private 
 * 返回 : void
 *
 */
void CStereoVisionDlg::OnBnClkDefaultViewfield()
{
    // TODO: 在此添加控件通知处理程序代码
    m_nViewWidth = 200;
    m_nViewHeight = 200;
    m_nViewDepth = 200;
    UpdateData(FALSE);
}


/*----------------------------
 * 功能 : 对已有的双目匹配参数清零
 *----------------------------
 * 函数 : CStereoVisionDlg::DoClearParamsOfStereoMatch
 * 访问 : private 
 * 返回 : void
 *
 * 参数 : void
 */
void CStereoVisionDlg::DoClearParamsOfStereoMatch(void)
{
	m_nMinDisp = 0;	
	m_nMaxDisp = 0;
	m_nSADWinSiz = 0;
	m_nTextThres = 0;
	m_nDisp12MaxDiff = -1;
	m_nPreFiltCap = 0;
	m_nUniqRatio = 0;
	m_nSpeckRange = 0;
	m_nSpeckWinSiz = 0;
	m_pCheck = (CButton*)GetDlgItem(IDC_CHK_fullDP);
	m_pCheck->SetCheck(0);
	UpdateData(FALSE);
	return;
}


/*----------------------------
 * 功能 : 点击选择 BM 算法，已有参数清零，使能相关控件
 *----------------------------
 * 函数 : CStereoVisionDlg::OnBnClkRad_BM
 * 访问 : private 
 * 返回 : void
 *
 */
void CStereoVisionDlg::OnBnClkRad_BM()
{
	// TODO: Add your control notification handler code here
	DoClearParamsOfStereoMatch();
	m_spinPreFiltCap.SetRange(0, 31);
	GetDlgItem(IDC_EDIT_minDisp)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_maxDisp)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SADWinSiz)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_textThres)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_disp12MaxDiff)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_preFiltCap)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_uniqRatio)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_speckRange)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_speckWinSiz)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHK_fullDP)->EnableWindow(FALSE);
}


/*----------------------------
 * 功能 : 点击选择 SGBM 算法，已有参数清零，使能相关控件
 *----------------------------
 * 函数 : CStereoVisionDlg::OnBnClkRad_SGBM
 * 访问 : private 
 * 返回 : void
 *
 */
void CStereoVisionDlg::OnBnClkRad_SGBM()
{
	// TODO: Add your control notification handler code here
	DoClearParamsOfStereoMatch();
	m_spinPreFiltCap.SetRange(0, 100);
	GetDlgItem(IDC_EDIT_minDisp)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_maxDisp)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SADWinSiz)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_textThres)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_disp12MaxDiff)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_preFiltCap)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_uniqRatio)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_speckRange)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_speckWinSiz)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHK_fullDP)->EnableWindow(TRUE);
}


/*----------------------------
 * 功能 : 设置最大视差值的旋转按钮  响应程序
 *----------------------------
 * 函数 : CStereoVisionDlg::OnDeltaposSpin_MaxDisp
 * 访问 : private 
 * 返回 : void
 *
 * 参数 : NMHDR * pNMHDR
 * 参数 : LRESULT * pResult
 */
void CStereoVisionDlg::OnDeltaposSpin_MaxDisp(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	UpdateData(TRUE);

	m_nMaxDisp += (int)pNMUpDown->iDelta * 16;
	if(m_nMaxDisp<16) 
		m_nMaxDisp = 16;
	if(m_nMaxDisp>240)
		m_nMaxDisp = 240;

	UpdateData(FALSE);
}


/*----------------------------
 * 功能 : 设置SAD窗口大小的旋转按钮  响应程序
 *----------------------------
 * 函数 : CStereoVisionDlg::OnDeltaposSpin_SADWinSiz
 * 访问 : private 
 * 返回 : void
 *
 * 参数 : NMHDR * pNMHDR
 * 参数 : LRESULT * pResult
 */
void CStereoVisionDlg::OnDeltaposSpin_SADWinSiz(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_BM, IDC_RAD_GC);
	if (m_nID_RAD == IDC_RAD_BM)
	{
		UpdateData(TRUE);
		m_nSADWinSiz += (int)pNMUpDown->iDelta * 2; 
		if(m_nSADWinSiz % 2 == 0)
			m_nSADWinSiz += 1;
		if(m_nSADWinSiz < 5)
			m_nSADWinSiz = 5;
		if(m_nSADWinSiz > 21)
			m_nSADWinSiz = 21;
		UpdateData(FALSE);
	}
	else if (m_nID_RAD == IDC_RAD_SGBM)
	{
		UpdateData(TRUE);
		m_nSADWinSiz += (int)pNMUpDown->iDelta * 2;
		if(m_nSADWinSiz % 2 == 0)
			m_nSADWinSiz += 1;
		if(m_nSADWinSiz < 1)
			m_nSADWinSiz = 1;
		if(m_nSADWinSiz > 11)
			m_nSADWinSiz = 11;
		UpdateData(FALSE);
	}
}


/*----------------------------
 * 功能 : 设置SpeckRange值的旋转按钮  响应程序
 *----------------------------
 * 函数 : CStereoVisionDlg::OnDeltaposSpin_SpeckRange
 * 访问 : private 
 * 返回 : void
 *
 * 参数 : NMHDR * pNMHDR
 * 参数 : LRESULT * pResult
 */
void CStereoVisionDlg::OnDeltaposSpin_SpeckRange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_BM, IDC_RAD_GC);
	if (m_nID_RAD == IDC_RAD_BM)
	{
		UpdateData(TRUE);
		m_nSpeckRange += (int)pNMUpDown->iDelta;
		if(m_nSpeckRange < 0)
			m_nSpeckRange = 0;
		if(m_nSpeckRange > 64)
			m_nSpeckRange = 64;
		UpdateData(FALSE);
	}
	else if (m_nID_RAD == IDC_RAD_SGBM)
	{
		UpdateData(TRUE);
		m_nSpeckRange += (int)pNMUpDown->iDelta * 16;
		if(m_nSpeckRange < 0)
			m_nSpeckRange = 0;
		if(m_nSpeckRange > 64)
			m_nSpeckRange = 64;
		UpdateData(FALSE);
	}
}


/*----------------------------
 * 功能 : 设置 视场宽度的旋转按钮  响应程序
 *----------------------------
 * 函数 : CStereoVisionDlg::OnDeltaposSpin_ViewWidth
 * 访问 : private 
 * 返回 : void
 *
 * 参数 : NMHDR * pNMHDR
 * 参数 : LRESULT * pResult
 */
void CStereoVisionDlg::OnDeltaposSpin_ViewWidth(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	UpdateData(TRUE);

	m_nViewWidth += (int)pNMUpDown->iDelta * 10;
	if(m_nViewWidth<60) 
		m_nViewWidth = 60;
	if(m_nViewWidth>600)
		m_nViewWidth = 600;

	UpdateData(FALSE);
}


/*----------------------------
 * 功能 : 设置 视场高度的旋转按钮  响应程序
 *----------------------------
 * 函数 : CStereoVisionDlg::OnDeltaposSpin_ViewHeight
 * 访问 : private 
 * 返回 : void
 *
 * 参数 : NMHDR * pNMHDR
 * 参数 : LRESULT * pResult
 */
void CStereoVisionDlg::OnDeltaposSpin_ViewHeight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	UpdateData(TRUE);

	m_nViewHeight += (int)pNMUpDown->iDelta * 10;
	if(m_nViewHeight<40) 
		m_nViewHeight = 40;
	if(m_nViewHeight>400)
		m_nViewHeight = 400;

    UpdateData(FALSE);
}


/*----------------------------
 * 功能 : 设置 视场深度的旋转按钮  响应程序
 *----------------------------
 * 函数 : CStereoVisionDlg::OnDeltaposSpin_ViewDepth
 * 访问 : private 
 * 返回 : void
 *
 * 参数 : NMHDR * pNMHDR
 * 参数 : LRESULT * pResult
 */
void CStereoVisionDlg::OnDeltaposSpin_ViewDepth(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	UpdateData(TRUE);

	m_nViewDepth += (int)pNMUpDown->iDelta * 10;
	if(m_nViewDepth<60) 
		m_nViewDepth = 60;
	if(m_nViewDepth>600)
		m_nViewDepth = 600;

	UpdateData(FALSE);
}


//////////////////////////////////////////////////////////////////////////
/*----------------------------------
 * 功能 :	初始化（创建）程序运行所需的文件夹
 *----------------------------------
 * 函数 :	CStereoVisionDlg::F_InitWorkDir
 * 访问 :	private 
 * 返回 :	程序运行时所在的文件夹路径
 */
CString CStereoVisionDlg::F_InitWorkDir()
{
	CStringA strPath;
 	TCHAR path[_MAX_PATH];
	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	TCHAR fname[_MAX_FNAME];
	TCHAR ext[_MAX_EXT];
	::GetModuleFileName(AfxGetApp()->m_hInstance, path, _MAX_PATH);
	_tsplitpath(path, drive, dir, fname, ext);

	strPath.Empty();
	strPath += CString(drive);
	strPath += CString(dir); 

    string saveDir = strPath;
    saveDir += "/Imgs";
    F_CheckDir(saveDir, true);
    saveDir += "/SaveFrame";
    F_CheckDir(saveDir, true);

	return CString(strPath);
}


//////////////////////////////////////////////////////////////////////////
/*----------------------------------
 * 功能 : 检查文件夹是否存在
 *----------------------------------
 * 函数 : CStereoVisionDlg::CheckDir
 * 访问 : private 
 * 返回 : 1 - 文件夹存在；0 - 不存在
 *
 * 参数 : dir		[in]	文件夹路径
 * 参数 : creatDir	[in]	是否创建文件夹
 */
bool CStereoVisionDlg::F_CheckDir(const string dir, bool creatDir /* = false */)
{
	bool RetVal = false;

	string fileName = dir;
	fileName += "\\*";

	_finddata_t FileInfo;
	long Handle = _findfirst(fileName.c_str(), &FileInfo);	

	if (Handle == -1L)
	{
		if (creatDir)
		{
			if(_mkdir(dir.c_str())==0)
			{
				RetVal = true;
			}
		}
	}
	else
	{
		RetVal = true;
		_findclose(Handle);
	}

	return RetVal;
}


/*----------------------------
 * 功能 : 显示图像
 *		 将要绘制的图像 src 复制到 des，然后绘制到控件号为 ID 的 Picture 控件
 *----------------------------
 * 函数 : CStereoVisionDlg::F_ShowImage
 * 访问 : private 
 * 返回 : void
 *
 * 参数 : src	[in]	待显示图像
 * 参数 : des	[in]	窗口图像
 * 参数 : ID		[in]	图像窗口控件ID
 */
void CStereoVisionDlg::F_ShowImage(Mat& src, Mat& des, UINT ID)
{
	if (src.empty())
	{
		return;
	}

    des = Scalar::all(0);

    // 计算将图片缩放到 Image 区域所需的比例因子
    double wRatio = des.cols / (double)src.cols;
    double hRatio = des.rows / (double)src.rows;
    double srcWH = src.cols / (double)src.rows;
    double desWH = des.cols / (double)des.rows;
    double scale = srcWH > desWH ? wRatio : hRatio;

    // 缩放后图片的宽和高
    int nw = (int)( src.cols * scale );
    int nh = (int)( src.rows * scale );

    // 为了将缩放后的图片存入 des 的正中部位，需计算图片在 des 左上角的期望坐标值
    int tlx = (int)((des.cols - nw) / 2);
    int tly = (int)((des.rows - nh) / 2);

    // 设置 des 的 ROI 区域，用来存入图片 img
    Mat desRoi = des(Rect(tlx, tly, nw, nh));

	// 如果src是单通道图像，则转换为三通道图像
	if (src.channels() == 1)
	{
		Mat src_c;
		cvtColor(src, src_c, CV_GRAY2BGR);
		// 对图片 src_t 进行缩放，并存入到 des 中
		resize(src_c, desRoi, desRoi.size());
	}
	else
	{
		// 对图片 src 进行缩放，并存入到 des 中
		resize( src, desRoi, desRoi.size() );
	}

	CDC* pDC = GetDlgItem( ID ) ->GetDC();		// 获得显示控件的 DC
	HDC hDC = pDC ->GetSafeHdc();				// 获取 HDC(设备句柄) 来进行绘图操作
	CRect rect;
	GetDlgItem(ID) ->GetClientRect( &rect );	// 获取控件尺寸位置
	CvvImage cimg;
	IplImage cpy = des;
	cimg.CopyOf( &cpy );						// 复制图片
	cimg.DrawToHDC( hDC, &rect );				// 将图片绘制到显示控件的指定区域内
	ReleaseDC( pDC );
}


/*----------------------------
 * 功能 : 保存当前的立体匹配结果至本地
 *		包括左右视图、视差图和视差数据
 *----------------------------
 * 函数 : CStereoVisionDlg::F_Saveframe
 * 访问 : private 
 * 返回 : void
 *
 * 参数 : Mat & lfImg
 * 参数 : Mat & riImg
 * 参数 : Mat & lfDisp
 */
void CStereoVisionDlg::F_Saveframe(Mat& lfImg, Mat&riImg, Mat& lfDisp)
{
	// TODO: Add your control notification handler code here
	static int nSavedFrames = 0;

	CStringA lfImgName(m_workDir), riImgName(m_workDir), lfDispName(m_workDir), xmlName(m_workDir);
	lfImgName.AppendFormat("Imgs\\SaveFrame\\left_%02d.png", nSavedFrames);
	riImgName.AppendFormat("Imgs\\SaveFrame\\right_%02d.png", nSavedFrames);
	lfDispName.AppendFormat("Imgs\\SaveFrame\\disp_%02d.png", nSavedFrames);
	xmlName.AppendFormat("Imgs\\SaveFrame\\disp_%02d.txt", nSavedFrames);
	nSavedFrames++;

    try
    {
        imwrite( lfImgName.GetBuffer(0), lfImg);
        imwrite( riImgName.GetBuffer(0), riImg);
        imwrite( lfDispName.GetBuffer(0), lfDisp);

        FILE* fp;
        fopen_s(&fp, xmlName.GetBuffer(0), "wt");
        fprintf(fp, "%d\n", lfDisp.rows);
        fprintf(fp, "%d\n", lfDisp.cols);
        for(int y = 0; y < lfDisp.rows; y++)
        {
            for(int x = 0; x < lfDisp.cols; x++)
            {
                short disp = lfDisp.at<short>(y, x);	
                fprintf(fp, "%d\n", disp);
            }
        }

        fclose(fp);
    }
    catch (...)
    {
    }

    lfDispName.ReleaseBuffer();
    lfImgName.ReleaseBuffer();
    riImgName.ReleaseBuffer();
    xmlName.ReleaseBuffer();
}


/*----------------------------
 * 功能 : 边缘检测
 *		 将原图像 src 执行 Canny 边缘检测，输出至图像 des
 *----------------------------
 * 函数 : CStereoVisionDlg::F_EdgeDetectCanny
 * 访问 : private 
 * 返回 : void
 *
 * 参数 : src	[in]	源图像
 * 参数 : des	[out]	边缘图像
 */
void CStereoVisionDlg::F_EdgeDetectCanny(Mat& src, Mat& des)
{
	Mat gray, edge, edge8u;

	edge = cv::Mat(src.size(), CV_16S);

	// 将源图像转为灰度图像
	if (src.channels() == 1)
		src.copyTo(gray);
	else
		cvtColor( src, gray, CV_RGB2GRAY );

	// 边缘检测
	Sobel(gray, edge, CV_16S, 0, 1);
	edge.convertTo(edge8u, CV_8U);

	// 将边缘检测图像转至输出图像格式
	if(des.channels() == 1)
		edge8u.copyTo(des);
	else
		cvtColor( edge8u, des, CV_GRAY2BGR );	
}


/*----------------------------
 * 功能 : 显示摄像头实时画面
 *----------------------------
 * 函数 : CStereoVisionDlg::DoShowOrigFrame
 * 访问 : private 
 * 返回 : void
 *
 */
void CStereoVisionDlg::DoShowOrigFrame(void)
{
	m_CBNMethodList.SetCurSel(0);
	m_ProcMethod = SHOW_ORIGINAL_FRAME;
	SetTimer(1, 50, NULL);	// 50ms 定时显示
}


/*----------------------------
 * 功能 : 对帧图像进行处理
 *----------------------------
 * 函数 : CStereoVisionDlg::DoFrameProc
 * 访问 : private 
 * 返回 : void
 *
 * 参数 : src	[in]	源图像
 * 参数 : des	[out]	处理后图像
 */
void  CStereoVisionDlg::DoFrameProc(Mat& src, Mat& dst)
{
	try
	{
		switch( m_ProcMethod )
		{
		case SHOW_EDGE_IMAGE:
			{
				F_EdgeDetectCanny(src, dst);
			}
			break;
		case SHOW_EQUAL_HISTOGRAM:
			{
				vector<Mat> rgb;
				// 分解各个分量
				split(src, rgb);
				// 对各个分量依次进行直方图均衡
				for (int i=0;i<3;i++)
				{
					equalizeHist(rgb[i], rgb[i]);
				}
				// 合并各分量
				merge(rgb, dst);
			}
			break;
		case SHOW_CONVERT_COLOR:
			{
				m_nID_RAD = GetCheckedRadioButton(IDC_RAD_ToHSV, IDC_RAD_ToXYZ);
				int type = 
					m_nID_RAD == IDC_RAD_ToHSV ? CV_BGR2HSV :
					m_nID_RAD == IDC_RAD_ToHLS ? CV_BGR2HLS :		
					m_nID_RAD == IDC_RAD_ToLab ? CV_BGR2Lab :	
					m_nID_RAD == IDC_RAD_ToLuv ? CV_BGR2Luv :	
					m_nID_RAD == IDC_RAD_ToYCrCb ? CV_BGR2YCrCb :
					CV_BGR2XYZ ;
				cvtColor(src, dst, type);
			}
			break;
		}
	}
	catch (cv::Exception& e)
	{
		char err[2048];
		sprintf_s(err, "发生错误: %s", e.what());
		CStringW errInfo;
		errInfo = err;
		AfxMessageBox(errInfo);
	}
	catch (...)
	{
		AfxMessageBox(_T("发生未知错误！"));
	}

	return;
}


//////////////////////////////////////////////////////////////////////////

void CStereoVisionDlg::OnClose()
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    if (lfCam.isOpened() || riCam.isOpened())
    {
        AfxMessageBox(_T("请先关闭摄像头！"));
        return;
    }

    CDialog::OnClose();
}

