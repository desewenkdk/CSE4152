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

	//�ȼ����� 1/2�� �ٿ��� ��Ӱ� ����� �κ�.
	int h = (int)m_height1, w = (int)m_width1;
	m_MatR = Mat(h, w, m_Mat1.type());
	for (int c = 0; c < h; c++)
		for (int r = 0; r < w; r++)
			m_MatR.at<uchar>(c, r) = m_Mat1.at<uchar>(c, r) * 1 / 2;
	

	Create_bmiInfoHeader(&m_MatR); // ��������� ����
	processedF = true; // ó�� �ϷḦ flag�� ���Ͽ� �˸���
	g_pView->Invalidate(); // OnDraw�� ȣ���Ѵ�

}

void SWL01::BrightenGrayscaleImage(void) {
	Mat * pMat = nullptr; // m_Mat�� ó���� ������ -> �ʿ��Ѱ�?

	//1�� �̹��� - ó���� �̹����� ���ȴ��� �켱 Ȯ��
	if (readImageF1 == false) {
		AfxMessageBox(L"Read image1 first!", MB_OK, 0);
		return;
	}

	//8bit grayscale image���� ���θ� Ȯ��.
	pMat = &m_Mat1;
	string s1 = "8UC1";
	if (type2str((*pMat).type()).compare(s1) != 0) {//compare�� ������ 0�� �����ϴ� ��ģ �Լ�
		AfxMessageBox(L"Only 8bit grayscale image can be processed!", MB_OK, 0);
		return;
	}


	//�ȼ����� 2��� ����� ��� ����� �κ�. �� ��, 255�� �ʰ����� �ʵ��� �Ѵ�.
	int h = (int)m_height1, w = (int)m_width1;
	uchar tmpPixel = 0;
	m_MatR = Mat(h, w, m_Mat1.type());
	for (int c = 0; c < h; c++)
		for (int r = 0; r < w; r++) {
			tmpPixel = m_Mat1.at<uchar>(c, r);//tmpPixel = m_Mat1.at<uchar>(c,r) * 2
			//tmpPixel�� 2�踦 ���ع����� �ȵǴ°�, 8bit���̶� �����÷ο� ����. ����, ���ؼ� 255�� ���� �ʴ� �� ���ϱ� ���� Ȯ���ؾ���.
			if (tmpPixel >= 128) 
				m_MatR.at<uchar>(c, r) = 255;
			else
				m_MatR.at<uchar>(c, r) = tmpPixel * 2;//���ؼ� 255�� ���� ������, *2�� ���� ����.
		}


	Create_bmiInfoHeader(&m_MatR); // ��������� ����
	processedF = true; // ó�� �ϷḦ flag�� ���Ͽ� �˸���
	g_pView->Invalidate(); // OnDraw�� ȣ���Ѵ�

}