#include "stdafx.h"
#include "s141506L01_Mfc.h"

void SWL01::DarkenGrayscaleImage(void) {
	Mat * pMat = nullptr; // m_Mat�� ó���� ������ -> �ʿ��Ѱ�?

	//1�� �̹��� - ó���� �̹����� ���ȴ��� �켱 Ȯ��
	if (readImageF1 == false) {
		AfxMessageBox(L"Read image1 first!", MB_OK, 0);
		return;
	}

	//8bit grayscale image���� ���θ� Ȯ��.
	pMat = &m_Mat1;
	string s1 = "8UC1";
	if (type2str((*pMat).type()).compare(s1)!=0) {//compare�� ������ 0�� �����ϴ� ��ģ �Լ�
		AfxMessageBox(L"Only 8bit grayscale image can be processed!", MB_OK, 0);
		return;
	}

}