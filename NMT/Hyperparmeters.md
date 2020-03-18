## Hyperparameter란?

Weight = parameter

hyperparamter : 파라미터 이외에 사람이 직접 설정하는 값

예) batch_size, teacher_forcing_ratio, use_bidirectional, hidden_size, layer_size, dropout_ratio, etc.  
seq2seq에 특히 hyperparameter가 중요하다고 함. 이 값에 따라 성능이 크게 달라질 수 있음. (천차만별!)

## Batch, Epoch, Step 개념 정리하기

1. Batch : 한 번에 몇 개의 데이터씩 처리할지. mini-batch 그 개념. 병렬적으로 처리되는 각 데이터 뭉탱이. 일반적으로 랜덤 추출.
  랜덤하게 해야 오버피팅 방지할 수 있다. random shuffle 한 뒤 batch size로 자를 수도 있다.  
2. Step : 한 배치가 도는 것. 1 batch 도는 것 = 1 step.   
3. Epoch : 전체 데이터에 대해 한 바퀴 도는 것. 일반적으로 1 에폭이 끝나면 데이터를 랜덤으로 섞는다.  

예를 들어, 전체 데이터 개수는 1000개, Batch_size = 100 일 경우
1 Epoch에서 step은 10번 돈다. 따라서 Batch_size, ephoch을 정해주면 step은 자동적으로 계산되기에 사실 hyperparameter는 아니다.

## NMT에서 중요하게 여겨지는 hyperparmeters

layer_size : RNN 계층의 개수.   
hidden_size (hidden state size) : hidden state vector의 사이즈. 256 / 512 .. 모델에 따라 다르니 잘 조정해줄 것.  
dropout_ratio : ![](https://opennmt.net/OpenNMT/img/dropout.jpg)  

learning rate (lr) : 학습율.
