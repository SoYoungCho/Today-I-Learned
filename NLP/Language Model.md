## Language Model

Language Model (LM) is a probability distribution over sequences of words. LM provides **context**.

sequence 에 **확률**을 부여
이 때, 확률은 sequence가 일어날 가능성의 확률. 자연스러운 정도

### Language Model의 응용

1. output 문장이 자연스러운지 평가
  + especially those that generate text as an output. 기계번역, 음성인식
2. 새로운 문장을 생성하는 용도
  + 언어모델은 **단어 순서의 자연스러움을 확률적으로 평가 가능**하기에 그 확률분포에 따라 다음으로 적학한 단어 샘플링 가능 (추출)
