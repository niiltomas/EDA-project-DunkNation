#include <stdio.h>
#include <windows.h>
#include <stddef.h>
#include <wchar.h>
#include <stdlib.h>
#include "estructuras.c"
#include "library.h"
#include <stdbool.h>



#define FILE_MENU_EXIT 3
#define GENERATE_BUTTON 5
#define LOGIN 6
#define NEW_PLAYER 7
#define ARCHIVO_USERS 8
#define MAX_CHAR 100

LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);

///para incluir una función en el codigo antes se tiene que llamar aqui
//////////////////////////////////////////////
void AddMenus(HWND);///funcion para añadir los menus
void AddControls(HWND);///funcion para añadir los controles
void registerDialogClass(HINSTANCE);///funcion para registrar la clase del dialog
void displayDialog(HWND);///funcion para mostrar el dialog
void printuser(ListNode*);///funcion para imprimir los datos de un usuario
void print_user_list(ListNode*);///funcion para imprimir la lista de usuarios
int read_users_file(User*, ListNode**);///funcion para leer el archivo de usuarios
//////////////////////////////////////////////
Publicacion* crearPublicacion(const char*);
void mostrarPublicaciones(User*);
void agregarPublicacion(User*,Publicacion*);
//////////////////////////////////////////////
void inicializarDiccionario();///funcion para inicializar el diccionario
Node* buscarPalabra(char* palabra);///funcion para buscar una palabra en el diccionario
void insertarPalabra(char* palabra);///funcion para insertar una palabra en el diccionario
int compararConteo(const void* a, const void* b);///funcion para comparar el conteo de dos palabras
void mostrarPalabrasFrecuentes();///funcion para mostrar las palabras frecuentes
void procesarPublicacion(char* contenido);///funcion para procesar una publicacion
//////////////////////////////////////////////
void eliminar_solicitud_amistad(FriendRequestNode*, FriendRequestQueue*);///funcion para eliminar una solicitud de amistad
//////////////////////////////////////////////

/// Función para inicializar la pila
void initializeStack(Stack*);

///Función para comprobar si la pila está vacía
bool isEmpty(Stack*);


///Función para empujar un elemento a la pila
void push(Stack* ,char);

/// Función para sacar un elemento de la pila
char pop(Stack*);


///Función para comprobar si la dirección de correo electrónico tiene solo un símbolo "@"
bool validateEmail(char*);




////*****************************************
User* currentUser = NULL;

HMENU hMenu;
HWND hLogo,hEdit;
HBITMAP hLogoImage,hGenerateImage;

ListNode* userList = NULL;
ListNode* llista = NULL;
ListNode* current;
ListNode* searchUser(char* , int, ListNode* );
ListNode* searchUser2(char*, ListNode* );

