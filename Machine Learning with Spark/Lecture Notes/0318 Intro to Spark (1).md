# Using Apache Spark

## 1. 스파크란 ?
* 스파크는 **클러스터 컴퓨팅 시스템**으로 하둡과 호환가능하다.  
* 하둡 vs 스파크  
하둡 : 디스크 기반  
스파크 : 메모리 기반 의 분산 병렬 처리 플랫폼. => 속도가 훨씬 빠르다.  
* 그래프 형태  
* Java, Scala, Python에서 가능.   
	+ Scala도 Java와 같이 JVM에서 돌아가는데, 훨씬 간결하다.  
	+ Python의 Spark도 Scala 기반이기에 Scala 쓰는 것이 빠르다.  
	+ Java에서 사용할 경우 코드가 더 길어진다는 단점이 있다.  

## 2. 스파크의 Key Concepts
: 분산된 데이터셋 **RDD**에 대해 transformation.

![](https://postfiles.pstatic.net/MjAyMDAzMThfMjMg/MDAxNTg0NTM1MTg3NTA3.NI8mgfGbN7o90zfQV6rXViGdoQitWPjBr72AVJuU0Mcg.juhBfw0T__AI7b1pzEIa2ySYZfhd6FO4GBSqc1tJAyEg.PNG.wazoskee/image.png?type=w773)

#### 1. RDD : Resilient Distributed Datasets
- RAM 혹은 디스크에 저장된 객체집합으로, 클러스터에 분산된다. (쉽게 이해하면 array)  
- 병렬처리(transformation) 되어 만들어진다.  
- 문제가 발생할 경우 스파크가 자동으로 복구 (신경 쓸 필요 X)  
	+ 고장에도 끄떡 없는! fault tolerant 한 점을 resilient 하다고 한다.  
	+ element-wise 로 하게 될 경우 복구가 어려움.  
전체에 대해 operation을 통째로 적용해서 복구 가능 (아래에 설명 더 나옴)  

#### 2. Operations
a. Transformations : map, filter, groupby 등. (병렬하게 처리됨)  
	- map : 쉽게 말하면 array에 일괄적으로 적용되는 함수 (ex) x+1)  
	- filter :  조건으로 필터링하는 것 (x < 100)  
b. Actions : count, collect, save 등  

SQL연산자와 유사하다. 위 예시 외에도 join, reduce 등 있다.

로컬하게 안 돌리고 클러스터링 컴퓨팅할 경우 (분산처리)  
transformation과 action은 cluster에서 돌아간다. 내 컴터에는 결과만!  

#### RDD operation의 개념적 vs 물리적 동작 차이 (주의) 

1. 개념적 : copy한 새로운 RDD가 만들어진다. (원본은 그대로)  
2. 물리적  
- 실제로는 메모리 내부적으로 operation(연산)의 기록만 남긴다.  (ex) map -> filter -> ... 기록.  
-  action 연산을 만나면 지금까지의 transformation 작업이 한꺼번에 이루어진다. 연산 명령어(*lineage*)기억했다가 한번에 실행.
(tensorflow에서 그래프 그려놓고 session run 해서 한번에 실행하는 것과 비슷)
-  원하면 중간에 cache에 연산과정을 저장할 수 있다. (default는 저장 X)  

**스파크의 핵심은 RDD 가 병렬처리 되는 것이 핵심!**


## 3. Fault Recovery

위에서 말한 것과 같이, RDD는 데이터가 날아가도 **연산 명령어 리스트**(*lineage*)를 추적하기에 이 연산을 순서대로 실행해 정상 복구 가능. 

## 4. 기타

- 스파크 실행시 속도를 올리고 싶다면 메모리 많은 곳에서 올려야.  
(메모리 적으면 cache가 다 안되어 속도가 느릴 수)  
- Administrative GUI를 통해 어떻게 돌아가는지 확인 가능 (tensor board와 유사)  
- Databricks Community Edition를 통해 실행 가능 (주피터 노트북과 유사)  
