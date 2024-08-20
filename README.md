# Roulette Casino Simulator
Aplicación que simula una ruleta de casino, elaborado con $C++$ y $Graphics.h$.

## Estructura
* `Init.cpp` archivo principal que ejecuta las demas dependencias y incluye la logica del juego, etc.
* `Panel.h` archivo de cabecera que incluye la clase <strong>_Panel_</strong>. Su funcionalidad es crear los paneles de Roulette, Tablero y Usuario.
* `Ruleta.h` archivo de cabecera que contiene la clase <strong>_Roulette_</strong>. Su funcionalidad es elaborar la ruleta, realizar las rotaciones de esta y la bola, desaceleracion de la ruleta y la bola, calcular en que casilla cayo la pelota.
* `Tablero.h` archivo de cabecera que tiene añadido la clase de <strong>_Board_</strong>. Su funcionalidad es integrar un area rectangular que contenga las casillas numericas de la ruleta.
* `Casilla_Tablero.h` archivo de cabecera que contiene la clase <strong>_Board_Box_</strong>. Su funcionalidad es inicializar e incluir cada una de las casillas de la ruleta al area interna del tablero y que almacene los creditos.
* `Boton.h` archivo de cabecera que incluye la clase <strong>_Button_</strong>. Su funcionalidad es elaborar un boton que puede ser usado para accionar la ruleta o limpiar las fichas del tablero.

## Herramientas
- **Graphics.h**
- **Embarcadero Dev-C++**
- **TDM-GCC 9.2.0 32-bit**

### Imagenes

![Ruleta](https://github.com/Cristian-Marcano/Roulette-Casino-Simulator/assets/136503211/d5d8a864-73d7-4cf9-a4bb-d685185b835d)
