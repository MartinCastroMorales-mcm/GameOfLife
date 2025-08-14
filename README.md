Esta es mi version del juego de la vida en raylib.


version wasm: https://martincastromorales-mcm.github.io/GameOfLife/

Reglas
Cada cuadrado es blanco si esta muerto y rojo si esta vivo.
Se consideran las diagonales.

- Un cuadrado vivo con 0 o 1 vecinos muere.
- Un cuadrado vivo con 4 o mas vecinos muere
- Un cuadrado vivo con 2 o 3 vecinos vive.
- Un cuadrado muerto con 3 vecinos vive.

Dependencias
- raylib: https://github.com/raysan5/raylib
- raygui: https://github.com/raysan5/raygui
