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
int read_users_file(const char*,User*,HWND);
void cargarlogo();

HMENU hMenu;
HWND hLogo;
HBITMAP hLogoImage,hGenerateImage;

ListNode* userList = NULL;
ListNode* current;

ListNode* searchUserByUsername(char* username, ListNode* userList) {
    ListNode* current = userList;
    while (current != NULL) {
        if (strcmp(current->user->username, username) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

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
    ListNode* head = NULL;
    char username[20];
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
                        printf(" - Correo electronico: %s\n", user[i].email);
                        printf(" - Ciudad: %s\n", user[i].city);
                        printf(" - Preferencia 1: %s\n", user[i].preferences[0]);
                        printf(" - Preferencia 2: %s\n", user[i].preferences[1]);

                    }
                    break;
                case GENERATE_BUTTON:///sitio donde se tendrá que poner el codigo de mostrar todos los usuarios
                    // Recorrer la lista de usuarios e imprimir sus datos
                    current = userList;
                    while (current != NULL) {
                        printf("Username: %s\n", current->user->username);
                        printf("Age: %d\n", current->user->age);
                        printf("Email: %s\n", current->user->email);
                        printf("City: %s\n", current->user->city);
                        for (int i = 0; i < MAX_PREFERENCES; i++) {
                            printf("- %s\n", current->user->preferences[i]);
                        }
                        printf("\n");
                        current = current->next;
                    }
                    break;
                case NEW_PLAYER:///en esta parte hay donde se escanea la parte del new player (la entrada es por consola)
                    MessageBox(hwnd, "click aceptar, then enter name age email and city(separated by space)", "New player", MB_OK);
                    scanf("%s %d %s %s", user->username, &user->age, user->email, user->city);
                    MessageBox(hwnd, "click aceptar, then enter preferences separated by spaces", "New player", MB_OK);
                    for (int i = 0; i < MAX_PREFERENCES; i++) {
                        scanf("%s", user->preferences[i]);
                    }
                    ///prints para comprobar
                    printf("Username: %s\n", user->username);
                    printf("Age: %d\n", user->age);
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
                    MessageBox(hwnd, "click aceptar, then enter username and a numerical password(separated by space)", "login", MB_OK);
                    scanf("%s %d",username,&password);
                    printf("\nuser: %s\n",username);
                    printf("\npassword: %d\n",password);

                    ListNode* userList = NULL;
                    // Código para agregar usuarios a la lista userList

                    // Ejemplo de búsqueda por nombre de usuario
                    char searchUsername[20];
                    printf("Ingrese el nombre de usuario a buscar: ");
                    scanf("%s", searchUsername);

                    ListNode* foundUser = searchUserByUsername(searchUsername, userList);
                    if (foundUser != NULL) {
                        printf("Usuario encontrado:\n");
                        printf(" - Nombre de usuario: %s\n", foundUser->user->username);
                        printf(" - Edad: %d\n", foundUser->user->age);
                        printf(" - Correo electrónico: %s\n", foundUser->user->email);
                        printf(" - Ciudad: %s\n", foundUser->user->city);
                        printf(" - Preferencia 1: %s\n", foundUser->user->preferences[0]);
                        printf(" - Preferencia 2: %s\n", foundUser->user->preferences[1]);

                        // Mostrar el submenú aquí

                    } else {
                        printf("Usuario no encontrado.\n");
                    }

                    return 0;
            }

            break;
        case WM_CREATE: ///moment en el què la finestra s'ha creat i tot seguit hi afegim els menus etc. a la finestra
            cargarlogo();
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

void AddMenus(HWND hwnd){ ///exit de arriba a la izquierda
    hMenu = CreateMenu();

    /// Crear el elemento de menu "File"
    HMENU hFileMenu = CreateMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");

    // Crear elementos de submenu en "File"
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

    ///Crear el elemento de  Submenu
    HMENU hSubMenu = CreateMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Submenu");

    // Agregar elementos de submenú en Submenu
    const UINT_PTR SUBMENU_ITEM_2;
    AppendMenu(hSubMenu, MF_STRING, SUBMENU_ITEM_2 , "Submenu Item 1");
    AppendMenu(hSubMenu, MF_STRING, SUBMENU_ITEM_2 , "Submenu Item 2");

    // Add the rest of the menu items
    AppendMenu(hMenu, MF_STRING, GENERATE_BUTTON, "All Players");
    AppendMenu(hMenu, MF_STRING, ARCHIVO_USERS, "User File");

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
    hLogo=CreateWindowW(L"Static",NULL,WS_VISIBLE |WS_CHILD|SS_BITMAP,0,200,38,38,hwnd,(HMENU)FILE_MENU_EXIT,0,0);
    SendMessageW(hLogo,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hLogoImage);
}

int read_users_file(const char* file,User* user,HWND hwnd){///funció leer el archivo; parametros de entrada(nombre de archivo, user (struct USER) y ventana hwnd)
    FILE *fp=fopen(file,"r"); ///abrir fichero
    if (fp == NULL) {
        MessageBox(hwnd, "Ha habido un error al abrir el archivo\n", "login", MB_OK);///ventana emergente en el menu principal
        printf("Error al abrir el archivo\n");
        return 0;
    }
    int i=0;
    printf("%s","fitxer obert correctament\n");
    while(fscanf(fp,"%[^,],%d,%[^,],%[^,],%[^,],%[^,\n]\n",user[i].username,&user[i].age,user[i].email,user[i].city,user[i].preferences[0],user[i].preferences[1])!=EOF){
        i++;
    }
    ///llegeix els parametres fins que troba una coma
    printf("%s","fitxer llegit correctament\n");

    fclose(fp);///cerramos el fichero
    return i; ///devolvemos el numero de usuarios
}

void cargarlogo(){
    hLogoImage=(HBITMAP)LoadImageW(NULL,L"logo2.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
}

LRESULT CALLBACK DialogProcedure(HWND hwnd,UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg)
    {
        case WM_COMMAND:
            switch(wp)
            {
                case 1:
                    DestroyWindow(hwnd);
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
    ///ventana emergente login
    HWND hDlg= CreateWindowW(L"login",L"LOGIN",WS_VISIBLE | WS_OVERLAPPEDWINDOW,400,400,500,300,hwnd,0,0,0);
    ///botón cerrar
    CreateWindowW(L"Button",L"Close",WS_VISIBLE|WS_CHILD,190,200,100,40,hDlg,(HMENU)1,NULL,NULL);
    ///a partir de aqui, lo de las coordenadas i dimensiones es importante, y lkos tipos, botones, static,,,... el video lo explica perfectamente, vale la pena
    ///cuadro de texto: "introduce el nombre de usuario"
    CreateWindowW(L"Static",L"Introduce el nombre de usuario:",WS_VISIBLE | WS_CHILD |WS_BORDER,20,20, 300,30,hDlg,(HMENU)1,NULL,NULL);/// posicion (x,y) en la ventana (en pixeles) i dimensiones (x,y)
    CreateWindowW(L"Edit",L"...",WS_VISIBLE |WS_CHILD |WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL |ES_AUTOHSCROLL,20,70,100,50,hDlg,(HMENU)NEW_PLAYER,0,0);
    ///cuadro de texto: "introduce la contraseña"
    CreateWindowW(L"Static",L"Introduce la contraseña del usuario:",WS_VISIBLE | WS_CHILD |WS_BORDER,20,130, 300,30,hDlg,(HMENU)1,NULL,NULL);
    CreateWindowW(L"Edit",L"",WS_VISIBLE |WS_CHILD |WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL |ES_AUTOHSCROLL,20,170,100,50,hDlg,(HMENU)GENERATE_BUTTON,0,0);
}