#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AGENDA 200

struct contacto {
    char nombre[60];
    char apellido[60];
    char numero[13];
    int tipoNumero;
    char correo[100];
    char referencia[100];
};

typedef struct contacto Contacto;

Contacto agenda[AGENDA];
int totalContactos = 0;

void leerArchivo() {
    FILE *file = fopen("agenda.txt", "r");
    if (file == NULL) return;

    while (fscanf(file, "%s %s %s %d %s %[^\n]",
                  agenda[totalContactos].nombre,
                  agenda[totalContactos].apellido,
                  agenda[totalContactos].numero,
                  &agenda[totalContactos].tipoNumero,
                  agenda[totalContactos].correo,
                  agenda[totalContactos].referencia) == 6) {
        totalContactos++;
        if (totalContactos >= AGENDA) break;
    }

    fclose(file);
}

void guardarArchivo() {
    FILE *file = fopen("agenda.txt", "a");
    for (int i = 0; i < totalContactos; i++) {
        fprintf(file, "%s %s %s %d %s %s\n",
                agenda[i].nombre,
                agenda[i].apellido,
                agenda[i].numero,
                agenda[i].tipoNumero,
                agenda[i].correo,
                agenda[i].referencia);
    }
    fclose(file);
}

void agregarContacto() {
    if (totalContactos >= AGENDA) {
        printf("Agenda llena.\n");
        return;
    }

    Contacto nuevo;

    printf("Nombre: "); scanf("%s", nuevo.nombre);
    printf("Apellido: "); scanf("%s", nuevo.apellido);
    printf("Número: "); scanf("%s", nuevo.numero);
    printf("Tipo de número (1=Celular, 2=Casa, etc): "); scanf("%d", &nuevo.tipoNumero);
    printf("Correo: "); scanf("%s", nuevo.correo);
    printf("Referencia: "); getchar(); fgets(nuevo.referencia, 100, stdin);

    agenda[totalContactos++] = nuevo;
    printf("Contacto agregado.\n");
}

void buscarContacto() {
    int opcion;
    char entrada[100];

    printf("Buscar por: 1.Nombre 2.Telefono 3.Correo: ");
    scanf("%d", &opcion);
    printf("Ingrese valor a buscar: ");
    scanf("%s", entrada);

    int encontrado = 0;

    for (int i = 0; i < totalContactos; i++) {
        if ((opcion == 1 && strcmp(agenda[i].nombre, entrada) == 0) ||
            (opcion == 2 && strcmp(agenda[i].numero, entrada) == 0) ||
            (opcion == 3 && strcmp(agenda[i].correo, entrada) == 0)) {

            printf("\nContacto encontrado:\n");
            printf("Nombre: %s %s\n", agenda[i].nombre, agenda[i].apellido);
            printf("Teléfono: %s\n", agenda[i].numero);
            printf("Correo: %s\n", agenda[i].correo);
            printf("Referencia: %s\n", agenda[i].referencia);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Contacto no encontrado.\n");
    }
}
void borrarContacto() {
    int opcion;
    char entrada[100];

    printf("Eliminar por: 1.Nombre 2.Telefono 3.Correo: ");
    scanf("%d", &opcion);
    printf("Ingrese valor a eliminar: ");
    scanf("%s", entrada);

    int encontrado = 0;

    for (int i = 0; i < totalContactos; i++) {
        if ((opcion == 1 && strcmp(agenda[i].nombre, entrada) == 0) ||
            (opcion == 2 && strcmp(agenda[i].numero, entrada) == 0) ||
            (opcion == 3 && strcmp(agenda[i].correo, entrada) == 0)) {

            for (int j = i; j < totalContactos - 1; j++) {
                agenda[j] = agenda[j + 1];
            }

            totalContactos--;
            encontrado = 1;
            printf("Contacto eliminado.\n");
            break;
        }
    }
}
int main() {
    int opcion;
    leerArchivo(); // Cargar contactos desde archivo

    for (;;) { // Bucle infinito (como while true)
        printf("\nAgenda:\n");
        printf("1. Agregar contacto\n");
        printf("2. Buscar contacto\n");
        printf("3. Borrar contacto\n");
        printf("4. Salir y guardar\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);

        if (opcion == 1) {
            agregarContacto();
        } else if (opcion == 2) {
            buscarContacto();
        }else if (opcion == 3) {
            borrarContacto();
        } else if (opcion == 4) {
            guardarArchivo();
            printf("Guardado. Saliendo...\n");
            break;
        } else {
            printf("Opcion invalida.\n");
        }
    }

    return 0;
}
