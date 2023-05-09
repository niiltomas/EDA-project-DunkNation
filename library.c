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

LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);

///para incluir una función en el codigo antes se tiene que llamar aqui
void AddMenus(HWND);
void AddControls(HWND);


HMENU hMenu;

ListNode* userList = NULL;
ListNode* current;

///no tocar nada de aqui, ya que es la configuracion de la ventana principal
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
    char username[20];
    int aux,password;
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
                case GENERATE_BUTTON:///sitio donde se tendrá que poner el codigo de mostrar todos los usuarios
                    // Recorrer la lista de usuarios e imprimir sus datos
                    ///ListNode* current = userList;
                    while (current != NULL) {
                        printf("Username: %s\n", current->user->username);
                        printf("Age: %d\n", current->user->age);
                        printf("Email: %c\n", current->user->email);
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


                    ///user = malloc(sizeof(User)); // Asignar memoria para el usuario
                    ///scanf("%s %d %c %s", user->username, &user->age, &user->email, user->city); // Leer datos del usuario desde la consola
                    ///for (int i = 0; i < MAX_PREFERENCES; i++) {
                    ///scanf("%s", user->preferences[i]);
                    ///}
                    ListNode* newNode = malloc(sizeof(ListNode));  // Crear un nuevo nodo para el usuario
                    newNode->user = user;
                    newNode->next = NULL;
                    if (userList == NULL) { // Agregar el nuevo nodo a la lista
                        userList = newNode; // La lista está vacía, el nuevo nodo es el primer nodo
                    } else {
                        current = userList;
                        while (current->next != NULL) { // La lista no está vacía, agregar el nuevo nodo al final
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

void AddMenus(HWND hwnd){ ///exit de arriba a la izquierda
    hMenu = CreateMenu();
    AppendMenu(hMenu,MF_STRING,FILE_MENU_EXIT,"Exit");
    SetMenu(hwnd,hMenu);

}

void AddControls(HWND hwnd) {
    ///botones del main
    CreateWindowW(L"Button",L"LOGIN",WS_VISIBLE |WS_CHILD|WS_BORDER,100,50,98,38,hwnd,(HMENU)LOGIN,0,0);
    CreateWindowW(L"Button",L"NEW PLAYER",WS_VISIBLE |WS_CHILD|WS_BORDER ,250,50,98,38,hwnd,(HMENU)NEW_PLAYER,0,0);
    CreateWindowW(L"Button",L"ALL PLAYERS",WS_VISIBLE |WS_CHILD|WS_BORDER,100,120,98,38,hwnd,(HMENU)GENERATE_BUTTON,0,0);
    CreateWindowW(L"Button",L"EXIT",WS_VISIBLE |WS_CHILD|WS_BORDER,250,120,98,38,hwnd,(HMENU)FILE_MENU_EXIT,0,0);

}





///otros para mas adelante si tenemos que guardar los valores del user
// Copy user preferences to User structure
///for (int i = 0; i < MAX_PREFERENCES; i++) {
///strncpy(user->preferences[i], preferences[i], sizeof(user->preferences[i]) - 1);
///user->preferences[i][sizeof(user->preferences[i]) - 1] = '\0';
