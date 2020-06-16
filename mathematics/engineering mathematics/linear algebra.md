# 선형대수 (벡터와 행렬)

## 1. 내적 (inner product)

- 벡터 간 곱, 결과는 스칼라. 
- 벡터의 각 성분을 곱한 뒤 더해주는 것.

- 보통 벡터+벡터 = 벡터 / 스칼라 + 스칼라 = 스칼라인데,
- 내적은 결과가 스칼라인 벡터와 벡터의 연산
- 두 열벡터의 내적을 구할 경우, 둘 중 한 벡터를 transpose 해 행벡터로 바꾼 후 벡터와 벡터곱을 시킨다

### 내적의 의미

∥v∥=√⟨v,v⟩
	- 한 벡터의 norm을 구할 수 있다

d(u,v)=∥u−v∥=√⟨u−v,u−v⟩d(u,v)=∥u−v∥=⟨u−v,u−v⟩
	- 두 벡터 사이의 거리는 내적을 이용하여 표현할 수 있다

![](https://losskatsu.github.io/assets/images/innerproduct/innerproduct01.JPG)


u⋅v=∥u∥∥v∥cosθ
	- 이를 활용해 두 벡터 간 위치 관계 알 수 있다. **코사인 유사도**에서 활용 가능
	- 또한 내적 값이 0일 경우 두 벡터가 수직임을 알 수 있다.

- 내적은 한 벡터를 다른 벡터에 정사영 시킨 후 각 벡터의 크기를 곱하는 것이다.

[losskatsu 참고블로그](https://losskatsu.github.io/linear-algebra/innerproduct/#3%EB%AC%BC%EB%A6%AC%ED%95%99-%EA%B4%80%EC%A0%90%EC%9C%BC%EB%A1%9C-%EB%B3%B4%EB%8A%94-%EB%82%B4%EC%A0%81)

## 2. determinant (행렬식)

- 일종의 계산 식인데, 식 자체가 아닌 **식을 통해 나온 값이 행렬의 특성을 나타내기**에 의미있다.
- 직역하면 '결정요인'. 결정적인 역할을 하는 느낌?
- 정방행렬에 수를 대응시키는 함수 (nxn)
- **정방행렬이 나타내는 선형	변환이 부피를 확대시키는 정도**
- **행렬식 : 주어진 벡터들이 이루는 공간의 부피**
	- detA11 은 A행렬에서 1행, 1열을 제외한 행렬의 행렬식
	- 2 x 2 행렬의 행렬식은 ad - bc


![](https://losskatsu.github.io/assets/images/determinant/determinant02.JPG)

- 행렬식의 절댓값은 도형의 면적, 부피
- nxn 행렬의 행렬식 -> n차원 공간의 벡터들로 구성된 도형의 부피
- 다시 말해, **|행렬식| = 부피**
	- 각 벡터로 구성된 도형 부피가 0이라는 것
	- 행렬식 = 0 이라는 것은, 이는 행렬을 구성하는 **벡터가 서로 동일선상에 있음**을 의미
	- 행렬식 = 0 이라는 것은, 이 **벡터들이 해당공간의 기저(basis)가 아님**을 의미
	- 행렬식 = 0 이라는 것은, **역행렬이 없다**

[losskatsu 참고블로그](https://losskatsu.github.io/linear-algebra/determinant/#3-3-by-3-%ED%96%89%EB%A0%AC)
[ratsgo 참고블로그](https://ratsgo.github.io/linear%20algebra/2017/05/21/determinants/)

## 3.  역행렬 (inverse matrix)

![](https://dthumb-phinf.pstatic.net/?src=%22https%3A%2F%2Fpostfiles.pstatic.net%2F20160525_60%2Ftlaja_14641492975458E0r1_JPEG%2F%25BF%25AA%25C7%25E0%25B7%25C42.JPG%3Ftype%3Dw2%22&type=w2)
- 역행렬 : 원래 행렬과 곱했을 때 단위행렬이 되는 행렬 
- 선형방정식에서의 활용
![](https://mblogthumb-phinf.pstatic.net/20160527_111/tlaja_1464315743292YIvFz_PNG/3.png?type=w2)
![](https://mblogthumb-phinf.pstatic.net/20160527_102/tlaja_1464315743538yEcp5_PNG/4.png?type=w2)
위와 같이 X를 구할 수 있다.
- 역행렬의 존재여부를 판단할 수 있는 것이 행렬식
	- 행렬식 det(A) = 0 -> 역행렬이 없다
	- 행렬식 det(A) != 0 -> 역행렬이 있다 => 연립방정식을 만족하는 유일해 X가 존재

[참고 네이버 블로그](https://m.blog.naver.com/PostView.nhn?blogId=tlaja&logNo=220720682588&proxyReferer=https:%2F%2Fwww.google.com%2F)

## 4. 고유값 (eigenvalue)

- 고유벡터 : 어떤 벡터에 선형변환을 취했을때, 방향은 변하지 않고 크기만 변환되는 벡터
- 고유값 : 고유벡터가 변환되는 그 ‘크기’를 의미
	- 예) 고유값이 2라면, 기존벡터 크기의 2배만큼 길어진 것

	Ax=λx

	- 정방행렬 A의 고유벡터 : 영벡터가 아닌 벡터 x
	- 고유값 : λ

-  선형변환?
좌표공간 내에서 일어날 수 있는 모든 변환 (축소, 확대, 회전, 반사 등)

--> Ax는 따라서 x라는 벡터에 선형변환(A)을 취한 것

[losskatsu.github.io](https://losskatsu.github.io/linear-algebra/eigen/#%EC%84%A0%ED%98%95%EB%B3%80%ED%99%98%EC%9D%98-%EC%9D%98%EB%AF%B8)

## 5. 직교 (orthogonality)

- 직교행렬 : **행벡터와 열벡터가** 유클리드 공간(좌표공간계)의 **정규 직교 기저를 이루는 실수 행렬**

- *용어정리*
	- 기저 : 어떤 벡터공간을 생성하는 벡터들 (basis)
	- 정규 : 벡터 크기가 1
	- 두 직선 또는 두 평면이 직각을 이루며 만나는 것
	
- 직교행렬 특징
	-  역행렬 = 전치행렬
		- 정규직교 인 사실을 알 경우 이 성질을 이용해 쉽게 역행렬을 구할 수 있다. 전치만 하면 되니까.
	 - 행렬식은 1 또는 -1

- 정규 직교 기저 : 벡터 크기가 1이고 서로 수직인 기저 벡터
- 이 정규직교 성질은 여러 복잡한 사오항을 단순화하기 편해서 중요함

[losskatsu 참고 블로그](https://losskatsu.github.io/linear-algebra/orthogonal/#)

## 6. rank

- 기저 : 벡터공간 생성하는 선형독립 벡터들
- 벡터공간 : 기저벡터로 생성 가능한 공간
- 부분공간 : 벡터집합의 일부분으로 만든 공간. 기저 벡터 n개 중 일부만 가지고 만들 수 있는 공간
- span : 기저벡터들로 부분공간을 만드는 것. 기저벡터들은 부분공간을 span 한다
- 차원 : 기저벡터의 개수 (dimension)

	> rank of a matrix A is the dimension of the vector space generated (or spanned) by its columns.

![](https://losskatsu.github.io/assets/images/rank/rank03.JPG)

즉, Rank는 해당 행렬의 열벡터에 의해 span 된 벡터공간의 차원. 위 행렬의 랭크는 2이다.

[losskatsu 참고 블로그](https://losskatsu.github.io/linear-algebra/rank-dim/)

---
- 행렬의 랭크는 **행렬이 나타낼 수 있는 벡터 공간에서 기저의 개수**를 의미
- 이 기저는 서로 독립인 행 또는 열의 벡터의 개수에 의해서 결정된다. (선형독립)
- 열과 행의 랭크는 서로 같은 값을 가지므로, 행렬의 랭크를 구할 때에는 한 쪽의 랭크만 계산하면 되고, 서로 선형 독립인 벡터가 몇 개가 되는지만 확인하면 된다.
 [[기초 선형대수] 행렬에서 Rank (랭크) 란?](http://blog.naver.com/sw4r)

