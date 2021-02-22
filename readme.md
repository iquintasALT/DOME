![PROYECTOS 2 GAME HEADER](./docs/headers/h_title.png)
 Juego de Proyectos II hecho en c++ con SDL.

## ENLACES
[PÁGINA WEB](https://www.pivotaltracker.com/n/projects/2489079)\
[PIVOTAL (editable)](https://www.pivotaltracker.com/n/projects/2489079)\
[DIAGRAMA UML](https://lucid.app/lucidchart/invitations/accept/355e2dc6-1896-49d8-9c1d-601517544eb8)\

![Descripción](./docs/headers/h_descripcion.png)

Survival shooter scroller 2D donde controlas a un superviviente en un refugio (upgradeable) y cada día desde un mapa seleccionas una localización para raidear(similar a This War of Mine) pero con más focus en el combate con armas de fuego y saqueo con el objetivo de conseguir mejor equipamiento de combate, comida, materiales, etc.

![Mecánicas](./docs/headers/h_mecanicas.png)

### Día a día

Mecánica principal/loop de juego: cada día el jugador tendrá que dividir su tiempo (24h  1min/h? 24min/loop) entre trabajar en el refugio (instalando mejoras, comiendo, descansando, crafteando items como munición o medicinas) y decidir si ir a saquear una localización seleccionada desde un mapa.

### Raid

Los lugares de saqueo serán pequeños y contendrán loot dependiendo del lugar (farmacia--> medicinas , supermercado---> comida, etc) rápidos de recorrer el jugador gastara tiempo del día mientras esta en ellos y solo podrá saquear lo que su equipamiento (y su estado? herido, hambriento, cansado ) le permita llevar de vuelta al refugio.

Estos lugares pueden presentar obstáculos como puertas bloqueadas, necesidad de contraseñas o herramientas para saquearlo completamente.

Existe la posibilidad de volver a la misma localización.

Los lugares de saqueo tendrán descripciones que ayuden al jugador a saber que esperar por ejemplo en una casa abandonada puede poner debajo de la descripción peligro: gran número hostiles en la zona o sustancia química en el aire, etc.

### Refugio

El refugio es una zona pequeña donde el jugador podrá construir y mejorar diferentes estaciones de crafteo, crear items o descansar.

Ejemplo: caja de comida (comida se caduca un 10% más lenta, 4 espacios), nevera pequeña (comida se caduca un 25% más lenta, 8 espacios), nevera (comida se caduca un 50% más lenta, 16 espacios)

### Equipamiento

El jugador dispondrá de un sistema básico de equipamiento.

Arma: distintos tiers de armas facilitan el combate contra ciertos enemigos, o por ejemplo ciertos enemigos son resistentes y el jugador deberá llevar algún tipo de arma con capacidad para eliminarlos.

Armadura: Afecta la resistencia del jugador, ciertas mejoras o armaduras darán resistencia a efectos por ejemplo para poder saquear una zona contaminada o con radiación el jugador sacrifica resistencia balística por resistencia a un cierto elemento.

Mochila: Afecta la capacidad de saqueo del jugador.

### Loot

El loot puede ser básico por ejemplo como en Metro Exodus dónde el jugador recoge componentes mecánicos y componentes químicos para crafteos y de manera más específica nuevo equipamiento (armas, mochilas, armaduras).

This War of mine usa un sistema de loot un poco más específico para crafteos con construcción, electrónicos, eléctricos, mecánicos y después el equipamiento.

Escape from Tarkov utiliza un sistema especifico de loot donde no hay abstracción en ningún caso y cada objeto está representado por sí mismo.

COMIDA: cruda (más común dura poco), enlatada (menos común no caduca)

MEDICINAS: ya creadas (más rara), por componentes (por ejemplo, ropa + antiséptico = vendas)

EN GENERAL EL LOOT DE LAS ZONAS DEBE SER ESCASO Y DEBE FORZAR AL JUGADOR A SAQUEAR UNOS ITEMS ANTES QUE OTROS POR NECESIDAD Y POR TIEMPO.

### Combate

Combate de point and click con posibilidad de agacharte detrás de objetos y levantarte para disparar.
Los mapas tendrán verticalidad con plataformas, pero el jugador no podrá navegar el mapa con solo su salto; necesitará usar las escaleras del mapa.
Hay daño de caída (una caída notable tiene una posibilidad de causar una concusión o una lesión, con mayor probabilidad mientras más grande la caída).
El daño no se refleja en puntos de golpe, sino en efectos de estado o heridas. Cada ataque de cada enemigo puede inflingir ciertos tipos de herida. Si en algún momento el jugador sufre de 5 heridas diferentes, muere. Cada herida (ejs.: quemadura, músculo desgarrado, concusión, hemorragia) aportará una debilidad al jugador, parecidos a los efectos negativos del frío, el hambre, la sed y el cansancio.
Las armas no son perfectamente certeras. Siempre que el jugador apunte, habrá una desviación oscilante en la trayectoria de su puntería.
BAJA PRIORIDAD: El jugador se puede agachar, reduciendo su tamaño y velocidad de movimiento, pero reduciendo la desviación de sus disparos.
BAJA PRIORIDAD: Las balas atraviesan las plataformas, de tal forma que si una criatura está directamente sobre otra, puedan dispararse.

### Supervivencia

Comida: Si se pasan dos días sin comer, se aplicará el debufo de hambre. Hay dos tipos de ración de comida: proteínas (carne) y vitaminas (verdura). Comer uno de cada en un solo día se considera una comida completa, y aportará un bufo al jugador que le otorgará un 15% de probabilidad de evitar sufrir heridas cuando recibe daño. Este efecto dura un día.

Bebida: Si no se bebe una ración de agua cada día, se aplicará el debufo de sed. Si no se bebe un día en el que ya está sediento el personaje, muere.

Descanso: Por cada 30 minutos por encima de 6 horas que se duerme, el tiempo de viaje a una raid se reduce en un 5%, hasta un máximo de 40% de reducción. De tal forma que el de tiempo juegable final de la raid será Tf = (12-Tv) + min(0.4, 0.05*(m/30))*(12-Tv); siendo Tf el tiempo final, Tv el tiempo de viaje no modificado, m/30 el número de incrementos de 30 minutos dormidos por encima de las 6 horas. Esta modificación se aplica también en negativo, de tal forma que si se duermen solo 4 horas, el tiempo de viaje a la raid se incrementa un 20%, reduciendo la cantidad de tiempo que se tiene para jugar el nivel.


Hambre: El hambre es un debufo stackeable que reduce el espacio de carga. Cada nivel de hambre adquirido deshabilida el último espacio disponible del inventario (modo fácil) o un espacio aleatorio (modo difícil). Si hay un objeto en el espacio deshabilitado en el momento de aplicarse el debufo, ese objeto se colocará en el almacenamiento del refugio. Comer una ración de comida restará dos niveles de hambre; comer una comida completa restará todos los niveles de hambre.

Sed: La sed es un debufo que reduce la precisión de las armas, incrementando el índice de desviación de cada bala disparada. Este debufo se limpia cuando se bebe una ración de agua.

Ciertas mejoras del refugio pueden hacer esto más llevadero, una cama mejor te permite estar sin dormir durante 2 días o algo así.

### Medicina

Heridas de bala.

Heridas por corte o mordeduras si hacemos enemigo a melee.

Heridas por rebuscar en ciertos objetos peligrosos (estilo Darkest Dungeon).

Muerte por infección por no tratar las heridas de manera correcta.

Muerte por no comer beber o descansar.

Muerte por enfermedad al comer comida cruda o algo así.

Medicina para contrarrestarlo antibióticos(infecciones) vendajes(sangrados o laceraciones leves) kit medico (sacar balas grapar heridas graves o laceraciones profundas).

![Dinámicas](./docs/headers/h_dinamicas.png)

### Objetivos y conflictos

Sobrevivir, encontrar las "piezas necesarias" para un objetivo final (escapar de la isla, zona, planeta, colonia, etc).

### Comportamiento esperado

El jugador estará en este gameplay loop de crafteo->raid->loot->rest cada día progresando, mejorando su refugio y equipamiento, así como haciendo progreso en el objetivo final.

Es un challenge de supervivencia donde el jugador tendrá que gestionar las necesidades de su avatar para completarlo sin morir y en el menor tiempo posible.

![Contenido](./docs/headers/h_contenido.png)

### placeholder

![Estética](./docs/headers/h_estetica.png)

### placeholder

![Controles](./docs/headers/h_controles.png)

### placeholder

![Interfaz y Menús](./docs/headers/h_interfaz.png)

### placeholder

![Referencias](./docs/headers/h_referencias.png)

- *This War of Mine (Supervivencia día a día)*
- *Escape from Tarkov (Raids / Equipamiento)*
- *Project Zomboid (Skills / Equipamiento)*
- *Metro Exodus (Crafting / Loot)*