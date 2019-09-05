
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "swLab19f.h"

#include "MainFrm.h"
#include "swLab19fDoc.h"
#include "swLab19fView.h"
#include "MsgView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()//창 크기 변화시 발생되는 메시지.
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	return 0;
}
/*MFC 분할창 관련 코드*/
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	BOOL flag = m_wndSplitter.CreateStatic(this, 2, 1);		// *** 창을 2 열로 나누고
	if (flag)
	{	// *** 각 창별 뷰를 선언한다
		m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CswLab19fView), CSize(100, 100), pContext);// 위 창은 C…View 창으로 사용(그리기 창)
		m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CRichEditView), CSize(100, 100), pContext);// 아래 창은 문자 출력용으로 사용
		/*CRichEditView는 문서 처리 기능을 갖는 클래스인데, 이를 통하여 문자열 출력 함수가 있는 MsgView.cpp (~.h) 두 파일
		을 프로젝트에 복사, 등록(1)하고, 다음 코드를 추가한다. 현재 파일의 헤더에는 
		#include "swLab19fDoc.h"
		#include "swLab19fView.h"
		#include "MsgView.h"추가.*/
		initMessage((CRichEditView*)m_wndSplitter.GetPane(1, 0));
		m_bSplitter = true;
	}
	return flag;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

/*함수 OnSize( )는 View를 항상 8 (이미지) : 2 (문자열)로 나누
어 주는 기능을 수행한다*/
void CMainFrame::OnSize(UINT nType, int cx, int cy) {
	CFrameWnd::OnSize(nType, cx, cy);
	if (m_bSplitter) {
		m_wndSplitter.SetRowInfo(0, int(cy * 0.8), 10);
		m_wndSplitter.RecalcLayout();
	}
}
// CMainFrame 메시지 처리기

