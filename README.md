# T1 ICG - Rasterização de Linhas

## Participantes

Diego Felipe Gonçalves do Nascimento - 20170171680

Glauber Ferreira Ângelo - 20160144357

### [Introdução](https://github.com/FelipeNasci/Line_Rasterization/blob/master/README.md#introdu%C3%A7%C3%A3o)

### [Rasterização de linhas](https://github.com/FelipeNasci/Line_Rasterization/blob/master/README.md#rasteriza%C3%A7%C3%A3o-de-linhas-1)

### [Resultados](https://github.com/FelipeNasci/Line_Rasterization/blob/master/README.md#resultados-1)

### [Problemas encontrados](https://github.com/FelipeNasci/Line_Rasterization/blob/master/README.md#problemas-encontrados-1)

### [Referências](https://github.com/FelipeNasci/Line_Rasterization/blob/master/README.md#refer%C3%AAncias-1)

# Introdução

  Este trabalho tem como objetivo apresentar alguns algoritmos para rasterização de linhas em um monitor gráfico diretamente e memória de video, como os sistemas operacionais modernos impedem acesso direto a memória de vídeo, foi utilizado um framework para realizar esta simulação.

  Mas antes, devemos conhecer alguns conceitos como: primitivas, rasterização, como rasterizar primitivas gráficas e o funcionamento em um monitor gráfico.
  
## Rasterização

  Primitivas em computação gráfica são elementos básicos, como pontos e retas. A rasterização é responsável por capturar estas primitivas e transformá-las em novas imagens, ou seja, é justamente o que acontece em monitores, displays, e até mesmo impressoras.

## Monitores

  Inicialmente devemos imaginar o display como uma matriz _(grid)_ bidimensional, composto por **_m linhas_** e **_n colunas_**, onde no centro de cada posição da matriz existe um ponto com um par de coordenadas _(x,y)_. 
  
  
