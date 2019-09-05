#pragma once
#include <opencv2/opencv.hpp> //OpenCV header
#include "MsgView.h"//문자열 출력 함수:CString
#include "CDIB.H"//~.bmp처리모듈헤더

using namespace std;
using namespace cv;

class SWL01 {
protected:
	// DIB data(image1) (read from a .bmp file)
	CDib m_dibFile1;
	LONG m_width1, m_height1; // height and width
	int m_depth1; // bits per pixel
	LPBITMAPINFO mg_lpBMIH1; // bmp infoHeader

	// DIB data(image2)
	CDib	m_dibFile2;
	LONG	m_width2, m_height2;	// height and width
	int     m_depth2;				// bits per pixel
	LPBITMAPINFO mg_lpBMIH2;		// bmp infoHeader

public:
	bool readImageF1;	// set true after reading an image1
	bool readImageF2;	// set true after reading an image2
	bool processedF;    // set true when any processing is done

	SWL01() {//생성자
		readImageF1 = false;
		readImageF2 = false;
		processedF = false;
	}
	~SWL01() {//소멸자
	}
	// read an image & store it to img_org
	void readImage(CString pathName, int which);

	void drawImage(CDC *pDC, int dcLTx, int dcLTy, int which);//image display해주는 함수
};