# **Estructura de datos y algoritmos II, 2022-2023**
## **DUNK NATION**

Integrantes del grupo:


- Nil Tomas (u214575)
- Anshpreet Singh Kaur (u215093) 
- Danial Imran Muhammad Begum (u215090)

# **INFORME DEL PROJECTO**

## **TABLA DE CONTENIDOS**

1. Introduccion
2. Objetivos del projecto
3. Solución
4. Referencias

## **INTRODUCCION** [maximo 250 palabras]

En un mundo que avanza a estar cada vez más conectado, las redes sociales son y serán una parte fundamental de nuestras vidas. Así pues, a nuestro equipo nos ha surgido la necesidad de crear una red social de baloncesto llamada Dunk Nation, que permita a los jugadores comunicarse y organizar partidos de una forma fácil y eficaz, ya que muy a menudo, los jugadores no encuentran compañeros con quién compartir o sitios adecuados para jugar. Para crear esta red social, nos hemos inspirado en Facebook por el sistema de crear publicaciones, en el que se va a definir el lugar y hora del encuentro, y los otros jugadores podrán publicar si asisten o no.
Los objetivos alcanzados hasta el momento han sido: un sistema de registro y login de jugadores, un sistema de perfiles con las características de cada usuario (datos personales, ubicación, posición de juego, etc.), enviar solicitudes de amistad a otros jugadores, realizar publicaciones sobre encuentros y mostrar aquellos más comunes. 


## **OBJETIVOS DEL PROJECTO** [maximo 2500 palabras]


### Objetios obligatorios cumplidos
En esta sección se deben cubrir los objetivos alcanzados en el proyecto. Cada objetivo presentado en las siguientes subsecciones debe cubrir los siguientes elementos:
- Descripción general: Describir cómo se ha implementado. Más allá de lo que se le proporcionó en el documento de orientación, indique las características principales de las estructuras de datos y los algoritmos implementados para lograr este objetivo y su comportamiento. Debería incluir:
	- ¿Qué variables se utilizaron y con qué propósito?
	- ¿Cuáles fueron las estructuras de datos elegidas para este objetivo? ¿Para que se utilizó?
	- ¿Cuál fue el algoritmo elegido para este objetivo? ¿Cuál es su comportamiento esperado?
	- ¿Qué limitaciones tiene el algoritmo? ¿Cómo pasó en su implementación?
	- ¿Qué se puede mejorar?
- Tiempo: Tiempo necesario para desarrollar este objetivo
- Ubicación: a qué línea de código y en qué archivo se encuentra esta implementación.

LISTA

- Descripción general: Para implementar la lista enlazada, hemos utilizado diferentes variables con el objetivo de almacenar los diferentes usuarios y sus datos. Dentro de la lista ListNode, se han incluido una variable puntero llamada user de tipo estructura del usuario, User y un puntero llamado next que apunta a la siguiente posición de la lista (llamada recursiva a la ListNode). Esta última variable permite acceder al siguiente usuario de la lista y añadir usuarios de una forma más sencilla. El comportamiento esperado de la lista es poder añadir y guardar usuarios.
Una de las mejoras que permitiría un acceso más eficiente a los nodos almacenados, podría ser una lista doblemente enlazada (en la que se tendría que añadir una variable puntero apuntando al usuario anterior).

- Tiempo: El desarrollo de esta lista nos llevó aproximadamente unos 10 minutos.

- Ubicación: La estructura ListNode se encuentra en la línea 23 en el archivo estructuras.c.


COLA: (pendiente de terminar)

- Descripción general:

- Tiempo:

- Ubicación:


PILA: (no la hacemos, habrá que pensar qué hacemos)

- Descripción general:

- Tiempo:

- Ubicación:


ALGORITMO DE BÚSQUEDA: (Linear Search)

- Descripción general: Para implementar el algoritmo de búsqueda lineal, hemos creado una función llamada searchUser() que tiene como parámetros de entrada las siguientes variables: nombre de usuario username y contraseña password, y una variable puntero userList que apunta a la lista enlazada de usuarios ListNode. Con el objetivo de realizar la búsqueda al mismo tiempo que se accede a la lista de usuarios. El programa utiliza la lista dinámica ListNode con la intención de comparar si los datos del usuario coinciden con el username y password de entrada. El algoritmo que hemos utilizado es de búsqueda secuencial por lo que va a recorrer toda la lista enlazada hasta encontrar los valores coincidentes y devolverá el nodo del usuario. La principal limitación del algoritmo es que tiene una complejidad temporal de O(n), de manera que a medida que aumenta la lista enlazada, también aumenta en la misma proporción el tiempo de ejecución. Por lo que si el usuario se encuentra al final de la lista, el algoritmo va a tener que recorrerla toda. Sólo podemos implementar este algoritmo de búsqueda secuencial ya que los usuarios no están ordenados, y por lo tanto no tenemos una medida para ordenarlos. Algunas de las mejoras que se nos han ocurrido a lo largo del proyecto es utilizar otro parámetro de comparación (ej: el correo), ya que los nombres se pueden repetir, aun así, nosotros asumimos que los nombres no se van a repetir. O ordenar los usuarios por orden alfabético, por lo que podríamos haber utilizado un algoritmo de búsqueda más eficiente,el Binary Search entre otros.

