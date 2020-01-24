---


---

<h1 id="neural-machine-translation">Neural Machine Translation</h1>
<p>기계번역의 전반적 흐름 파악하기 위해 towards data science 홈페이지의 <a href="https://towardsdatascience.com/neural-machine-translation-15ecf6b0b">이 글</a>을 참고.</p>
<h3 id="encoder-decoder-구조">Encoder decoder 구조</h3>
<p>2개의 RNN 네트워크로 이루어짐. 여기에 attention 메커니즘이 적용되면 좋은 결과를 낼 수 있다.</p>
<p>뉴럴 네트워크, 딥러닝, forward-propagation, loss functions, back-propagation, train &amp; test 데이터셋의 중요성은 어느정도 알고 시작하자.</p>
<h2 id="nmt-소개-및-encoder-decoder-구조">1. NMT 소개 및 Encoder Decoder 구조</h2>
<p>인코더 디코더 구조를 알기 전에, 머신러닝에 넣을 수 있도록 문장들을 변환하는 방법을 알아야 한다.</p>
<p>즉, textual data -&gt; numeric 형태로.</p>
<h3 id="one---hot-encoding-vector">One - hot encoding vector</h3>
<p>한 단어에 대응하는 인덱스 위치에는 1, 그 외의 모든 인덱스에는 0인 벡터.</p>
<p>이렇게 하면 각 단어는 자기만의 원핫인코딩 벡터를 가지기에 데이터셋의 모든 단어를 numerical 하게 표현할 수 있다.</p>
<ol>
<li>input 언어의 모든 단어에 고유 인덱스를 부여(Assign an index to each unique word)하여 vocabulary 생성.</li>
<li>output 언어에도 마찬가지로 모든 단어에 인덱스를 부여하여 vocabulary 생성.</li>
</ol>
<p>하지만, 언어에 따라 수백개에서 수천개의 단어들이 이 vocabulary가 될 수 있는데, 나온 횟수별로 <span class="katex--inline"><span class="katex"><span class="katex-mathml"><math><semantics><mrow><mi>N</mi></mrow><annotation encoding="application/x-tex">N</annotation></semantics></math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut" style="height: 0.68333em; vertical-align: 0em;"></span><span class="mord mathdefault" style="margin-right: 0.10903em;">N</span></span></span></span></span>개의 단어들만 사용하게 된다. (<span class="katex--inline"><span class="katex"><span class="katex-mathml"><math><semantics><mrow><mi>N</mi></mrow><annotation encoding="application/x-tex">N</annotation></semantics></math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut" style="height: 0.68333em; vertical-align: 0em;"></span><span class="mord mathdefault" style="margin-right: 0.10903em;">N</span></span></span></span></span>은 데이터셋 사이즈에 따라 1000 - 100,000개 정도로 임의로 선택된다.)</p>
<p><img src="https://miro.medium.com/max/245/1*_Pp0bAv3nZPYHbPFlvO7Hg.png" alt="test"></p>
<p>위 테이블 보면 0~12까지 인덱스에 모든 단어를 부여했다.</p>
<p>&lt;SOS&gt; 와 &lt;EOS&gt; 의미는 Start of sentence, End of sentence 의미. (일반적으로는 sentence 대신 sequence라고 하는 것 같다.) 문장에서 시작 부분과 끝 부분을 구분하기 위해 사용한다.</p>
<p><img src="https://miro.medium.com/max/1130/1*nxHrAM5dwoqqFFldP0Wv6w.png" alt="figure 2"></p>
<p>위 vocabulary 테이블을 이용해 the blue whale ate the red fish 라는 문장을 원핫 인코딩 벡터들로 표현할 경우 위 사진과 같이 나타낼 수 있다.</p>
<p>사용된 vocabulary 테이블의 전체 사이즈가 13이기 때문에 각 단어도 길이가 13인 벡터가 된다. 그리고 단어 별 부여되었던 인덱스에만 1, 그 외에는 0들로 구성되었다.</p>
<h3 id="section"></h3>
<p>문장을 numeric 하게 표현하는 방법을 알았으니, 인코더 디코더 알고리즘에 대해 자세히 알아보자.</p>
<p>인코더 부분은 input 언어의 문장을 받고 이 문장으로부터 <em>thought vector</em>를 만드는데, 이 <em>thought vector</em>는 문장의 의미를 담고 있으며 디코더 부분으로 전달되어 output 언어로 번역된 문장을 출력한다. 그림으로 표현하면 다음과 같다.</p>
<p><img src="https://miro.medium.com/max/1554/1*KeD0mc9o9DQZ59-nO95sPw.png" alt=""></p>
<p>인코더 부분과 디코더 부분은 둘 다 Recurrent Neural Networks (RNN)이다. 본 게시글에서는 LSTM 모델을 사용할 것이다. (종종 GRU와 같은 다른 RNN 아키텍처도 쓰인다.)</p>
<pre><code>LSTM : Long Short-Trem Memory 모델.
RNN의 종류 중 하나라고 한다. 
</code></pre>
<ul>
<li>RNN 과 LSTM에 대한 추가 설명은 <a href="https://colah.github.io/posts/2015-08-Understanding-LSTMs/">여기</a></li>
<li>번역에서의 LSTM에 대해 더 자세히 알고 싶다면 <a href="http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.248.4448&amp;rep=rep1&amp;type=pdf">여기</a></li>
</ul>
<h3 id="encoder">Encoder</h3>
<p>인코더의 경우 -&gt; 입력 문장의 각 단어들은 모델에 일정 시간을 단위로 (time-step) 들어간다. (each word in the input sentence is fed separately into the model in a number of consecutive time-steps)</p>
<p><em>정확히 말하면 인코더 안에는 한 번에 들어가고, 인코더 안의 LSTM 셀에 시간 차로 들어간다고 함.</em></p>
<p>모델은 해당 time-step <span class="katex--inline"><span class="katex"><span class="katex-mathml"><math><semantics><mrow><mi>t</mi></mrow><annotation encoding="application/x-tex">t</annotation></semantics></math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut" style="height: 0.61508em; vertical-align: 0em;"></span><span class="mord mathdefault">t</span></span></span></span></span>에 모델로 입력되는 단어 정보를 이용해 hidden vector <span class="katex--inline"><span class="katex"><span class="katex-mathml"><math><semantics><mrow><mi>h</mi></mrow><annotation encoding="application/x-tex">h</annotation></semantics></math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut" style="height: 0.69444em; vertical-align: 0em;"></span><span class="mord mathdefault">h</span></span></span></span></span>를 업데이트한다. 이 hidden vector는 입력된 문장에 대한 정보를 저장하기 위한 것이다.</p>
<p>어떤 단어도 인코더로 입력되기 전인 time-step <span class="katex--inline"><span class="katex"><span class="katex-mathml"><math><semantics><mrow><mi>t</mi></mrow><annotation encoding="application/x-tex">t</annotation></semantics></math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut" style="height: 0.61508em; vertical-align: 0em;"></span><span class="mord mathdefault">t</span></span></span></span></span> = 0일 때, 이 때는 인코더의 hidden state 는 비어있는 벡터 (empty vector)로 시작한다. 이 hidden state을 다음 그림과 같이 나타낸다.</p>
<p><img src="https://miro.medium.com/max/150/1*GZCzxYAMHdiCLiTTHNBsSw.png" alt=""></p>
<p>위 그림에서 <span class="katex--inline"><span class="katex"><span class="katex-mathml"><math><semantics><mrow><mi>t</mi></mrow><annotation encoding="application/x-tex">t</annotation></semantics></math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut" style="height: 0.61508em; vertical-align: 0em;"></span><span class="mord mathdefault">t</span></span></span></span></span>=0 이라는 것은 time-step = 0 이라는 것이고,<br>
<span class="katex--inline"><span class="katex"><span class="katex-mathml"><math><semantics><mrow><mi>E</mi></mrow><annotation encoding="application/x-tex">E</annotation></semantics></math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut" style="height: 0.68333em; vertical-align: 0em;"></span><span class="mord mathdefault" style="margin-right: 0.05764em;">E</span></span></span></span></span>가 의미하는 것은 Encoder의 hidden state라는 것을 의미.<br>
(Decoder의 경우 <span class="katex--inline"><span class="katex"><span class="katex-mathml"><math><semantics><mrow><mi>D</mi></mrow><annotation encoding="application/x-tex">D</annotation></semantics></math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut" style="height: 0.68333em; vertical-align: 0em;"></span><span class="mord mathdefault" style="margin-right: 0.02778em;">D</span></span></span></span></span>)</p>
<p>각 time-step에서의 hidden vector는 해당 time-step의 input word 정보를 받는다. 이 때, hidden vector는 이전 time-step들에서 이미 저장한 정보들을 가지고 있다. (이전의 모든 단어에 대한 정보를 다 가지고 있다!)</p>
<p>이렇게 time-step 마다 들어온 단어들에 대한 정보를 보유한채 전달- 전달- 전달되어 마지막 단어까지 저장된 hidden vector는 전체 입력 문장의 의미를 다 담고 있다. 이 마지막 time-step의 hidden vector는 위에서 언급했던 thought vector로, 디코더의 input이 된다.</p>
<p>"the cat likes to eat pizza"라는 문장이 있다면 인코더에서 아래 그림과 같이 동작한다.</p>
<p><img src="https://miro.medium.com/max/2958/1*xd8j4KoKRSzRq0b1Vx0FAA.png" alt=""></p>
<p>위 그림에서, <strong>파란색 화살표</strong>는 <strong>weight matrix</strong>, 즉 weight 행렬이다. 더 정확한 번역을 할 수 있도록 학습할 부분인데, 일단 이 정도만 알아두고 넘어가자.</p>
<p>또한, 위 그림에서 인코더의 마지막 hidden state가 thought vector 가 되는 것에 주목! 이 때 <span class="katex--inline"><span class="katex"><span class="katex-mathml"><math><semantics><mrow><msubsup><mi>h</mi><mrow><mi>t</mi><mo>=</mo><mi>n</mi></mrow><mi>E</mi></msubsup></mrow><annotation encoding="application/x-tex">h^{E}_{t=n}</annotation></semantics></math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut" style="height: 1.08833em; vertical-align: -0.247em;"></span><span class="mord"><span class="mord mathdefault">h</span><span class="msupsub"><span class="vlist-t vlist-t2"><span class="vlist-r"><span class="vlist" style="height: 0.841331em;"><span class="" style="top: -2.453em; margin-left: 0em; margin-right: 0.05em;"><span class="pstrut" style="height: 2.7em;"></span><span class="sizing reset-size6 size3 mtight"><span class="mord mtight"><span class="mord mathdefault mtight">t</span><span class="mrel mtight">=</span><span class="mord mathdefault mtight">n</span></span></span></span><span class="" style="top: -3.063em; margin-right: 0.05em;"><span class="pstrut" style="height: 2.7em;"></span><span class="sizing reset-size6 size3 mtight"><span class="mord mtight"><span class="mord mathdefault mtight" style="margin-right: 0.05764em;">E</span></span></span></span></span><span class="vlist-s">​</span></span><span class="vlist-r"><span class="vlist" style="height: 0.247em;"><span class=""></span></span></span></span></span></span></span></span></span></span>이 <span class="katex--inline"><span class="katex"><span class="katex-mathml"><math><semantics><mrow><msubsup><mi>h</mi><mrow><mi>t</mi><mo>=</mo><mn>0</mn></mrow><mi>D</mi></msubsup></mrow><annotation encoding="application/x-tex">h^{D}_{t=0}</annotation></semantics></math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut" style="height: 1.08944em; vertical-align: -0.248108em;"></span><span class="mord"><span class="mord mathdefault">h</span><span class="msupsub"><span class="vlist-t vlist-t2"><span class="vlist-r"><span class="vlist" style="height: 0.841331em;"><span class="" style="top: -2.45189em; margin-left: 0em; margin-right: 0.05em;"><span class="pstrut" style="height: 2.7em;"></span><span class="sizing reset-size6 size3 mtight"><span class="mord mtight"><span class="mord mathdefault mtight">t</span><span class="mrel mtight">=</span><span class="mord mtight">0</span></span></span></span><span class="" style="top: -3.063em; margin-right: 0.05em;"><span class="pstrut" style="height: 2.7em;"></span><span class="sizing reset-size6 size3 mtight"><span class="mord mtight"><span class="mord mathdefault mtight" style="margin-right: 0.02778em;">D</span></span></span></span></span><span class="vlist-s">​</span></span><span class="vlist-r"><span class="vlist" style="height: 0.248108em;"><span class=""></span></span></span></span></span></span></span></span></span></span>으로 다르게 표기 되는 것도 주목!</p>
<p>이는 <strong>인코더의 마지막 hidden vector = 디코더의 첫번째 hidden vector</strong>라는 것이다.<br>
문장의 인코딩된 의미를(encoded meaning) 디코더로 넘겨 번역될 수 있도록 하는 것이다.</p>
<p>But! 인코더랑 달리, 디코더는</p>
<hr>
<p>디코더에 대해 물어보았다.</p>
<p><img src="https://postfiles.pstatic.net/MjAyMDAxMjRfMjYy/MDAxNTc5ODA2NjY0OTA1.f91Zthaq4weJMyB1kOsejgmsFPsAUwttqSXOILZ19dIg.ABPzgofet5_3NmRoX7s9nizdzjWzRhNxlzl6oORYYN4g.PNG.wazoskee/image.png?type=w773" alt=""></p>
<p>디코더도 인코더처럼 입력이 있다. 디코더 쪽의 입력과 인코더에서 나온 행렬 형태의 context vector를 합해서 유추.</p>
<p>디코더에서 첫번째 cell 에 주목. context vector가 들어감. RNN 특징은 입력이 2개. hidden state와 입력데이터 x</p>
<p>그런데 이 hidden state에 해당하는게 context vector 입력데이터 x에 처음에 넣을게 없으니까 &lt;SOS&gt;를 같이 넣어준다. 이 두개를 합쳐서 예측. 무슨 말인가. 이 결과가 안녕하세요 라고 한다면, 디코더 두번째 셀로 넘어감.<br>
어떻게 넘어가냐면 RNN에서 내부적으로 계산해서 hidden state 가 나온다고 했지.<br>
context vector 랑 sos 랑 내부적으로 계산해서 hidden state가 나옴. 이게 디코더 두번째 셀의 입력으로 들어감.<br>
그림에서 h가 context vector. &lt;S&gt; 는 &lt;SOS&gt; 이 두개가 들어가서 안녕하세요가 나왔으면 첫번째 셀 역할은 끝. x + context vector =&gt; 새로운 hidden state.</p>
<p>인코더에서 넘겨준건 context vector 하나 뿐인데, 기계번역에서는 짧은 문장에서만 효과를 발휘. 문장이 긴데 계속 고정된 사이즈의 context 벡터로 하면 엉망진창</p>
<p>Q. 아무리 짧은 문장에서만 성능이 좋더라도, 어떻게 처음에 인코더 context vector랑 디코더 &lt;SOS&gt;만 넣었는데 안녕하세요가 나오지? 아무리 문장이 짧더라도 , 안녕하세요 카이립입니다 이러면 입니다 부분이나와야하는 것 아닌가?<br>
A. &lt;SOS&gt;의 역할이 바로 이것. 문장들을 학습하면서 &lt;SOS&gt;가 오면 문장의 시작부분이 오는게 좋겠다 이것을 학습한 것. 안녕하세요 다음에는 우리는이 자연스럽겠다. context vector가 고려된 첫번째 lstm 셀의 hidden state 와 안녕하세요. 고려</p>
<hr>
<p>그래서 인코더에 주목. 위 구조에서는 인코더가 하는일이 없다 이렇게 사람들이 판단함. we가 들어간 LSTM에 주목하면 방금 들어온 we에 대한 정보가 많다. hi가 들어가면 hi에 대한 정보가 많고. 이런 점을 활용해서 이를 인코더 디코더를 합쳐본 것.<br>
디코더 해석을 할 때 마지막 context vector를 하는게 아니라 hi에 해당하는 그 넣어주었던 시점의 인코더를 참고 / 활용해보자.</p>
<p>어떤게 어떤 시점에 더 중요한지 모르니까, 지금 현재 예측하고 있는 디코더의 T번째 셀이 예측할 때 가지고 있는 hidden state 행렬이랑<br>
인코더의 RNN들 (그림상 LSTM) 이거를 각각 내적.(애초에 서로 같게 설정. 인코더에서 나온 히든 스테이트가 디코더의 입력 데이터 각각 웨이트 곱해진 것 더함. LSTM GRU 는 내부적인 계산이 조금 다를 수 있지만 기본은 이런 형태.)</p>
<p><img src="https://postfiles.pstatic.net/MjAyMDAxMjRfMjYy/MDAxNTc5ODA2NjY0OTA1.f91Zthaq4weJMyB1kOsejgmsFPsAUwttqSXOILZ19dIg.ABPzgofet5_3NmRoX7s9nizdzjWzRhNxlzl6oORYYN4g.PNG.wazoskee/image.png?type=w773" alt=""></p>
<p>RNN은 새로 들어온 입력데이터랑 전에서 넘어온 히든 스ㄷ테이트. 이 두개 참고하죠. 이 히든 스테이트는 똑같은게 오더라도 입력데이터가 인지 안녕하세용니지 에 따라 다른 값이 나올 수 있다는 것. 이 왔으니까 앞에 많이 나오는 단어에 대해서 좋은 점수가 배정이된다.</p>
<p>Q. 좋은 점수를 배정한다는건 어떻게?<br>
A. affine 계층. 흔히 말하는 feed forward. 이렇게 점수를 매기는게 affine 계층. 이 점수에 softmax 해서 확률 가장 높게 나오는게 안녕하세요. / 우리는//<br>
히든 스테이트가 256개라고 가정하면, 이 256개에 대해 가중치를 주어서 점수를 쫙 낸다. 히든 스테이트가 입력으로 들어감 affine 계층에.</p>
<p>한글에서 영어로 번역하면, 문자 단위로 하면<br>
한글 800개 영어 알파벳 24개라고 하면. lstm에서 히든 스테이트가 몇개이던 아우풋은 24개로 맞춰야.<br>
어파인 계층에서 256 * 24 의 행렬이 있으면 24개의 행렬로 바꿔주어야. 히든 스테이트 개수가 몇 개든 원하는 아웃풋 사이즈로 맞춰주는 계산을 해주는게 어파인. 웨이트를 곱해주고 24개가 나왔다. 어파인 계층의 인풋은 히든스테이트 사이즈가 되고 아웃은 24개. 분류 개수.  그래서 내부적으로 웨이트 계산이 되면 24개 알파벳에 대한 점수들이 각각 들어오게 된다.<br>
Q. 이 웨이트는 어떻게 계산하는걸까? A, 백프로파게이션으로 업데이트. 그동안 열심히 배운 백프로파게이션!! 그것.<br>
이렇게 어파인 계층에서 점수가 계산이 되었으면 소프트맥스로 가장 높은 확률의 ‘안녕하세요’  이렇게 출력.</p>
<p>첫번째 LSTM이랑… 이렇게 모든 인코더들이랑 계<br>
백터 내적의 의미 : 서로 얼마나 닮았는지 유사도.내적을 하면 상수가 나온다.<br>
디코더 현재 셀과 유사한 셀을 고르는 것<br>
각 각 지금 디코더의 셀과 얼마나 유사한지 상수로 표현할 수 있다. 이 값들을 softmax로 . 다합하면 1로 만들어주지.</p>
<p>소프트 맥스로 상수가 나왔지. 각 인코더의 히든스테이트를 보유중이라고 가정 (저장되어 있을 것). 소프트 맥스를 하면 실수가 나오면 각각 곱해줌. 첫번째 인코더의 소프트 맥스가 05이면 첫번째 인코더<br>
각 히든스테이트의 자기에 해당하는 실수를 곱한 것.<br>
인코더의 각 히든스테이트에 중요한 만큼 곱을 해준 것.</p>
<p>설명할 때는 쉽게 설명하고자 단어 단위라고 하는데<br>
인코더 셀이 5개라고 하면 들어온 것을 5개의 부분으로 나눠서 가져감.<br>
(인코더 셀의 개수는 정해져 있으니까.)</p>
<p>그림을 먼저 이해하고<br>
알 것 같은게 있고 모르는게 있으면<br>
모르는 부분 집중해서 코드를 더 보면<br>
이해가 더 잘 돼요!<br>
(예를 들어 이 부분 넘어갈 때 뭘 어떻게 넘기지? 더해서? 곱해서? 하는 부분!)</p>
<hr>
<p><img src="https://postfiles.pstatic.net/MjAyMDAxMjRfMTA2/MDAxNTc5ODA2NjkxNjc0.FGhg8RO0mdYi0Apn0WCeIQCN6Aup_4IKfrH7UuaRBb0g.DGNiRNuwpeJzjMQZrG81XiDoCR6Y6_Vwre06Fk-Wp2og.PNG.wazoskee/image.png?type=w773" alt=""></p>
<p>인코더 부분. 흔히 아는 RNN,</p>
<p><img src="https://postfiles.pstatic.net/MjAyMDAxMjRfMjYy/MDAxNTc5ODA2NjY0OTA1.f91Zthaq4weJMyB1kOsejgmsFPsAUwttqSXOILZ19dIg.ABPzgofet5_3NmRoX7s9nizdzjWzRhNxlzl6oORYYN4g.PNG.wazoskee/image.png?type=w773" alt=""></p>
<p>디코더 부분</p>
<p>전체 그림 넣기</p>
<p>지금까지가 seq2seq 여기서 문제가 아까 위에서 말한 것.</p>
<p>그래서 나온게 인코더 각 셀과 디코더 각 셀을 합치는 것.</p>
<p>hi 라고 말한 셀에는 hi 정보가 많다. 이러한 점을 이용.</p>
<p>인코더 각 각과 내적. 인코더 각각의 히든 스테이트에 대해 내적한 결과가 나오겠찌? 내적의 결과는 상수. 이 상수에 소프트맥스 적용하여 합이 1이 되도록. 즉, 스칼라들을 다 주엇을 때 확률적으로 바꿔줌.</p>
<p>빨간색 그림</p>
<p>0~1까지의 값이 나오면 이것이 각 인코더 셀의 weight가 된다. 그래서 등장한 것이 각 각의 히든 스테이트들을 합지낟.</p>
<p>빨간색 그림 에 h 곱하는 것</p>
<p>소프트맥스 적용한 상수들에 인코더 히든 스테이트를 합친다.  행렬이 유사도를 구하는 데 백터의 내적을 한 것 . 벡터 내적을 하면 각 인코더에 대한 유사도 점수가 나올 것 . 이 유사한지에 대한 점수를 소프트 맥스. 이 중요도를 총 합치면 1이니까 인코더 각 셀의 퍼센트를 나타낼 수 있다. 이거를 각 인코더의 히든 스테이트랑 곱한 것 0`1까지의 실수를 . hi라는 인풋이 0.5 점수를 받았어 그러면 인코더 히든 스테이트에 곱해서 더함. 다 합쳐서 하나의 히든 스테이트가 나오면…디코더 아웃풋으로 나온 히든 스테이트랑 concat 둘이 이어줌.</p>
<p>Q. 순차적으로 해석이 안되는건 어떻게?<br>
A. 압축이 될 때 시간 순서는 고려가 안됨.<br>
기계가 보았을 때 그 입력의 조합을 학습.<br>
우리 입장에서는 순차적으로 학습하는 것 처럼 보이지만, 기계는 조합을 학습해서 계속 학습하면서 찾아가는것.</p>
<p>Q. 그러면 RNN 을 쓰는 것은 왜? 입력하는 순서를 위해서?<br>
A. No, RNN은 순서를 고려한다기보단 이전에 있던 것도 기억을 한다고 이해하면 쉬움. RNN을 메모리가 있는 알고리즘이라고 하듯이.</p>

