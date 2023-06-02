#define MAX_PREFERENCES 2

//Estructura del usuario
typedef struct {
    char username[50];
    int age;
    char email[50];
    char city[50];
    char preferences[MAX_PREFERENCES][50];
    int password;
    void *friendRequests;
}User;

typedef struct ListNode {
    User* user;
    struct ListNode* next;
} ListNode;

typedef struct FriendRequest {
    User* sender;
    User* receiver;
    struct FriendRequest* next;
} FriendRequest;