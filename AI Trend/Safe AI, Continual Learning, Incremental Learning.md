##  Safe AI
1. adversarial attacks
2. unexplainable AI
	- XAI 두 가지
		-  기존 데이터 잘 설명 (오프라인)
		- 새로운 예측에 대한 설명 (온라인)
		- 설명이 가능해야 Safe AI 사용 가능
3.  Data Privacy
	- 데이터를 옮기는게 아니라 데이터로 학습한 모델의 weight를 이동시켜서 데이터 보안 유지
	- federated learning
## Continual Learning
- 데이터가 계속 늘어나고 있는 문제, 모델을 업데이트 하면 catastrophic forgetting
- catastrophic forgetting : 조금이라도 다른 새로운 데이터에 대해 학습시키면 성능이 급격히 떨어짐
- 이를 해결하기 위한 기법들 memory replay, regularization, dynamic architecture
	- 아키텍처 변경 . 하이퍼파라미터 영역을 학습의 영역으로 바꿈
## Incremental Learning
- implicit changes in data (시간에 따라 데이터가 변화)
	- 예) 척추측만증 환자의 치료 경과, 나이 듦에 따라 변화는 얼굴인식 잘 못함
- concept drift
- 종류 1. sudden change 갑자기 변함
- 종류 2. gradual change : 찔끔찔끔..
- 종류 3. incremental change : 서서히 변함
	- 방법 1. sliding time window 방법. but 윈도우 사이즈 뭘로 정할건지 (하이퍼파라미터 발생)
	- 방법 2. 매번 학습.
		- 파라미터는 없지만, 잘 동작하지 않는다. 아웃라이어들까지 학습되기에.
	- 방법 3. 실제 데이터 분포가 어떻게 변하는지 . 변화가 있으면 학습
		- 시그마를 이용해 threshold 잡음
		- threshold 넘어서면 넘어선 데이터들을 이용해 모델 학습하여 업데이트, robust 하다.
