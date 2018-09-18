# T2 ICG - Rasterização de Linhas

## Participantes

Diego Felipe Gonçalves do Nascimento - 20170171680

Glauber Ferreira Ângelo - 20160144357

### [Introdução](https://github.com/FelipeNasci/Line_Rasterization/blob/master/README.md#introdu%C3%A7%C3%A3o)

### [Rasterização de linhas](https://github.com/FelipeNasci/Line_Rasterization/blob/master/README.md#rasteriza%C3%A7%C3%A3o-de-linhas-1)

### [Resultados](https://github.com/FelipeNasci/Line_Rasterization/blob/master/README.md#resultados-1)

### [Problemas encontrados](https://github.com/FelipeNasci/Line_Rasterization/blob/master/README.md#problemas-encontrados-1)

### [Referências](https://github.com/FelipeNasci/Line_Rasterization/blob/master/README.md#refer%C3%AAncias-1)

# Introdução
  
  Este é o segundo trabalho de computação gráfica e tem como objetivo apresentar todo o processo de renderização de um objeto desde a sua criação até a apresentação na tela.
  Ao final serão utilizados algoritmos para rasterização das primitivas que geram o objeto.
  
## Considerações iniciais

  Para um melhor entendimento deste texto é necessário o conhecimento sobre coordenadas homogêneas e multiplicações operacões entre matrizes e vetores.
  
  Os vetores apresentados no texto serão do tipo coluna;
  
  Os vetores contidos nas matrizes serão do tipo linha;
  
  Todas as matrizes e vetores utilizadas no texto estão em 4 dimensões, onde os objetos são 3D e a 4ª coordenada é homogênea.
  
## Pipeline Gráfico

  Em computação, o pipeline gráfico é um modelo conceitual que descreve todos os passos necessários para transformar uma cena 3D em 2D recebendo as coordenadas de tela. Denominamos cada etapa por “Espaço”, onde para da renderizar uma cena passamos por 6 espaços e cada um desempenha uma função específica.
  
## Transformações Geométricas

  Ao longo do pipeline gráfico são executadas uma série de transformações que na realidade são apenas operações entre matrizes e vetores, a seguir veremos as transformações mais comuns utilizadas neste processo.
  
### Escala

  Esta matriz de transformação aumenta ou diminui o tamanho do objeto.
  
  //Inserir imagem das casinhas mostradas no slide
  
 ```C
  escala = {   sX, 0.0f, 0.0f, 0,
	     0.0f,   sY, 0.0f, 0,
	     0.0f, 0.0f,   sZ, 0,
	     0.0f, 0.0f, 0.0f, 1.0f };
```

  A escala em um objeto possui 02 tipos:

  Isotrópica: Quando todos os eixos recebem o mesmo valor de escala

```
sX = sY;
```

  Anisotrópica: Quando os eixos recebem valores de escala diferentes
  
```
sX ≠ sY;
```

//EXIBIR IMAGENS DE ESCALA ISOTRÓPICA E ANISOTRÓPICA CONTIDAS NO SLIDE

  Escala de objetos fora da origem recebem uma translação implícita. Uma forma de contornar este problema é translada-lo para a origem, escalar e por fim translada-lo para o ponto incial.
  
//EXIBIR IMAGENS DE ESCALA DE OBJETOS FORA DA ORIGEM CONTIDAS NO SLIDE

### Espelhamento

  O espelhamento é realizado por uma matriz de escala com valor = -1 no eixo em que se deseja espelhar (x,y,z). Nos casos em que se deseja espelhar e modificar o tamanho do objeto basta multiplicá-lo pelo valor de escala negativo.

//Exibir imagem de de objetos espelhados

### Rotação

  É o movimento giratório em torno dos eixos fixados. no openGL a rotação por padrão é no sentido anti-horário, porém para rotacionar no sentido inverso basta aplicar uma angulação oposta ao ângulo desejado.
  
  Rotação em torno do eixo X
   
