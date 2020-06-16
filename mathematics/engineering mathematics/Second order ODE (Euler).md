# Second Order ODE

Q. Euler-type second-order ordinary differential equation 

- DE (미분 방정식) 함수와 그 함수의 도함수로 이루어진 방정식.
- ODE (상미분 방정식) : 방정식에 독립변수가 하나 뿐일 때. 즉 1개의 변수에 대한 미분항이 포함된 방정식
- PDE (편미분 방정식) : 방정식에 독립변수가 여러 개일 때. 2개 이상의 변수에 대한 편미분항이 포함된 방정식

first order ODE : y' , y , x만 방정식에 나온다는 뜻.
second order ODE : y'' 까지 나오는 방정식 

## Second Order DE

### 오일러 공식

#### [위키](https://ko.wikipedia.org/wiki/%EC%98%A4%EC%9D%BC%EB%9F%AC_%EA%B3%B5%EC%8B%9D)

- 복소수 지수를 정의하는 데의 출발점
- **삼각함수와 지수함수에 대한 관계**를 나타낸다
- 실수 x에 대해 허수 지수 ix를 정의한 식. e는 자연로그의 밑인 상수, i는 제곱하면 -1이 되는 허수
- 테일러 급수로 증명할 수 있다.

- 일반화된 오일러 방법 -> 선형방정식을 푸는 수치해석법의 기본 개념
- 앞으로 자연상수 e위에 복소수 i가 올라가는 일이 종종 발생
- 이 때 취급하기 편하게 cos, sin 함수로 고치는 작업을 하기 위한 기본  
  
![](https://dthumb-phinf.pstatic.net/?src=%22https%3A%2F%2Fssl.pstatic.net%2Fimages.se2%2Fsmedit%2F2017%2F1%2F12%2Fixu2pi2h3ejzao.jpg%22&type=w2)

[참고 사이트](https://stementor.tistory.com/entry/%EC%B0%B8%EC%83%88%EC%99%80%ED%95%A8%EA%BB%98%ED%95%98%EB%8A%94-%EA%B8%B0%EC%B4%88-%EA%B3%B5%ED%95%99%EC%88%98%ED%95%99-8-2nd-order-ODE1-homogeneous-1)

### 오일러 방법

![](https://lh3.googleusercontent.com/proxy/VmJ3cIaEPvJcY40lHLwILNC7q0GBSaoLwWDELABv7vfEHLizQGlukaz5WumKInEif8o33h7HyWI5wqK25oKo4S-vqmRJfP3RFAJ6yOhZV5ooTfnFTSXyf7Ao1fAlf4tcQmxYnH9buUr43D6zlcCs18NHqKtjR3wli8OC089tnIdPAn9wij1-PQ91IZw)

- 주어진 초기값 x0을 이용해 다음 xi에서의 yi를 구하고, 또 이 둘을 이용해 다음 xi+1, yi+1을 구하고.. 이를 반복하여 원래 함수에 근사해나가는것?
- 저 h 값이 작을수록 오차가 줄어든다.
- 
### 오일러방법 이용 2계 상미분방정식 

![](https://dthumb-phinf.pstatic.net/?src=%22https%3A%2F%2Fssl.pstatic.net%2Fimages.se2%2Fsmedit%2F2016%2F1%2F18%2Fijk6m5arcndovw.jpg%22&type=w2)
여기서 
![](https://dthumb-phinf.pstatic.net/?src=%22https%3A%2F%2Fssl.pstatic.net%2Fimages.se2%2Fsmedit%2F2016%2F1%2F18%2Fijk4di4keh5uyg.jpg%22&type=w2)
![](https://dthumb-phinf.pstatic.net/?src=%22https%3A%2F%2Fssl.pstatic.net%2Fimages.se2%2Fsmedit%2F2016%2F1%2F18%2Fijk6pkrm90bbu4.jpg%22&type=w2)

2차 오일러방법은 계산이 번거롭다고 함..

[참고 블로그](https://m.blog.naver.com/PostView.nhn?blogId=mykepzzang&logNo=220601629315&proxyReferer=https:%2F%2Fwww.google.com%2F)
