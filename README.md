# T2 ICG - Etapas do Pipeline Gráfico

## Participantes

Diego Felipe Gonçalves do Nascimento - 20170171680

Danillo Medeiros Moraes Batista - 20160164313

### [Introdução](https://github.com/FelipeNasci/Line_Rasterization/blob/master/README.md#introdu%C3%A7%C3%A3o)

### [Transformações Geométricas](https://github.com/FelipeNasci/Line_Rasterization/blob/master/README.md#rasteriza%C3%A7%C3%A3o-de-linhas-1)

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
  
  Para elaboração deste trabalho foi utilizada a biblioteca GLM para tratar as operações com matrizes
  
## Pipeline Gráfico

  Em computação, o pipeline gráfico é um modelo conceitual que descreve todos os passos necessários para transformar uma cena 3D em 2D recebendo as coordenadas de tela. Denominamos cada etapa por “Espaço”, onde para da renderizar uma cena passamos por 6 espaços e cada um desempenha uma função específica.
  
  ![pipeline](https://github.com/FelipeNasci/Pipeline_Grafico/blob/Texto_T2-ICG/images/Pipeline/pipelne.PNG?raw=true)
  
## Transformações Geométricas

  Ao longo do pipeline gráfico são executadas uma série de transformações que na realidade são apenas operações entre matrizes e vetores, a seguir veremos as transformações mais comuns utilizadas neste processo.
  
### Escala

  Esta matriz de transformação aumenta ou diminui o tamanho do objeto.
  
  ![Escala](https://github.com/FelipeNasci/Pipeline_Grafico/blob/Texto_T2-ICG/images/Transforma%C3%A7%C3%B5es/escala.PNG?raw=true)
  
 ```C
escala	( sX, 0.0f, 0.0f, 0.0f,
	0.0f,   sY, 0.0f, 0.0f,
	0.0f, 0.0f,   sZ, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f );
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

![iso_ani](https://github.com/FelipeNasci/Pipeline_Grafico/blob/Texto_T2-ICG/images/Transforma%C3%A7%C3%B5es/Escala_Iso_Ani.jpg?raw=true)

  Escala de objetos fora da origem recebem uma translação implícita. Uma forma de contornar este problema é translada-lo para a origem, escalar e por fim translada-lo para o ponto incial.
  
  ![Escala-Fora-Origem](https://github.com/FelipeNasci/Pipeline_Grafico/blob/Texto_T2-ICG/images/Transforma%C3%A7%C3%B5es/escala_fora_do_x.gif?raw=true)

### Espelhamento

  O espelhamento é realizado por uma matriz de escala com valor = -1 no eixo em que se deseja espelhar (x,y,z). Nos casos em que se deseja espelhar e modificar o tamanho do objeto basta multiplicá-lo pelo valor de escala negativo.

![Mirror](https://github.com/FelipeNasci/Pipeline_Grafico/blob/Texto_T2-ICG/images/Transforma%C3%A7%C3%B5es/Espelhamento.PNG?raw=true)

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

````C
rotateZ   (cos(rZ),   -sin(rZ),    0,  0,
	   sin(rZ),    cos(rZ),    0,  0,
	   0,          0,          1,  0,
	   0,          0,          0,  1 );
````
  
  Rotações fora da origem geram uma translação implícita
  
### Shear

  Esta transformação fixa um conjunto de vértices em um ponto e translada o restante.

![shear](https://github.com/FelipeNasci/Pipeline_Grafico/blob/Texto_T2-ICG/images/Transforma%C3%A7%C3%B5es/shear.PNG?raw=true)
  
  Toda matriz com diagonal principal igual a “1”  e o restante diferente de 1’s é uma matriz de shear. As API’s gráficas não implementam o shear, o mesmo é obtido através de transformações de rotação e escala.
  
  ![shear2](https://github.com/FelipeNasci/Pipeline_Grafico/blob/Texto_T2-ICG/images/Transforma%C3%A7%C3%B5es/shear2.PNG?raw=true)

### Translação
  
  A translação é o movimento que um objeto faz de um ponto a outro. Basicamente somamos o valor de translação a coordenada correspondente do objeto a ser transladado.
  
  ![translacao](https://github.com/FelipeNasci/Pipeline_Grafico/blob/Texto_T2-ICG/images/Transforma%C3%A7%C3%B5es/Transla%C3%A7%C3%A3o.gif?raw=true)
  
  Não é possível obter uma matriz de translação sem a utilização de coordenadas homogênias.
  
```C
translacao (1.0f, 0.0f, 0.0f, tX,
	    0.0f, 1.0f, 0.0f, tY,
	    0.0f, 0.0f, 1.0f, tZ,
	    0.0f, 0.0f, 0.0f, 1.0f );
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

### Transformações inversas

  Podem ocorrer situações em que ao aplicarmos uma transformação em um objeto tenhamos a necessidade de voltar para o estado anterior.
  Suponha que após aplicamos as transformações de Rotação, Escala e Translação (nesta ordem) em M e necessitamos retornar para o ponto de origem. Isso pode ser resolvido com as transformações (matrizes) inversas, aplicadas na ordem oposta a aplicada na matriz original. Podemos fazer uma analogia com uma pilha
  
```
Seja M = T * E * R;

M =

   2.00000   0.00000   0.00000   5.00000
   0.00000   1.57597  -2.55271   3.00000
   0.00000   0.85090   0.52532   2.00000
   0.00000   0.00000   0.00000   1.00000
```

```
M’ = R^-1 * S^-1 * T^-1;

M’ =

   0.50000   0.00000   0.00000  -2.50000
   0.00000   0.17511   0.85090  -2.22713
   0.00000  -0.28363   0.52532  -0.19974
   0.00000   0.00000   0.00000   1.00000
```

```
M’ * M = Matriz_Identidade

   1.00000   0.00000   0.00000   0.00000
   0.00000   1.00000   0.00000   0.00000
   0.00000   0.00000   1.00000   0.00000
   0.00000   0.00000   0.00000   1.00000
```

Perceba que as transformações inversas são a ordem contrária das transformações originais:

```
T^-1 =			S^-1 =				R^-1 =

   1   0   0  -X		1/X   0    0   0		1	  0   	  0   	   0
   0   1   0  -Y		0    1/Y   0   0		0   	Cos(θ)   Sin(θ)    0
   0   0   1  -Z		0     0   1/Z  0		0	-Sin(θ)  Cos(θ)    0
   0   0   0   1		0     0    0   1		0	  0   	  0   	   1
```

A Rotação possui um caso especial, onde que para obter sua inversa basta calcular sua transposta. O processo para se obter a rotação inversa nos eixos Y e Z são análogos.


## Espaço do Objeto

  É o processo de importação do objeto que se deseja renderizar, este objeto pode ser projetado por softwares especializados como Blender e Maya. Cada objeto é composto por uma lista de vértices, lista de arestas e conjunto de matrizes de transformação.
  A matriz deste espaço é chamada de MODEL.
  
  ![Obj1](https://github.com/FelipeNasci/Pipeline_Grafico/blob/Texto_T2-ICG/images/Espa%C3%A7o%20do%20Objeto/Objeto1.gif?raw=true)
  
  No código fonte, localizado na classe Obj.cpp é possível localizar os vértices para um cubo, eles sofrerão as transformações ao longo do pipeline e serão interligados por uma lista de arestas.

## Espaço do Universo

  É o espaço em que a cena será criada, ele aloca cada objeto em sua devida posição através de transformações de rotação, escala e translação.
  A matriz deste espaço é chamada de VIEW. As transformações e vértices do objeto são aplicadas nesta matriz.
  
  ![Universe](https://github.com/FelipeNasci/Pipeline_Grafico/blob/Texto_T2-ICG/images/Universo/space_uni.PNG?raw=true)
  
## Espaço da Câmera

  É o responsável por definir como a cena será visualizada, isto é possível porque os objetos são levados para o sistema de coordenadas da própria câmera.
  
  ```
  Câmera atrás do objeto
  ```
  
  ![GTA1](https://github.com/FelipeNasci/Pipeline_Grafico/blob/Texto_T2-ICG/images/Espa%C3%A7o%20da%20Camera/Camera1.gif?raw=true)
  
  ```
  Câmera em 1ª pessoa
  ```
  
  ![GTA2](https://github.com/FelipeNasci/Pipeline_Grafico/blob/Texto_T2-ICG/images/Espa%C3%A7o%20da%20Camera/Camera2.gif?raw=true)
  
  ```
  Câmera com visualização frontal do personagem
  ```
  
  ![GTA3](https://github.com/FelipeNasci/Pipeline_Grafico/blob/Texto_T2-ICG/images/Espa%C3%A7o%20da%20Camera/Camera3.gif?raw=true)
  
  O objetivo de definir um sistema de coordenadas para a camera é especificar a posição e direção da cena que será renderizada.
  
  ![space-Cam](https://github.com/FelipeNasci/Pipeline_Grafico/blob/Texto_T2-ICG/images/Espa%C3%A7o%20da%20Camera/Camera4.gif?raw=true)
  
### Definindo a câmera

  A camera possui básicamente 03 vetores como parâmeros:

```C++
    vec3 position (pX, pY, pZ);             //  Posicao da camera no universo.
    vec3 lookAt (lX,lY,lZ);                 //  Ponto para onde a camera esta olhando no universo.
    vec3 up (uX,uY,uZ);                     //  Indica qual a parte de cima da camera (geralmente eixo Y -> (0,1,0) ).
```

  Com estes parâmetros é possível identificar a direção da câmera, que é o ponto para onde ela está olhando em seu sistema de coordenadas.

```C++
    vec3 direction ( lookAt - position );   //  Para onde a camera esta olhando no espaço da câmera
```

```C++
    //auxilia no calculo da base
    vec3 zAux ( -(direction) / length(direction) );                 	// Normalizando vetor de direcao
    vec3 xAux ( cross(   up, zAux ) / length( cross( up,zAux ) ) );	// Produto vetorial / norma de produto vetorial
    vec3 yAux ( cross( zAux, xAux ) );					// Produto vetorial
```

  Estes parâmetros definem o sistema de coordenadas da câmera, que é composta pela multiplicação entre uma matriz de rotação e uma translação.
  
```C++
    ///Base da Camera
    vec4 Xc ( xAux , 0 );
    vec4 Yc ( yAux , 0 );
    vec4 Zc ( zAux , 0 );

    mat4 Bt (Xc,
             Yc,
             Zc,
             homogenious);

    mat4 T( 1, 0, 0, -position[0],
            0, 1, 0, -position[1],
            0, 0, 1, -position[2],
            0, 0, 0, 1);

    mat4 M_view ( T * Bt );		// Sistema de coordenadas da Câmera
```  

## Espaço de Recorte

  Define a área que estará visível na tela através de um cubo definido de (-1,-1,-1) a (1,1,1), onde os objetos que estiverem dentro dele serão renderizados na tela.
  Este cubo também define a projeção dando a sensação de 3D deixando os objetos mais próximos da câmera maiores e os mais distantes menores.
  
 ![viewPlane](https://github.com/FelipeNasci/Pipeline_Grafico/blob/Texto_T2-ICG/images/Clipping/clip1.png?raw=true)
  
## Espaço de Canônico

  Esta é a etapa de desomogeneização, é o único processo do pipeline que não pode ser realizado por multiplicação de matrizes.
  
  Após os vértices do objeto sofrerem todas as modificações dos espaços anteriores, a coordenada homogênia é modificada, neste espaço dividimos todos os vértices por esta coordenada.
  
  Esta etapa do pipeline pode ser pulada e realizada no fim de todas as outras transformações.

## Espaço de Tela
  
  A função deste espaço é obter os vértices do objetos em coordenadas de tela. A matriz deste espaço é uma composição de 03 transformações: Escala, Translação e Escala
  
  ```C
    GLfloat w = (IMAGE_WIDTH - 1)/2 ;
    GLfloat h = (IMAGE_HEIGHT - 1)/2 ;

    mat4 S1 (1, 0,  0, 0,	mat4 T2 (1, 0, 0, 1,		mat4 S2 (w, 0, 0, 0,
             0, -1, 0, 0,		 0, 1, 0, 1,			 0, h, 0, 0,
             0, 0,  1, 0,		 0, 0, 1, 0,			 0, 0, 1, 0,
             0, 0,  0, 1 );		 0, 0, 0, 1 );			 0, 0, 0, 1 );

    mat4 M_viewPort( S1 * T2 * S2 );
  ```
  
  neste espaço também é empregado a rasterização das primitivas.
  
  
## Pipeline
  
  ```C
      space_Obj(objeto);

    mat4 viewPort = ( space_World( obj.t.getAllTransformations() ) *
                     space_Camera() * space_Clipping() * space_Screen() );

    space_Canonical(viewPort);
    screen();
```

# Resultados

# Problemas encontrados

# Referências
