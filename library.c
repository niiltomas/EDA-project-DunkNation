#include "library.h"
#include <stdio.h>
#include <windows.h>
#include <stddef.h>
#include <wchar.h>
#include <stdlib.h>
#include "estructuras.c"


#define FILE_MENU_EXIT 3
#define GENERATE_BUTTON 5
#define LOGIN 6
#define NEW_PLAYER 7
#define MAX_PREFERENCES 2
#define ARCHIVO_USERS 8
#define SORTUSERS 9
#define MAX_CHAR 100
LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);

///para incluir una función en el codigo antes se tiene que llamar aqui
//////////////////////////////////////////////
void AddMenus(HWND);
void AddControls(HWND);
void registerDialogClass(HINSTANCE);
void displayDialog(HWND);
void printuser(ListNode*);
void print_user_list(ListNode*);
int read_users_file(User*, ListNode**);
//////////////////////////////////////////////
Publicacion* crearPublicacion(const char*);
void mostrarPublicaciones(User*);
void agregarPublicacion(User*,Publicacion*);
//////////////////////////////////////////////
void initializeQueue(QueueF* queue);
int isQueueEmpty(QueueF* queue);
int isQueueFull(QueueF* queue);
void enqueue(QueueF* queue, User user);
User dequeue(QueueF* queue);
void displayFriendList(User* friends, int count);
//////////////////////////////////////////////

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
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst,LPSTR arg , int ncmdshow) {
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
LRESULT CALLBACK WindowProcedure(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp) {
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
                    // Recorrer la lista de usuarios e imprimir sus datos
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
                    MessageBox(hwnd, "click aceptar, then enter your first favourite player and the second (separeted by space) ", "New player", MB_OK);
                    scanf("%s %s", user->j1,user->j2);
                    ///prints para comprobar
                    printf("Username: %s\n", user->username);
                    printf("Age: %d\n", user->age);
                    printf("Password: %d\n", user->password);
                    printf("Email: %s\n", user->email);
                    printf("City: %s\n", user->city);
                    printf("Jugador 1: %s\n", user->j1);
                    printf("Jugador 2: %s\n", user->j2);


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
                    }
                    break;

                case LOGIN: ///parte donde se escanea los parametros del user
                    MessageBox(hwnd, "click aceptar, then enter username and password(separated by space)", "LOGIN", MB_OK);
                    printf("Introduce nombre de usuario y contrasenya: ");
                    scanf("\n%s %d", username, &password);
                    foundUser = searchUser(username, password, userList);
                    if (foundUser != NULL) {
                        printf("Usuario encontrado:\n");
                        printuser(foundUser);
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


void AddControls(HWND hwnd) {
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



FriendRequestQueue friendRequestsQueue = { NULL, NULL };
FriendRequestQueue sentRequestsQueue = { NULL, NULL };


LRESULT CALLBACK DialogProcedure(HWND hwnd,UINT msg, WPARAM wp, LPARAM lp)
{
    User* user= malloc(sizeof(User));
    user->timeline = NULL;
    user->numPublicaciones = 0;
    //    user->timeline=NULL;
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
                    // Ver solicitudes de amistad recibidas
                    printf("Solicitudes de amistad recibidas:\n");
                    FriendRequestNode* currentNode = friendRequestsQueue.front;
                    while (currentNode != NULL) {
                        printf("De: %s\n", currentNode->request->sender->username);
                        currentNode = currentNode->next;
                    }
                    break;
                }

                case 3:{
                    // Enviar solicitud de amistad
                    printf("Introduce el nombre de usuario al que quieres enviar la solicitud: ");
                    scanf("%s", username);
                    foundUser = searchUser2(username, userList);
                    if (foundUser != NULL) {
                        // Crear la solicitud de amistad
                        FriendRequest* request = malloc(sizeof(FriendRequest));
                        request->sender = user;
                        request->receiver = foundUser->user;

                        // Crear el nodo de la solicitud de amistad
                        FriendRequestNode* requestNode = malloc(sizeof(FriendRequestNode));
                        requestNode->request = request;
                        requestNode->sender = user;
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


                case 4:///Anshpreet aqui tiene que ir tu parte de diccionarios la línea de free(user->timeline); te borrará los datos, así que tu codigo tiene que ir entremedio
                    printf("--- Publica  ---\n");

                    for (int i = 0; i < 11; i++) {
                        char contenido[MAX_CARACTERES];

                        printf("Ingresa el contenido de la publicacion %d: ", i + 1);
                        fgets(contenido, MAX_CARACTERES, stdin);

                        // Eliminar el salto de línea al final del contenido
                        contenido[strcspn(contenido, "\n")] = '\0';

                        // Crear la publicación
                        Publicacion* publicacion = (Publicacion*)malloc(sizeof(Publicacion));
                        strncpy(publicacion->contenido, contenido, MAX_CARACTERES);
                        publicacion->contenido[MAX_CARACTERES - 1] = '\0';

                        // Agregar la publicación al timeline del usuario
                        agregarPublicacion(user, publicacion);

                        printf("Publicacion realizada con exito.\n");
                    }

                    // Mostrar todas las publicaciones del usuario
                    mostrarPublicaciones(user);
                    ///inicio diccionario (Tabla Hash)
                    ///ten en cuenta que el diccionario tiene que leer las palabras, entonces devolverá el top 3 de palabras que mas salgan





                    ///fin diccionario (Tabla Hash)
                    // Liberar memoria
                    free(user->timeline);
                    break;
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
    CreateWindowW(L"Button",L"Diccionario con publicación",WS_VISIBLE | WS_CHILD |WS_BORDER,20,130, 300,30,hDlg,(HMENU)4,NULL,NULL);


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







int calcularHash(char* palabra) {
    int hash = 0;
    int i = 0;

    while (palabra[i] != '\0') {
        hash += palabra[i];
        i++;
    }

    return hash % TABLE_SIZE;
}

void inicializarTabla(HashTable* tabla) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        tabla->tabla[i] = NULL;
    }
}

void insertarPalabra(HashTable* tabla, char* palabra) {
    int indice = calcularHash(palabra);

    Node* nodo = tabla->tabla[indice];

    while (nodo != NULL) {
        if (strcmp(nodo->palabra, palabra) == 0) {
            nodo->conteo++;
            return;
        }

        nodo = nodo->siguiente;
    }

    Node* nuevoNodo = (Node*)malloc(sizeof(Node));
    strcpy(nuevoNodo->palabra, palabra);
    nuevoNodo->conteo = 1;
    nuevoNodo->siguiente = tabla->tabla[indice];
    tabla->tabla[indice] = nuevoNodo;
}

///**************************************** Inicio declaracion de funciones de imprimir usuarios de una lista, imprimir usuarios,  leer archivo de usuarios,*************
///**************************************************  agregar_publicacion y mostrar publicación   **********************************************************************
void print_user_list(ListNode* llista) {
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
    if (fp == NULL) {
        printf("Error al abrir el archivo\n");
        return 0;
    }

    char linea[MAX_CHAR];
    int i = 0;
    while (fgets(linea, MAX_CHAR, fp) != NULL && i < max_usuarios) {
        char* token;
        token = strtok(linea, ",");

        User* newUser = (User*)malloc(sizeof(User)); ///creamos el nuevo usuario
        if (newUser == NULL) {
            printf("Error al asignar memoria para el nuevo usuario\n");
            fclose(fp);
            return 0;
        }

        strncpy(newUser->username, token, MAX_CHAR);// lee los datos del nombre
        token = strtok(NULL, ",");

        newUser->age = atoi(token);// lee los datos de la edad
        token = strtok(NULL, ",");

        newUser->password = atoi(token);// lee los datos de la contraseña
        token = strtok(NULL, ",");

        strncpy(newUser->email, token, MAX_CHAR);// lee los datos del email
        token = strtok(NULL, ",");

        strncpy(newUser->city, token, MAX_CHAR);// lee los datos de la ciudad
        token = strtok(NULL, ",");

        strncpy(newUser->j1, token, MAX_CHAR);// lee los datos del email
        token = strtok(NULL, ",");
        strncpy(newUser->j2, token, MAX_CHAR);// lee los datos del email
        token = strtok(NULL, ",");
        strncpy(newUser->posicion, token, MAX_CHAR);// lee los datos del email
        token = strtok(NULL, ",");

        ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));// Crear un nuevo nodo de lista
        if (newNode == NULL) {
            printf("Error al asignar memoria para el nuevo nodo de lista\n");
            free(newUser);
            fclose(fp);
            return 0;
        }


        newNode->user = newUser;// Asignamos el usuario al nodo
        newNode->next = *llista;// Asignamos el siguiente nodo al actual
        *llista= newNode;// Actualizamos el puntero de la lista al nuevo nodo

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
            // Comparar los nombres sin distinguir entre mayúsculas y minúsculas
            if (strcasecmp(ptr1->user->username, ptr1->next->user->username) > 0) {
                // Intercambiar los usuarios entre nodos para lograr el ordenamiento
                User* temp = ptr1->user;
                ptr1->user = ptr1->next->user;
                ptr1->next->user = temp;
                swapped = 1;  // Indicar que se realizó un intercambio
            }

            ptr1 = ptr1->next;  // Avanzar al siguiente nodo
        }

        lptr = ptr1;  // Marcar el último nodo ordenado
    } while (swapped);  // Repetir hasta que no se realicen intercambios

    fclose(fp); ///cerramos el fichero
    return i; ///devolvemos el numero de usuarios leídos
}

