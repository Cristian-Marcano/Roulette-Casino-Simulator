# Roulette Casino Simulator
Aplicación que simula una ruleta de casino, elaborado con $C++$ y $Graphics.h$.

## Estructura
* `Init.cpp` archivo principal que ejecuta las demas dependencias y incluye la logica del juego, etc.
* `Panel.h` archivo de cabecera que incluye la clase _Panel_. Su funcionalidad es crear los paneles de Roulette, Tablero y Usuario.
* `Ruleta.h` archivo de cabezera que contiene la clase _Roulette_. Su funcionalidad es elaborar la ruleta, realizar las rotaciones de esta y la bola, desaceleracion de la ruleta y la bola, calcular en que casilla cayo la pelota.
* `Tablero.h` archivo de cabezera que tiene añadido la clase de _Board_. Su funcionalidad es integrar un area rectangular que contenga las casillas numericas de la ruleta.
* `Casilla_Tablero.h` archivo de cabezera que contiene la clase _Board_Box_. Su funcionalidad es inicializar e incluir cada una de las casillas de la ruleta al area interna del tablero y que almacene los creditos.
* `Boton.h` archivo de cabezera que incluye la clase _Button_. Su funcionalidad es elaborar un boton que puede ser usado para accionar la ruleta o limpiar las fichas del tablero.

### Imagenes

