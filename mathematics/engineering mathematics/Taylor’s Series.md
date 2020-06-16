# Taylor’s Series Expansion 

테일러 급수 전개

## 1. 테일러 급수의 이해

테일러급수 (Taylor Series) 혹은 테일러 전개(Taylor Expansion)이란
- n번 미분한 함수를 구할 수 있다면, 어떠한 함수라도 다항식을 포함한 x에 대한 무한급수로 나타낼 수 있는 표현 방식
- 도함수들의 한 점에서의 값으로 계산된 항의 무한합으로 해석함수 나타내는 방법이다.
- **어떤 미지의 함수 f(x)를 근사 다항함수로 표현하는 것**.
- 다시 말해, x=a에서 f(x)와 동일한 미분계수를 갖는 다항함수로 f(x)를 근사시키는 것
![](https://t1.daumcdn.net/cfile/tistory/1340E73A517E1FB703)
![](https://t1.daumcdn.net/cfile/tistory/03295235517E200D16)

- x=a 근처에서만 성립, a로부터 멀어질수록 오차가 커진다.
- 근사다항식의 차수는 높을수록 잘 근사

### 테일러 정리
![](https://t1.daumcdn.net/cfile/tistory/0168C93A517E279819)

- n번 미분가능한 함수 f(x)에 대해 아래를 만족하는 실함수 h(x)가 반드시 존재한다는 것 (맨 오른쪽 h(x)(x-a)^n는 근사오차)
 - 어떤 함수를 유한차수(n차)의 다항함수로 근사시킬 수 있는 수학적 근거를 제공

## 2. 테일러 급수의 의미

- 쉽게 말하면 우리가 **잘 모르거나 복잡한 함수를 다루기 쉽고 이해하기 쉬운 다항함수로 대체**시키기 위함
- 어떤 함수를 테일러 급수로 표현하면 **그 함수의 특성을 분석하기가 좀더 용이**해지기 때문

1. 정적분의 계산 근사적으로 가능

- 부정적분을 계산하기 힘든 함수의 경우에 테일러 급수를 활용하면 정적분의 계산값을 근사적으로 구할 수
![](https://t1.daumcdn.net/cfile/tistory/01795533517E382319)

#### 참고! sin, cos, tan 함수

![](https://lh3.googleusercontent.com/proxy/KdAXgMscE9ap1eifg7NQcMtKMzhabnSyXqjafL3LCrDaGymNYa04YWzRuRNyC6R91Ss5qOT6u1RLNsLGKKftk66WSvYYCfbeb_yOvkyJNa7_eVGZuvU_6rTV-FfcE0q-nDsuGMnqCqYjlMAd10UQmzXi8xyS)

2. 함수의 점근 특성 파악
- 테일러 급수를 활용하면 함수(특히 삼각함수, 지수함수, 로그함수와 같은 초월함수)의 점근적 특성을 손쉽게 파악

3. **문제 / 모델의 단순화**
- 어떤 복잡한 또는 잘 모르는 함수가 있을 때, 이 함수를 **저차의(1~3차) 다항함수로 근사하여 사용**함으로써 문제 또는 모델을 단순화시키는데 테일러 급수가 활용될 수 있습니다
	- 어떤 이론이나 주장에 대한 논리적 근거를 단순화하여 설명할 때 유용하게 사용되는 기법 중의 하나

[https://darkpgmr.tistory.com/59](https://darkpgmr.tistory.com/59)
