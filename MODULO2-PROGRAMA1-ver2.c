#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Estructura de sesion: equipo, hora de inicio y siguiente nodo */
typedef struct Sesion {
    int  num_equipo;
    char hora_inicio[20];
    struct Sesion *siguiente;
} Sesion;

/* Cabeza de la lista enlazada */
Sesion *cabeza = NULL;

/* Obtiene la hora actual en formato HH:MM:SS */
void obtener_hora_actual(char *buffer, int tam) {
    time_t ahora = time(NULL);
    struct tm *t  = localtime(&ahora);
    strftime(buffer, tam, "%H:%M:%S", t);
}

/* Registra una nueva sesion de equipo */
void alta_sesion(void) {
    int equipo;
    printf("\n  Numero de equipo (1-12): ");
    if (scanf("%d", &equipo) != 1) {
        /* Limpiar buffer si hay entrada invalida */
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("  [ERROR] Entrada invalida.\n");
        return;
    }

    /* Validar rango 1-12 */
    if (equipo < 1 || equipo > 12) {
        printf("  [ERROR] Numero de equipo fuera de rango. Solo se permiten valores del 1 al 12.\n");
        return;
    }

    /* Verificar sesion duplicada */
    Sesion *aux = cabeza;
    while (aux != NULL) {
        if (aux->num_equipo == equipo) {
            printf("  [AVISO] El equipo %d ya tiene una sesion activa.\n", equipo);
            return;
        }
        aux = aux->siguiente;
    }

    /* Crear nuevo nodo */
    Sesion *nuevo = (Sesion *)malloc(sizeof(Sesion));
    if (nuevo == NULL) {
        printf("  [ERROR] No se pudo reservar memoria.\n");
        return;
    }

    /* Inicializar nodo e insertarlo al frente */
    nuevo->num_equipo = equipo;
    obtener_hora_actual(nuevo->hora_inicio, sizeof(nuevo->hora_inicio));
    nuevo->siguiente  = cabeza;
    cabeza = nuevo;

    printf("  [OK] Sesion registrada: Equipo %d  Hora: %s\n",
           nuevo->num_equipo, nuevo->hora_inicio);
}

/* Elimina una sesion de la lista */
void baja_sesion(void) {
    if (cabeza == NULL) {
        printf("\n  [INFO] No hay sesiones activas en el sistema.\n");
        return;
    }

    int equipo;
    printf("\n  Numero de equipo a dar de baja (1-12): ");
    if (scanf("%d", &equipo) != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("  [ERROR] Entrada invalida.\n");
        return;
    }

    if (equipo < 1 || equipo > 12) {
        printf("  [ERROR] Numero de equipo fuera de rango.\n");
        return;
    }

    Sesion *actual   = cabeza;
    Sesion *anterior = NULL;

    /* Buscar nodo en la lista */
    while (actual != NULL && actual->num_equipo != equipo) {
        anterior = actual;
        actual   = actual->siguiente;
    }

    /* Si no existe la sesion */
    if (actual == NULL) {
        printf("  [AVISO] No se encontro sesion activa para el equipo %d.\n", equipo);
        return;
    }

    /* Desconectar nodo y ajustar apuntadores */
    if (anterior == NULL) {
        cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    printf("  [OK] Sesion del equipo %d finalizada (inicio: %s).\n",
           actual->num_equipo, actual->hora_inicio);

    /* Liberar memoria */
    free(actual);
    actual = NULL;
}

/* Muestra todas las sesiones activas */
void mostrar_sesiones(void) {
    printf("\n  ============================================\n");
    printf("  SESIONES ACTIVAS - PAD-Bienestar\n");
    printf("  ============================================\n");

    if (cabeza == NULL) {
        printf("  (sin sesiones registradas)\n");
        printf("  ============================================\n");
        return;
    }

    Sesion *aux = cabeza;
    int contador = 1;

    while (aux != NULL) {
        printf("  %d. Equipo: %2d  |  Inicio: %s\n",
               contador, aux->num_equipo, aux->hora_inicio);
        aux = aux->siguiente;
        contador++;
    }
    printf("  ============================================\n");
    printf("  Total de sesiones activas: %d\n", contador - 1);
    printf("  ============================================\n");
}

/* Libera toda la memoria de la lista */
void liberar_lista(void) {
    Sesion *aux = cabeza;
    while (aux != NULL) {
        Sesion *tmp = aux->siguiente;
        free(aux);
        aux = tmp;
    }
    cabeza = NULL;
}

/* Muestra el menu y retorna la opcion del usuario */
int menu_principal(void) {
    int opcion;
    printf("\n");
    printf("  +------------------------------------------+\n");
    printf("  |       SISTEMA - MARVIN / MAYRA           |\n");
    printf("  +------------------------------------------+\n");
    printf("  |  1. Dar de alta una sesion               |\n");
    printf("  |  2. Dar de baja una sesion               |\n");
    printf("  |  3. Mostrar sesiones activas             |\n");
    printf("  |  4. Salir                                |\n");
    printf("  +------------------------------------------+\n");
    printf("  Opcion: ");
    if (scanf("%d", &opcion) != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return -1;
    }
    return opcion;
}

/* Ciclo principal del programa */
int main(void) {
    int opcion;

    printf("\n  Bienvenido al sistema de gestion de sesiones\n");
    printf("  Punto PAD-Bienestar | SIG-Conecta\n");

    do {
        opcion = menu_principal();
        switch (opcion) {
            case 1: alta_sesion();    break;
            case 2: baja_sesion();    break;
            case 3: mostrar_sesiones(); break;
            case 4:
                liberar_lista();
                printf("\n  Sistema cerrado. Hasta luego.\n\n");
                break;
            default:
                printf("  [ERROR] Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 4);

    return 0;
}