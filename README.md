# **Estructura de datos y algoritmos II, 2022-2023**
## **DUNK NATION**

Integrantes del grupo:


- Nil Tomàs Plans (u214575)
- Anshpreet Singh Kaur (u215093) 
- Danial Imran Muhammad Begum (u215090)

# **INFORME DEL PROYECTO**

## **TABLA DE CONTENIDOS**

1. Introducción
2. Objetivos del projecto
3. Solución
4. Enlace video de la presentacion
5. Referencias


## **INTRODUCCIÓN** [maximo 250 palabras]

En un mundo que avanza a estar cada vez más conectado, las redes sociales son y serán una parte fundamental de nuestras vidas. Así pues, a nuestro equipo nos ha surgido la necesidad de crear una red social de baloncesto llamada Dunk Nation, que permita a los jugadores comunicarse y organizar partidos de una forma fácil y eficaz, ya que muy a menudo, los jugadores no encuentran compañeros con quién compartir o sitios adecuados para jugar. Para crear esta red social, nos hemos inspirado en Facebook por el sistema de crear publicaciones, en el que se va a definir el lugar y hora del encuentro, y los otros jugadores podrán publicar si asisten o no.
Los objetivos alcanzados hasta el momento han sido: un sistema de registro y login de jugadores, un sistema de perfiles con las características de cada usuario (datos personales, ubicación, posición de juego, etc.), enviar solicitudes de amistad a otros jugadores, realizar publicaciones sobre encuentros y mostrar aquellos más comunes. 


## **OBJETIVOS DEL PROJECTO** [maximo 2500 palabras]


### Objetios obligatorios cumplidos


LISTA:

- Descripción general: Para implementar la lista enlazada, hemos utilizado diferentes variables con el objetivo de almacenar los diferentes usuarios y sus datos. Dentro de la lista ListNode, se han incluido una variable puntero llamada user de tipo estructura del usuario, User y un puntero llamado next que apunta a la siguiente posición de la lista (llamada recursiva a la ListNode). Esta última variable permite acceder al siguiente usuario de la lista y añadir usuarios de una forma más sencilla. El comportamiento esperado de la lista es poder añadir y guardar usuarios.
Una de las mejoras que permitiría un acceso más eficiente a los nodos almacenados, podría ser una lista doblemente enlazada (en la que se tendría que añadir una variable puntero apuntando al usuario anterior).

- Tiempo: El desarrollo de esta lista nos llevó aproximadamente unos 10 minutos.

- Ubicación: La estructura ListNode se encuentra en la línea 23 en el archivo estructuras.c.


COLA:

- Descripción general: Para la implementación de la cola hemos utilizado las variables friendRequestsQueue y sentRequestsQueue, de tipo FriendRequestQueue que son las utilizadas para almacenar las solicitudes de amistad. La primera es para las recibidas y la segunda para las enviadas. Las estructuras de datos que hemos utilizado son FriendRequestQueue; estructura para la  cola de solicitudes de amistad. Consiste en un puntero al primer y último nodo de la cola para encolar y desencolar. FriendRequestNode: Es la solicitud de la cola . Contiene un puntero a una estructura FriendRequest son las solicitudes de amistad, así como un puntero a la siguiente solicitud en la cola. La mejora que contemplamos es que no se pueda enviar más de una solicitud a la misma persona, ya que no tiene sentido y se está ocupando memoria de manera innecesaria. 

- Tiempo: Nos llevo más menos una semana.

- Ubicación: La implementación de la cola se encuentra a partir de la línea 250-251 y 276-349 en el archivo library.c


PILA: 
- Descripción general:En esta red social, hemos implementado una pila que va a  comprobar si el correo electrónico del usuario que se está registrando tiene el formato correcto o no, por lo que mirará que el email tenga un ”@”.
Las funciones que hemos utilizado para esta implementación són las funciones básicas de las pilas; pop() para extraer un elemento y push() para insertar un nuevo elemento. Además se una función para iniciarla, initializeStack(), una para comprobar si está vacía (ya que solo queremos saber si hay una. En caso de haber más, pues saldrá un error de email incorrecto) y finalmente validateEmail() donde se busca a cada elemento “@”, se añade a la pila y se comprueba si solo hay un elemento. Las estructuras que utiliza es una lista enlazada NODE (para la pila) y otra llamada Stack donde maneja el top (nivel) de la pila. Aspectos a mejorar que se podrían tener en cuenta es el hecho de comprobar la posición de “@”, ya que teóricamente no puede ir en la primera posición de la dirección

