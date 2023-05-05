#include "library.h"
#include <stdio.h>
#include <windows.h>
#include <stddef.h>
#include <wchar.h>
#include <stdlib.h>
#include "codigo primcipal.h"
#include "codigo primcipal.c"


#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
///#define CHANGE_TITLE 4
#define GENERATE_BUTTON 5
#define LOGIN 6

///int main() {
///menu();
///return 0;
///}

LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);


void AddMenus(HWND);
void AddControls(HWND);
void registerDialogClass(HINSTANCE);
void displayDialog(HWND);


HMENU hMenu;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst,LPSTR arg , int ncmdshow)
{
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
    CreateWindowW(L"myWindowClass",L"DUNK NATION",WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100,500,500,
                  NULL,NULL,NULL,NULL);

    MSG msg = {0};
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
LRESULT CALLBACK WindowProcedure(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{
    int aux;
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
                case GENERATE_BUTTON:
                    break;
                case LOGIN:
                    MessageBoxW(NULL,L"NAME AND PASSWORD",L"LOGIN",MB_OK );
                    break;
            }

            break;
        case WM_CREATE: ///moment en el què la finestra s'ha creat i tot seguit hi afegim els menus etc. a la finestra
            displayDialog(hwnd);
            AddMenus(hwnd);
            AddControls(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hwnd,msg,wp,lp);

    }

}

void AddMenus(HWND hwnd)
{
    hMenu = CreateMenu();

    AppendMenu(hMenu,MF_STRING,FILE_MENU_EXIT,"Exit");

    SetMenu(hwnd,hMenu);

}

void AddControls(HWND hwnd)
{
    ///botons del main
    CreateWindowW(L"Button",L"LOGIN",WS_VISIBLE |WS_CHILD|WS_BORDER,100,50,98,38,hwnd,(HMENU)LOGIN,0,0);
    CreateWindowW(L"Button",L"NEW PLAYER",WS_VISIBLE |WS_CHILD|WS_BORDER ,250,50,98,38,hwnd,(HMENU)GENERATE_BUTTON,0,0);
    CreateWindowW(L"Button",L"ALL PLAYERS",WS_VISIBLE |WS_CHILD|WS_BORDER,100,120,98,38,hwnd,(HMENU)GENERATE_BUTTON,0,0);
    CreateWindowW(L"Button",L"EXIT",WS_VISIBLE |WS_CHILD|WS_BORDER,250,120,98,38,hwnd,(HMENU)FILE_MENU_EXIT,0,0);

    ///boton login
}

LRESULT CALLBACK DialogProcedure(HWND hwnd,UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        default:
            return DefWindowProcW(hwnd,msg,wp,lp);

    }
}

void registerDialogClass(HINSTANCE hInst)
{
    WNDCLASSW dialog={0};
    dialog.hbrBackground= (HBRUSH) COLOR_WINDOW;
    dialog.hCursor = LoadCursor (NULL,IDC_CROSS);
    dialog.hInstance=hInst;
    dialog.lpszClassName = L"myDialogClass";
    dialog.lpfnWndProc = DialogProcedure;

    RegisterClassW(&dialog);

}
void displayDialog(HWND hwnd)
{
    CreateWindowW(L"myDialogClass",L"Dialog",WS_VISIBLE | WS_OVERLAPPEDWINDOW,400,400,200,200,hwnd,0,0,0);

}