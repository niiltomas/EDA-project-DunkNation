#define MAX_PREFERENCES 2
#define MAX_CARACTERES 120
// Definición de la estructura de publicación
typedef struct {
    char contenido[MAX_CARACTERES + 1];
} Publicacion;
//Estructura del usuario
typedef struct {
    char username[50];
    int age;
    char email[50];
    char city[50];
    char preferences[MAX_PREFERENCES][50];
    int password;
    Publicacion* timeline;
    int numPublicaciones;
}User;
typedef struct ListNode {
    User* user;
    struct ListNode* next;
} ListNode;