- Tiempo:60 minutos aproximadamente.

- Ubicación: Las funciones para la implementación de la pila se encuentran en las líneas713 a 767 del archivo library.c y luego sus estructuras en el archivo estructuras.c


ALGORITMO DE BÚSQUEDA: (Linear Search)

- Descripción general: Para implementar el algoritmo de búsqueda lineal, hemos creado una función llamada searchUser() que tiene como parámetros de entrada las siguientes variables: nombre de usuario username y contraseña password, y una variable puntero userList que apunta a la lista enlazada de usuarios ListNode. Con el objetivo de realizar la búsqueda al mismo tiempo que se accede a la lista de usuarios. El programa utiliza la lista dinámica ListNode con la intención de comparar si los datos del usuario coinciden con el username y password de entrada. El algoritmo que hemos utilizado es de búsqueda secuencial por lo que va a recorrer toda la lista enlazada hasta encontrar los valores coincidentes y devolverá el nodo del usuario. La principal limitación del algoritmo es que tiene una complejidad temporal de O(n), de manera que a medida que aumenta la lista enlazada, también aumenta en la misma proporción el tiempo de ejecución. Por lo que si el usuario se encuentra al final de la lista, el algoritmo va a tener que recorrerla toda. Sólo podemos implementar este algoritmo de búsqueda secuencial ya que los usuarios no están ordenados, y por lo tanto no tenemos una medida para ordenarlos. Algunas de las mejoras que se nos han ocurrido a lo largo del proyecto es utilizar otro parámetro de comparación (ej: el correo), ya que los nombres se pueden repetir, aun así, nosotros asumimos que los nombres no se van a repetir. O ordenar los usuarios por orden alfabético, por lo que podríamos haber utilizado un algoritmo de búsqueda más eficiente,el Binary Search entre otros.

- Tiempo: El desarrollo de esta función nos llevó aproximadamente unos 60 minutos.

- Ubicación: La función searchUser() se encuentra en la línea 479 en el archivo estructuras.c.

ALGORITMO DE ORDENAMIENTO:

- Descripción general: para implementar el algoritmo de ordenamiento, desde el grupo hemos decidido que utilizamos el algoritmo BubbleSort con una complejidad de  O(n2). Ese lo aplicaremos a la lista de usuarios que vamos a imprimir por consola, en que se podrán apreciar los usuarios ordenados alfabéticamente. 
Su implementación se encuentra dentro de la función de lectura de usuarios del archivo_users.csv, read_users_file(), después de haber escaneado los diferentes parámetros. 
Así pues, para el desarrollo del algoritmo hemos utilizado un entero para indicar si se ha realizado el intercambio de usuarios. Además hemos utilizado dos punteros de ListNode, uno para comparar y otro para marcar el último nodo ordenado, que va a ser el que sea alfabéticamente mayor. Las estructuras de datos utilizadas son la lista enlazada ListNode y la estructura User. Una posible limitación es la complejidad cuadrática del algoritmo, pero aun así no tiene un efecto muy importante en el programa ya que el número de usuarios es bastante reducido por lo que no tiene un gran impacto en el tiempo de ejecución. Mejoras a tener en cuenta, uso del algoritmo QuickSort, con complejidad de O(nlog(n))

- Tiempo:el desarrollo de esta parte de la función del read_user_file nos llevó 40 minutos aproximadamente.

- Ubicación: La función read_users_file() se encuentra en la línea 479 del documento library.c. En el caso del archivo se encuentra en el archivo_users.csv


DICCIONARIO : 

- Descripción general:Para implementar el  diccionario de palabras, se han desarrollado varias funciones. En primer lugar, se utiliza la función "inicializarDiccionario()" para establecer y reservar memoria, estableciendo los punteros de inicio y fin del diccionario como NULL. A continuación, se utiliza "insertarPalabra()" para agregar una palabra al diccionario. Esta función crea un nuevo nodo para la palabra y lo coloca al principio o al final del diccionario, según corresponda. "buscarPalabra()" busca una palabra en el diccionario y devuelve el nodo correspondiente si se encuentra. La función "eliminarPalabra()" elimina una palabra del diccionario si está presente. "destruirDiccionario()" se encarga de liberar la memoria asignada al diccionario y a sus nodos.
- Tiempo: La implementación nos llevo   2 horas.
- Ubicación:las funciones se encuntran en el archivo library.c en las 592 a 680 y luego su implemetación esta en case 4.




