# scd-productor-consumidor-semaforos
Solución al problema del productor-consumidor LIFO y FIFO basada en semáforos.

### Problema y aplicaciones
- El problema del productor consumidor surge cuando se quiere diseñar un programa en el cual un proceso o hebra produce ítems de datos en memoria que otro proceso o hebra consume.
- En general, el productor calcula o produce una secuencia de  de datos (uno a uno), y el consumidor lee o consume dichos ítems (tambien uno a uno).
- El tiempo que se tarda en producir un ítem de datos puede ser variable y en general distinto al que se tarda en consumirlo
(también variable).

### Solución de dos hebras con un vector de ítems
- Suele ser conveniente implementar el productor y el consumidor como dos hebras independientes, ya que esto permite tener ocupadas las CPUs disponibles el máximo de tiempo.
- Se puede usar una variable compartida que contiene un ítem de datos.
- Las esperas asociadas a la lectura y la escritura pueden empeorar la eficiencia. Esto puede mejorarse usando un vector que pueda contener muchos ítems de datos producidos y pendientes de leer.

### En esta situación, la implementación debe asegurar que:
- Cada ıtem producido es leıdo (ningún ítem se pierde).
- Ningún ítem se lee más de una vez.
Lo cual implica que:
- El productor tendra que esperar antes de poder escribir en el vector cuando haya creado un ítem pero el vector esté completamente ocupado por ítems pendientes de leer.
- El consumidor debe esperar cuando vaya a leer un ítem del vector pero dicho vector no contenga ningún ítem pendiente de leer.
- En algunas aplicaciones el orden de lectura debe coincidir con el de escritura, en otras podría ser irrelevante.

### Soluciones para la gestión de la ocupación
- Hay básicamente dos alternativas posibles para gestionar la ocupación: LIFO (pila acotada) y FIFO (cola circular).

### Objetivos
1. Diseñar una solución que permita conocer que entradas del vector están ocupadas y que entradas están libres.
2. Diseñar una solución, mediante semáforos, que permita realizar las esperas necesarias para cumplir los requisitos descritos.
3. Implementar la solución descrita en un programa C/C++ con hebras y semáforos POSIX. El programa debe escribir la palabra fin cuando hayan terminado las dos hebras.
4. Comprobar que el programa es correcto: verificar que cada número natural producido es consumido exactamente una vez.
