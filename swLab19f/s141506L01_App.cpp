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

void SWL01::Color24toGrayscale(void) {
	Mat * pMat = nullptr; // m_Mat�� ó���� ������ -> �ʿ��Ѱ�?

	//1�� �̹��� - ó���� �̹����� ���ȴ��� �켱 Ȯ��
	if (readImageF1 == false) {
		AfxMessageBox(L"Read image1 first!", MB_OK, 0);
		return;
	}

	//24bit color image���� ���θ� Ȯ��.
	pMat = &m_Mat1;
	string s1 = "8UC3";
	if (type2str((*pMat).type()).compare(s1) != 0) {//compare�� ������ 0�� �����ϴ� ��ģ �Լ�
		AfxMessageBox(L"Only 24bit color image can be processed!", MB_OK, 0);
		return;
	}

	//
	int h = (int)m_height1, w = (int)m_width1;
	m_MatR = Mat(h, w, CV_8UC1);//��ȯ ����� 8��Ʈ �׷��̽�����
	
	for (int r = 0; r < h; r++) {
		uchar *pMatRow = m_Mat1.ptr<uchar>(r);
		for (int c = 0; c < w; c++) {
			//GRAY = 0.299R + 0.587G + 0.114B
			m_MatR.at<uchar>(r, c) = pMatRow[3 * c] * 0.299 + pMatRow[3 * c + 1] * 0.587 + pMatRow[3 * c + 2] * 0.114;
		}
	}

	Create_bmiInfoHeader(&m_MatR); // ��������� ����
	processedF = true; // ó�� �ϷḦ flag�� ���Ͽ� �˸���
	g_pView->Invalidate(); // OnDraw�� ȣ���Ѵ�
}

void SWL01::Color16toGrayscale() {
	Mat * pMat = nullptr; // m_Mat�� ó���� ������ -> �ʿ��Ѱ�?

	//1�� �̹��� - ó���� �̹����� ���ȴ��� �켱 Ȯ��
	if (readImageF1 == false) {
		AfxMessageBox(L"Read image1 first!", MB_OK, 0);
		return;
	}

	//16bit color image���� ���θ� Ȯ��.
	pMat = &m_Mat1;
	string s1 = "16UC1";
	if (type2str((*pMat).type()).compare(s1) != 0) {//compare�� ������ 0�� �����ϴ� ��ģ �Լ�
		AfxMessageBox(L"Only 16bit color image can be processed!", MB_OK, 0);
		return;
	}

	int h = (int)m_height1, w = (int)m_width1;
	m_MatR = Mat(h, w, CV_8UC1);//��ȯ ����� 8��Ʈ �׷��̽�����

	//m_MatR = Mat(h, w, CV_16UC1);
	for (int r = 0; r < h; r++) {
		unsigned short *pixel1 = (*pMat).ptr<unsigned short>(r);
		for (int c = 0; c < w; c++) {
			//ushort pixel = m_Mat1.at<ushort>(r, c);
			
			//pixel <<= 1;
			unsigned short red = pixel1[c];// = pixel & 0 111110000000000;
			unsigned short green = pixel1[c];// = pixel & 0 000001111100000;
			unsigned short blue = pixel1[c];// = pixel & 0 000000000011111;
			

			red >> 10; green >>= 5; //blue >>= 0;
			red = red & 31; green = green & 31; blue = blue & 31;//right shift�ϸ鼭 �����ִ� ��ȣ��Ʈ�� ������ �۾� + �ʿ��� 5bit�� �����.
			
			uchar result = (uchar)(red * 0.299 + green * 0.587 + blue * 0.114);

			result *= 8;//scale up

			//GRAY = 0.299R + 0.587G + 0.114B
			m_MatR.at<uchar>(r, c) = result;
			//m_MatR.at<ushort>(r, c) = (*pMat).at<ushort>(r, c);
		}
	}

	Create_bmiInfoHeader(&m_MatR); // ��������� ����
	processedF = true; // ó�� �ϷḦ flag�� ���Ͽ� �˸���
	g_pView->Invalidate(); // OnDraw�� ȣ���Ѵ�
}