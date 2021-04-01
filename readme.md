![PROYECTOS 2 GAME HEADER](./docs/headers/h_title.png)
 Juego de Proyectos II hecho en c++ con SDL.

## ENLACES
[PÁGINA WEB](https://www.pivotaltracker.com/n/projects/2489079)\
[PIVOTAL (editable)](https://www.pivotaltracker.com/n/projects/2489079)\
[DIAGRAMA UML - MENUS, ESCENA Y REFUGIO](https://lucid.app/lucidchart/invitations/accept/aae27cba-d4f9-486b-8103-88b7f02d1c62)\
[DIAGRAMA UML - MECÁNICAS DE SAQUEO](https://lucid.app/lucidchart/invitations/accept/355e2dc6-1896-49d8-9c1d-601517544eb8)\
[DIAGRAMA UML - COMPONENTES](https://lucid.app/lucidchart/invitations/accept/4e6c891a-a004-42ba-a569-ac58c1c28972)\

## INDICE

- [Descripción](#desc)
- [Mecánicas](#mec)
    - [Ciclo diario](#day)
    - [Raid](#rai)
    - [Refugio](#refu)
    - [Inventario](#inv)
    - [Combate](#comb)
    - [Supervivencia](#supe)
    - [Enemigos](#enem)
    - [Medicina](#medi)
- [Dinámicas](#dina)
- [Contenido](#cont)
- [Estética](#este)
- [Controles](#keys)
- [Interfaz y menús](#hud)
- [Referencias](#refe)

![Descripción](./docs/headers/h_descripcion.png) <a name="desc"></a>

DOME es un survival shooter scroller 2D donde el jugador controlará a uno de los últimos supervivientes de una colonia establecida en el planeta helado Aurora. Cada día, deberá aprovechar las horas de luz para buscar los objetos que necesita para sobrevivir en este hostil y frío lugar. Además, durante las horas de noche el frío es mortal por lo que deberá volver al refugio a descansar y gestionar sus recursos. ¿Serás capaz de escapar?.

![Mecánicas](./docs/headers/h_mecanicas.png) <a name="mec"></a>

# Ciclo diario <a name="day"></a>

El jugador tendrá que escapar del planeta antes de que pasen unos dias determinados (31 dias, que podrán disminuir con respecto a la dificultad) antes de que el refugio se congele y el jugador quede encerrado en Aurora.

Así, cada día de juego el jugador dispondrá de 12 horas (que se jugarán como 12 minutos cronometrados) para saquear puntos de interés, seguidas por otras 12 (que se gestionan como recurso de forma discreta) para descansar y gestionar sus recursos en el refugio, ya que será de noche y el frío le impedirá salir.

![alt text](./docs/images/infogfx_daycycle.png)

# Raid <a name="rai"></a>

Los lugares de saqueo serán pequeños, rápidos de recorrer y contendrán botín escaso dependiendo del lugar (farmacia--> medicinas , supermercado--> comida, etc) en los que el jugador gastará tiempo del día. Solo podrá saquear lo que su equipamiento y su estado (herido, hambriento, cansado) le permita llevar de vuelta al refugio.

La dificultad de cada lugar de saqueo será definido por el peligro que presentan los enemigos (apartado "Combate") que haya. Además, la distancia sobre el mapa entre el lugar de saqueo y el refugio reducirá el tiempo del cual dispone el jugador para saquear.

Estos lugares pueden presentar obstáculos como puertas bloqueadas, necesidad de contraseñas o herramientas para saquearlo completamente.

Existe la posibilidad de volver a la misma localización por si en el anterior ciclo no terminaste de saquearlo por completo.

Los lugares de saqueo tendrán descripciones que ayuden al jugador a saber que esperar. Por ejemplo en una casa abandonada la descripción  podría indicar peligro de esta forma: gran número hostiles en la zona, posiblemente haya medicinas. No obstante, al principio del juego solo estarán descritas un poequeño número de zonas. Una zona no descrita aún se puede saquear, pero el jugador no sabrá a qué se enfrenta ni qué recompensas esperar. Cuando se complete un saqueo, independientemente del resultado, se desbloquearán la descripciones de las dos zonas más cercanas sobre el mapa a la zona saqueada.

Para poder volver al refugio, el jugador tendrá que salir por la zona por la que entró. En caso de que tarde más del tiempo del dia, empezará a implantarse en él un estado de hipotermia o congelacion, que dependiendo de la tardanza puede conllevar desde un pequeño debufo hasta la muerte del jugador.

# Refugio <a name="refu"></a>

El refugio es una zona pequeña donde el jugador podrá construir y mejorar diferentes estaciones de crafteo, crear objetos o descansar. En él, el jugador podrá interactuar con distintas estructuras del refugio para realizar acciones que gastarán parte del tiempo (discreto) disponible. Cuando gaste todo el tiempo, o bien cuando se vea sin acciones, podrá dormir y avanzar al siguiente día.

Las estructuras estarán ya situadas en distintas zonas del refugio (cohete, base de datos, terminal, mesa de crafteo??), pudiendo el jugador interactuar con ellas para mejorarlas, repararlas, o realizar acciones. Además, habrá alguna forma de almacenamiento del loot obtenido en la raid (nevera, armario, despensa {podrá ser limitado o no dependiendo de feeling del gameplay}).

En un principio, el jugador podrá seleccionar las distintas localizaciones para poder acceder a las acciones disponibles.
*MEDIA PRIORIDAD: El jugador se moverá en el propio refugio.*

![alt text](./docs/images/hideout_concept.png)

# Inventario <a name="inv"></a>

El jugador dispondrá de un inventario por bloques, como en los comienzos de la saga Resident Evil, donde almacenar los objetos que quiera llevarse a la hora de saquear. Cada objeto ocupará un espacio diferente (pero siempre cuadrilatero) en el inventario, y la distribución eficiente del espacio físico permitirá al jugador cargar con más objetos.

Además, habrá una seccion en la que el jugador pueda establecer su equipamiento (armas, armaduras).

## Armas

Existen tres categorías de armas que facilitan el combate contra ciertos enemigos, (ciertos enemigos son resistentes, con algunas armas será más facil dar al enemigo, etc.) que además podrán ser mejoradas en el refugio para obtener distintos efectos/estadísticas.

- **Armas de pólvora:** trazan una línea recta que colisiona con el primer objeto o enemigo que encuentre. Pistola --> subfusil --> fusil de asalto. Requieren balas como munición.

- **Armas de energía:** el jugador debe mantener pulsada la tecla de disparo por un momento para cargar el arma antes de disparar. Los proyectiles atraviesan enemigos. Requieres de baterías como munición.

- **Armas poliméricas:** disparan un proyectil de alta velocidad que rebota sobre superficies hasta colisionar con un enemigo. La primera fase solo rebota una vez, la segunda puede rebotar dos veces y la última puede rebotar cuatro veces. Requieren filamento poliatílico como munición.

*BAJA PRIORIDAD: Alguna de las armas de arriba implementa algun tipo de daño AOE.*

Además, durante la raid, podremos cambiar entre arma principal y la que haya en el inventario durante la raid.

## Armaduras

Afecta la resistencia del jugador, ciertas mejoras o armaduras darán resistencia a efectos para por ejemplo poder saquear una zona contaminada o con radiación. El

## Mochilas

Aumenta la capacidad del inventario del jugador.

# Combate <a name="comb"></a>

- Combate de point and click con posibilidad de agacharte detrás de objetos y levantarte para disparar.
- Los mapas tendrán verticalidad con plataformas, pero el jugador no podrá navegar el mapa con solo su salto; necesitará usar las escaleras del mapa.
- Hay daño de caída (una caída notable tiene una posibilidad de causar una concusión o una lesión, con mayor probabilidad mientras más grande la caída).
- El daño no se refleja en puntos de golpe, sino en efectos de estado o heridas. Cada ataque de cada enemigo puede inflingir ciertos tipos de herida. Si en algún momento el jugador sufre de 5 heridas diferentes, muere. Cada herida (ejs.: quemadura, músculo desgarrado, concusión, hemorragia) aportará una debilidad al jugador, parecidos a los efectos negativos del frío, el hambre, la sed y el cansancio.
- Las armas no son perfectamente certeras. Siempre que el jugador apunte, habrá una desviación oscilante en la trayectoria de su puntería.

*BAJA PRIORIDAD: El jugador se puede agachar, reduciendo su tamaño y velocidad de movimiento, pero reduciendo la desviación de sus disparos.*
*BAJA PRIORIDAD: Las balas atraviesan las plataformas, de tal forma que si una criatura está directamente sobre otra, puedan dispararse.*

# Supervivencia <a name="supe"></a>

- **Cansancio:** El cansancio es un debufo stackeable que reduce la velocidad de movimiento en la raid y el tiempo de viaje hacia las localizaciones.
Para reestablecer niveles de cansancio se podrá descansar en el refugio y cuanto más tiempo se dedique a dormir, mas descansado estará el jugador y por lo tanto
su velocidad de movimiento mejorará.

- **Hambre:** El hambre es un debufo stackeable que reduce el espacio de carga. Cada nivel de hambre adquirido incrementa la velocidad a la que la condición de desangrado se propaga. Comer una ración de comida restará dos niveles de hambre; comer una comida completa restará todos los niveles de hambre.

# Enemigos <a name="enem"></a>

Pepega a melee: comportamiento más agresivo, rushea al jugador cuando se da cuenta de su presencia y ataca en "horda", el jugador deberá ser rápido eliminando a estos enemigos ya que el combate a melee es peligroso.

Pepega a rango: comportamiento más cauteloso, se comportan como guardias usando coberturas para frenar el avance del jugador siguen patrones de disparo que el jugador deberá usar para eliminarlos.

# Salud <a name="medi"></a>

El sistema de salud en raid se basa en un modelo de carretes. No hay barra de salud como tal.
Cada estado que recibes se añade a una pila de tal forma que se van acumulando y cada uno de aplica un debufo concreto.
La mayoría de estados simplemente se quedarán ahí hasta que le apliques la medicina correcta y algunos de estos se acumularán y podrán generar más estados, como por ejemplo
el desangrado. Otros daños como una contusión, aplica un debufo por un tiempo y luego desaparece solo.
Si en algún momento tienes X debufos activos a la vez, la pantalla se vuelve muy roja por 5 segundos, si en este tiempo no te curas alguno, mueres.
Cuando vuelves al refugio, se te curan todas las heridas.

Algún ejemplo de daño en raid:

Daño por bala o proyectil enemigo (Lo que causaría desangrado). Este daño, si no se cura, hace que cada cierto tiempo se añada un nuevo estado de desangrado al sistema. (Permanente hasta ser curado)

Daño por cortes o mordeduras de enemigos. Este daño aumenta el tiempo que tardan en desaparecer los daños temporales. (Permanente hasta ser curado)

Daño por caer desde gran altura. (Rotura de huesos). Este daño hace que el jugador no pueda saltar. (Temporal)

Daño por intoxicación (Radiación o gases dañinos). Este daño hace que la distancia para ser detectado por los enemigos se reduzca. (Temporal)

Daño por hipotermia. Este daño aplica un debufo en el disparo, aumentando la dispersión de las balas. (Permanente e incurable, es decir, marca el límite de tiempo que el jugador puede esta en raid)

![Dinámicas](./docs/headers/h_dinamicas.png) <a name="dina"></a>

# Objetivos y conflictos

El jugador deberá aguantar lo suficiente para lograr saquear las piezas que permiten reparar su nave y así escapar del planeta.

# Comportamiento esperado

El jugador estará en este gameplay loop de crafteo->raid->loot->rest cada día progresando, mejorando su refugio y equipamiento, así como haciendo progreso en el objetivo final. Se espera que elija la localización más adecuada a sus necesidades y de una dificultad asequible para él, ya que de lo contrarió morirá. En caso de que muera lo esperable es que entienda a la perfección cual ha sido su fallo para mejorar la siguiente partida.

Es un reto de supervivencia donde el jugador tendrá que gestionar las necesidades de su avatar para completarlo sin morir y en el menor tiempo posible.

![Contenido](./docs/headers/h_contenido.png) <a name="cont"></a>

# Localizaciones

| Nombre | Sprite | Desc | Dificultad/Enemigos |
|--------|--------|-------|-------|
| Puesto de seguridad | N/A | bla bla bla bla bla | 3 pepegas |
| N/A | N/A | N/A | N/A |

# Contenedores

| Nombre | Sprite | Loot table |
|--------|--------|-------|
| Estantería | N/A | Componentes electrónicos (5-10) / Materiales (10-20) |
| N/A | N/A | N/A |

# Equipamiento

## Armas
| Tier 1 | Tier 1 Sprite | Tier 2 | Tier 2 Sprite | Tier 3 | Tier 3 Sprite |
|--------|--------|--------|--------|--------|--------|
| Tier 1 Weapon | ![alt text](./docs/images/w_tier_1.png)| Tier 2 Weapon | ![alt text](./docs/images/w_tier_2.png)| Tier 3 Weapon | ![alt text](./docs/images/w_tier_3.png)|

## Armaduras/Trajes
| Nombre | Sprite | Stats |
|--------|--------|-------|
| N/A | N/A | N/A |

# Loot en localización

![loot](./docs/images/loot_system.png)

## Específico
| Nombre | Sprite | Tamaño de stack | Uso |
|--------|--------|-----------------|-----|
| Kit de mejora básico | N/A | 1 | Permite la mejora de armas a nivel 2 |
| Kit de mejora avanzado | N/A | 1 | Permite la mejora de armas a nivel 3 |
| Armas | N/A | N/A | N/A |
| Restos clave de la nave | N/A | N/A | N/A |
| Munición | N/A | N/A | N/A |
| Mochila | N/A | N/A | N/A |
| Placas de metal | N/A | N/A | N/A |

## Genérico
| Nombre | Sprite | Tamaño de stack |
|--------|--------|-----------------|
| Materiales de construcción | N/A | 5 |
| Partes mecánicas | N/A | 10 |
| Restos electronicas | N/A | 10 |
| Componentes médicos | N/A | N/A |
| Agua | N/A | N/A |
| Elementos orgánicos | N/A | N/A |
| Comida | N/A | N/A |

## Crafteos
| Objeto | Elementos necesarios | Uso |
|--------|----------------------|-----|
| Vendas | x componentes médicos + x agua + x elementos orgánicos | Curan sangrado |
| Antídoto | x comida + x agua + x componenetes médicos | Cura infecciones |
| Férula | x partes mecánicas + x agua | Cura contusiones |
| Cohetes de la nave | x restos clave de la nave + x materiales de construcción + restos electrónicos + x placas de metal | Primera parte de la nave |
| Arma mejorada | x partes mecánicas + x restos electrónicos + kit de mejora | Aumenta el tier del arma |
| Munición arma clásica | x partes mecánicas + x componentes médicos + x placas de metal | Munición para el arma clásica |
| Mochila mejorada | kit de mejora + x elementos orgánicos + x vendas |
Mejora la mochila |
| Placas de metal | x materiales de construcción + x partes mecánicas | Para reaizar otros crafteos |
| Armadura mejorada | kit de mejora + x placas de metal + x elementos orgánicos | Mejora la armadura |


# Refúgio

## Estación médica
| Crafteo/Acción | Sprite | Coste | Tiempo (Coste) |
|-----|-----|-----|-----|
| N/A | N/A | N/A | N/A |

## Taller
| Crafteo/Acción | Sprite | Coste | Tiempo (Coste) |
|-----|-----|-----|-----|
| N/A | N/A | N/A | N/A |

# Enemigos
| Nombre | Sprite | .... |
|--------|--------|-------|
| Melé | N/A | Se acerca al jugador y le hace daño (daño/explosion) |
| Torreta | N/A | Fijo en el suelo, dispara al jugador |
| Volador | N/A | Vuela, persigue al jugador (bombardero, la abeja del Hollow Knight) |

*MENOS PRIORIDAD:*
| Blob de Minecraft | N/A | Le matas y se divide |


![Estética](./docs/headers/h_estetica.png) <a name="este"></a>

El juego tiene estetica en pixel-art, concretamente en 64-bits. Esta ambientado en la cúpula de un planeta desertico. Inspirado en Kingdom.

![alt text](./docs/images/estetica.gif)

![Controles](./docs/headers/h_controles.png) <a name="keys"></a>

![alttext](./docs/images/infogfx_keybinds.png)

## En partida
- **A,D ->** Movimiento lateral
- **W,S ->** Seleccionar el subir y bajar escaleras
- **SPACE ->** Saltar
- **C ->** Agacharse
- **Movimiento del raton ->** Apuntar
- **Click izquierdo ->** Disparar
- **R ->** Recargar el arma
- **Tab ->** Abrir el inventario
- **E ->** Interactuar con elementos del mapa
- **ESC ->** Menu de pausa

## En menús
- **Tab ->** Volver al juego
- **Click izquierdo ->** Arrastrar un objeto del inventario
- **Click derecho ->** Rotar el objeto que estas arrastrando

![Interfaz y Menús](./docs/headers/h_interfaz.png) <a name="hud"></a>

# Menu de inicio
En este menu el jugador tendra la opcion de salir del juego,ir al juego o  irse al menu de opciones

# Menu de opciones
Menu de ajustes donde el jugador podra seleccionar el idioma del juego y el volumen del mismo.

# Menu de selección de raid
En este menu el jugador tendra que seleccionar a que zona del mapa se quiere dirigir para efectuar la raid. Ademas en la parte superior izquierda se veran los estados del jugador para facilitarle el ver que es lo que mas necesita en ese momento. Tambien aparecera la distacia que hay al lugar y el tiempo que podras pasar en el.

![raidmenu](./docs/images/select_raid.png)

# Menu de pausa
Este menu aparecera si una vez in-game el jugador pulsa esc, aqui el jugador podra irse al menu de opciones, volver a la partida o volver al menu principal

# Inventario
Menu que se le abrira al jugador cuasndo pulse la F, aqui el jugador podra ver el estado de su armadura, la vida que le queda y sus distintos estados ademas de la hora que es en ese momento y los objetos que tiene en el inventario.

![inventory](./docs/images/inventory.png)

# Menu interactuar con espacios de almacenamiento
En este menu el jugador podra arrastrar objetos del lugar de almacenamiento a su inventario y viceversa.

![openchest](./docs/images/take_objects.jpg)

# Interfaz In-Game
Hay que discutirlo

![Referencias](./docs/headers/h_referencias.png) <a name="refe"></a>

- *This War of Mine (Supervivencia día a día)*
- *Escape from Tarkov (Raids / Equipamiento)*
- *Project Zomboid (Skills / Equipamiento)*
- *Metro Exodus (Crafting / Loot)*
