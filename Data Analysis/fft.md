# fft (Fast Fourier Transform)

- 고속 푸리에 변환
- 시간 도메인 신호들을 주파수 도메인 (Frequency-Domain)으로 변환
- 시간을 주파수로. 

### 파형에 FFT를 적용하는 이유
- 단순히 시간 도메인에서 나타나지 않은 신호의 특성에 대한 통찰력을 얻을 수 있다
- 많은 신호들이 시간 도메인과 반대되는 스펙트럼 분석에서 많은 정보를 가지고 있다.
- 예) 기계적 진동 분석에서 발생한 신호들은 **주파수 도메인에서 가장 훌륭하게 관찰**된다

### FFT 이론
- 무한히 연속되어 있는 시간 도메인 신호는 모두 주파수 도메인 스펙트럼으로 변환된다는 것을 **가정**한다 (실제로는 불가능)
- 따라서 이론과 실제 차이를 극복하기 위해 **신호의 주기성, 대칭성을 이용해 신호의 특정 부분을 선택 -> 같은 신호가 무한히 반복된다고 보고 고속 푸리에변환**을 연산


[참고 블로그1]([http://blog.naver.com/lecroykorea/130176731669](http://blog.naver.com/lecroykorea/130176731669))
[참조 블로그2]([https://m.blog.naver.com/PostView.nhn?blogId=lecroykorea&logNo=130182273773&proxyReferer=https:%2F%2Fwww.google.com%2F](https://m.blog.naver.com/PostView.nhn?blogId=lecroykorea&logNo=130182273773&proxyReferer=https:%2F%2Fwww.google.com%2F))
