#define MAX_PREFERENCES 2

//Estructura del usuario
typedef struct {
    char username[50];
    int age;
    char email;
    char city[50];
    char preferences[MAX_PREFERENCES][50];
}User;



typedef struct ListNode {
    User* user;
    struct ListNode* next;
} ListNode;