///configuracion de la ventana principal
///es la equivalencia al main "normal" pero es el main utilizado para abrir una ventana
/// : ##################################################################################################
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst,LPSTR arg , int ncmdshow) {///funcion principal
    WNDCLASSW wc={0};
    wc.hbrBackground= (HBRUSH) (COLOR_WINDOW-1);
    wc.hCursor = LoadCursor (NULL,IDC_ARROW);
    wc.hInstance=hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;
    if(!RegisterClassW(&wc)) {
        return -1;
    }
    registerDialogClass(hInst);
    CreateWindowW(L"myWindowClass",L"DUNK NATION",WS_OVERLAPPEDWINDOW | WS_VISIBLE, 300, 100,500,500,NULL,NULL,NULL,NULL);

    MSG msg = {0};
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

///#########################################################################
LRESULT CALLBACK WindowProcedure(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp) {///funcion que se encarga de la ventana principal
    User* user = malloc(sizeof(User));

    ///ListNode* current = userList;
    ListNode* foundUser = NULL;
    char username[20];
    int aux,password;
    FILE *fp=fopen("archivo_users.csv","r");

    User usuaris[22];
    ListNode* llista = NULL;
    int numUsers;
    usuaris->timeline = NULL;
    usuaris->numPublicaciones = 0;
    switch(msg)
    {
        case WM_COMMAND: ///ÉS EL MISSATGE
            switch(wp)
            {

                case FILE_MENU_EXIT: ///case para cerrar la ventana principal del main
                    aux= MessageBoxW(hwnd,L"Estas segur que vols sortir?",L"EXIT",MB_YESNO|MB_ICONEXCLAMATION);
                    if (aux==IDYES)
                    {
                        DestroyWindow(hwnd);
                    }
                    break;

                case ARCHIVO_USERS:///leer archivo que contiene los datos de 20 usuarios
                    printf("hola");
                    numUsers = read_users_file(usuaris, &llista);
                    printf("Se leyeron %d usuarios\n", numUsers);
                    print_user_list(llista);
                    ///a partir de aqui liberamos la memoria
                    ListNode* currentNode = llista;
                    while (currentNode != NULL) {
                        llista = currentNode->next;
                        free(currentNode->user);
                        free(currentNode);
                        currentNode = llista;
                    }
                    break;
                case GENERATE_BUTTON:///codigo que muestra todos los usuarios
                    ///Recorrer la lista de usuarios e imprimir sus datos
                    current = userList;////
                    while (current != NULL) {
                        printuser(current);///imprime los datos del usuario
                        printf("\n");
                        current = current->next;
                    }
                    break;
                case NEW_PLAYER:///en esta parte hay donde se escanea la parte del new player (la entrada es por consola)
                    MessageBox(hwnd, "click aceptar, then enter name age password email and city(separated by space)", "New player", MB_OK);
                    scanf("%s %d %d %s %s", user->username, &user->age, &user->password,user->email, user->city);
                    MessageBox(hwnd, "click aceptar, then enter your first favourite player and the second (separeted by space) and position", "New player", MB_OK);
                    scanf("%s %s %s", user->j1,user->j2,user->posicion);
                    if (validateEmail(user->email)) {
                        printf("La dirección de correo electrónico es válida.\n");
                        printf("Username: %s\n", user->username);
                        printf("Age: %d\n", user->age);
                        printf("Password: %d\n", user->password);
                        printf("Email: %s\n", user->email);
                        printf("City: %s\n", user->city);
                        printf("Jugador 1: %s\n", user->j1);
                        printf("Jugador 2: %s\n", user->j2);
                        printf("Posicion: %s\n", user->posicion);

                        ListNode* newNode = malloc(sizeof(ListNode));  /// Crear un nuevo nodo para el usuario
                        newNode->user = user;
                        newNode->next = NULL;
                        if (userList == NULL) { /// Agregar el nuevo nodo a la lista
                            userList = newNode; /// La lista está vacía, el nuevo nodo es el primer nodo
                        } else {
                            current = userList;
                            while (current->next != NULL) { /// La lista no está vacía, agregar el nuevo nodo al final
                                current = current->next;
                            }
                            current->next = newNode;
                        }///
                    } else {
                        printf("La dirección de correo electrónico no es válida.\n");
                    }
                    ///prints para comprobar
                    break;

                case LOGIN: ///parte donde se escanea los parametros del user
                    MessageBox(hwnd, "click aceptar, then enter username and a numerical password(separated by space)", "LOGIN", MB_OK);
                    printf("Introduce nombre de usuario y contrasenya: ");
                    scanf("\n%s %d", username, &password);
                    foundUser = searchUser(username, password, userList);
                    if (foundUser != NULL) {
                        printf("Usuario encontrado:\n");
                        printuser(foundUser);
                        currentUser = foundUser->user;
                        displayDialog(hwnd);
                    }
                    else {
                        printf("Usuario no encontrado.\n");
                    }


                    break;

            }

            break;
        case WM_CREATE: ///moment en el què la finestra s'ha creat i tot seguit hi afegim els menus etc. a la finestra
            AddMenus(hwnd);
            AddControls(hwnd);
            break;
        case WM_DESTROY: ///cierra la ventana cuando se llama a este comando
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hwnd,msg,wp,lp);

    }

}


void AddMenus(HWND hwnd) {///exit de arriba a la izquierda
    hMenu = CreateMenu();
    AppendMenu(hMenu,MF_STRING,FILE_MENU_EXIT,"Exit");
    SetMenu(hwnd, hMenu);
}


