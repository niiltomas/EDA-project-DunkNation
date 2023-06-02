#define MAX_PREFERENCES 2

typedef struct FriendRequest {
    char sender[50];
    struct FriendRequest* next;
} FriendRequest;

//Estructura del usuario
typedef struct {
    char username[50];
    int age;
    char email[50];
    char city[50];
    char preferences[MAX_PREFERENCES][50];
    int password;
    struct FriendRequestNode *friendRequests;
}User;

typedef struct ListNode {
    User* user;
    struct ListNode* next;
} ListNode;
