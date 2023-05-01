//escribe aqui la estructura 
#define MAX_PREFERENCES

typedef struct {
    char username[50];
    int age;
    char email;
    char city[50];
    char preferences[MAX_PREFERENCES][50]
}User;
