#include "stdafx.h"
#include "swLab19fDoc.h"
#include "swLab19fView.h"
#include "MainFrm.h"

#include "s141506L01_Mfc.h"
#include "CDIB.H"
#include "s141506L01_ext.h"

void SWL01::DarkenGrayscaleImage(void) {
	Mat * pMat = nullptr; // m_Mat을 처리할 포인터 -> 필요한가?

	//1번 이미지 - 처리할 이미지가 열렸는지 우선 확인
	if (readImageF1 == false) {
		AfxMessageBox(L"Read image1 first!", MB_OK, 0);
		return;
	}

	//8bit grayscale image인지 여부를 확인.
	pMat = &m_Mat1;
	string s1 = "8UC1";
	if (type2str((*pMat).type()).compare(s1)!=0) {//compare는 같으면 0을 리턴하는 미친 함수
		AfxMessageBox(L"Only 8bit grayscale image can be processed!", MB_OK, 0);
		return;
	}

	int h = (int)m_height1, w = (int)m_width1;
	m_MatR = Mat(h, w, m_Mat1.type());
	for (int c = 0; c < h; c++)
		for (int r = 0; r < w; r++)
			m_MatR.at<uchar>(c, r) = m_Mat1.at<uchar>(c, r) * 1 / 2;
	

	Create_bmiInfoHeader(&m_MatR); // 인포헤더를 갱신
	processedF = true; // 처리 완료를 flag을 통하여 알린다
	g_pView->Invalidate(); // OnDraw를 호출한다

}