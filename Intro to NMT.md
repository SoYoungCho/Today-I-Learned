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