void AddControls(HWND hwnd) {///añade los botones y demas a la ventana principal
    ///botones del main
    ///primer parametro indica si es un boton (interactuable) o fijo, el segungo el nombre a imprimir al boton, el siguiente bordes, visible,... ,
    ///los cuatro siguientes hacen referencia a las dimensiones en pixeles (x,y) (tercer,cuarto paramtro) y localización de los botones (x,y) (primero,segundo).
    /// LOS PARAMETROS QUE ACOMPAÑAN AL (HMENU) NOS LLAVARAN A LOS DIFERENTES CASES
    CreateWindowW(L"Button",L"LOGIN",WS_VISIBLE |WS_CHILD|WS_BORDER,100,50,108,38,hwnd,(HMENU)LOGIN,0,0);
    CreateWindowW(L"Button",L"NEW PLAYER",WS_VISIBLE |WS_CHILD|WS_BORDER ,250,50,128,38,hwnd,(HMENU)NEW_PLAYER,0,0);
    CreateWindowW(L"Button",L"ALL PLAYERS",WS_VISIBLE |WS_CHILD|WS_BORDER,100,120,108,38,hwnd,(HMENU)GENERATE_BUTTON,0,0);
    CreateWindowW(L"Button",L"PRINT USER_FILE",WS_VISIBLE |WS_CHILD|WS_BORDER,250,120,128,38,hwnd,(HMENU)ARCHIVO_USERS,0,0);
    CreateWindowW(L"Button",L"EXIT",WS_VISIBLE |WS_CHILD|WS_BORDER,100,190,278,38,hwnd,(HMENU)FILE_MENU_EXIT,0,0);
    ///este fragmento de código es un intento fallido de insertar una imagen en la pagina principal
    hLogo=CreateWindowW(L"Static",NULL,WS_VISIBLE |WS_CHILD|SS_BITMAP,0,0,38,38,hwnd,0,0,0);
    SendMessageW(hLogo,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hLogoImage);
    ///
}



FriendRequestQueue friendRequestsQueue = { NULL, NULL };///cola de solicitudes de amistad
FriendRequestQueue sentRequestsQueue = { NULL, NULL };///cola de solicitudes de amistad enviadas

