# CSE4152
고소실1_MFC와이미지프로세싱

### stdio.h stdafx.h등 기본 헤더를 찾을 수 없다??
* [window SDK설치하기](https://embeddedaroma.tistory.com/12)
* [미리 컴파일 된 헤더 사용 여부 체크하기](http://blog.naver.com/PostView.nhn?blogId=ndb796&logNo=220788188276&parentCategoryNo=62&categoryNo=&viewDate=&isShowPopularPosts=true&from=search)

* **VS 2019부터는, stdafx.h말고 pdh.h?인지뭔지 다른 헤더를 사용함.->2017이하와 호환안됨**


### 초기화되지 않았을 수 있는 로컬 포인터 변수 'name'이(가) 사용되었습니다.
* [컴파일러 경고(수준 4) C4703](https://docs.microsoft.com/ko-kr/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4703?view=vs-2019#example)
  - 포인터의 경우, 초기화를 선언과 동시에 nullptr로 해주자.
