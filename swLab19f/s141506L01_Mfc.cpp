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
	CFile file;// CFile class(C���� FILE�� ����)
	LPCTSTR str = pathName;// CString�� ������ class
	
	// �Ʒ� ��� �����ͷ� �� ������ �� �̹����� �о�� �ؼ�
	CDib  *pDibF;// DIB class
	LONG  *width, *height;
	int   *depth;
	LPBITMAPINFO *bmInfoHd;// DIB infoHeader

	/////////////*pointer setting�ϴ� ��/��.*///////////////
	if (which == 1) {
		pDibF = &m_dibFile1;	// when reading image1
		width = &m_width1; height = &m_height1;
		depth = &m_depth1;  bmInfoHd = &mg_lpBMIH1;
		readImageF1 = true;
	}
	else if (which == 2) {
		// image2�� image1 ���� �Ŀ��� ���� �� �ִ�
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

	///////////////////////****�̹��� �д� �κ�******///////////////////////////
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

	//�޽��� ��� �� �׸��� ��û
	CString msga, msgb;
	msga.Format(L"Read an image from %s and save it to image %d", pathName, which);
	msgb.Format(L"  Its size and depth are (w = %d, h = %d, depth = %d)",
		*width, *height, *depth);
	showMessage(msga); 
	showMessage(msgb);

	g_pView->Invalidate();//���⼭ pView�κ��� �׸��� ��û.
}

/*�̹��� �׸��� �Լ�:OnDraw���� ȣ��*/
void SWL01::drawImage(CDC *pDC, int dcLTx, int dcLTy, int which) {
	if (which == 1) {
		m_dibFile1.Draw(pDC, CPoint(dcLTx, dcLTy), CSize(m_width1, m_height1));
	}
	else if (which == 2) {
		m_dibFile2.Draw(pDC, CPoint(dcLTx + 20 + m_width1, dcLTy), CSize(m_width2, m_height2));
	}
}