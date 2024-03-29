#include "stdafx.h"

#include "swLab19fDoc.h"
#include "swLab19fView.h"
#include "MainFrm.h"

#include "s141506L01_Mfc.h"
#include "CDIB.H"


SWL01 SWL01_inst; // SWL01 instance
CswLab19fView *g_pView = NULL; // View instance
CMainFrame *g_pMainF = NULL; // Frame instant


/*멤버 함수 readImage( )에서 Mat 변환 함수까지 호출해서, CDib로 읽고 Mat으로 변환하자.*/
void SWL01::readImage(CString pathName, int which) {
	// read an image & store it to img_org
	CFile file;// CFile class(C에서 FILE과 유사)
	LPCTSTR str = pathName;// CString과 유사한 class
	
	// 아래 모두 포인터로 한 이유는 두 이미지를 읽어야 해서
	CDib  *pDibF = nullptr;// DIB class
	LONG  *width = nullptr, *height = nullptr;
	int   *depth = nullptr;
	LPBITMAPINFO *bmInfoHd = nullptr;// DIB infoHeader

	/////////////*pointer setting하는 부/분.*///////////////
	if (which == 1) {
		pDibF = &m_dibFile1;	// when reading image1
		width = &m_width1; height = &m_height1;
		depth = &m_depth1;  bmInfoHd = &mg_lpBMIH1;
		readImageF1 = true;
	}
	else if (which == 2) {
		// image2는 image1 읽은 후에나 읽을 수 있다
		if (readImageF1 == false) {
			AfxMessageBox(L"Read image1 first!", MB_OK, 0);
			return;
		}
		pDibF = &m_dibFile2;	// when reading addtional image2
		width = &m_width2; height = &m_height2;
		depth = &m_depth2;  bmInfoHd = &mg_lpBMIH2;
		readImageF2 = true;
	}
	////////////////////////////////////////////////////////////////////////

	///////////////////////****이미지 읽는 부분******///////////////////////////
	(*pDibF).Empty();	// clear any previouse read image
	file.Open(str, CFile::modeRead);
	if ((*pDibF).Read(&file) != TRUE) {
		file.Close();
		return;
	}
	file.Close();
	*width = ((*pDibF).m_lpBMIH)->biWidth;
	*height = ((*pDibF).m_lpBMIH)->biHeight;
	*depth = ((*pDibF).m_lpBMIH)->biBitCount;
	*bmInfoHd = (LPBITMAPINFO)((*pDibF).m_lpBMIH);

	//이미지 다 읽었으면 CDib -> Mat으로
	DIBtoMat(which);/*which = 1, 2는 각각 읽은 이미지 1과 2를 의미하고, 3은 차후 이미지 처리 결과를 보일 때 사용한다.*/

	processedF = false;	// will be true after doing somthing
	////////////////////////////////////////////////////////////////////////

	//메시지 출력 및 그리기 요청
	CString msga, msgb;
	msga.Format(L"Read an image from %s and save it to image %d", pathName, which);
	msgb.Format(L"  Its size and depth are (w = %d, h = %d, depth = %d)",
		*width, *height, *depth);
	showMessage(msga); 
	showMessage(msgb);

	g_pView->Invalidate();//여기서 pView로부터 그리기 요청.
}

/*이미지 그리는 함수:OnDraw에서 호출*/
void SWL01::drawImage(CDC *pDC, int dcLTx, int dcLTy, int which) {
	if (which == 1) {
		m_dibFile1.Draw(pDC, CPoint(dcLTx, dcLTy), CSize(m_width1, m_height1));
	}
	else if (which == 2) {
		m_dibFile2.Draw(pDC, CPoint(dcLTx + 20 + m_width1, dcLTy), CSize(m_width2, m_height2));
	}
}