//aqui es donde se controla y se guardan las publicaciones. Estas se almacenan aqui usuario->timeline[i].contenido
void agregarPublicacion(User* usuario, Publicacion* publicacion) {
    usuario->timeline = (Publicacion*)realloc(usuario->timeline, (usuario->numPublicaciones + 1) * sizeof(Publicacion));
    usuario->timeline[usuario->numPublicaciones] = *publicacion;
    usuario->numPublicaciones++;
}

// Función para mostrar todas las publicaciones del usuario
void mostrarPublicaciones(User* usuario) {
    printf("\nTodas las publicaciones del usuario:\n");
    for (int i = 0; i < usuario->numPublicaciones; i++) {
        printf("%d. %s\n", i + 1, usuario->timeline[i].contenido);
    }
}
///**********************************************************************    FIN    ************************************************************************************


void inicializar(Lista* lista) {
    lista->inicio = NULL;
    lista->fin = NULL;
}

void insertar(Lista* lista, int dato) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = nuevoNodo;
        lista->fin = nuevoNodo;
    } else {
        lista->fin->siguiente = nuevoNodo;
        lista->fin = nuevoNodo;
    }
}

void mostrar(Lista* lista) {
    Nodo* actual = lista->inicio;

    while (actual != NULL) {
        printf("%d ", actual->dato);
        actual = actual->siguiente;
    }
    printf("\n");
}