LRESULT CALLBACK DialogProcedure(HWND hwnd,UINT msg, WPARAM wp, LPARAM lp)///funcion que se encarga de la ventana de dialog
{
    User* user= malloc(sizeof(User));
    user->timeline = NULL;
    user->numPublicaciones = 0;

    ListNode* current = userList;
    ListNode* foundUser = NULL;

    char username[20];


    switch(msg)
    {
        case WM_COMMAND:
            switch(wp)
            {

                case 1:
                    DestroyWindow(hwnd);
                    break;

                case 2:{
                    ///Ver solicitudes de amistad recibidas
                    printf("Solicitudes de amistad recibidas:\n");
                    FriendRequestNode* currentNode =friendRequestsQueue.front;
                    while (currentNode != NULL) {
                        if (strcmp(currentNode->request->receiver->username, currentUser->username) == 0) {///comparem si els noms són els mateixos,
                            /// ja que a la llista on es guarden les solicituds estan totes barrejades, aleshores si coincideix el nom del receptor amb el nom d'usuari es permet de gestionar la solicitud
                            ///si no no
                            printf("De: %s\n", currentNode->request->sender->username);///imprimimos por pantalla el emisor de la solicitud de amistad
                            printf("Aceptar solicitud? (s/n): ");

                            char si_o_no;///variable per a guardar si o no
                            scanf(" %c",&si_o_no); ///escaneamos la respuesta del receptor sobre si quiere aceptar la solicitud o no
                            ///puede introducir 's' o 'S'
                            if (si_o_no == 's' || si_o_no == 'S') {
                                printf("Solicitud aceptada.\n");

                                eliminar_solicitud_amistad(currentNode, &friendRequestsQueue);///eliminamos la solicitud una vez ya se ha aceptado
                            } else {///el usuario ha rechazado la solicitud
                                printf("Solicitud rechazada.\n");
                            }
                            if (currentNode->next == NULL)break; ///si no hay siguiente, que salga
                            currentNode= currentNode->next; ///entonces
                        }else{
                            printf("Esta solicitud no es para ti \n");
                            currentNode = currentNode->next;///el usuario en question pasa a ser el siguiente
                        }

                        }
                    break;
                    }

                case 3:{
                    ///Enviar solicitud de amistad
///Solicita al usuario que
///ingrese el nombre de usuario de la persona a la que desea enviar la solicitud, verifique si el nombre de usuario no es el
///igual que el nombre de usuario del usuario actual, busca al usuario en la lista de usuarios, crea un amigo
///objeto de solicitud, crea un nodo de solicitud de amistad, agrega el nodo de solicitud de amistad a la solicitud de amistad
///queue e imprime un mensaje que indica si la solicitud se envió correctamente o no.
                    printf("Introduce el nombre de usuario al que quieres enviar la solicitud: ");
                    scanf("%s", username);
                    if (strcmp(currentUser->username,username) == 0) {
                        printf("No puedes enviar una solicitud de amistad a ti mismo.\n");
                        break;
                    }
                    foundUser = searchUser2(username, userList);
                    if (foundUser != NULL) {
                        // Crear la solicitud de amistad
                        FriendRequest* request = malloc(sizeof(FriendRequest));
                        request->sender = currentUser;
                        request->receiver = foundUser->user;

                        // Crear el nodo de la solicitud de amistad
                        FriendRequestNode* requestNode = malloc(sizeof(FriendRequestNode));
                        requestNode->request = request;
                        request->sender = currentUser;
                        requestNode->receiver = foundUser->user;
                        requestNode->next = NULL;

                        // Agregar la solicitud a la cola de solicitudes de amistad
                        if (friendRequestsQueue.front == NULL) {
                            friendRequestsQueue.front = requestNode;
                            friendRequestsQueue.rear = requestNode;
                        } else {
                            friendRequestsQueue.rear->next = requestNode;
                            friendRequestsQueue.rear = requestNode;
                        }

                        printf("Solicitud de amistad enviada a: %s\n", foundUser->user->username);
                    } else {
                        printf("Usuario no encontrado.\n");
                    }
                    break;
                }


                case 4:{
/// usuario publique 10 publicaciones y luego muestre las más frecuentes
///palabras usadas en esos mensajes con uso de tabla de hash
                    printf("--- Publica  ---\n");

                    inicializarDiccionario();

                    char publicacion[MAX_LENGTH];
                    printf("Ingrese 10 publicaciones:\n");

                    for (int i = 0; i < 11; i++) {
                        printf("Publicacion %d: ", i + 1);
                        fgets(publicacion, sizeof(publicacion), stdin);

                        ///Eliminar el carácter de nueva línea si está presente
                        char* newline = strchr(publicacion, '\n');
                        if (newline != NULL) {
                            *newline = '\0';
                        }

                        procesarPublicacion(publicacion);
                    }

                    ///Mostrar las palabras más frecuentes
                    mostrarPalabrasFrecuentes();
                    ///Liberar memoria
                    free(user->timeline);

                    break;
                }

            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        default:
            return DefWindowProcW(hwnd,msg,wp,lp);
    }
}


void registerDialogClass(HINSTANCE hInst){///Configuración de la ventana emergente del submenu

    WNDCLASSW dialog={0};
    dialog.hbrBackground= (HBRUSH) (COLOR_WINDOW-1); ///Para cambiar el color
    dialog.hCursor = LoadCursor (NULL,IDC_ARROW);///caracteristicas del cursor
    dialog.hInstance=hInst;
    dialog.lpszClassName = L"login"; ///Nombre de la ventana
    dialog.lpfnWndProc = DialogProcedure;

    RegisterClassW(&dialog);

}

void displayDialog(HWND hwnd){///configuracion de los botones del submenu del usuario

    /// posicion (x,y) en la ventana (en pixeles) i dimensiones (x,y)
    ///ventana emergente login
    HWND hDlg= CreateWindowW(L"login",L"LOGIN",WS_VISIBLE | WS_OVERLAPPEDWINDOW,400,400,500,300,hwnd,0,0,0);
    ///botón cerrar para cerrar la ventana de usuario login
    CreateWindowW(L"Button",L"Close",WS_VISIBLE|WS_CHILD,190,200,100,40,hDlg,(HMENU)1,NULL,NULL);

    ///boton para ver solicitudes pendientes de aceptar"
    CreateWindowW(L"Button",L"Solicitudes pendientes",WS_VISIBLE | WS_CHILD |WS_BORDER,20,70, 300,30,hDlg,(HMENU)2,NULL,NULL);

    ///boton para enviar una solicitud de amistad"
    CreateWindowW(L"Button",L" Enviar solicitud de amistad",WS_VISIBLE | WS_CHILD |WS_BORDER,20,20, 300,30,hDlg,(HMENU)3,NULL,NULL);

    ///boton para publicar publicaciones"
    CreateWindowW(L"Button",L"Publicar (con diccionario)",WS_VISIBLE | WS_CHILD |WS_BORDER,20,130, 300,30,hDlg,(HMENU)4,NULL,NULL);


}

ListNode* searchUser(char* username,int password, ListNode* userList) {///función que busca el usuario dentro de una lista donde hay todos los usuarios.
///El algoritmo utilizado es sequencial, ya que los usuarios no estan ordenados, por lo que va a recorrer toda la lista de usuarios hasta encontrarlo
    ListNode* current = userList;
    while (current != NULL) {
        /// Comprueba si el nombre de usuario y la contraseña coinciden con el usuario actual de la lista de users
        if (strcmp(current->user->username, username) == 0 && current->user->password == password) {
            return current;/// Devolver el usuario actual si se encuentra
        }
        current = current->next;///si no lo encontramos, pasamos al siguiente
    }
    return NULL;///Devuelve NULL si no encontró el usuario
}

ListNode *searchUser2(char *username, ListNode *userList) {///función que busca el usuario dentro de una lista donde hay todos los usuarios.
///El algoritmo utilizado es sequencial, ya que los usuarios no estan ordenados, por lo que va a recorrer toda la lista de usuarios hasta encontrarlo
    ListNode *current = userList;
    while (current != NULL) {
        /// Comprueba si el nombre de usuario y la contraseña coinciden con el usuario actual de la lista de users
        if (strcmp(current->user->username, username) == 0) {
            return current;/// Devolver el usuario actual si se encuentra
        }
        current = current->next;///si no lo encontramos, pasamos al siguiente
    }
    return NULL;///Devuelve NULL si no encontró el usuario
}


///**************************************** Inicio declaracion de funciones de imprimir usuarios de una lista, imprimir usuarios,  leer archivo de usuarios,*************
///**************************************************  agregar_publicacion y mostrar publicación   **********************************************************************
void print_user_list(ListNode* llista) {///función de impresión de usuarios
    printf("Lista de usuarios:\n");

    ListNode* currentNode = llista;
    while (currentNode != NULL) {
        User* user = currentNode->user;
        printf("Username: %s\n", user->username);
        printf("Age: %d\n", user->age);
        printf("Password: %d\n", user->password);
        printf("Email: %s\n", user->email);
        printf("City: %s\n", user->city);
        printf("jugador 1: %s\n", user->j1);
        printf("jugador 2: %s\n", user->j2);
        printf("Posicion favorita: %s\n", user->posicion);

        currentNode = currentNode->next;
    }
}

void printuser(ListNode*User){///función de impresión de usuarios
    printf(" - Nombre de usuario: %s\n", User->user->username);
    printf(" - Edad: %d\n", User->user->age);
    printf(" - Password: %d\n", User->user->password);
    printf(" - Correo electronico: %s\n", User->user->email);
    printf(" - Ciudad: %s\n", User->user->city);
    printf(" - Jugador 1: %s\n", User->user->j1);
    printf(" - Jugador 2: %s\n", User->user->j2);


}

int read_users_file(User* user, ListNode** llista) {
    int max_usuarios = 20;
    FILE* fp = fopen("archivo_users.csv", "r");
    if (fp == NULL) {///si no se puede abrir el archivo
        printf("Error al abrir el archivo\n");
        return 0;
    }

    char linea[MAX_CHAR];
    int i = 0;
    while (fgets(linea, MAX_CHAR, fp) != NULL && i < max_usuarios) {///lee el archivo de usuarios
        char* token;
        token = strtok(linea, ",");///separa los datos por comas

        User* newUser = (User*)malloc(sizeof(User)); ///creamos el nuevo usuario
        if (newUser == NULL) {
            printf("Error al asignar memoria para el nuevo usuario\n");
            fclose(fp);
            return 0;
        }

        strncpy(newUser->username, token, MAX_CHAR);///lee los datos del nombre
        token = strtok(NULL, ",");

        newUser->age = atoi(token);///lee los datos de la edad
        token = strtok(NULL, ",");

        newUser->password = atoi(token);///lee los datos de la contraseña
        token = strtok(NULL, ",");

        strncpy(newUser->email, token, MAX_CHAR);///lee los datos del email
        token = strtok(NULL, ",");

        strncpy(newUser->city, token, MAX_CHAR);///lee los datos de la ciudad
        token = strtok(NULL, ",");

        strncpy(newUser->j1, token, MAX_CHAR);///lee los datos del email
        token = strtok(NULL, ",");
        strncpy(newUser->j2, token, MAX_CHAR);///lee los datos del email
        token = strtok(NULL, ",");
        strncpy(newUser->posicion, token, MAX_CHAR);///lee los datos del email
        token = strtok(NULL, ",");

        ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));///Crear un nuevo nodo de lista
        if (newNode == NULL) {
            printf("Error al asignar memoria para el nuevo nodo de lista\n");
            free(newUser);
            fclose(fp);
            return 0;
        }


        newNode->user = newUser;///Asignamos el usuario al nodo
        newNode->next = *llista;///Asignamos el siguiente nodo al actual
        *llista= newNode;///Actualizamos el puntero de la lista al nuevo nodo

        i++;
    }
     /// Ordenar la lista por orden alfabético utilizando el nombre (ordenamiento burbuja)
    ///declaramos las variables y listas enlazadas que utilizaremos, además de inicalizarlas
    int swapped;
    ListNode* ptr1;
    ListNode* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *llista;

        while (ptr1->next != lptr) {
            ///Comparar los nombres sin distinguir entre mayúsculas y minúsculas
            if (strcasecmp(ptr1->user->username, ptr1->next->user->username) > 0) {
                ///Intercambiar los usuarios entre nodos para lograr el ordenamiento
                User* temp = ptr1->user;
                ptr1->user = ptr1->next->user;
                ptr1->next->user = temp;
                swapped = 1;  ///Indicar que se realizó un intercambio
            }

            ptr1 = ptr1->next;  ///Avanzar al siguiente nodo
        }

        lptr = ptr1;  ///Marcar el último nodo ordenado
    } while (swapped);  ///Repetir hasta que no se realicen intercambios

    fclose(fp); ///cerramos el fichero
    return i; ///devolvemos el numero de usuarios leídos
}

