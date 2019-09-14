#include "stdafx.h"
#include "swLab19fDoc.h"
#include "swLab19fView.h"
#include "MainFrm.h"

#include "s141506L01_Mfc.h"
#include "CDIB.H"
#include "s141506L01_ext.h"

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

	int h = (int)m_height1, w = (int)m_width1;
	m_MatR = Mat(h, w, m_Mat1.type());
	for (int c = 0; c < h; c++)
		for (int r = 0; r < w; r++)
			m_MatR.at<uchar>(c, r) = m_Mat1.at<uchar>(c, r) * 1 / 2;
	

	Create_bmiInfoHeader(&m_MatR); // ��������� ����
	processedF = true; // ó�� �ϷḦ flag�� ���Ͽ� �˸���
	g_pView->Invalidate(); // OnDraw�� ȣ���Ѵ�

}