- Tiempo: El desarrollo de esta función nos llevó aproximadamente unos 60 minutos.

- Ubicación: La función searchUser() se encuentra en la línea X en el archivo estructuras.c.

ALGORITMO DE ORDENAMIENTO: (pendiente de hacer)

- Descripción general:

- Tiempo:

- Ubicación:


DICCIONARIO O TABLA HASH: 

- Descripción general:

- Tiempo:

- Ubicación:



LEER DATOS DE UN ARCHIVO EXTERNO CSV:

- Explicado en apartado de Objetivos libres cumplidos, conjuntamente con el guardado de datos.

PERSONALIZACIÓN DE LA RED SOCIAL:

- Descripción general:

- Tiempo:

- Ubicación:


### Objetivos deseables alcanzados


LEER DATOS DE UN ARCHIVO EXTERNO CSV:

- Explicado en apartado de Objetivos libres cumplidos, conjuntamente con el guardado de datos.

PERSONALIZACIÓN DE LA RED SOCIAL:

- Descripción general:

- Tiempo:

- Ubicación:




### Objetivos libres cumplidos

INTERFAZ DE USUARIO:

- Descripción general: Para implementar la interfaz gráfica, hemos utilizado la biblioteca WinAPI de aplicaciones de Windows. Entonces, la función main() estándar es la equivalente a la función WINAPI WinMain() que utilizamos en nuestro programa. La biblioteca que hemos necesitado ha sido windows.h. Las principales variables utilizadas para la creación de la estructura de la interfaz y su funcionamiento (no el contenido en sí) han sido las siguientes: hInst de tipo HINSTANCE; que almacena el identificador de la instancia de la aplicación, hWnd de tipo HIMAGELIST; guarda el identificador de la ventana principal, hUserList de tipo HWND;  almacena el identificador de la lista de usuarios y hMenu que almacena datos de la ventana (acompaña a variables globales para la interacción con el usuario). Las funciones principales y sus funcionalidades son: CreateWindowEx; utilizada para crear la ventana principal, el título o el tipo de ventana (emergente o fija) entre otros, CreateWindow; utilizada para crear controles de la interfaz gráfica, en nuestro caso los botones, ShowWindow; utilizada para mostrar la ventana principal en la pantalla. El uso y definición de estas variables nos han permitido crear los diferentes elementos interactivos y visuales de nuestra red social.

- Tiempo: el desarrollo de la interfaz nos llevó aproximadamente 180 minutos.

- Ubicación: La interfaz se encuentra en el archivo library.c, en la línea 42 del código.


IMPLEMENTACIÓN DE FUNCIONALIDADES DE LECTURA Y GUARDADO DE DATOS DESDE UN ARCHIVO.CSV:

- Descripción general: Para implementar la funcionalidad de lectura de datos procedentes de un archivo .csv, primero hemos creado el archivo .csv con los siguientes datos de los usuarios: nombre, edad, contraseña, email, ciudad, equipo y jugador de básquet favorito y finalmente la posición de juego. Y por otra parte la función read_users_file(). 
Las variables utilizadas para esta función són: max_usuarios; número de iteraciones a realizar, fp; puntero a FILE que lo utilizamos para leer y abrir los datos del archivo, linea; array de carácteres utilizada para leer la línea de datos a cada iteración y finalmente  i; índice para llevar la cuenta de los usuarios leídos. Las estructuras de datos utilizadas han sido: user conteniendo los datos de los usuarios, y lo utilizamos para almacenar los datos de cada usuario leído del archivo.Y ListNode, lista enlazada utilizada para crear la lista enlazada de los 20 usuarios.El algoritmo utilizado para esta función es un algoritmo de lectura y construcción de lista enlazada, y esperamos que lea cada línea del archivo, y asigne los diferentes datos separados por comas, a los diferentes parámetros de cada nodo de la ListNode. El principal problema de la función, es si los datos leídos no son del tipo que se espera que sean, por ejemplo si espera un int, y en vez hay un string de carácteres, por lo que llevaría a resultados incorrectos a lo largo de la ejecución. Un aspecto que se podría mejorar, es utilizar estructuras de datos más eficientes para almacenar los usuarios, por ejemplo árboles o tablas hash, en lugar de una lista enlazada.

- Tiempo: El desarrollo de este conjunto de código nos llevó aproximadamente 4 horas.

- Ubicación: La función read_users_file() se encuentra en la línea X del documento library.c. En el caso del archivo se encuentra en el archivo_users.csv


