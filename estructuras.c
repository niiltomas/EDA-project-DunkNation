#define MAX_PREFERENCES 2

//Estructura del usuario
typedef struct {
    char username[50];
    int age;
    char email[50];
    char city[50];
    char preferences[MAX_PREFERENCES][50];
    int password;
}User;

typedef struct ListNode {
    User* user;
    struct ListNode* next;
} ListNode;



// Nodo de la cola
typedef struct QueueNode {
    User user;
    struct QueueNode* next;
} QueueNode;

// Cola de solicitudes de amistad
typedef struct {
    QueueNode* front;
    QueueNode* rear;
} FriendRequestQueue;