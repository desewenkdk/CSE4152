#pragma once
#include <opencv2/opencv.hpp> //OpenCV header
#include "MsgView.h"//문자열 출력 함수:CString
#include "CDIB.H"//~.bmp처리모듈헤더

using namespace std;
using namespace cv;

string type2str(int type);

class SWL01 {
private:
	BYTE tmp[sizeof(BITMAPINFO) +  255*sizeof(RGBQUAD)];//인포헤더저장영역
protected:
	LPBITMAPINFO mg_lpBMIHR = (LPBITMAPINFO)&tmp;//tmp가 위의 저 인포헤더. 저장은 byte타입, 꺼내쓸땐, lp형태로.

	// DIB data(image1) (read from a .bmp file)
	CDib m_dibFile1;
	LONG m_width1, m_height1; // height and width
	int m_depth1; // bits per pixel
	LPBITMAPINFO mg_lpBMIH1; // bmp infoHeader
	//CDib -> Mat을 위한 Mat객체들
	Mat m_Mat1; //image1에 해당하는 Mat객체

	// DIB data(image2)
	CDib	m_dibFile2;
	LONG	m_width2, m_height2;	// height and width
	int     m_depth2;				// bits per pixel
	LPBITMAPINFO mg_lpBMIH2;		// bmp infoHeader
	//CDib -> Mat을 위한 Mat객체들
	Mat m_Mat2; //image2에 해당하는 Mat객체

	// Resulting Mat after processing something
	Mat     m_MatR;		//선언만 하고 할당은 ,.App에서

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
	
	/*which = 1, 2는 각각 읽은 이미지 1과 2를 의미하고, 3은 차후 이미지 처리 결과를 보일 때 사용한다.*/
	void drawMatPopUp(int which);//Mat을 PopUp 창에 보이기.
	

	void DIBtoMat(int which);//CDib 를 Mat 으로 변환.

	//LPBITMAPINFO구조를 만드는 함수, infoheader저장할 장소는  private에할당.
	void Create_bmiInfoHeader(cv::Mat *image);

	//Image Darken function
	void DarkenGrayscaleImage(void);

	//이미지 프로세싱 결과 생긴 이미지를 저장하는 코드
	void saveImage(CString pathName);
};