void liberar(Lista* lista) {
    Nodo* actual = lista->inicio;
    Nodo* siguiente = NULL;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    lista->inicio = NULL;
    lista->fin = NULL;
}

////////////////////////////////////////////////////



////////////////////////////////////////////////////////
void initializeQueue(QueueF* queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
}

int isQueueEmpty(QueueF* queue) {
    return (queue->count == 0);
}

int isQueueFull(QueueF* queue) {
    return (queue->count == MAX_FRIENDS);
}

void enqueue(QueueF* queue, User user) {
    if (isQueueFull(queue)) {
        printf("La cola de solicitudes de amistad está llena.\n");
        return;
    }

    queue->rear = (queue->rear + 1) % MAX_FRIENDS;
    queue->friendList[queue->rear] = user;
    queue->count++;
}

User dequeue(QueueF* queue) {
    User emptyUser;
    strcpy(emptyUser.username, "");

    if (isQueueEmpty(queue)) {
        printf("La cola de solicitudes de amistad está vacía.\n");
        return emptyUser;
    }

    User user = queue->friendList[queue->front];
    queue->front = (queue->front + 1) % MAX_FRIENDS;
    queue->count--;

    return user;
}

void displayFriendList(User* friends, int count) {
    if (count == 0) {
        printf("No tienes amigos en tu lista aún.\n");
        return;
    }

    printf("Lista de amigos aceptados:\n");
    for (int i = 0; i < count; i++) {
        printf("- %s\n", friends[i].username);
    }
}
////////////////////////////////////////////////////////

// Función para enviar una solicitud de amistad
void enviarSolicitud(User* remitente, User* destinatario) {
    // Aquí puedes implementar la lógica para enviar la solicitud
    printf("Solicitud enviada: %s -> %s\n", remitente->username, destinatario->username);
}

// Función para liberar la memoria de la lista de usuarios
void liberarUsuarios(ListNode* listaUsuarios) {
    ListNode* temp;
    while (listaUsuarios != NULL) {
        temp = listaUsuarios;
        listaUsuarios = listaUsuarios->next;
        free(temp->user->timeline);
        free(temp->user);
        free(temp);
    }
}