///aqui es donde se controla y se guardan las publicaciones. Estas se almacenan aqui usuario->timeline[i].contenido
void agregarPublicacion(User* usuario, Publicacion* publicacion) {
    usuario->timeline = (Publicacion*)realloc(usuario->timeline, (usuario->numPublicaciones + 1) * sizeof(Publicacion));
    usuario->timeline[usuario->numPublicaciones] = *publicacion;///guardamos la publicación en el timeline del usuario
    usuario->numPublicaciones++;
}

///Función para mostrar todas las publicaciones del usuario
void mostrarPublicaciones(User* usuario) {
    printf("\nTodas las publicaciones del usuario:\n");
    for (int i = 0; i < usuario->numPublicaciones; i++) {
        printf("%d. %s\n", i + 1, usuario->timeline[i].contenido);
    }
}
///**********************************************************************    FIN    ************************************************************************************


/////////////////////////////////////////////////////////
Lista* diccionario;

///Función para inicializar el diccionario
void inicializarDiccionario() {///inicializamos el diccionario
    diccionario = malloc(sizeof(Lista));///reservamos memoria para el diccionario
    diccionario->inicio = NULL;///inicializamos el inicio
    diccionario->fin = NULL;///inicializamos el fin del diccionario
}

///Función para buscar una palabra en el diccionario
Node* buscarPalabra(char* palabra) {
    Node* nodoActual = diccionario->inicio;
    while (nodoActual != NULL) {///recorremos el diccionario
        if (strcmp(nodoActual->palabra, palabra) == 0) {///si encontramos la palabra, devolvemos el nodo
            return nodoActual;
        }
        nodoActual = nodoActual->siguiente;///si no encontramos la palabra, avanzamos al siguiente nodo
    }
    return NULL;
}

