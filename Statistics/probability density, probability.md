# Probability Density & Probability

Q. probability density와 확률의 차이를 설명하라.

확률에는 1. 이산적(discrete) 사건의 확률 2. 연속적(continusous) 사건의 확률이 있다.

연속적인 입력 값에 대해서는 확률 값을 모두 나열할 수 없다. 예를 들어 몸무게 50kg ~ 51kg 사이에는 무수히 많은 실수 값이 존재한다. 따라서 확률 값을 **구간(range)**으로 표현한다.
![](http://norman3.github.io/prml/images/Figure1.12.png)
여기서 p(x) 가 확률 밀도 (probability density)이다.

## 확률 밀도 (probability density) 에서의 확률
- 연속적인 값에 대한 변수는 구간으로 표현, 적분을 통해 확률값을 구할 수 있다.
- 연속 확률 밀도함수 (probability density funtion)에서 **확률 밀도 p(x)**를 통해 얻어진 실수 값은 정확히 말하면 **실제 확률 값이 아닌 확률함수의 반환 값**이다. 
- 확률밀도 함수에서의 확률은 그 자체로 확률값이 아닌 **구간 적분하여 얻은 값**이 확률값이 된다.

[참고 블로그](http://norman3.github.io/prml/docs/chapter01/2.html)

-----
## Probability density VS Probability

설명 1.
- probability density : "density" function. 말 그대로 '밀도'함수.
- 반면, probability : 0과 1 사이의 특정 값.

설명 2.
- 특정값 x에 대한 확률밀도는 해당 변수 x에 대한 특정 구간 내의 확률의 밀도
- 확률은 그 구간을 적분하여 얻게 된 값.

나의 정리
- 확률밀도 : 연속적인 사건의 확률을 표현한 밀도 함수. 
- 확률 : 확률 밀도함수에서 해당 사건에 대한 특정 구간을 적분하여 얻은 어떠한 값.

[영어로 검색한 사이트](https://math.stackexchange.com/questions/521575/difference-between-probability-and-probability-density) 
