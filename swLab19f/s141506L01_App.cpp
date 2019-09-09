#include "stdafx.h"
#include "s141506L01_Mfc.h"

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

}