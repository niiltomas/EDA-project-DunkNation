#include <stdio.h>
#include <stdlib.h>
#include "estructuras.c"

void menu() {
    int opcion;

    do {
        printf("\n----- MENU -----\n");
        printf("1. Insertar un nuevo usuario\n");
        printf("2. Listar todos los usuarios existentes\n");
        printf("3. Operar como un usuario especIfico\n");
        printf("4. Enviar solicitudes de amistad\n");
        printf("5. Gestionar las solicitudes pendientes\n");
        printf("6. Realizar una publicacion\n");
        printf("7. Listar las publicaciones del usuario seleccionado\n");
        printf("8. Volver al menu principal\n");
        printf("9. Salir (Terminar ejecucion)\n");

        printf("\n Elija una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                // Código --> insertar un nuevo usuario
                break;
            case 2:
                // Código --> listar todos los usuarios existentes
                break;
            case 3:
                // Código --> operar como un usuario específico
                break;
            case 4:
                // Código --> enviar solicitudes de amistad
                break;
            case 5:
                // Código --> gestionar las solicitudes pendientes
                break;
            case 6:
                // Código --> realizar una publicación
                break;
            case 7:
                // Código --> listar las publicaciones del usuario seleccionado
                break;
            case 8:
                // Volver --> menú principal
                break;
            case 9:
                printf("Saliendo del programa...\n");
                exit(0);
            default:
                printf("Opción inválida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 9);
}


