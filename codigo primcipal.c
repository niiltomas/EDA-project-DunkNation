#include <stdio.h>
#include <stdlib.h>

void menu() {
    int opcion;

    do {
        printf("\n----- MENÚ -----\n");
        printf("1. Insertar un nuevo usuario\n");
        printf("2. Listar todos los usuarios existentes\n");
        printf("3. Operar como un usuario específico\n");
        printf("4. Enviar solicitudes de amistad\n");
        printf("5. Gestionar las solicitudes pendientes\n");
        printf("6. Realizar una publicación\n");
        printf("7. Listar las publicaciones del usuario seleccionado\n");
        printf("8. Volver al menú principal\n");
        printf("9. Salir (Terminar ejecución)\n");

        printf("\n Elija una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                // Código para insertar un nuevo usuario
                break;
            case 2:
                // Código para listar todos los usuarios existentes
                break;
            case 3:
                // Código para operar como un usuario específico
                break;
            case 4:
                // Código para enviar solicitudes de amistad
                break;
            case 5:
                // Código para gestionar las solicitudes pendientes
                break;
            case 6:
                // Código para realizar una publicación
                break;
            case 7:
                // Código para listar las publicaciones del usuario seleccionado
                break;
            case 8:
                // Volver al menú principal
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