## **SOLUCIÓN** [maximo 1500 palabras]

Esta sección debe profundizar en la solución desarrollada para este proyecto.

### Arquitectura del sistema [maximo 750 palabras]

La arquitectura de nuestra red social, se basa en una arquitectura de tres capas, compuesta por la capa de creación de la ventana de la interfaz, la capa de interacción de la interfaz con el/los usuario/s y la capa de datos y funciones que permite el correcto funcionamiento de la interacción. Para ayudar a la comprensión del funcionamiento, a continuación se adjunta un diagrama del funcionamiento general de la interfaz:

[Figura 1: Diagrama interfaz gráfica de Dunk Nation [04/06/23]](https://github.com/niiltomas/EDA2/blob/0763fc1c0a5e66e6652519bc115237aaae3f387d/Captura%20de%20pantalla%202023-06-05%20110034.png)
El primer bloque, se caracteriza por crear la interfaz y su configuración. En primer lugar, hemos definido la estructura WNDCLASSW para registrar la clase de ventana, donde habrá información sobre el color de fondo (COLOR_WINDOW), el cursor (IDC_ARROW) o la instancia del programa hInst, entre otras funciones. A continuación con CreateWindowW creamos la interfaz con dimensiones (500,500)px  y nombre DUNK NATION. Cabe destacar que para inicializar esta ventana hemos utilizado la función de Windows WINAPI llamada WinMain(), donde va a ser la equivalencia al main() sin capa gráfica.

En el segundo bloque, correspondiente a la implementación de todas aquellas interacciones interfaz - usuario, se encuentran por una parte, en las funciones AddMenus() y AddControls() a todas aquellas que corresponden a implementaciones de botones (creados con la función CreateWindowW) de la página principal como el NEW PLAYER, LOGIN, EXIT, etc. Cada uno de estos botones tendrá una hInstance definida, que cuando el usuario interaccione con el botón, este lo direccionará a la función LRESULT CALLBACK WindowProcedure donde va a ser ejecutada la funcionalidad para el botón seleccionado. Esta parte corresponde al menú principal, por lo que las ventanas que emerjan de la principal, van a tener la misma configuración que las anteriores (igual que sus botones), pero en vez de estar definidas en AddMenus() y AddControls() se localizan en las funciones registerDialogClass() y DisplayDialog() y sus botones van a redireccionar a LRESULT CALLBACK DialogProcedure()

En este tercer bloque correspondiente a las funcionalidades de la red social, van a ser funciones implementadas dentro de cada case en función del botón elegido. Estas funciones las hemos escrito en la parte baja del archivo library.c como pueden ser read_users_file() o searchUser(). Un apunte a destacar, es la necesidad de definir las funciones al inicio del código, para que este compile correctamente.

Esta subsección debe incluir al menos un diagrama de la arquitectura del sistema y una descripción de los bloques principales y su funcionalidad.

### Manejo de errores [maximo 250 palabras]

Durante el desarrollo de la red social Dunk Nation, nos hemos encontrado con errores que han afectado la evolución del proyecto. A continuación expondremos esos errores así como los razonamientos para solucionarlos.
El primer error que nos encontramos estuvo relacionado con la apertura del fichero de usuarios (archivo_users.csv), donde el fichero no se abría. Para solucionarlo borramos la siguiente línea del código que lo estaba causando: #include “archivo_users.csv”. 

En la misma línea, tuvimos otro problema relacionado con este fichero, y consistia en que a veces leía los usuarios correctamente y otras veces no. A primera vista pensamos que estaba causado por algún error de fragmentación en la memoria, ya que estábamos utilizando una interfaz gráfica. Así pues, después de darle muchas vueltas, nos decantamos por cambiar la función que leía los datos; pasamos de escanear los datos con fscanf() a fgets() y entonces solucionamos el error.

El segundo error que nos encontramos, fue la imposibilidad de implementar una imagen como logo de la red social. El código compilaba bien, pero la imagen no se mostraba. A día de hoy, aún no lo hemos conseguido resolver, a continuación adjuntamos el logo que teníamos pensado implementar:

Figura 2: Logo Dunk Nation [15/06/23](https://github.com/niiltomas/EDA2/blob/e4e3110ad528569583962592079e26e703b6c3fb/Logo_DunkNation.png)


### Diseño de modelo de datos [maximo 250 palabras]

Esta subsección debe incluir al menos un diagrama de flujo de datos de la solución y su descripción.

### Descripción y procesamiento del conjunto de datos [maximo 250 palabras]

Esta subsección debe incluir una descripción de los conjuntos de datos utilizados, cómo se leyeron y procesaron.

## **REFERENCIAS**

Esta sección debe incluir las referencias utilizadas en el informe. Estas referencias incluyen cualquier sitio web, material de lectura, publicaciones o libros utilizados como inspiración.
