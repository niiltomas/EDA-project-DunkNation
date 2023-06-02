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

LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);

///para incluir una función en el codigo antes se tiene que llamar aqui
void AddMenus(HWND);
void AddControls(HWND);
void registerDialogClass(HINSTANCE);
void displayDialog(HWND);
int read_users_file(const char*,User*,HWND);
void printuser(ListNode*);
void enqueueFriendRequest(User* sender, User* receiver);

HMENU hMenu;
HWND hLogo,hEdit;
HBITMAP hLogoImage,hGenerateImage;

ListNode* userList = NULL;
ListNode* current;
ListNode* searchUser(char*, int, ListNode* );
ListNode* searchUser2(char*, ListNode* );
FriendRequest* friendRequests = NULL;


///no tocar nada de aqui, ya que es la configuracion de la ventana principal
///es la equivalencia al main "normal" pero es el main utilizado para abrir una ventana
/// : ##################################################################################################
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst,LPSTR arg , int ncmdshow) {
    WNDCLASSW wc={0};
    wc.hbrBackground= (HBRUSH) COLOR_WINDOW;
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
    User* user= malloc(sizeof(User));
    ListNode* current = userList;
    ListNode* foundUser = NULL;
    char username[20],lol;
    int aux,password, num_users=0;
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
                    num_users=read_users_file("archivo_users.csv",user,hwnd);
                    for (int i = 0; i < num_users; i++) {
                        printf("Usuario %d:\n", i+1);
                        printf(" - Nombre de usuario: %s\n", user[i].username);
                        printf(" - Edad: %d\n", user[i].age);
                        printf(" - password: %d\n", user[i].password);
                        printf(" - Correo electronico: %s\n", user[i].email);
                        printf(" - Ciudad: %s\n", user[i].city);
                        printf(" - Preferencia 1: %s\n", user[i].preferences[0]);
                        printf(" - Preferencia 2: %s\n", user[i].preferences[1]);

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

                    ListNode* newNode = malloc(sizeof(ListNode)*2);  /// Crear un nuevo nodo para el usuario
                    newNode->user = user;
                    newNode->user->friendRequests = NULL;  // Inicializa la cola de solicitudes de amistad del nuevo usuario
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
                        foundUser->user->friendRequests = friendRequests;

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

int read_users_file(const char* file,User* user,HWND hwnd){///funció leer el archivo; parametros de entrada(nombre de archivo, user (struct USER) y ventana hwnd)
    FILE *fp=fopen(file,"r"); ///abrir fichero
    if (fp == NULL) {///comprobamos que el fichero se haya abierto correctamente
        MessageBox(hwnd, "Ha habido un error al abrir el archivo\n", "login", MB_OK);///ventana emergente en el menu principal
        printf("Error al abrir el archivo\n");
        return 0;
    }
    int i=0;
    printf("%s","fitxer obert correctament\n");
    while(fscanf(fp,"%[^,],%d,%d,%[^,],%[^,],%[^,],%[^,\n]\n",user[i].username,&user[i].password,&user[i].age,user[i].email,user[i].city,user[i].preferences[0],user[i].preferences[1])!=EOF){
        i++;
    }
    ///llegeix els parametres fins que troba una coma
    printf("%s","fitxer llegit correctament\n");

    fclose(fp);///cerramos el fichero
    return i; ///devolvemos el numero de usuarios
}


LRESULT CALLBACK DialogProcedure(HWND hwnd,UINT msg, WPARAM wp, LPARAM lp)
{
    User* user= malloc(sizeof(User));
    FriendRequest* currentRequest = NULL;
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
                case 2:
                    //printf("\n aqui és on s'haurà d'anar gestionant totes les solicituds d'amistat rebudes\n");
                    printf(foundUser->user->username);
                    printf(foundUser->user->friendRequests);
                    currentRequest = foundUser->user->friendRequests;
                    while (currentRequest != NULL) {
                        printf("Solicitud de amistad:\n");
                        printf("Enviada por: %s\n", currentRequest->sender);
                        currentRequest = currentRequest->next;
                    }
                    break;
                case 3:
                    //printf("\n aqui és on s'haurà de fer el codi per enviar les solicituds damistat\n");
                    MessageBox(hwnd, "Haz clic en Aceptar y luego ingresa el nombre de usuario al que deseas enviar una solicitud", "Enviar solicitud de amistad", MB_OK);
                    scanf("%s", username);  // Escanea el nombre de usuario
                    foundUser = searchUser2(username, userList);  // Busca el usuario en la lista
                    if (foundUser != NULL) {
                        // Usuario encontrado, muestra los datos y abre la ventana emergente
                        printf("Usuario encontrado:\n");
                        printuser(foundUser);

                        User *receiverUser;
                        enqueueFriendRequest(foundUser->user, receiverUser);

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
    CreateWindowW(L"Button",L"Solicitudes pendientes",WS_VISIBLE | WS_CHILD |WS_BORDER,20,20, 300,30,hDlg,(HMENU)2,NULL,NULL);

    ///boton para ver solicitudes pendientes de aceptar"
    CreateWindowW(L"Button",L"Enviar solicitud de amistad",WS_VISIBLE | WS_CHILD |WS_BORDER,20,70, 300,30,hDlg,(HMENU)3,NULL,NULL);

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
    for (int i = 0; i < MAX_PREFERENCES; i++) {
        printf("- %s\n", User->user->preferences[i]);
    }
}

void enqueueFriendRequest(User* sender, User* receiver) {
    FriendRequest* newRequest = malloc(sizeof(FriendRequest));
    //newRequest->sender = sender->username;
    strcpy(newRequest->sender, sender->username);
    newRequest->next = NULL;
    if (friendRequests == NULL) {
        friendRequests = newRequest;
    } else {
        FriendRequest* current = friendRequests;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newRequest;
    }
}