///Función para insertar una palabra en el diccionario
void insertarPalabra(char* palabra) {
    Node* nodoExistente = buscarPalabra(palabra);///buscamos la palabra en el diccionario
    if (nodoExistente != NULL) {///si la palabra ya existe, aumentamos su conteo
        nodoExistente->conteo++;
    } else {
        Node* nuevoNodo = malloc(sizeof(Node));///si la palabra no existe, la insertamos en el diccionario
        strcpy(nuevoNodo->palabra, palabra);
        nuevoNodo->conteo = 1;
        nuevoNodo->siguiente = NULL;

        if (diccionario->inicio == NULL) {///si el diccionario está vacío, el nuevo nodo será el inicio y el fin
            diccionario->inicio = nuevoNodo;
            diccionario->fin = nuevoNodo;
        } else {///si el diccionario no está vacío, el nuevo nodo será el nuevo fin
            diccionario->fin->siguiente = nuevoNodo;
            diccionario->fin = nuevoNodo;
        }
    }
}

///Función de comparación para ordenar las palabras por conteo
int compararConteo(const void* a, const void* b) {
    Node* nodoA = *(Node**)a;
    Node* nodoB = *(Node**)b;
    return nodoB->conteo - nodoA->conteo;
}

///Función para mostrar las palabras más frecuentes
void mostrarPalabrasFrecuentes() {
    int numPalabras = 0;///inicializamos  numPalabras a 0, que se usará para contar
                        ///el numero de palabras en el diccionario
    Node* nodoActual = diccionario->inicio;
    while (nodoActual != NULL) { ///recorremos el diccionario
        numPalabras++;
        nodoActual = nodoActual->siguiente;///avanzamos al siguiente nodo
    }

    Node** arregloPalabras = malloc(numPalabras * sizeof(Node*));///creamos un arreglo de nodos
    nodoActual = diccionario->inicio;
    int i = 0;
    while (nodoActual != NULL) {///recorremos el diccionario
        arregloPalabras[i] = nodoActual;///asignamos el nodo actual al arreglo
        nodoActual = nodoActual->siguiente;
        i++;
    }

    qsort(arregloPalabras, numPalabras, sizeof(Node*), compararConteo);///ordenamos el arreglo de palabras

    int numMostradas = numPalabras > 10 ? 10 : numPalabras;///mostramos las 10 palabras mas frecuentes
    printf("Las 10 palabras mas frecuentes son:\n");///recorremos el arreglo de palabras
    for (i = 0; i < numMostradas; i++) {
        printf("%s: %d\n", arregloPalabras[i]->palabra, arregloPalabras[i]->conteo);///mostramos la palabra y su conteo
    }

    free(arregloPalabras);///liberamos el arreglo de palabras
}

