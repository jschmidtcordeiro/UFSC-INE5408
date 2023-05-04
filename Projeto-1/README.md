<div class="no-overflow"><p><span style="font-size: medium; color: #0000ff;"><strong style="font-size: medium; color: #0000ff;">Objetivo</strong></span></p>
<p>Este projeto consiste na utilização de estruturas lineares, vistas até o momento no curso, e aplicação de conceitos de pilha e/ou fila para o processamento de arquivos XML contendo matrizes binárias que representam cenários de ação de um robô aspirador. A implementação deverá resolver dois problemas (listados a seguir), e os resultados deverão ser formatados em saída padrão de tela de modo que possam ser automaticamente avaliados no VPL.</p>
<ul>
<li><span style="color: #ff0000;">Entradas:</span>
<ul>
<li><a href="https://www.inf.ufsc.br/~alexandre.goncalves.silva/courses/datasets/robo/cenarios.zip">cenarios.zip</a></li>
</ul>
</li>
<li><span style="color: #ff0000;">Saídas esperadas:</span>
<ul>
<li><a href="https://www.inf.ufsc.br/~alexandre.goncalves.silva/courses/datasets/robo/vpl_evaluate.cases.txt">vpl_evaluate.cases</a></li>
</ul>
</li>
<li><span style="color: #ff0000;">Dica:</span>
<ul>
<li>utilize <strong>"avaliar"</strong> (e não "executar") para que as entradas sejam automaticamente carregadas</li>
</ul>
</li>
</ul>
<p></p>
<p><span style="font-size: medium; color: #0000ff;"><strong style="font-size: medium; color: #0000ff;">Materiais</strong></span></p>
<p>De modo a exemplificar uma entrada para o seu programa, segue o arquivo XML utilizado no primeiro teste:</p>
<ul>
<li><a href="https://www.inf.ufsc.br/~alexandre.goncalves.silva/courses/datasets/robo/cenarios1.xml">cenarios1.xml</a>, <a href="https://www.inf.ufsc.br/~alexandre.goncalves.silva/courses/datasets/robo/cenarios2.xml">cenarios2.xml</a>, <a href="https://www.inf.ufsc.br/~alexandre.goncalves.silva/courses/datasets/robo/cenarios3.xml">cenarios3.xml</a>, <a href="https://www.inf.ufsc.br/~alexandre.goncalves.silva/courses/datasets/robo/cenarios4.xml">cenarios4.xml</a>, <a href="https://www.inf.ufsc.br/~alexandre.goncalves.silva/courses/datasets/robo/cenarios5.xml">cenarios5.xml</a>, <a href="https://www.inf.ufsc.br/~alexandre.goncalves.silva/courses/datasets/robo/cenarios6.xml">cenarios6.xml</a>
<ul>
<li>Arquivo compactado com todos os arquivos XML: <a href="https://www.inf.ufsc.br/~alexandre.goncalves.silva/courses/datasets/robo/cenarios.zip">cenarios.zip</a></li>
</ul>
</li>
<li>dicas sobre leitura e escrita com arquivos em C++<br>
<ul>
<li><a href="http://www.cplusplus.com/doc/tutorial/files/">http://www.cplusplus.com/doc/tutorial/files/</a></li>
</ul>
</li>
<li>para a criação e concatenação de palavras/caracteres, sugere-se o uso da classe <span style="font-family: courier new, courier, monospace;">string</span>:
<ul>
<li><a href="http://www.cplusplus.com/reference/string/string/">http://www.cplusplus.com/reference/string/string/</a></li>
</ul>
</li>
</ul>
<p></p>
<p><span style="font-size: medium; color: #0000ff;"><strong style="font-size: medium; color: #0000ff;">Primeiro problema:</strong> validação de arquivo XML</span></p>
<p>Para esta parte, pede-se exclusivamente a verificação de aninhamento e fechamento das marcações (<em>tags</em>) no arquivo XML (qualquer outra fonte de erro pode ser ignorada). Se houver um erro de aninhamento, deve se impresso <span style="color: #ff0000;"><strong><span style="font-family: courier new, courier, monospace;">erro</span></strong></span> na tela. Um identificador constitui uma marcação entre os caracteres <strong><span style="color: #800080; font-family: courier new, courier, monospace;">&lt;</span></strong> e&nbsp;<strong><span style="color: #800080; font-family: courier new, courier, monospace;">&gt;</span></strong>, podendo ser de abertura (por exemplo: <strong><span style="color: #800080; font-family: courier new, courier, monospace;">&lt;cenario&gt;</span></strong>) ou de fechamento com uma <span style="font-family: courier new, courier, monospace;"><strong><span style="color: #800080;">/</span></strong></span> antes do identificador (por exemplo: <span style="font-family: courier new, courier, monospace;"><strong><span style="color: #800080;">&lt;/cenario&gt;</span></strong></span>). Como apresentando em sala de aula, o algoritmo para resolver este problema é baseado em pilha (<span style="color: #ff0000;"><strong>LIFO</strong></span>):</p>
<ul>
<li>Ao encontrar uma marcação de abertura, empilha o identificador</li>
<li>Ao encontrar uma marcação de fechamento, verifica se o topo da pilha tem o mesmo identificador e desempilha. Aqui duas situações de erro podem ocorrer:
<ul>
<li>Ao consultar o topo, o identificador é diferente (ou seja, uma marcação aberta deveria ter sido fechada antes)</li>
<li>Ao consultar o topo, a pilha encontra-se vazia (ou seja, uma marcação é fechada sem que tenha sido aberta antes)</li>
</ul>
</li>
<li>Ao finalizar a análise (<em>parser</em>) do arquivo, é necessário que a pilha esteja vazia. Caso não esteja, mais uma situação de erro ocorre, ou seja, há marcação sem fechamento</li>
</ul>
<p></p>
<p><span style="font-size: medium; color: #0000ff;"><strong style="font-size: medium; color: #0000ff;">Segundo problema:</strong> determinação de área do espaço que o robô deve limpar<br></span></p>
<p>Cada XML, contém matrizes binárias, com altura e largura, definidas respectivamente pelas marcações&nbsp;<span style="font-family: courier new, courier, monospace; color: #800080;"><strong>&lt;altura&gt;</strong></span> e&nbsp;<span style="font-family: courier new, courier, monospace;"><strong><span style="color: #800080;">&lt;largura&gt;</span></strong></span>, e sequência dos pontos, em modo texto, na marcação <span style="font-family: courier new, courier, monospace;"><strong><span style="color: #800080;">&lt;matriz&gt;</span></strong></span>. Cada ponto corresponde a uma unidade de área, sendo 0 para não pertencente ou 1 para pertencente ao espaço que deve ser limpo, como passo mínimo do robô em uma de quatro direções possíveis (vizinhança-4),&nbsp; Para cada uma dessas matrizes, pretende-se determinar a área (quantidade de pontos iguais a 1 na região do robô) que deve ser limpa, conforme a posição inicial, linha <span style="font-family: courier new, courier, monospace; color: #800080;"><strong>&lt;x&gt;</strong></span> e coluna <span style="font-family: courier new, courier, monospace;"><strong><span style="color: #800080;">&lt;y&gt;</span></strong></span>, do robô (primeira linha e primeira coluna são iguais a zero). Para isso, seguem algumas definições importantes:</p>
<ul>
<li>A <span style="text-decoration: underline;"><strong>vizinhança-4</strong></span> de um ponto na linha <em><span style="font-family: courier new, courier, monospace;"><strong>x</strong></span></em> e coluna <em><strong><span style="font-family: courier new, courier, monospace;">y</span></strong></em>, ou seja, na coordenada <span style="font-family: courier new, courier, monospace;"><strong>(<em>x</em>,<em>y</em>)</strong></span>, é um conjunto de pontos adjacentes nas coordenadas:
<ul>
<li><span style="font-family: courier new, courier, monospace;"><strong>(<em>x</em>-1, <em>y</em>)</strong></span></li>
<li><span style="font-family: courier new, courier, monospace;"><strong>(<em>x</em>+1, <em>y</em>)</strong></span></li>
<li><span style="font-family: courier new, courier, monospace;"><strong>(<em>x</em>, <em>y</em>-1)</strong></span></li>
<li><span style="font-family: courier new, courier, monospace;"><strong>(<em>x</em>, <em>y</em>+1)</strong></span></li>
</ul>
</li>
<li>Um <span style="text-decoration: underline;"><strong>caminho</strong></span> entre um um ponto <em><span style="font-family: courier new, courier, monospace;"><strong>p</strong></span></em><span style="font-family: courier new, courier, monospace;"><strong><sub>1</sub></strong></span> e outro <em><span style="font-family: courier new, courier, monospace;"><strong>p<sub>n</sub></strong></span></em> é em um sequência de pontos distintos <span style="font-family: courier new, courier, monospace;"><strong>&lt;<em>p</em><sub>1</sub>,<em>p</em><sub>2</sub>,...,<em>p<sub>n</sub></em>&gt;</strong></span>, de modo que <span style="font-family: courier new, courier, monospace;"><em><strong>p<sub>i</sub></strong></em></span> é vizinho-4 de <span style="font-family: courier new, courier, monospace;"><em><strong>p<sub>i</sub></strong></em><strong><sub>+1</sub></strong></span>., sendo <span style="font-family: courier new, courier, monospace;"><strong><em>i</em>=1,2,...,<em>n</em>-1</strong></span></li>
<li>Um ponto <span style="font-family: courier new, courier, monospace;"><strong><em>p</em></strong></span> é <span style="text-decoration: underline;"><strong>conexo</strong></span> a um ponto <span style="font-family: courier new, courier, monospace;"><em><strong>q</strong></em></span> se existir um caminho de <span style="font-family: courier new, courier, monospace;"><em><strong>p</strong></em></span> a <span style="font-family: courier new, courier, monospace;"><em><strong>q</strong></em><span style="font-family: arial, helvetica, sans-serif;"> (no contexto deste trabalho, só há interesse em pontos com valor 1, ou seja, pertencentes ao espaço a ser limpo)</span><strong></strong><em><strong><br></strong></em></span></li>
<li>Um <span style="text-decoration: underline;"><strong>componente conexo</strong></span> é um conjunto maximal (não há outro maior que o contenha) <em><strong>C</strong></em> de pontos, no qual quaisquer dois pontos selecionados deste conjunto <em><strong>C</strong></em> são conexos</li>
</ul>
<p>Para a determinação da área a ser limpa, é necessário identificar quantos pontos iguais a 1 estão na região em que o robô se encontra, ou seja, é preciso determinar a área do componente conexo. Conforme apresentado em aula, segue o algoritmo de reconstrução de componente conexo usando uma fila (<strong><span style="color: #ff0000;">FIFO</span></strong>):</p>
<ul>
<li>Criar uma matriz <strong>R</strong> de <strong>0</strong> (zeros) com o mesmo tamanho da matriz de entrada <strong>E</strong> lida</li>
<li>Inserir <strong>(x,y)</strong> na fila
<ul>
<li>na coordenada <strong>(x,y)</strong> da imagem <strong>R</strong>, atribuir <strong>1</strong></li>
</ul>
</li>
<li style="text-align: left;">Enquanto a fila não estiver vazia
<ul>
<li style="text-align: left;"><strong>(x,y)</strong> ← remover da fila</li>
<li style="text-align: left;">inserir na fila as coordenadas dos quatro vizinhos que estejam dentro do domínio da matriz (não pode ter coordenada negativa ou superar o número de linhas ou de colunas), com intensidade <strong>1</strong> (em <strong>E</strong>) e ainda não tenha sido visitado (igual a <strong>0</strong> em <strong>R</strong>)
<ul>
<li style="text-align: left;">na coordenada de cada vizinho selecionado, na imagem <strong>R</strong>, atribuir <strong>1</strong></li>
</ul>
</li>
</ul>
</li>
</ul>
<p>O conteúdo final da matriz <strong>R</strong> corresponde ao resultado da reconstrução. A quantidade de <strong>1</strong> (uns) deste único componente conexo é a resposta do segundo problema.</p>
<p></p>
</ul>
</li>
</ul>
</li>
</ul>
<p></p></div>