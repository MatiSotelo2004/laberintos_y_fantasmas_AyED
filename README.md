Bienvenido a Laberintos y Fantasmas!

Comentarios para los jugadores que quieran participar:

INTRODUCCIÓN:

El Jugador (J) deberá atravesar el laberinto desde la Entrada (E) hasta la Salida (S), evitando ser capturado
por alguno de los Fantasmas (F).
A lo largo del laberinto se encuentran distribuidos un conjunto de Premios (P), que otorgan puntos; Vidas extra (V),
que permiten incrementar el número de vidas disponibles para jugar; y dos Portales (O), que le permiten al jugador
teletransportarse hacia el otro portal.

Si el jugador es capturado por un fantasma, perderá una vida y regresará a la entrada. El fantasma será eliminado
del laberinto y, en caso de haber otros fantasmas, estos se reposicionarán.
Cuando el jugador capture un premio, se incrementará el Contador de Premios. Si el jugador hubiera capturado un premio
y luego es capturado por un fantasma, al continuar el juego se mantendrá el estado actual de los premios.
Cuando el jugador capture una vida, se incrementará el Número de Vidas y tendrá mayores posibilidades de finalizar
la travesía de manera exitosa.

CONFIGURACIÓN:

El juego se encuentra previamente configurado mediante un archivo con el nombre "config.txt". En este se pueden
modificar el número de elementos que contendrá nuestro laberinto: límites del laberinto, cantidad de fantasmas, cantidad
de vidas extra, cantidad de premios y con cuántas vidas comenzará el jugador.

CONTROLES:

Las teclas para poder jugar y desplazarse por el laberinto son 'a-w-s-d'.

- Arriba: 'w'

- Abajo: 's'

- Izquierda: 'a'

- Derecha: 'd'

FIN DEL JUEGO:

Cuando el jugador llegue a la salida o se quede sin vidas, el juego finalizará con un mensaje correspondiente.
También podrá consultar el registro de movimientos realizados por el jugador durante el juego.

Siempre, al finalizar, se generará un archivo con el nombre "laberinto.txt", donde podrá ver el laberinto inicial junto al
registro de movimientos realizados por el jugador.

Avisos parroquiales:

Para poder compilar y ejecutar el proyecto deben abrir los proyectos tableroLaberintosFantasmas.cbp y servidor.cbp.
Con ambos proyectos abiertos, podrán jugar y vivir la experiencia del laberinto, junto con las consultas al servidor para ver el historial de puntajes de los jugadores.