### Objetivos deseables alcanzados


LEER DATOS DE UN ARCHIVO EXTERNO CSV:

- Descripción general: Para implementar la funcionalidad de im de datos procedentes de un archivo .csv, primero hemos creado el archivo .csv con los siguientes datos de los usuarios: nombre, edad, contraseña, email, ciudad, jugador 1 y jugador 2 de básquet favorito y finalmente la posición de juego. Y por otra parte la función read_users_file(). 
Las variables utilizadas para esta función són: max_usuarios; número de iteraciones a realizar, fp; puntero a FILE que lo utilizamos para leer y abrir los datos del archivo, linea; array de carácteres utilizada para leer la línea de datos a cada iteración y finalmente  i; índice para llevar la cuenta de los usuarios leídos. Las estructuras de datos utilizadas han sido: user conteniendo los datos de los usuarios, y lo utilizamos para almacenar los datos de cada usuario leído del archivo.Y ListNode, lista enlazada utilizada para crear la lista enlazada de los 20 usuarios.El algoritmo utilizado para esta función es un algoritmo de lectura y construcción de lista enlazada, y esperamos que lea cada línea del archivo, y asigne los diferentes datos separados por comas, a los diferentes parámetros de cada nodo de la ListNode. El principal problema de la función, es si los datos leídos no son del tipo que se espera que sean, por ejemplo si espera un int, y en vez hay un string de carácteres, por lo que llevaría a resultados incorrectos a lo largo de la ejecución. Un aspecto que se podría mejorar, es utilizar estructuras de datos más eficientes para almacenar los usuarios, por ejemplo árboles o tablas hash, en lugar de una lista enlazada.


Tiempo: El desarrollo de este conjunto de código nos llevó aproximadamente 4 horas.


Ubicación: La función read_users_file() se encuentra en la línea 479 del documento library.c. En el caso del archivo se encuentra en el archivo_users.csv

PERSONALIZACIÓN DE LA RED SOCIAL:

- Descripción general: Hemos personalizado nuestra red social de la siguiente manera. hemos implementado una funcionalidad de registro (New Player) que permite a los usuarios crear una cuenta y luego iniciar sesión. Para registrarse, el usuario debe proporcionar su nombre, edad, una contraseña y una dirección de correo electrónico válida. Además, se solicita al usuario que indique sus dos jugadores favoritos y su posición en el juego.Una vez completado el proceso de registro, el usuario puede iniciar sesión en la red social. Desde allí, pueden enviar y recibir solicitudes de amistad que se almacenan en una cola. Estas solicitudes de amistad se eliminan una vez que son aceptadas, mientras que permanecen en la cola si son rechazadas o no se toma ninguna acción. Por ultimo tiene la opcion de publicar contenido, el usario publica 10 publicaciones y luego puede ver las palabras mas usadas en ellas.

- Tiempo: La personalización de la red social, no podemos medir de una forma exacta el tiempo que le hemos invertido, ya que a lo largo del proyecto nos hemos ido adaptando a los errores y problemas con los que nos encontramos. Por lo que hemos hecho ajuster para podernos adaptarnos a las diferentes situaciones.


### Objetivos libres cumplidos

INTERFAZ DE USUARIO:

- Descripción general: Para implementar la interfaz gráfica, hemos utilizado la biblioteca WinAPI de aplicaciones de Windows. Entonces, la función main() estándar es la equivalente a la función WINAPI WinMain() que utilizamos en nuestro programa. La biblioteca que hemos necesitado ha sido windows.h. Las principales variables utilizadas para la creación de la estructura de la interfaz y su funcionamiento (no el contenido en sí) han sido las siguientes: hInst de tipo HINSTANCE; que almacena el identificador de la instancia de la aplicación, hWnd de tipo HIMAGELIST; guarda el identificador de la ventana principal, hUserList de tipo HWND;  almacena el identificador de la lista de usuarios y hMenu que almacena datos de la ventana (acompaña a variables globales para la interacción con el usuario). Las funciones principales y sus funcionalidades son: CreateWindowEx; utilizada para crear la ventana principal, el título o el tipo de ventana (emergente o fija) entre otros, CreateWindow; utilizada para crear controles de la interfaz gráfica, en nuestro caso los botones, ShowWindow; utilizada para mostrar la ventana principal en la pantalla. El uso y definición de estas variables nos han permitido crear los diferentes elementos interactivos y visuales de nuestra red social.

