# Violin plot

- 형상이 바이올린을 닮아 붙여진 이름
-  **카테고리컬한 데이터 분포를 시각적으로 비교하기 유용**
- 박스 플롯과 유사하지만 밀도를 더 깊이 이해할 수 있다
- 특히, 데이터 양이 많고 개별 관찰을 표시할 수 없는 경우에 적합
- 하나의 숫자 변수와 여러 그룹이 있을 때 사용
	- 한 그룹과 다른 그룹간 값 비교 가능

` 
sns.violinplot(data = data, x = data['label'], y = data['TCMD'])
plt.show()
` 

![](https://i1.wp.com/hleecaster.com/wp-content/uploads/2019/12/violin-plot.png?w=498)

### 해석방법
- 중심선을 따라 대칭인 KDE 플롯이 있다
	- KDE는 커널밀도추정 (Kernel Density Estimator) 의미
- 가운데 흰색 점은 중앙값(median) 의미
- 바이올린 중앙의 두꺼운 선은 사분위 범위 의미
- 바이올린 중앙의 얇은 선은 신뢰구간 의미 (95%의 신뢰구간)

[참고 블로그]([https://blog.naver.com/PostView.nhn?blogId=youji4ever&logNo=221864110030&categoryNo=0&parentCategoryNo=0&viewDate=&currentPage=1&postListTopCurrentPage=1&from=postView](https://blog.naver.com/PostView.nhn?blogId=youji4ever&logNo=221864110030&categoryNo=0&parentCategoryNo=0&viewDate=&currentPage=1&postListTopCurrentPage=1&from=postView))
