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

	//픽셀값을 1/2로 줄여서 어둡게 만드는 부분.
	int h = (int)m_height1, w = (int)m_width1;
	m_MatR = Mat(h, w, m_Mat1.type());
	for (int c = 0; c < h; c++)
		for (int r = 0; r < w; r++)
			m_MatR.at<uchar>(c, r) = m_Mat1.at<uchar>(c, r) * 1 / 2;
	

	Create_bmiInfoHeader(&m_MatR); // 인포헤더를 갱신
	processedF = true; // 처리 완료를 flag을 통하여 알린다
	g_pView->Invalidate(); // OnDraw를 호출한다

}

void SWL01::BrightenGrayscaleImage(void) {
	Mat * pMat = nullptr; // m_Mat을 처리할 포인터 -> 필요한가?

	//1번 이미지 - 처리할 이미지가 열렸는지 우선 확인
	if (readImageF1 == false) {
		AfxMessageBox(L"Read image1 first!", MB_OK, 0);
		return;
	}

	//8bit grayscale image인지 여부를 확인.
	pMat = &m_Mat1;
	string s1 = "8UC1";
	if (type2str((*pMat).type()).compare(s1) != 0) {//compare는 같으면 0을 리턴하는 미친 함수
		AfxMessageBox(L"Only 8bit grayscale image can be processed!", MB_OK, 0);
		return;
	}


	//픽셀값을 2배로 만들어 밝게 만드는 부분. 이 때, 255를 초과하지 않도록 한다.
	int h = (int)m_height1, w = (int)m_width1;
	uchar tmpPixel = 0;
	m_MatR = Mat(h, w, m_Mat1.type());
	for (int c = 0; c < h; c++)
		for (int r = 0; r < w; r++) {
			tmpPixel = m_Mat1.at<uchar>(c, r);//tmpPixel = m_Mat1.at<uchar>(c,r) * 2
			//tmpPixel에 2배를 곱해버리면 안되는게, 8bit뿐이라 오버플로우 가능. 따라서, 곱해서 255가 넘지 않는 지 곱하기 전에 확인해야함.
			if (tmpPixel >= 128) 
				m_MatR.at<uchar>(c, r) = 255;
			else
				m_MatR.at<uchar>(c, r) = tmpPixel * 2;//곱해서 255를 넘지 않으면, *2한 값을 저장.
		}


	Create_bmiInfoHeader(&m_MatR); // 인포헤더를 갱신
	processedF = true; // 처리 완료를 flag을 통하여 알린다
	g_pView->Invalidate(); // OnDraw를 호출한다

}