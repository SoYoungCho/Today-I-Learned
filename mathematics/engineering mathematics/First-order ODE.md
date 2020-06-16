# First-order ordinary differential equation 

## ODE (상미분방정식)

- DE : 미분방정식. 도함수를 포함하눈 방정식
- ODE (ordinary differential equation, 상미분 방정식)
	- 일변수 함수의 미분이 포함된 방정식 (y' 이 포함된 것이라는 뜻인가?)
	- 하나의 독립변수x 에 관해 하나 이상의 종속변수의 도함수를 포함하는 미분방정식
	- 구하려는 함수가 **하나의 독립변수만**을 가지고 있는 경우. 반대 개념은 편미분 방정식 (PDE)

[참고 사이트](https://joonyoungsun.tistory.com/entry/%EB%AF%B8%EB%B6%84-%EB%B0%A9%EC%A0%95%EC%8B%9D-Differential-Equations)

first order : y' , y , x만 방정식에 나온다는 뜻.
second order : y'' 까지 나오는 방정식 

## First - Order ODE

first order : y' , y , x만 방정식에 나온다는 뜻.
1. 변수 분리가 가능한 형태의 미분방정식
- 좌변에는 y 관련식만, 우변에는 x관련 식만 남길 수 있는 형태
2. 변수 분리 안되는 경우 -> 치환해서 풀기도 함

[참고 블로그](https://m.blog.naver.com/PostView.nhn?blogId=alsdnr7680&logNo=220909384806&proxyReferer=https:%2F%2Fwww.google.com%2F)

## homogeneous equations (동차 방정식, 제차 방정식)

y˙+p(t)y=0
- zero on the right hand side of the first form of the equation.
- 우변이 0
- **= 0** 꼴의 경우 호모지니어스 하다

- f(x,y)가  f(tx,ty)와 "종류가 같다", "카테고리가 같다"라는 의미
- f(x,y)의  x와  y를 동일한 비율로 다르게 넣어주어도
(x,y)=(1,1)을 넣어주든,  (x,y)=(2,2)를 넣어주든
**"물리적인 의미가 같은 결과"**, "카테고리가 같은 결과"가 나온다는 것이다.

   [https://tedder.tistory.com/104](https://tedder.tistory.com/104)
## exact equations (완전방정식)

- Exact Differential Equation (완전 미분방정식)  
![](https://dthumb-phinf.pstatic.net/?src=%22https%3A%2F%2Fssl.pstatic.net%2Fimages.se2%2Fsmedit%2F2013%2F8%2F5%2Fhjz0al500mfiyw.jpg%22&type=w2)  
![](https://dthumb-phinf.pstatic.net/?src=%22https%3A%2F%2Fssl.pstatic.net%2Fimages.se2%2Fsmedit%2F2013%2F8%2F5%2Fhjz0ea8j2hlxwi.jpg%22&type=w2)  
p(x,y)를 y로 편미분하고 q(x,y)를 x로 편미분했을 때의 값이 동일할 경우 '완전' 미분 방정식이다.

##  linear equations (선형 방정식, 일차 방정식)

- 미지수의 최고차항의 차수가 1을 넘지 않는 다항방정식
- 변수는 1개일 수, 2개 이상일 수 있다.
- 수학적 모델링에 필요한 비선형 방정식은 풀기 쉽도록 일차 방정식으로 근사하여 다루어진다.

[위키](https://ko.wikipedia.org/wiki/%EC%9D%BC%EC%B0%A8_%EB%B0%A9%EC%A0%95%EC%8B%9D)
