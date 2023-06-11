#define MAX_PREFERENCES 2
#define MAX_CARACTERES 120
#define MAX_LENGTH 1000
#define TABLE_SIZE 100
#define MAX_FRIENDS 50
#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

///Estructura de publicación que contiene una cadena que representa
/// el contenido de la publicación y un puntero a la siguiente publicación
/// en la lista.
typedef struct {
    char contenido[MAX_CARACTERES];
    struct Publicacion* siguiente_publi;
} Publicacion;

typedef struct {
    char username[50];///Una cadena que representa el nombre de usuario del usuario. Tiene una longitud máxima de 50 caracteres.
    int age;///Un entero que representa la edad del usuario.
    int password;///Un entero que representa la contraseña del usuario.
    char email[50];///String que representa el correo electrónico del usuario. Tiene una longitud máxima de 50 caracteres.
    char city[50];///String que representa la ciudad del usuario. Tiene una longitud máxima de 50 caracteres.
    char j1[50];///juadaor 1 favvorito
    char j2[50];///juadaor 2 favvorito
    char posicion[50];///posicion favorita
    Publicacion* timeline;///Un puntero a una publicación que representa la línea de tiempo del usuario.
    int numPublicaciones;///Un entero que representa el número de publicaciones que ha realizado el usuario.
    struct User** friends;///Un arreglo de punteros a usuarios que representan los amigos del usuario.
    int num_friends;///Un entero que representa el número de amigos del usuario.
    struct User** friend_requests;///Un arreglo de punteros a usuarios que representan las solicitudes de amistad que ha recibido el usuario.
    int num_friend_requests;///Un entero que representa el número de solicitudes de amistad que ha recibido el usuario.
}User;
///nodo de lista vinculada que contiene un puntero a una estructura de usuario y un puntero al siguiente nodo de la lista.
typedef struct ListNode {
    User* user;
    struct ListNode* next;
} ListNode;

typedef struct {
    User friendList[MAX_FRIENDS];
    int front;
    int rear;
    int count;
} QueueF;

///Esta es una definición de estructura para un nodo de lista enlazada que contiene una string y un número entero.
typedef struct Node {
    char palabra[MAX_LENGTH];
    int conteo;
    struct Node* siguiente;
} Node;

///Solicitud de amistad contiene punteros al emmisor y al receptor de una solicitud de amistad.
typedef struct {
    User* sender;
    User* receiver;
} FriendRequest;

///Nodo de la cola de solicitudes de amistad
typedef struct FriendRequestNode {
    FriendRequest* request;
    User* sender; // Remitente de la solicitud
    User* receiver; // Receptor de la solicitud
    struct FriendRequestNode* next;
} FriendRequestNode;

///Cola de solicitudes de amistad
typedef struct {
    FriendRequestNode* front;
    FriendRequestNode* rear;
} FriendRequestQueue;

typedef struct {
    Node* tabla[TABLE_SIZE];
} HashTable;
///Nodo de la cola de usuarios
typedef struct QueueNode {
    User* user;
    struct QueueNode* next;
} QueueNode;
///Cola de usuarios
typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;
///Nodo de la cola de publicaciones
typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
} Nodo;

///Cola de publicaciones
typedef struct Node2 {
    char palabra[MAX_LENGTH];
    int conteo;
    struct Node2* siguiente;
} Node2;
///Lista de publicaciones
typedef struct {
    Node2* inicio;
    Node2* fin;
} Lista;

///Nodo de la cola de publicaciones
typedef struct {
    char data;
    struct NODE* next;
} NODE;
///Cola de publicaciones
typedef struct {
    NODE* top;
} Stack;