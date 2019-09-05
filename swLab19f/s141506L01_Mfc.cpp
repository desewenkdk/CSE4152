#include "stdafx.h"
#include "swLab19fDoc.h"
#include "swLab19fView.h"
#include "MainFrm.h"

#include "s141506L01_Mfc.h"
#include "CDIB.H"


SWL01 SWL01_inst; // SWL01 instance
CswLab19fView *g_pView = NULL; // View instance
CMainFrame *g_pMainF = NULL; // Frame instant

void SWL01::readImage(CString pathName, int which) {
	// read an image & store it to img_org
	CFile file;// CFile class(C에서 FILE과 유사)
	LPCTSTR str = pathName;// CString과 유사한 class
	
	// 아래 모두 포인터로 한 이유는 두 이미지를 읽어야 해서
	CDib  *pDibF;// DIB class
	LONG  *width, *height;
	int   *depth;
	LPBITMAPINFO *bmInfoHd;// DIB infoHeader

	/////////////*pointer setting하는 부/분.*///////////////
	if (which == 1) {
		pDibF = &m_dibFile1;	// when reading image1
		width = &m_width1; height = &m_height1;
		depth = &m_depth1;  bmInfoHd = &mg_lpBMIH1;
		readImageF1 = true;
	}
	else if (which == 2) {
		// image2는 image1 읽은 후에나 읽을 수 있다
		if (readImageF1 == false) {
			AfxMessageBox(L"Read image1 first!", MB_OK, 0);
			return;
		}
		pDibF = &m_dibFile2;	// when reading addtional image2
		width = &m_width2; height = &m_height2;
		depth = &m_depth2;  bmInfoHd = &mg_lpBMIH2;
		readImageF2 = true;
	}
	////////////////////////////////////////////////////////////////////////

	///////////////////////****이미지 읽는 부분******///////////////////////////
	(*pDibF).Empty();	// clear any previouse read image
	file.Open(str, CFile::modeRead);
	if ((*pDibF).Read(&file) != TRUE) {
		file.Close();
		return;
	}
	file.Close();
	*width = ((*pDibF).m_lpBMIH)->biWidth;
	*height = ((*pDibF).m_lpBMIH)->biHeight;
	*depth = ((*pDibF).m_lpBMIH)->biBitCount;
	*bmInfoHd = (LPBITMAPINFO)((*pDibF).m_lpBMIH);

	processedF = false;	// will be true after doing somthing
	////////////////////////////////////////////////////////////////////////

	//메시지 출력 및 그리기 요청
	CString msga, msgb;
	msga.Format(L"Read an image from %s and save it to image %d", pathName, which);
	msgb.Format(L"  Its size and depth are (w = %d, h = %d, depth = %d)",
		*width, *height, *depth);
	showMessage(msga); 
	showMessage(msgb);

	g_pView->Invalidate();//여기서 pView로부터 그리기 요청.
}

/*이미지 그리는 함수:OnDraw에서 호출*/
void SWL01::drawImage(CDC *pDC, int dcLTx, int dcLTy, int which) {
	if (which == 1) {
		m_dibFile1.Draw(pDC, CPoint(dcLTx, dcLTy), CSize(m_width1, m_height1));
	}
	else if (which == 2) {
		m_dibFile2.Draw(pDC, CPoint(dcLTx + 20 + m_width1, dcLTy), CSize(m_width2, m_height2));
	}
}