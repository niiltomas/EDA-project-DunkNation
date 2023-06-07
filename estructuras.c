#define MAX_PREFERENCES 2
#define MAX_CARACTERES 120
#define MAX_LENGTH 1000
#define TABLE_SIZE 100
#define MAX_FRIENDS 50

// Definición de la estructura de publicación
typedef struct {
    char contenido[MAX_CARACTERES];
    struct Publicacion* siguiente_publi;
} Publicacion;

//Estructura del usuario
typedef struct {
    char username[50];
    int age;
    char email[50];
    char city[50];
    char j1[50];
    char j2[50];
    char preferences[MAX_PREFERENCES][50];
    int password;
    Publicacion* timeline;
    int numPublicaciones;
    struct User** friends;
    int num_friends;
    struct User** friend_requests;
    int num_friend_requests;
}User;

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


typedef struct Node {
    char palabra[MAX_LENGTH];
    int conteo;
    struct Node* siguiente;
} Node;

// Estructura de una solicitud de amistad
typedef struct {
    User* sender;
    User* receiver;
} FriendRequest;

// Nodo de la cola de solicitudes de amistad
typedef struct FriendRequestNode {
    FriendRequest* request;
    User* sender; // Remitente de la solicitud
    User* receiver; // Receptor de la solicitud
    struct FriendRequestNode* next;
} FriendRequestNode;

// Cola de solicitudes de amistad
typedef struct {
    FriendRequestNode* front;
    FriendRequestNode* rear;
} FriendRequestQueue;

typedef struct {
    Node* tabla[TABLE_SIZE];
} HashTable;


typedef struct QueueNode {
    User* user;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
} Nodo;

typedef struct {
    Nodo* inicio;
    Nodo* fin;
} Lista;

struct NodoDiccionario {
    char palabra[MAX_LENGTH];
    int conteo;
    struct NodoDiccionario* siguiente;
};