![Matriz-Grid](https://github.com/FelipeNasci/Line_Rasterization/blob/master/images/grids.png?raw=true)


  Note, nas figuras acima o Ponto _(0,0)_ está situado no topo a esquerda, e o Ponto _(m-1, n-1)_ está posicionado no canto inferior direito. Assim estão dispostos os pontos em um display.
  
  Outro fato a se observar é que a figura "Grid - 2" é uma abstração de "Grid - 1", e esta servirá de modelo para os próximos exemplos.
  
## Pixel

  Um Pixel é um ponto luminoso no monitor, uma imagem é formanda a partir de um conjunto de pixels. 
  
  É composto por três canais de cores - Vermelho, Verde e Azul, e mais um canal para tratar a transparência destas cores, chamamos este canal de alpha, compondo um sistema chamado RGBA.
  
  
  ![Disposição_Pixel](https://github.com/FelipeNasci/Line_Rasterization/blob/master/images/Disposi%C3%A7%C3%A3o_Pixel.png?raw=true)
  
  Para uma melhor clareza de código, foram utilizadas 02 estruturas:

* Define a intensidade das cores, onde 0 significa ausência de cor e 255 a intensidade máxima

```C
typedef struct Color
{   //INTENSIDADE DAS CORES
    int r = 255;
    int g = 255;
    int b = 255;
    int a = 0;
} Color;
```

* Define um pixel na tela, possui coordenadas _(x,y)_ e uma _cor_

```C
typedef struct Point
{
    int x;
    int y;

    struct Color color;

} Point;
  ```
  
  Estas cores são armazenadas em uma região de memória chamada _Color_Buffer_ , que é responsável por armazenar informações da imagem que será rasterizada na tela.
  
  
  ![ColorBuffer](https://github.com/FelipeNasci/Line_Rasterization/blob/master/images/ColorBuffer.png?raw=true)
  
  
  _OBS: Caso o computador não possua uma placa de vídeo dedicada, o Color_Buffer utiliza parte da memória RAM._
  
  
  ![ColorBuffer](https://github.com/FelipeNasci/Line_Rasterization/blob/master/images/ColorBuffer2.png?raw=true)
  

  Tendo em vista que o _Color_Buffer_ é uma região de memória, e a única informação que temos são pontos de coordenadas, utilizamos uma função _offset_ para encontrar a informação para determinada coordenada do monitor.

````C
offset = 4 * (x + y * IMAGE_WIDTH);
````

_**OBS:** O _offset_ encontra a posição de memória de determinado ponto _(x,y)_ , para que seja selecionada uma cor se faz necessário acessar os canais correspondente a cor desejada e informar sua intensidade (0 até 255), como é demonstrado na função putPixel()._

````C
void putPixel(Point point)
{
    FBptr[offset(point) + RED] = point.color.r;		  	//RED   == 0
    FBptr[offset(point) + GREEN] = point.color.g;		//GREEN == 1
    FBptr[offset(point) + BLUE] = point.color.b;		//BLUE  == 2
    FBptr[offset(point) + ALPHA] = point.color.a;		//ALPHA == 3
}
````

# Rasterização de linhas

Após entender a interação entre monitores e computadores, os algoritmos para traçar retas serão entendidos sem maiores dificuldades.

Antes de iniciar, assumimos que:

* Δx ≥ Δy, ou seja, 0 <= angulo_reta <= 1
* Nosso grid tem apenas coordenadas positivas (maior ou igual a 0)
* P(x0,y0) = (0,0)
* A distância entre cada pixel é 1

Note que retas que possuem ângulos iguais a 0°, 45° e 90° são triviais de serem rasterizados.


![angulos_triviais](https://github.com/FelipeNasci/Line_Rasterization/blob/master/images/Pixel%20angulos%200%2090%2045.jpg?raw=true)


Porém, retas com angulações diferentes demandam um maior esforço para serem desenhadas. A seguir são demonstrados alguns algoritmos para realizar esta tarefa.

### Equação geral da reta

Podemos representar uma reta _r_ do plano cartesiano por meio de uma equação. Essa equação pode ser obtida a partir de um ponto A(xA, yA) e do coeficiente angular _m_ dessa reta.

Considere uma reta r não-vertical, de coeficiente angular m, que passa pelo ponto A(xA, yA). Vamos obter a equação dessa reta, tomando um ponto _P(x, y)_ tal que P ≠ A.

Este é o meio mais trivial de se obter uma reta através de dois pontos. Vajamos a seguir seu desenvolvimento.

````
y - y0 = m * (x - x0)  
y - y0 = (m * x) + (-m * x0)
     y = (m * x) + (-m * x0)  + y0
     y = (m * x) + [ (-m * x0)  + y0 ]
     y = m * x + b
````


![Eq_Geral_Reta](https://github.com/FelipeNasci/Line_Rasterization/blob/master/images/Equa%C3%A7%C3%A3o%20Geral.png?raw=true)


Através desta equação podemos encontrar qualquer reta.
OBS: _Devemos nos atentar nos casos em que:_

````
Δx = 0 (pois inviabiliza a divisão Δy/Δx).
Δx > Δx, isso nos obriga a trocar o valor dos pontos.
````

A equação geral da reta é ineficiente em meios computacionais pois, para executá-la é necessário realizar multiplicações e arredondamentos de números reais a cada ponto que percorremos e isso torna o processamento lento.

### DDA

Uma alternativa mais leve é o Digital Differential Analyzer (DDA), o mesmo deriva da Equação Geral da Reta, porém, ao contrario da _Equação Geral da Reta_ , não é necessário realizar multiplicações a cada ponto encontrado.

O algoritmo trabalha de forma incremental, adicionando a _y_ (encontrado na iteração anterior) o _Coeficiente Angular_ da reta. Vejamos seu desenvolvimento:

Seja P(xi,yi) Um ponto a ser plotado no display.

````
P(x0,y0) = y0 = m * xi + b      //Equação_Geral_Reta
````

Então...

````
yi + 1 = m * (xi + 1) + b
yi + 1 = m * xi + m + b
yi + 1 = (m * xi +  b) + m
yi + 1 = y_anterior + m
yi + 1 = y + m
````


![DDA](https://github.com/FelipeNasci/Line_Rasterization/blob/master/images/dda.png?raw=true)


Este algoritmo ainda não é o ideal pois são necessários muitos arredondamentos de números reais. A seguir será apresentado uma solução melhor aplicável.

### Algoritmo de Bresenham

Também conhecido como algoritmo do ponto médio, é utilizado para traçar retas de forma incremental, trabalhando apenas com números inteiros.

A ideia do algoritmo é bastante simples, ele utiliza a equação implícita da reta como uma função de decisão, para identificar qual o próximo pixel a ser ativado. Esta função é utilizada de forma incremental em cada pixel. Veja abaixo o desenvolvimento da **Equação Implícita da Reta**.

````
y = mx + b                            //  Partimos da Equação Reduzida da Reta
y = (dy/dx)* x + b                    //  Destrinchando 'm' obtemos '(dy/dx)'
y * dx = dy * x + b * dx              //  Multiplicando a equação por 'dx'
dy * x + (-y * dx) + b * dx = 0       //  Igualando a equação a 0
````

Realizando as modificações abaixo para melhor entendimento:

````
α = dy
ß = -dx
c = b * dx
````

Obtemos:
````
decisão = f(x,y) = αx + ßy + c = 0
````

Se aplicarmos um ponto na equação implícita e obtivemos 0 como resultado, significa que o ponto está sobre a reta.

![Efeito_Eq_Implicita](https://github.com/FelipeNasci/Line_Rasterization/blob/master/images/Efeito%20Equa%C3%A7%C3%A3o%20Impl%C3%ADcita.png?raw=true)

Seja m = (x0 + 1, y0 + 1/2) o ponto médio entre os pixels  (x0 + 1, y0 + 1) e  (x0 + 1, y0), iremos utilizar a função de decisão para avaliar qual pixel acender.


![decPontoMedio](https://github.com/FelipeNasci/Line_Rasterization/blob/master/images/PontoM%C3%A9dio.png?raw=true)


Note que a reta parte do ponto _(x0, y0)_ logo, não existe decisão tomada anteriormente, podemos identificar o nosso valor de decisão aplicando f(x0 + 1,  y0  + 1/2) - f (x0,  y0).

``
 f (m) - f (inicio) =  ax0 + by0 + c + a + b/2 - (ax0 + by0 + c )
 f (m) - f (inicio) = a + b/2
``

Logo, nosso valor de decisão inicial é:

````
d = a + b/2
````

![pontoMedio](https://github.com/FelipeNasci/Line_Rasterization/blob/master/images/Ponto_m%C3%A9dio.png?raw=true)

Após identificar qual pixel ativar através da função de decisão, é necessário verificar qual será o nosso próximo ponto médio, (x0 + 2, y0 + 1/2) ou (x0 + 2, y0 + 3/2)


![Escolha_e_ne](https://github.com/FelipeNasci/Line_Rasterization/blob/master/images/Escolha_e_ne.png?raw=true)


````C
if (decisão <= 0){
  d = m3
 	putPixel (xi + 1, yi) //Pixel E
}else{
  d = m2
	putPixel (xi + 1, yi + 1) //Pixel NE
}
````

_Importante:_ Esta versão do algoritmo de Bresenham funciona apenas para _0° <= angulo <= 1°_ porém podemos obter retas com outros coeficientes angulares por reflexão, como demonstrado na imagem abaixo:


![Bresenham_Octantes](https://github.com/FelipeNasci/Line_Rasterization/blob/master/images/Bresenham_Octantes.png?raw=true)


## Debugging - Algoritmo de Bresenham

Execução do algoritmo de Bresenham


![Bresenham](https://github.com/FelipeNasci/Line_Rasterization/blob/master/images/test%20retas.png?raw=true)


# Resultados

### Função _DrawLine_

Traça retas a partir de 02 pontos utilizando o algoritmo de Bresenham


![Retas](https://github.com/FelipeNasci/Line_Rasterization/blob/master/images/Linhas_Octantes.png?raw=true)


### Função _InterporlaçãoCor_

````
	( COR_pontoA - COR_pontoB ) / DISTANCIA ENTRE OS PONTOS
	
	Se o canal_de_cor >= 255 ou canal_de_cor <=0
		stop_interpolação();
````


![interpolaCor](https://github.com/FelipeNasci/Line_Rasterization/blob/master/images/interpola%C3%A7%C3%A3oCor.png?raw=true)


### Função _DrawTriangle_

Desenha triângulos a partir de 03 pontos


![Triangulos](https://github.com/FelipeNasci/Line_Rasterization/blob/master/images/drawTriangle.png?raw=true)


# Problemas encontrados

* Generalizar o algoritmo para traçar retas em todos os octantes


![Erro_Bresenham](https://github.com/FelipeNasci/Line_Rasterization/blob/master/images/Erro_Pseudocodigo.png?raw=true)


* Interpolação de cores 

Uma ideia para interporlar cores foi: Incrementar ou decrementar em 1 bit cada canal de cor, até que a cor do canal do ponto de partida fosse igual ao canal de cor do ponto de chegada, porém o npumero de bits necessários é maior do que o disposto para cada canal de cor (geralmente 256 bits).


![Erro_InterpolaCor](https://github.com/FelipeNasci/Line_Rasterization/blob/master/images/Erro_Interpola%C3%A7%C3%A3o.png?raw=true)


# Referências

[infoescola - Equacoes da Reta](https://www.infoescola.com/geometria-analitica/equacoes-da-reta/).

[Bresenham's line algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm).

ALGORITMO DE BRESENHAM: O USO MICROCONTROLADORES PARA TRAÇAR RETAS EM LCDs - Jefferson Zortea Moro.

Notas de aula do professor [Christian Azambuja Pagot](http://buscatextual.cnpq.br/buscatextual/visualizacv.do?metodo=apresentar&id=K4792938P3)
