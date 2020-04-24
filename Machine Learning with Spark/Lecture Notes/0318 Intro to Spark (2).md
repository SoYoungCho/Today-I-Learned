# Job Execution

## 1. SW components

* 스파크는 라이브러리와 같이 동작. (app 당 1 instance (?))
* 로컬하게 / 클러스터 상으로 실행 가능
	+ 클러스터하게 실행하면 worker 컴퓨터에 task 분배
* 하둡의 InputFormat API로 저장소에 접근 가능
(HBase, HDFS, 아마존의 S3 등)

## 2. Task Scheduler

![](https://postfiles.pstatic.net/MjAyMDAzMThfMjEy/MDAxNTg0NTM1MjA5OTQ2.GvOFeJX8Rm1Zt81qI9Tat_dqyRUmsBvYCBlPqRuuLtog.qQ-C_i8FHSOiEP4yz1y3eq6lkNWXn1bxsQXm-KH9LGMg.PNG.wazoskee/image.png?type=w773)

* task schedule은 스파크가 자동으로 해줌
* 일대일로 대응되는 것 말고, 일대다로 화살표 가는 것이 shuffle이다.
* shuffle은 네트워크를 타고 와따리 가따리 하기에 느릴 수 있어서 최소화 하는 것이 좋다.  
  (일대일로 로컬하게 되는 것이 좋다)
* 위 그림의 groupBy 는 내부에 hash 함수 적용된 것과 마찬가지 (동일한 key로 join)
* 위 그림의 B와 F가 일대일로 실행된 것으로 보아 두 key가 동일했음을 알 수 있다. 반면, C D E에서의 map과 filter에서는 shuffle이 없었기에 E의 key를 F와 맞춰주기 위해 join하며 shuffle이 일어난 것.

---

# Spark 사용하기

### SparkContext

>스파크 사용할 때 *sc.어쩌고 저쩌고* 이렇게 쓴다.

### Transformations 종류

![](https://postfiles.pstatic.net/MjAyMDAzMThfNTYg/MDAxNTg0NTM2ODM1MTM0.h1LpBWRvnX2r06gEKrcD093FVE3nRqt_bj3pCChUDecg.4vdVCdREmU-Tn7cIOg3wlkbCBRIhv1NnrLaPYY7wdzQg.PNG.wazoskee/image.png?type=w773)

* map : 함수 적용
* filter : 조건으로 필터링
* flatmap : map 후 칸막이 구분 없이 하나로 flat하게 펼치기
	+ 왜 사용할까? 전체 텍스트 기준 word count 해야하는 경우 사용

### Actions 종류

￼![](https://postfiles.pstatic.net/MjAyMDAzMThfMTYy/MDAxNTg0NTM2ODQ5Mzg5.7N4Sf7u5tEtcT0cHHdLU6x6vuHStB4umMzF2IvafGfMg.djjzCyy4rZDHF8K_2km8Y-cK_tJZXBU7wRHTxDutcoUg.PNG.wazoskee/image.png?type=w773)

* reduce : 여러 개를 1개로 줄여주기.
	+ 위 예시에서는 1,2,3에서 x+y면 이진트리 처럼 (1+2) + 3 = 6.
	+ **분산처리의 operation에는 for loop 자체가 없음 주의!!!**

### Key-Value Operations

스파크의 분산 reduce는 key-value pair의 RDD 단위로 적용된다.

![](https://postfiles.pstatic.net/MjAyMDAzMThfMjYw/MDAxNTg0NTM4MjU5Mjc3.XnASjvqjpno4RVki1vXP7t4HTih_-Au5IhUTcpoPussg.G0lc9o4FgKq-a_7fb4aLGi6Tk4w3WXOWfSGjXaRTlBEg.PNG.wazoskee/image.png?type=w773)



## 기타

* RDD operation 할 때 파라미터로 몇 개의 task로 분산할지 옵션을 줄 수 있다.
* some : null인 것, 아닌 것 둘 다 표현할 수 있는 datatype