- Tiempo: el desarrollo de la interfaz nos llevó aproximadamente 180 minutos.

- Ubicación: La interfaz se encuentra en el archivo library.c, en la línea 42 del código.



## **SOLUCIÓN** [maximo 1500 palabras]


### Arquitectura del sistema [maximo 750 palabras]

La arquitectura de nuestra red social, se basa en una arquitectura de tres capas, compuesta por la capa de creación de la ventana de la interfaz, la capa de interacción de la interfaz con el/los usuario/s y la capa de datos y funciones que permite el correcto funcionamiento de la interacción. Para ayudar a la comprensión del funcionamiento, a continuación se adjunta un diagrama del funcionamiento general de la interfaz:

![Figura 1: Diagrama interfaz gráfica de Dunk Nation [04/06/23]](https://github.com/niiltomas/EDA2/blob/5a52c90547c6b925116d78cde04b0925d995e512/diagrama%20definitivo%20arquitectura%20Dunk%20Nation.png)

El primer bloque, se caracteriza por crear la interfaz y su configuración. En primer lugar, hemos definido la estructura WNDCLASSW para registrar la clase de ventana, donde habrá información sobre el color de fondo (COLOR_WINDOW), el cursor (IDC_ARROW) o la instancia del programa hInst, entre otras funciones. A continuación con CreateWindowW creamos la interfaz con dimensiones (500,500)px  y nombre DUNK NATION. Cabe destacar que para inicializar esta ventana hemos utilizado la función de Windows WINAPI llamada WinMain(), donde va a ser la equivalencia al main() sin capa gráfica.

En el segundo bloque, correspondiente a la implementación de todas aquellas interacciones interfaz - usuario, se encuentran por una parte, en las funciones AddMenus() y AddControls() a todas aquellas que corresponden a implementaciones de botones (creados con la función CreateWindowW) de la página principal como el NEW PLAYER, LOGIN, EXIT, etc. Cada uno de estos botones tendrá una hInstance definida, que cuando el usuario interaccione con el botón, este lo direccionará a la función LRESULT CALLBACK WindowProcedure donde va a ser ejecutada la funcionalidad para el botón seleccionado. Esta parte corresponde al menú principal, por lo que las ventanas que emerjan de la principal, van a tener la misma configuración que las anteriores (igual que sus botones), pero en vez de estar definidas en AddMenus() y AddControls() se localizan en las funciones registerDialogClass() y DisplayDialog() y sus botones van a redireccionar a LRESULT CALLBACK DialogProcedure()

En este tercer bloque correspondiente a las funcionalidades de la red social, van a ser funciones implementadas dentro de cada case en función del botón elegido. Estas funciones las hemos escrito en la parte baja del archivo library.c como pueden ser read_users_file() o searchUser(). Un apunte a destacar, es la necesidad de definir las funciones al inicio del código, para que este compile correctamente.

Esta subsección debe incluir al menos un diagrama de la arquitectura del sistema y una descripción de los bloques principales y su funcionalidad.

### Manejo de errores [maximo 250 palabras]

Durante el desarrollo de la red social Dunk Nation, nos hemos encontrado con errores que han afectado la evolución del proyecto. A continuación expondremos esos errores así como los razonamientos para solucionarlos.
El primer error que nos encontramos estuvo relacionado con la apertura del fichero de usuarios (archivo_users.csv), donde el fichero no se abría. Para solucionarlo borramos la siguiente línea del código que lo estaba causando: #include “archivo_users.csv”. 

En la misma línea, tuvimos otro problema relacionado con este fichero, y consistia en que a veces leía los usuarios correctamente y otras veces no. A primera vista pensamos que estaba causado por algún error de fragmentación en la memoria, ya que estábamos utilizando una interfaz gráfica. Así pues, después de darle muchas vueltas, nos decantamos por cambiar la función que leía los datos; pasamos de escanear los datos con fscanf() a fgets() y entonces solucionamos el error.

El segundo error que nos encontramos, fue la imposibilidad de implementar una imagen como logo de la red social. El código compilaba bien, pero la imagen no se mostraba. A día de hoy, aún no lo hemos conseguido resolver, a continuación adjuntamos el logo que teníamos pensado implementar:

![Figura 2: Logo Dunk Nation [15/06/23]](https://github.com/niiltomas/EDA2/blob/e4e3110ad528569583962592079e26e703b6c3fb/Logo_DunkNation.png)


### Diseño de modelo de datos [maximo 250 palabras]

![Figura 3: Diagrama de datos [05/06/23]](https://github.com/niiltomas/EDA2/blob/0d9fb3faeab103ee184d269cf52be65274f68a84/Diagrama%20definitivo%20de%20datos%20Dunk%20Nation.png)

Empezando por el inicio, podemos o bien hacer un nuevo registro o registrar 20 usuarios. Después hacemos un login, y si el nombre de usuario y contraseña son correctos podremos entrar al submenú del usuario. Dentro del menú podremos decidir si bien cerramos la sesión, enviamos una solicitud de amistad a otro usuario que esté registrado (si el nombre es correcto, si no nos direccionará al submenú). Además también tendremos otro botón para gestionar las solicitudes recibidas (si para añadir amigo o no para no serlo) y finalmente un botón para crear una publicación, y escribir el lugar del encuentro en el que vamos a jugar a baloncesto. Y este es el funcionamiento de nuestra red social.


### Descripción y procesamiento del conjunto de datos [maximo 250 palabras]

En esta subsección presentamos una visión detallada de los conjuntos de datos utilizados en nuestra red social, como los hemos obtenido y procesado.
El primer conjunto de datos utilizado, es un archivo de datos de 20 usuarios archivo_users.csv que creamos nosotros mismos de forma totalmente aleatoria. Cada usuario tiene asignado un nombre, edad, contraseña, email y ciudad. Para procesar el archivo nos decantamos por escanear cada línea del archivo por separado, y añadiendo cada usuario a una lista enlazada.


El segundo conjunto de datos utilizado, es el registro de un nuevo usuario (este paso se puede realizar varias veces con el fin de tener varios usuarios registrados a la plataforma) el cual se obtuvo mediante una introducción manual de los datos del usuario y se escaneó mediante la función scanf(). A continuación los guardamos en la lista enlazada de tipo ListNode llamada newNode almacenando así todos los usuarios con sus datos correspondientes.

## **ENLACE VIDEO** 

Teniamos problemas para subir el video a GitHub, por lo que lo hemos subido a Google Drive.
https://drive.google.com/file/d/1En3SOwcYVIFPzVsgpC4UqS2GnnWc5FmU/view?usp=sharing

## **REFERENCIAS**
MindMeister [4/06/23]. Recuperado de https://www.mindmeister.com/es

OpenAI [s.f.]. Recuperado de https://chat.openai.com/ 

The Pentamollis Project. [01/05/23]. Windows GUI Programming with C/C++ (Win32API) | Part -1 |Creating a window. YouTube. Recuperado de https://youtu.be/8GCvZs55mEM 

The Pentamollis Project. [01/05/23]. Windows GUI Programming with C/C++ (Win32API) | Part -2 |Menus. YouTube. Recuperado de https://youtu.be/7K6HCeog09c 

The Pentamollis Project. [01/05/23]. Windows GUI Programming with C/C++ (Win32API) | Part -3 |Edit and Static controls. YouTube. Recuperado de https://youtu.be/9JMQkUOhW1s 

The Pentamollis Project. [01/05/23]. Windows GUI Programming with C/C++ (Win32API) | Part -4 |Button Control and Demo Application. YouTube. Recuperado de https://youtu.be/o2NkH5xxDQs 

The Pentamollis Project. [01/05/23]. Windows GUI Programming with C/C++ (Win32API) | Part -5 |Working with Images (Bitmaps). YouTube. Recuperado de https://youtu.be/PTjlGiCvYZU 

The Pentamollis Project. [01/05/23]. Windows GUI Programming with C/C++ (Win32API) | Part -6 |The Message box Dialog. YouTube. Recuperado de https://youtu.be/R7RvaQR-mm0 

