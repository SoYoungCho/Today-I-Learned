2020 한국통신학회 동계종합학술발표회 - 5G 아이디어 경진대회 intro

# 1. 4차 산업혁명과 5G

## 통신 개념 & DSP

파장과 주파수는 반비례  
5G는 mm/p 단위. 높은 주파수, 짧은 파장

### 푸리에 변환
: 주파수와 시간 차이 변환하는 도구

r이 짧아지면 빨리 보낼 수 있음 -> 대역폭은 넓음 ('광대역'이 이 의미)

### bit와 symbol

symbol M = 2^k (k = bit 수)

k가 커질 경우  
장 ) 한 번에 많은 양의 데이터   
단 )  interference와 잡음에 약하다. 오류 확률 높아짐.  

## 4차 산업혁명

1차 산업혁명 - 증기기관차  
2차 산업혁명 - 대량생산, 공장 (포드 공장, 컨베이어 벨트)  
3차 산업혁명 - 전자제품, IT. 컴퓨터  
4차 산업혁명 - A new generation of wireless communication.(5G) connectivity (초연결)  
 all connected world of humans and objects. human dominated wireless communication  
 
 5G 공식 명칭 : IMT 2020 (2020년부터 본격적으로 서비스 시작해서)  
 
 INFRA : 고속도로. 여러 산업군의 Info를 나누어 줌으로써 4차 산업혁명 견인.
 

AI, IoT, 클라우드 컴퓨팅, 빅데이터, 모바일.

**5G 적용분야**

농경, 자동차 건설, 에너지, 금융, 건강, 제조업, 미디어, 공공안전, 도소매업, 교통  
해당 산업군과 5G 적용사례와 관련성 표시한 표를 보면 --> 스마트 시티, 제조업, 미디어, 도소매업

### 5G와 무선통신

무선통신의 역사 : 10년 단위로 바뀌어 왔음. 2030년이 다음 변화 아닐까 추측
LTE : long term evolution의 약자
carrier aggregation : 캐리어 모아서 보냄.

### 5G의 정의

ultra fast , ultar low-latency, super connectivity를 가능하게 해주는 core infrastructure

### 5G 응용 사례

자율주행(low latency, high reliabity. 차와 차, 차와 infra, 차와 사람 등 간의 연결 필요)
비상시의 연락망, 공장 자동화, 초고속 열차, large - outdoor event (예) 불꽃놀이) 트래픽 처리 (통화가 안되기 때문), 미디어 demand,  
원격 진료, 원격 수술, 쇼핑(쇼핑몰이 특히 스마트 시티의 축소판), 스마트 시티(high data rate. 열심히 집에서 일해야 하니. low latency, 다양한 환경에 따라 
맞춤형..), security, 경기장 (stadium), 막히는 교통, VR/AR

각 use case 별로 requirement가 있음. (low latency, high reliabity 이런거)

### Usage Senario of 5G

크게 3가지.

![](https://www.researchgate.net/profile/Pouria_Sayyad_Khodashenas/publication/326440023/figure/fig2/AS:649290988941317@1531814443735/Usage-scenarios-of-IMT-2020-and-beyond-Source-ITU-R-4.png)
1. enhansed mobile broadband (높은 data rate)
2. massive machine type communications (예) IoT)
3. ultra reliable and low latency communications (신뢰성, 낮은 지연성)

![](https://www.netmanias.com/ko/?m=attach&no=8176)

3가지 usage 시나리오는 모든 key capability를 만족하기 어렵다. 다 만족하는 것이 목표

![](https://www.netmanias.com/ko/?m=attach&no=8177)

# 2. 5G 기술 동향 (SKT)

기존 LTE 대비 차이 : 데이터 사용량 4배, 게임 사용량 2배, 미디어 사용량 2개, VR/AR 사용량 84배

**5G 특징**
speed, latency, massive connectivity, stability, security

예시

1. 5G AI 가상 비서  
실감형 개인화 서비스 --> 클라우드 서버 IoT 기반 빅데이터 수집, social/env. context 인지

2. 자율주행 차량으로 빠르고 안전한 출근

3. 스마트 오피스 : 안면인식 통한 신분 확인, 네트워크 슬라이딩, AR/VR 기반 가상회의, 스마트센싱 (IoT 기반 최적 업무환경), 히트맵 활용 공간 활용 최적화 (사람 많으면 분산시키는)

# 3. 5G 스마트 시티 (한국폴리텍대학)

1. Sustainable  
2. citizen-centric
3. data-driven

5G 기술을 활용

### 5G 스마트시티 서비스 시나리오

##### 스마트시티 위원회의 서비스

1. autonomous driving service 자율주행

여러 데이터가 자동차 간, 자동차와 네트워크, roadside의 entity들과 통신해야 C-V2X (cellular vehicle to Everything)  
정체를 막고, 발생하는 pollution 감소. faster and efficiently. 지자체가 관심이 많음

2. demand response intellogent transport system

지자체는 개인용 운행을 줄이고 싶어함 (공간 문제, 주차문제, air pollution)  
어떻게 하면 개인용 자동차 사용을 줄일 수 있을까.  
실제 국가교통부? 가 이런 사업 시행중. --> 자동차가 없는 도시.  
개인용 자동차가 특정 영역에 진입하지 못하도록. 대중교통 시스템 고도화 통해 개인용 자동차 사용 안해도 될 정도로.
대중교통 route plan을 daily update. 오늘은 이렇게 이동 이걸 매일 공지.
가장 가까이의 대중교통을 내 차처럼 타고 다닐 수 있게 하겠다.
예) 여의도 불꽃놀이 행사 - 특별 운행, 야간 운행 등. 이를 항시적으로 할 수 있도록

3. 대기질 (공기질)

4. engergy use optimization service

 에너지와 환경문제.
 물리층 - 전기 생산
 거래소 - 전기 거래
 소비단계까지
 
 데이터 추출, 효율적 관리. (스마트하게 연결해서)


5. smart crime prevention service 안전 및 방범

+ real time streep map

순찰차 정보 이용해 가장 최신의 정보 맵. (real time image collection)  

+ smart safe booth. 우범 지역에 설치. 카메라, 마이크, 경찰과 연결된 5G 네트워크. 만일 누가 쫓아온다!  
경찰이 출동할 것 메세지. 동시에 경찰 출동 (real time crime prevention)


6. 재난 상황이 발생했을 때 (fast disaster info. provisioning)

구조자 - 소방관, 경찰관.  
몇 명의 사람들, 어디에 위치

요구조자 - 어떤 길로 대피, 탈출해야하는지. 무슨 일을 해야 구조 받을 확률이 높아지는지 안내.

### KPI (Key Perfomance Index)

device density  
mobility 디바이스가 몇 km/h로 이동  
coverage 서비스가 영역 어디까지 (m단위) 커버  
리얼타임 /  
user data rate 최대 단일 유저가 몇 bps까지  
latency 기본 단위는 mm  
reliability : access prob.  
positioning : 예를 들어 자율주행 자동차. 세밀하게 거리 얼마나 이동했는지.  

등 총 14가지.

eMBB (data rate이 높아야하는 서비스), mMTC(연결되는 기기 수가 많아야 할 때), URLLC (고신뢰성, 데이터가 깨지지 않고)

창의적이고 새로운. 황당하진 않게 위 참고해서.

