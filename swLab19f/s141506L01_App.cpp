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

void SWL01::Color24toGrayscale(void) {
	Mat * pMat = nullptr; // m_Mat을 처리할 포인터 -> 필요한가?

	//1번 이미지 - 처리할 이미지가 열렸는지 우선 확인
	if (readImageF1 == false) {
		AfxMessageBox(L"Read image1 first!", MB_OK, 0);
		return;
	}

	//24bit color image인지 여부를 확인.
	pMat = &m_Mat1;
	string s1 = "8UC3";
	if (type2str((*pMat).type()).compare(s1) != 0) {//compare는 같으면 0을 리턴하는 미친 함수
		AfxMessageBox(L"Only 24bit color image can be processed!", MB_OK, 0);
		return;
	}

	//
	int h = (int)m_height1, w = (int)m_width1;
	m_MatR = Mat(h, w, CV_8UC1);//변환 결과는 8비트 그레이스케일
	
	for (int r = 0; r < h; r++) {
		uchar *pMatRow = m_Mat1.ptr<uchar>(r);
		for (int c = 0; c < w; c++) {
			//GRAY = 0.299R + 0.587G + 0.114B
			m_MatR.at<uchar>(r, c) = pMatRow[3 * c] * 0.299 + pMatRow[3 * c + 1] * 0.587 + pMatRow[3 * c + 2] * 0.114;
		}
	}

	Create_bmiInfoHeader(&m_MatR); // 인포헤더를 갱신
	processedF = true; // 처리 완료를 flag을 통하여 알린다
	g_pView->Invalidate(); // OnDraw를 호출한다
}

void SWL01::Color16toGrayscale() {
	Mat * pMat = nullptr; // m_Mat을 처리할 포인터 -> 필요한가?

	//1번 이미지 - 처리할 이미지가 열렸는지 우선 확인
	if (readImageF1 == false) {
		AfxMessageBox(L"Read image1 first!", MB_OK, 0);
		return;
	}

	//16bit color image인지 여부를 확인.
	pMat = &m_Mat1;
	string s1 = "16UC1";
	if (type2str((*pMat).type()).compare(s1) != 0) {//compare는 같으면 0을 리턴하는 미친 함수
		AfxMessageBox(L"Only 16bit color image can be processed!", MB_OK, 0);
		return;
	}

	int h = (int)m_height1, w = (int)m_width1;
	m_MatR = Mat(h, w, CV_8UC1);//변환 결과는 8비트 그레이스케일

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
			red = red & 31; green = green & 31; blue = blue & 31;//right shift하면서 남아있는 부호비트들 날리는 작업 + 필요한 5bit만 남기기.
			
			uchar result = (uchar)(red * 0.299 + green * 0.587 + blue * 0.114);

			result *= 8;//scale up

			//GRAY = 0.299R + 0.587G + 0.114B
			m_MatR.at<uchar>(r, c) = result;
			//m_MatR.at<ushort>(r, c) = (*pMat).at<ushort>(r, c);
		}
	}

	Create_bmiInfoHeader(&m_MatR); // 인포헤더를 갱신
	processedF = true; // 처리 완료를 flag을 통하여 알린다
	g_pView->Invalidate(); // OnDraw를 호출한다
}