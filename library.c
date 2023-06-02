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
void AddMenus(HWND);
void AddControls(HWND);
void registerDialogClass(HINSTANCE);
void displayDialog(HWND);
int read_users_file(User*);
void printuser(ListNode*);

HMENU hMenu;
HWND hLogo,hEdit;
HBITMAP hLogoImage,hGenerateImage;

ListNode* userList = NULL;
ListNode* current;
ListNode* searchUser(char* , int, ListNode* );
ListNode* searchUser2(char*, ListNode* );

///no tocar nada de aqui, ya que es la configuracion de la ventana principal
///es la equivalencia al main "normal" pero es el main utilizado para abrir una ventana
/// : ##################################################################################################
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst,LPSTR arg , int ncmdshow) {
    WNDCLASSW wc={0};
    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
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
    User users[20];
    ListNode* current = userList;
    ListNode* foundUser = NULL;
    char username[20];
    int aux,password, num_users=0;
    FILE *fp=fopen("archivo_users.csv","r");
    switch(msg)
    {
        case WM_COMMAND: ///ÉS EL MISSATGE
            switch(wp)
            {
                case FILE_MENU_EXIT:
                    aux= MessageBoxW(hwnd,L"Estas segur que vols sortir?",L"EXIT",MB_YESNO|MB_ICONEXCLAMATION);
                    if (aux==IDYES)
                    {
                        DestroyWindow(hwnd);
                    }
                    break;

                case ARCHIVO_USERS:///leer archivo que contiene 20 los datos de 20 usuarios
                    ///abrir fichero
                    num_users=read_users_file(users);
                    for (int i = 0; i < num_users; i++) {
                        printf("Usuario %d:\n", i+1);
                        printf(" - Nombre de usuario: %s\n", users[i].username);
                        printf(" - Edad: %d\n", users[i].age);
                        printf(" - password: %d\n", users[i].password);
                        printf(" - Correo electronico: %s\n", users[i].email);
                        printf(" - Ciudad: %s\n", users[i].city);
                        ///printf(" - Preferencia 1: %s\n", user[i].preferences[0]);
                        /// printf(" - Preferencia 2: %s\n", user[i].preferences[1]);

                    }
                    break;
                case GENERATE_BUTTON:///sitio donde se tendrá que poner el codigo de mostrar todos los usuarios
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
                    MessageBox(hwnd, "click aceptar, then enter preferences separated by spaces", "New player", MB_OK);
                    for (int i = 0; i < MAX_PREFERENCES; i++) {
                        scanf("%s", user->preferences[i]);
                    }
                    ///prints para comprobar
                    printf("Username: %s\n", user->username);
                    printf("Age: %d\n", user->age);
                    printf("Password: %d\n", user->password);
                    printf("Email: %s\n", user->email);
                    printf("City: %s\n", user->city);
                    for (int i = 0; i < MAX_PREFERENCES; i++) {
                        printf("- %s\n", user->preferences[i]);
                    }

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
                    ///Para operar con un usuario primero tenemos que buscar por el nombre de usuario a la persona, para ello,
                    /// la tarea es implementar un algoritmo de búsqueda que recorra la lista de usuarios hasta encontrarlo
                    /// y luego mostrar el submenú para ese usuario. Si no se encuentra el usuario, mostrar un mensaje de error.
                    MessageBox(hwnd, "click aceptar, then enter username and a numerical password (separated by space)", "login", MB_OK);
                    scanf("%s %d", username, &password);///escaneamos el nombre de usuario y password
                    foundUser = searchUser(username,password, userList); ///recorremos los usuarios inscritos
                    if (foundUser != NULL) {
                        printf("Usuario encontrado:\n");
                        printuser(foundUser);///función que imprime los datos del user
                        displayDialog(hwnd);///se abre la ventana emergente del usuario donde hay la gestión de las solicitudes de amistad
                    }
                    else {
                        printf("Usuario no encontrado:\n");
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
    /// los ultimos parametros nos van a dirigir a las funciones correspondientes que se encuentran en el menu principal
    CreateWindowW(L"Button",L"LOGIN",WS_VISIBLE |WS_CHILD|WS_BORDER,100,50,98,38,hwnd,(HMENU)LOGIN,0,0);
    CreateWindowW(L"Button",L"NEW PLAYER",WS_VISIBLE |WS_CHILD|WS_BORDER ,250,50,98,38,hwnd,(HMENU)NEW_PLAYER,0,0);
    CreateWindowW(L"Button",L"ALL PLAYERS",WS_VISIBLE |WS_CHILD|WS_BORDER,100,120,98,38,hwnd,(HMENU)GENERATE_BUTTON,0,0);
    CreateWindowW(L"Button",L"USER_FILE",WS_VISIBLE |WS_CHILD|WS_BORDER,250,120,98,38,hwnd,(HMENU)ARCHIVO_USERS,0,0);
    CreateWindowW(L"Button",L"EXIT",WS_VISIBLE |WS_CHILD|WS_BORDER,100,190,248,38,hwnd,(HMENU)FILE_MENU_EXIT,0,0);
    hLogo=CreateWindowW(L"Static",NULL,WS_VISIBLE |WS_CHILD|SS_BITMAP,0,0,38,38,hwnd,0,0,0);
    SendMessageW(hLogo,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hLogoImage);
}

int read_users_file(User* user){///funció leer el archivo; parametros de entrada(nombre de archivo, user (struct USER) y ventana hwnd)
    int max_usuarios=20;
    FILE* fp=fopen("archivo_users.csv","r");
    if (fp == NULL) {///comprobamos que el fichero se haya abierto correctamente
        printf("Error al abrir el archivo\n");
        return 0;
    }

    char linea[MAX_CHAR];
    int i=0;
    while (fgets(linea, MAX_CHAR, fp) != NULL && i < max_usuarios) {
        char* token;
        token = strtok(linea, ",");

        strncpy(user[i].username, token, MAX_CHAR);
        token = strtok(NULL, ",");

        user[i].age = atoi(token);
        token = strtok(NULL, ",");

        user[i].password = atoi(token);
        token = strtok(NULL, ",");

        strncpy(user[i].email, token, MAX_CHAR);
        token = strtok(NULL, ",");

        strncpy(user[i].city, token, MAX_CHAR);
        token = strtok(NULL, ",");

        i++;
    }

    fclose(fp);
    return i;
}

FriendRequestQueue friendRequestsQueue;

LRESULT CALLBACK DialogProcedure(HWND hwnd,UINT msg, WPARAM wp, LPARAM lp)
{
    User* user= malloc(sizeof(User));
    ListNode* current = userList;
    ListNode* foundUser = NULL;
    char *username[20];
    switch(msg)
    {
        case WM_COMMAND:
            switch(wp)
            {
                case 1:
                    DestroyWindow(hwnd);
                    break;
                case 2:
                    // Mostrar las solicitudes pendientes
                    printf("Solicitudes de amistad pendientes:\n");
                    FriendRequestNode* currentNode = friendRequestsQueue.front;
                    while (currentNode != NULL) {
                        printf("De: %s\n", currentNode->request->sender->username);
                        currentNode = currentNode->next;
                    }
                    // Pedir al usuario que seleccione una solicitud para aceptar o denegar
                    printf("Ingresa el nombre de usuario del remitente para aceptar o denegar la solicitud: ");
                    scanf("%s", username);
                    // Buscar la solicitud en la cola
                    FriendRequestNode* requestNode = friendRequestsQueue.front;
                    FriendRequestNode* prevNode = NULL;
                    while (requestNode != NULL) {
                        if (strcmp(requestNode->request->sender->username, username) == 0) {
                            // Solicitud encontrada, mostrar los detalles y preguntar al usuario si desea aceptar o denegar
                            printf("Solicitud encontrada:\n");
                            printf("Remitente: %s\n", requestNode->request->sender->username);
                            printf("Edad: %d\n", requestNode->request->sender->age);
                            printf("Email: %s\n", requestNode->request->sender->email);
                            printf("Ciudad: %s\n", requestNode->request->sender->city);
                            printf("Preferencias:\n");
                            for (int i = 0; i < MAX_PREFERENCES; i++) {
                                printf("- %s\n", requestNode->request->sender->preferences[i]);
                            }
                            // Preguntar al usuario si desea aceptar o denegar la solicitud
                            printf("Aceptar (A) / Denegar (D): ");
                            char response;
                            scanf(" %c", &response);
                            if (response == 'A' || response == 'a') {
                                // Aceptar solicitud
                                printf("Solicitud de amistad aceptada.\n");
                                // Realizar las acciones necesarias para aceptar la solicitud

                                // Eliminar la solicitud de la cola
                                if (prevNode != NULL) {
                                    prevNode->next = requestNode->next;
                                } else {
                                    friendRequestsQueue.front = requestNode->next;
                                }
                                free(requestNode->request);
                                free(requestNode);
                                break;
                            } else if (response == 'D' || response == 'd') {
                                // Denegar solicitud
                                printf("Solicitud de amistad denegada.\n");
                                // Realizar las acciones necesarias para denegar la solicitud

                                // Eliminar la solicitud de la cola
                                if (prevNode != NULL) {
                                    prevNode->next = requestNode->next;
                                } else {
                                    friendRequestsQueue.front = requestNode->next;
                                }
                                free(requestNode->request);
                                free(requestNode);
                                break;
                            } else {
                                printf("Respuesta inválida. Inténtalo nuevamente.\n");
                            }
                        }
                        prevNode = requestNode;
                        requestNode = requestNode->next;
                    }
                    if (requestNode == NULL) {
                        printf("Solicitud no encontrada.\n");
                    }
                    break;

                case 3:
                    MessageBox(hwnd, "Haz clic en Aceptar y luego ingresa el nombre de usuario al que deseas enviar una solicitud", "Enviar solicitud de amistad", MB_OK);
                    scanf("%s", username);  // Escanea el nombre de usuario
                    foundUser = searchUser2(username, userList);  // Busca el usuario en la lista
                    if (foundUser != NULL) {
                        // Usuario encontrado, muestra los datos y abre la ventana emergente
                        printf("Usuario encontrado:\n");
                        printuser(foundUser);

                        // Mostrar un mensaje de confirmación
                        MessageBox(hwnd, "Solicitud de amistad enviada", "Confirmación", MB_OK | MB_ICONINFORMATION);
                    } else {
                        // Usuario no encontrado, muestra un mensaje de error
                        MessageBox(hwnd, "Usuario no encontrado", "Error", MB_OK | MB_ICONERROR);
                    }


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

void registerDialogClass(HINSTANCE hInst)///Mejor no tocar XD
{
    WNDCLASSW dialog={0};
    dialog.hbrBackground= (HBRUSH) COLOR_WINDOW;
    dialog.hCursor = LoadCursor (NULL,IDC_ARROW);
    dialog.hInstance=hInst;
    dialog.lpszClassName = L"login";
    dialog.lpfnWndProc = DialogProcedure;

    RegisterClassW(&dialog);

}
void displayDialog(HWND hwnd)///aqui es donde tienes que poner los botones
{
    /// posicion (x,y) en la ventana (en pixeles) i dimensiones (x,y)
    ///ventana emergente login
    HWND hDlg= CreateWindowW(L"login",L"LOGIN",WS_VISIBLE | WS_OVERLAPPEDWINDOW,400,400,500,300,hwnd,0,0,0);
    ///botón cerrar
    CreateWindowW(L"Button",L"Close",WS_VISIBLE|WS_CHILD,190,200,100,40,hDlg,(HMENU)1,NULL,NULL);

    ///boton para enviar una solicitud de amistad"
    CreateWindowW(L"Button",L" Enviar solicitud de amistad",WS_VISIBLE | WS_CHILD |WS_BORDER,20,20, 300,30,hDlg,(HMENU)2,NULL,NULL);

    ///boton para ver solicitudes pendientes de aceptar"
    CreateWindowW(L"Button",L"Solicitudes pendientes",WS_VISIBLE | WS_CHILD |WS_BORDER,20,70, 300,30,hDlg,(HMENU)3,NULL,NULL);

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


void printuser(ListNode*User){///función de impresión de usuarios
    printf(" - Nombre de usuario: %s\n", User->user->username);
    printf(" - Edad: %d\n", User->user->age);
    printf(" - Password: %d\n", User->user->password);
    printf(" - Correo electronico: %s\n", User->user->email);
    printf(" - Ciudad: %s\n", User->user->city);
    ///for (int i = 0; i < MAX_PREFERENCES; i++) {
    //        printf("- %s\n", User->user->preferences[i]);
    //    }
}

// Función para realizar una publicación
void realizarPublicacion(User* usuario, const char* contenido) {
    if (strlen(contenido) <= MAX_CARACTERES) {
        Publicacion* nuevaPublicacion = (Publicacion*)malloc(sizeof(Publicacion));
        strcpy(nuevaPublicacion->contenido, contenido);

        // Añadir la nueva publicación al timeline del usuario
        usuario->timeline = (Publicacion*)realloc(usuario->timeline, (usuario->numPublicaciones + 1) * sizeof(Publicacion));
        usuario->timeline[usuario->numPublicaciones] = *nuevaPublicacion;
        usuario->numPublicaciones++;

        printf("Publicación realizada con éxito.\n");
    } else {
        printf("La publicación excede el límite de caracteres permitidos (%d).\n", MAX_CARACTERES);
    }
}

// Función para eliminar una publicación del timeline
void eliminarPublicacion(User* usuario, int indice) {
    if (indice >= 0 && indice < usuario->numPublicaciones) {
        // Liberar la memoria de la publicación a eliminar
        free(usuario->timeline[indice].contenido);

        // Desplazar las publicaciones restantes para llenar el espacio vacío
        for (int i = indice; i < usuario->numPublicaciones - 1; i++) {
            usuario->timeline[i] = usuario->timeline[i + 1];
        }

        // Redimensionar el timeline para reflejar la eliminación
        usuario->timeline = (Publicacion*)realloc(usuario->timeline, (usuario->numPublicaciones - 1) * sizeof(Publicacion));
        usuario->numPublicaciones--;

        printf("Publicación eliminada con éxito.\n");
    } else {
        printf("Índice de publicación inválido.\n");
    }
}

// Función para revisar el timeline de un usuario
void revisarTimeline(const User* usuario) {
    printf("Timeline de %s:\n", usuario->username);
    for (int i = 0; i < usuario->numPublicaciones; i++) {
        printf("- %s\n", usuario->timeline[i].contenido);
    }
}

// Función para liberar la memoria del timeline
void liberarTimeline(User* usuario) {
    for (int i = 0; i < usuario->numPublicaciones; i++) {
        free(usuario->timeline[i].contenido);
    }
    free(usuario->timeline);
    usuario->timeline = NULL;
    usuario->numPublicaciones = 0;
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