/// función para procesar una publicación y contar las palabras
void procesarPublicacion(char* contenido) {
    char* token = strtok(contenido, " ");
    while (token != NULL) {///recorremos la publicacion
        insertarPalabra(token);///insertamos la palabra en el diccionario
        token = strtok(NULL, " ");
    }
}

/////////////////////////////////////////////////////////

///esta funcion elimina la solicitud de amistad
void eliminar_solicitud_amistad(FriendRequestNode* solicitud, FriendRequestQueue* cola) {
    if (cola->front ==
        solicitud) { ///primero y antetodo comprobamos si la solicitud que queremos eliminar es el primer de la cola
        cola->front = solicitud->next; ///actualitzem el front per a que passi al seguent
        if (cola->rear == solicitud) {/// Si el node que s'ha d'eliminar és l'últim, actualitzem el punter a NULL
            cola->rear = NULL;
        }
    } else {
        ///si no es el primer busquem el node anterior
        FriendRequestNode *current = cola->front;
        while (current != NULL && current->next != solicitud) {
            current = current->next;
        }
        ///al trobar-lo actualitzem la seguent solicitud amb el punter next
        if (current != NULL) {
            current->next = solicitud->next;
            if (cola->rear ==
                solicitud) {/// si la solicitud a eliminar és la última a eliminar, atualitzem el punter rear a la sol. anterior
                if (cola->rear == solicitud) {
                    cola->rear = current;
                }
            }
        }
        free(solicitud->request);
        free(solicitud);///alliberem la memòria
    }
}

///comprovación con pila si EMAIL ES CORRECTO O NO


///Función para inicializar la pila
void initializeStack(Stack* stack) {
    stack->top = NULL;
}

///Función para comprobar si la pila está vacía
bool isEmpty(Stack* stack) {
    return (stack->top == NULL);
}

///Función para empujar un elemento a la pila
void push(Stack* stack, char data) {
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

///Función para sacar un elemento de la pila
char pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("La pila está vacía.\n");
        exit(EXIT_FAILURE);
    }

    NODE* temp = stack->top;
    char data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

///Función para comprobar si la dirección de correo electrónico tiene solo un símbolo "@"
bool validateEmail(char* email) {
    Stack stack;
    initializeStack(&stack);

    ///Recorre cada carácter de la cadena de correo electrónico
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            // Si encuentra un símbolo "@", lo empuja a la pila
            push(&stack, email[i]);
        }
    }

    ///Comprueba si la pila tiene exactamente un símbolo "@"
    if (isEmpty(&stack) || stack.top->next != NULL) {
        return false;
    } else {
        return true;
    }
}