```C
rotateX   (1,  0,          0,          0,
	   0,  cos(rX),    -sin(rX),   0,
	   0,  sin(rX),    cos(rX),    0,
           0,  0,          0,          1 );
```

Rotação em torno do eixo Y

```C
rotateY   (cos(rY),    0,  sin(rY),    0,
           0,          1,  0,          0,
           -sin(rY),   0,  cos(rY),    0,
           0,          0,  0,          1 );
```

Rotação em torno do eixo Z

```C
rotateZ   (cos(rZ),    -sin(rZ),   0,  0,
	   sin(rZ),    cos(rZ),    0,  0,
	   0,          0,          1,  0,
	   0,          0,          0,  1 );
```
  
  Rotações fora da origem geram uma translação implícita
  
### Shear

  Esta transformação fixa um conjunto de vértices em um ponto e translada o restante.

//Imagem Shear
  
  Toda matriz com diagonal principal igual a “1”  e o restante diferente de 1’s é uma matriz de shear. As API’s gráficas não implementam o shear, o mesmo é obtido através de transformações de rotação e escala.

### Translação
  
  A translação é o movimento que um objeto faz de um ponto a outro. Basicamente somamos o valor de translação a coordenada correspondente do objeto a ser transladado.
  Não é possível obter uma matriz de translação sem a utilização de coordenadas homogênias.
  
```C
translacao = {1.0f, 0.0f, 0.0f, tX,
	      0.0f, 1.0f, 0.0f, tY,
	      0.0f, 0.0f, 1.0f, tZ,
	      0.0f, 0.0f, 0.0f, 1.0f };
```

### Composição de matrizes

  Podemos utilizar todas as transformações desejadas em uma única matriz correspondente, esta prática reduz drasticamente o número de operações, pois não é preciso multiplicar a cada frame várias matrizes para obter uma transformação, este processo é executado apenas uma vez.
  Ex: Seja: 
  T uma matriz de translação; S uma matriz de escala;  R uma matriz de rotação no eixo “x”;  M será uma matriz de composta por estas transformações respectivamente
  
```
  T =				S =				R =

	1   0   0   5			2   0   0   0			1	0   	  0   	    0
	0   1   0   3			0   3   0   0			0   	Cos(45)  -Sin(45)   0
	0   0   1   2 			0   0   1   0			0   	Sin(45)   Cos(45)   0
	0   0   0   1			0   0   0   1			0   	0   	  0   	    1
```

```
  M = R * S * T
  
M =

    2.00000    0.00000    0.00000   10.00000
    0.00000    1.57597   -0.85090    3.02609
    0.00000    2.55271    0.52532    8.70878
    0.00000    0.00000    0.00000    1.00000

```

  Caso a ordem com que as matrizes sejam multiplicadas mude, o resultado será diferente
  
```
  M = T * S * R

M =

   2.00000   0.00000   0.00000   5.00000
   0.00000   1.57597  -2.55271   3.00000
   0.00000   0.85090   0.52532   2.00000
   0.00000   0.00000   0.00000   1.00000

```



a matriz M é composta por 03 transformações na seguinte ordem:
1 translação em x = 5, y = 3, z = 2
2 Escala em x = 2, y = 3 e z = 1
3 Rotação de 45 em torno do eixo X


M = R * E *  T

M =

    2.00000    0.00000    0.00000   10.00000
    0.00000    1.57597   -0.85090    3.02609
    0.00000    2.55271    0.52532    8.70878
    0.00000    0.00000    0.00000    1.00000

Perceba que a ordem se invertermos a ordem Inserindo primeiro a transformação de Rotação, em seguida a de escala e por último aplicar uma translação a matriz de resultante será modificada.

M = T * E * R

M =

   2.00000   0.00000   0.00000   5.00000
   0.00000   1.57597  -2.55271   3.00000
   0.00000   0.85090   0.52532   2.00000
   0.00000   0.00000   0.00000   1.00000



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
