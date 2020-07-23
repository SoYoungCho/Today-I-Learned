## 두 데이터를 함께 정렬하고 싶다면?

- x 데이터와 y 데이터(label)의 순서를 유지하면서 랜덤하게 섞고 싶을 때,  
이전에 enum 이런거 활용하는 방법도 수환오빠랑 했었는데 scikit-learn에서 제공하는 아래 shuffle 함수를 쓰면 더욱 간단하다.
- 오늘 진행한 AutoML에서 validation accuracy가 고정된 값으로 계속 나왔던 것이 바로 이 데이터가 shuffle 되지 않았기 때문이였고, shuffle 하니 오버피팅이 해결되어 결과를 잘 확인할 수 있었다.

``` python
x_train = np.array([[1., 0.], [2., 1.], [0., 0.]])
y_train = np.array([0, 1, 2])
from sklearn.utils import shuffle
x_train, y_train = shuffle(x_train, y_train, random_state=0)
```