/*팝업 드로잉 함수*/
void SWL01::drawMatPopUp(int which) {
	string str("Input Image ");
	const char *cstr = nullptr;
	const char *Rstr = "Output Image";
	Mat *pMat = nullptr;
	//which값에 따라 제목을 만든다.
	if (which == 1) {
		str.append("1");
		cstr = str.c_str();		// conversion from string to (const char *)
		pMat = &m_Mat1;
	}
	else if (which == 2) {
		str.append("2");
		cstr = str.c_str();
		pMat = &m_Mat2;
	}
	else if (which == 3) {
		cstr = Rstr;
		pMat = &m_MatR;
	}

	//????????
	string s1 = "8UC1", s3 = "8UC3";
	string st = type2str((*pMat).type());
	if (st.compare(s1) != 0 && st.compare(s3) != 0) {
		AfxMessageBox(L"Only 8bit grayscale or 24bit color can be shown!", MB_OK, 0);
		return;
	}
	//namedWindow(cstr, WINDOW_AUTOSIZE);

	//imshow호출
	imshow(cstr, *pMat);
	waitKey(0);
}

/*CDib to MAt*/
void SWL01::DIBtoMat(int which) {
	CDib  *pDibF = nullptr;
	Mat   *pMat = nullptr;
	int   w, h, depth;

	//////////which 값에 따라 필요한 변수 포인터 배정하는 부분///////////////////////
	if (which == 1) {
		pDibF = &m_dibFile1; pMat = &m_Mat1;
		w = m_width1; h = m_height1; depth = m_depth1;
	}
	else if (which == 2) {
		pDibF = &m_dibFile2; pMat = &m_Mat2;
		w = m_width2; h = m_height2; depth = m_depth2;
	}
	(*pMat).release();		// clear any previous image data
	///////////////////////////////////////////////////////////////////

	switch (depth) {//depth : 이미지 비트 수
	case 8:
		*pMat = Mat(h, w, CV_8UC1);	// allocate Mat			
		break;
	case 16:	// in this case we create CV_16UC1 Mat(drawable? anyway...)
		*pMat = Mat(h, w, CV_16UC1);
		break;
	case 24:
		*pMat = Mat(h, w, CV_8UC3);
	};
	unsigned char *pMatData = (*pMat).data;//이미 data를 이용, pMat의 포인터:이미지 데이터의 시작 포인터를 직접 얻어 복사하려함. 
	unsigned char *pDibData = (*pDibF).m_lpImage;//이미지
	//***아래에 실제 이미지를 복사하는 빈 부분을 짥게 작성하자:실습자료 중 Mat으로 복사하는 부분.***
	//***   8,16,24 모든 이미지를 볼 수 있어야 한다:포인터연산을 사용한다.                ***
	
	for (int p = 0; p < h * w * (*pMat).channels(); p++) {
		*pMatData++ = *pDibData++;
	}
	/*위 코드를 풀면 다음과 같다.
	for (int r = 0; r < h; r++)
		for (int c = 0; c < w; c++) {
		pMatData[r * h * 3 + c * 3 ] = *pDib_data++;
		pMatData[r * h * 3 + c * 3 + 1] = *pDib_data++;
		pMatData[r * h * 3 + c * 3 + 2] = *pDib_data++;
	}
	*/
	//***
	flip((*pMat), (*pMat), 0);	// upside down
}



//주어진 Mat의 type을 심볼로 출력하는 함수.
// Global Functions
//
/*
+--------+----+----+----+----+------+------+------+------+
|        | C1 | C2 | C3 | C4 | C(5) | C(6) | C(7) | C(8) |
+--------+----+----+----+----+------+------+------+------+
| CV_8U  |  0 |  8 | 16 | 24 |   32 |   40 |   48 |   56 |
| CV_8S  |  1 |  9 | 17 | 25 |   33 |   41 |   49 |   57 |
| CV_16U |  2 | 10 | 18 | 26 |   34 |   42 |   50 |   58 |
| CV_16S |  3 | 11 | 19 | 27 |   35 |   43 |   51 |   59 |
| CV_32S |  4 | 12 | 20 | 28 |   36 |   44 |   52 |   60 |
| CV_32F |  5 | 13 | 21 | 29 |   37 |   45 |   53 |   61 |
| CV_64F |  6 | 14 | 22 | 30 |   38 |   46 |   54 |   62 |
+--------+----+----+----+----+------+------+------+------+
*/
string type2str(int type) {
	// https://stackoverflow.com/questions/10167534/how-to-find-out-what-type-of-a-mat-object-is-with-mattype-in-opencv
	string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans + '0');

	return r;
}