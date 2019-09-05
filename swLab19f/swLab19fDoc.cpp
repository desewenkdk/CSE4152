
// swLab19fDoc.cpp: CswLab19fDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "swLab19f.h"
#endif

#include "swLab19fDoc.h"
//page35에서 추가
#include "swLab19fView.h"
#include "MainFrm.h"
#include "s141506L01_Mfc.h"
#include "s141506L01_ext.h" 
///////////////////////////////////
#include <propkey.h>




#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CswLab19fDoc

IMPLEMENT_DYNCREATE(CswLab19fDoc, CDocument)

BEGIN_MESSAGE_MAP(CswLab19fDoc, CDocument)
	ON_COMMAND(ID_FOPEN01, &CswLab19fDoc::On_FOpen1)
	ON_COMMAND(ID_FOPEN02, &CswLab19fDoc::On_FOpen2)
END_MESSAGE_MAP()


// CswLab19fDoc 생성/소멸

CswLab19fDoc::CswLab19fDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CswLab19fDoc::~CswLab19fDoc()
{
}

BOOL CswLab19fDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CswLab19fDoc serialization

void CswLab19fDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CswLab19fDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CswLab19fDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CswLab19fDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CswLab19fDoc 진단

#ifdef _DEBUG
void CswLab19fDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CswLab19fDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CswLab19fDoc 명령


void CswLab19fDoc::On_FOpen1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFileDialog dlgfile(TRUE);
	// show file open dialog
	/*이 코드는 파일 선택창을 통하여 파일을 선택하고 이의 경
로 및 파일 이름을 pathName에 저장한다.*/
	if (IDOK == dlgfile.DoModal()) {
		CString pathName = dlgfile.GetPathName();
		SWL01_inst.readImage(pathName, 1);//SWL01 클 래 스 의 인 스 턴 스 로s074419L01_Mfc.cpp에 광역 변수로 선언할 것
	}
}

//이미지배치, 이미지허용여부는 이미 .Mfc.cpp에서 구현됨
void CswLab19fDoc::On_FOpen2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFileDialog dlgfile(TRUE);
	// show file open dialog
	/*이 코드는 파일 선택창을 통하여 파일을 선택하고 이의 경
로 및 파일 이름을 pathName에 저장한다.*/
	if (IDOK == dlgfile.DoModal()) {
		CString pathName = dlgfile.GetPathName();
		SWL01_inst.readImage(pathName, 2);//2번째 이미지이므로, 이미지번호는2
	}
}
